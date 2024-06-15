#include "GameManager.h"
#include "StateMachine.h"

void GameManager::Initialize()
{
	sm.Initialize();
}

void GameManager::Update()
{
	sm.Update();
}

void GameManager::Finalize()
{
	sm.~StateMachine();
}
