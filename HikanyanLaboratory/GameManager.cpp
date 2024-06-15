//#include "../stdafx.h"
#include "GameManager.h"

#include "StateMachine.h"

void GameManager::Initialize()
{
	sm = StateMachine();
}

void GameManager::Update()
{
	font(U"Test").draw(10, 10);
	sm.Update();
}

void GameManager::Finalize()
{
	sm.~StateMachine();
}
