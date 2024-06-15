//#include "stdafx.h"
#include "StateMachine.h"

#include "TitleState.h"


StateMachine::StateMachine() : currentState(new TitleState(this))
{
	currentState->Enter();
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
	if (currentState)
	{
		currentState->Exit();
		delete currentState;
	}
	currentState = newState;
	currentState->Enter();
}


void StateMachine::Update()
{
	if (currentState)
	{
		currentState->Update();
	}
}

void StateMachine::Initialize()
{
}
