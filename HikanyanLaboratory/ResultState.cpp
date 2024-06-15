#include "ResultState.h"

#include "TitleState.h"

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
