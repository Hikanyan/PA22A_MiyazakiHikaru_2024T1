#pragma once
#include "Singleton.h"
#include "StateMachine.h"

class GameManager : public Singleton<GameManager>
{
public:
	StateMachine sm;
	Font font{ 20 };

	void Initialize();
	void Update();
	void Finalize();
};
