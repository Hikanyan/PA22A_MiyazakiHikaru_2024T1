#pragma once
#include "Singleton.h"

class GameManager : public Singleton<GameManager>
{
public:
	void Initialize();
	void Update();
	void Finalize();
};
