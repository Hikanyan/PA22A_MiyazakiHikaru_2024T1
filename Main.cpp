#include <Siv3D.hpp>

class StateMachine;
class GameState;

namespace constants
{
	namespace ball
	{
		constexpr double BALL_SPEED = 480.0;
	}

	namespace bricks
	{
		constexpr Size BRICK_SIZE{40, 20};
		constexpr int Y_COUNT = 2;
		constexpr int X_COUNT = 5;
		constexpr int MAX = Y_COUNT * X_COUNT;
	}

	namespace paddle
	{
		constexpr Size SIZE{60, 10};
	}

	namespace player
	{
		constexpr int MAX_LIFE = 3;
		constexpr int MAX_SCORE = 0;
	}
}


// class State
// {
// protected:
// 	StateMachine* stateMachine;
//
// public:
// 	State(StateMachine* machine) : stateMachine(machine)
// 	{
// 	}
//
// 	virtual void Enter() = 0;
// 	virtual void Update() = 0;
// 	virtual void Exit() = 0;
// };

// class StateMachine
// {
// private:
// 	State* currentState;
//
// public:
// 	StateMachine();
//
// 	~StateMachine()
// 	{
// 		if (currentState)
// 		{
// 			currentState->Exit();
// 			delete currentState;
// 		}
// 	}
//
// 	void ChangeState(State* newState)
// 	{
// 		if (currentState)
// 		{
// 			currentState->Exit();
// 			delete currentState;
// 		}
// 		currentState = newState;
// 		if (currentState)
// 		{
// 			currentState->Enter();
// 		}
// 	}
//
// 	void Update()
// 	{
// 		if (currentState)
// 		{
// 			currentState->Update();
// 		}
// 	}
// };

class Player
{
public:
	int life;
	int score;
	bool isAlive;
	Font font{20};

	Player() : life(constants::player::MAX_LIFE), score(0), isAlive(true)
	{
	}

	void DecreaseLife()
	{
		if (life > 0)
		{
			--life;
		}
		else
		{
			isAlive = false;
		}
	}

	void Update() const
	{
		font(U"Life: ", life).draw(10, 10);
		font(U"Score: ", score).draw(10, 30);
	}
};

class Ball
{
public:
	Vec2 velocity;
	Circle model;

	Ball() : velocity(0, -constants::ball::BALL_SPEED), model{400, 400, 10}
	{
	}

	void Update(Player& player);

	void Draw() const
	{
		model.draw();
	}
};

class Bricks
{
public:
	Rect bricksModel[constants::bricks::MAX];

	Player* player;

	Bricks() : player(nullptr)
	{
		using namespace constants::bricks;
		for (int y = 0; y < Y_COUNT; ++y)
		{
			for (int x = 0; x < X_COUNT; ++x)
			{
				int index = y * X_COUNT + x;
				bricksModel[index] = Rect{
					x * BRICK_SIZE.x,
					60 + y * BRICK_SIZE.y,
					BRICK_SIZE
				};
			}
		}
	}

	void Draw()
	{
		for (int i = 0; i < constants::bricks::MAX; ++i)
		{
			bricksModel[i].stretched(-1).draw(HSV(bricksModel[i].y - 40));
		}
	}

	// ブロックとボールの衝突判定
	void Intersects(Ball& ball)
	{
		for (int i = 0; i < constants::bricks::MAX; ++i)
		{
			Rect& refBrick = bricksModel[i];
			if (refBrick.intersects(ball.model)) // ブロックとボールが衝突したら
			{
				if (refBrick.bottom().intersects(ball.model) || refBrick.top().intersects(ball.model))
				{
					ball.velocity.y *= -1;
				}
				else
				{
					ball.velocity.x *= -1;
				}
				//Scoreを加算
				if (player)
				{
					player->score += 10;
				}
				refBrick.y -= 600;
				break;
			}
		}
	}

	bool AllBricksDestroyed() const
	{
		for (int i = 0; i < constants::bricks::MAX; ++i)
		{
			if (bricksModel[i].y >= 0)
			{
				return false;
			}
		}
		return true;
	}
};

