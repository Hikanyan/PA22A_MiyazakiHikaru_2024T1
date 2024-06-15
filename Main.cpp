#include <Siv3D.hpp>
#include "HikanyanLaboratory/GameManager.h"


void Main()
{
	GameManager::getInstance()->Initialize();
	while (System::Update())
	{
		GameManager::getInstance()->Update();
	}
	GameManager::getInstance()->Finalize();
}
