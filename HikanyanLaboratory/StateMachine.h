#pragma once
#include "State.h"

class StateMachine
{
private:
	State* currentState;

public:
	StateMachine();

	~StateMachine();

	void ChangeState(State* newState);

	void Update();
	void Initialize();
};
