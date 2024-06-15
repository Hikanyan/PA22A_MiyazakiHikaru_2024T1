#pragma once
#include "Singleton.h"
#include "StateMachine.h"

class GameManager : public Singleton<GameManager>
{
public:
	StateMachine sm;
	void Initialize();
	void Update();
	void Finalize();
};
