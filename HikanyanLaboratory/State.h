#pragma once

class StateMachine;

class State
{
protected:
	StateMachine* stateMachine;

public:
	virtual ~State() = default;

	State(StateMachine* machine) : stateMachine(machine)
	{
	}

	virtual void Enter() = 0;
	virtual void Update() = 0;
	virtual void Exit() = 0;
};
