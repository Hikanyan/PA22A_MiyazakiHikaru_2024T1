#pragma once

class Player
{
public:
	int MAX_LIFE = 3;
	int MAX_SCORE = 0;

	int life;
	int score;
	bool isAlive;
	Font font{20};

	Player() : life(MAX_LIFE), score(0), isAlive(true)
	{
	}

	void DecreaseLife()
	{
		if (life > 0)
		{
			--life;
		}
		else
		{
			isAlive = false;
		}
	}

	void Update() const
	{
		font(U"Life: ", life).draw(10, 10);
		font(U"Score: ", score).draw(10, 30);
	}
};
