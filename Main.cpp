#include <Siv3D.hpp>

class StateMachine;
//class TitleState;
class GameState;

namespace constants {
	namespace ball {
		constexpr double BALL_SPEED = 480.0;
	}

	namespace bricks {
		constexpr Size BRICK_SIZE{ 40, 20 };
		constexpr int Y_COUNT = 5;
		constexpr int X_COUNT = 20;
		constexpr int MAX = Y_COUNT * X_COUNT;
	}

	namespace paddle {
		constexpr Size SIZE{ 60, 10 };
	}
}



class State {
protected:
	StateMachine* stateMachine;

public:
	State(StateMachine* machine) : stateMachine(machine) {}
	virtual void Enter() = 0;
	virtual void Update() = 0;
	virtual void Exit() = 0;
};

class StateMachine {
private:
	State* currentState;

public:
	StateMachine();

	~StateMachine() {
		if (currentState) {
			currentState->Exit();
			delete currentState;
		}
	}

	void ChangeState(State* newState) {
		if (currentState) {
			currentState->Exit();
			delete currentState;
		}
		currentState = newState;
		if (currentState) {
			currentState->Enter();
		}
	}

	void Update() {
		if (currentState) {
			currentState->Update();
		}
	}
};

class Ball {
public:
	Vec2 velocity;
	Circle model;

	Ball() : velocity(0, -constants::ball::BALL_SPEED), model{ 400, 400, 10 } {}

	void Update() {
		model.moveBy(velocity * Scene::DeltaTime());
	}

	void Draw() const {
		model.draw();
	}
};

class Bricks {
public:
	Rect bricksModel[constants::bricks::MAX];

	Bricks() {
		using namespace constants::bricks;
		for (int y = 0; y < Y_COUNT; ++y) {
			for (int x = 0; x < X_COUNT; ++x) {
				int index = y * X_COUNT + x;
				bricksModel[index] = Rect{
					x * BRICK_SIZE.x,
					60 + y * BRICK_SIZE.y,
					BRICK_SIZE
				};
			}
		}
	}

	void Draw() {
		for (int i = 0; i < constants::bricks::MAX; ++i) {
			bricksModel[i].stretched(-1).draw(HSV(bricksModel[i].y - 40));
		}
	}

	void Intersects(Ball& ball) {
		for (int i = 0; i < constants::bricks::MAX; ++i) {
			Rect& refBrick = bricksModel[i];
			if (refBrick.intersects(ball.model)) {
				if (refBrick.bottom().intersects(ball.model) || refBrick.top().intersects(ball.model)) {
					ball.velocity.y *= -1;
				}
				else {
					ball.velocity.x *= -1;
				}
				refBrick.y -= 600;  // Move the brick out of the scene
				break;  // Prevent multiple collisions in the same frame
			}
		}
	}
};

class Paddle {
public:
	Rect model;

	Paddle() : model(Arg::center(Cursor::Pos().x, 500), constants::paddle::SIZE) {}

	void Update() {
		model.x = Cursor::Pos().x - (constants::paddle::SIZE.x / 2);
	}

	void Intersects(Ball& ball) {
		if ((ball.velocity.y > 0) && model.intersects(ball.model)) {
			ball.velocity = Vec2{
				(ball.model.x - model.center().x) * 10,
				-ball.velocity.y
			}.setLength(constants::ball::BALL_SPEED);
		}
	}

	void Draw() const {
		model.rounded(3).draw();
	}
};

class TitleState : public State {
public:
	TitleState(StateMachine* machine) : State(machine) {}
	void Enter() override { Print << U"TitleState Enter"; }
	void Update();
	void Exit() override { Print << U"TitleState Exit"; }
};

class GameState : public State {
public:
	Ball ball;
	Bricks bricks;
	Paddle paddle;

	GameState(StateMachine* machine) : State(machine) {}

	void Enter() override {}
	void Update();
	void Exit() override {}
};

StateMachine::StateMachine() : currentState(nullptr) {
	currentState = new TitleState(this);
	currentState->Enter();
}

void TitleState::Update() {
	if (KeyEnter.down()) {
		stateMachine->ChangeState(new GameState(stateMachine));
	}
}

void GameState::Update() {
	if (KeyEnter.down()) {
		stateMachine->ChangeState(new TitleState(stateMachine));
	}

	ball.Update();
	paddle.Update();
	bricks.Intersects(ball);
	paddle.Intersects(ball);
	ball.Draw();
	bricks.Draw();
	paddle.Draw();
}

void Main()
{
	StateMachine sm;
	while (System::Update()) {
		sm.Update();
	}
}
