#pragma once
#include "State.h"

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
