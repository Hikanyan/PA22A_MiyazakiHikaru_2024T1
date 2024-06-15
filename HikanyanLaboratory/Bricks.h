#pragma once
#include "Ball.h"
#include "Player.h"

class Bricks
{
public:
	Size BRICK_SIZE{40, 20};
	int Y_COUNT = 2;
	int X_COUNT = 5;
	int MAX = Y_COUNT * X_COUNT;

	Rect bricksModel[MAX];

	Player* player;

	Bricks() : player(nullptr)
	{
		for (int y = 0; y < Y_COUNT; ++y)
		{
			for (int x = 0; x < X_COUNT; ++x)
			{
				int index = y * X_COUNT + x;
				bricksModel[index] = Rect{
					x * BRICK_SIZE.x,
					60 + y * BRICK_SIZE.y,
					BRICK_SIZE
				};
			}
		}
	}

	void Draw()
	{
		for (int i = 0; i < MAX; ++i)
		{
			bricksModel[i].stretched(-1).draw(HSV(bricksModel[i].y - 40));
		}
	}

	// ブロックとボールの衝突判定
	void Intersects(Ball& ball)
	{
		for (int i = 0; i < MAX; ++i)
		{
			Rect& refBrick = bricksModel[i];
			if (refBrick.intersects(ball.model)) // ブロックとボールが衝突したら
			{
				if (refBrick.bottom().intersects(ball.model) || refBrick.top().intersects(ball.model))
				{
					ball.velocity.y *= -1;
				}
				else
				{
					ball.velocity.x *= -1;
				}
				//Scoreを加算
				if (player)
				{
					player->score += 10;
				}
				refBrick.y -= 600;
				break;
			}
		}
	}

	bool AllBricksDestroyed() const
	{
		for (int i = 0; i < MAX; ++i)
		{
			if (bricksModel[i].y >= 0)
			{
				return false;
			}
		}
		return true;
	}
};
