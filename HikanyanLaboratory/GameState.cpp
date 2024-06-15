#include "GameState.h"

#include "ResultState.h"
#include "TitleState.h"

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