class Paddle
{
public:
	Rect model;

	Paddle()
	{
		Update();
	}

	void Update()
	{
		model = Rect{Arg::center(Cursor::Pos().x, 500), constants::paddle::SIZE};
	}

	void Intersects(Ball& ball)
	{
		if ((ball.velocity.y > 0) && model.intersects(ball.model))
		{
			ball.velocity = Vec2{
				(ball.model.x - model.center().x) * 10,
				-ball.velocity.y
			}.setLength(constants::ball::BALL_SPEED);
		}
	}

	void Draw() const
	{
		model.rounded(3).draw(HSV{ 55 });
	}
};

class TitleState : public State
{
public:
	TitleState(StateMachine* machine) : State(machine)
	{
	}

	Font font{50};

	void Enter() override;
	void Update() override;
	void Exit() override;
};

class GameState : public State
{
public:
	Player player;
	Ball ball;
	Bricks bricks;
	Paddle paddle;
	bool isGameClear;

	GameState(StateMachine* machine) : State(machine), isGameClear(false)
	{
		bricks.player = &player;
	}

	void GameClearCheck();

	void Enter() override
	{
	}

	void Update() override;

	void Exit() override
	{
	}
};

class ResultState : public State
{
public:
	int finalScore;
	int remainingLives;
	bool isGameClear;
	Font font = Font(40);

	ResultState(StateMachine* machine, int score, int lives, bool clear) :
		State(machine), finalScore(score), remainingLives(lives), isGameClear(clear)
	{
	}

	void Enter() override
	{
	}

	void Update() override;

	void Exit() override;
};

StateMachine::StateMachine() : currentState(new TitleState(this))
{
	currentState->Enter();
}

void Ball::Update(Player& player)
{
	model.moveBy(velocity * Scene::DeltaTime());
	if (model.x < 0 || model.x > 800)
	{
		velocity.x *= -1;
	}
	if (model.y < 0)
	{
		velocity.y *= -1;
	}
	if (model.y > 600)
	{
		model.setPos(400, 400);
		velocity = Vec2(0, -constants::ball::BALL_SPEED);
		player.DecreaseLife();
	}
}

void TitleState::Enter()
{
}

void TitleState::Update()
{
	if (KeyEnter.down())
	{
		stateMachine->ChangeState(new GameState(stateMachine));
		return;
	}
	font(U"Press Enter to start").drawAt(Scene::Center(), Palette::Blue);
}

void TitleState::Exit()
{
}

void GameState::GameClearCheck()
{
	if (bricks.AllBricksDestroyed())
	{
		isGameClear = true;
		stateMachine->ChangeState(new ResultState(stateMachine, player.score, player.life, isGameClear));
	}
}

void GameState::Update()
{
	if (KeyEnter.down())
	{
		stateMachine->ChangeState(new TitleState(stateMachine));
		return;
	}
	if (player.isAlive == false)
	{
		stateMachine->ChangeState(new ResultState(stateMachine, player.score, player.life, isGameClear));
		return;
	}

	player.Update();
	ball.Update(player);
	paddle.Update();
	bricks.Intersects(ball);
	paddle.Intersects(ball);
	ball.Draw();
	bricks.Draw();
	paddle.Draw();
	GameClearCheck();
}

void ResultState::Update()
{
	if (KeyEnter.down())
	{
		stateMachine->ChangeState(new TitleState(stateMachine));
		return;
	}
	// Draw result
	if (!isGameClear)
	{
		font(U"Game Over").drawAt(Scene::Center(), Palette::Red);
	}
	else
	{
		font(U"Clear!").drawAt(Scene::Center(), Palette::Green);
		font(U"Remaining Lives: ", remainingLives).drawAt(Scene::Center().movedBy(0, 120), Palette::White);
	}
	font(U"Final Score: ", finalScore).drawAt(Scene::Center().movedBy(0, 60), Palette::White);
	font(U"Press Enter to restart").drawAt(Scene::Center().movedBy(0, 180));
}

void ResultState::Exit()
{
}

void Main()
{
	StateMachine sm;
	while (System::Update())
	{
		sm.Update();
	}
}
