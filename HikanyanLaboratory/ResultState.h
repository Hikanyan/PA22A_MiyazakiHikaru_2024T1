#pragma once
#include "State.h"

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
