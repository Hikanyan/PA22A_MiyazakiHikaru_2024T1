//#include "stdafx.h"
#include "StateMachine.h"

StateMachine::StateMachine()
{
}

StateMachine::~StateMachine()
{
	if (currentState)
	{
		currentState->Exit();
		delete currentState;
	}
}

void StateMachine::ChangeState(State* newState)
{
}

void StateMachine::Update()
{
	if (currentState)
	{
		currentState->Update();
	}
}
