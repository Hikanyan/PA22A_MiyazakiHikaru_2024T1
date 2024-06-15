#pragma once
#include "Ball.h"

class Paddle
{
public:
	Size size{60, 10};

	Rect model;

	Paddle()
	{
		Update();
	}

	void Update()
	{
		model = Rect{Arg::center(Cursor::Pos().x, 500), size};
	}

	void Intersects(Ball& ball)
	{
		if ((ball.velocity.y > 0) && model.intersects(ball.model))
		{
			ball.velocity = Vec2{
				(ball.model.x - model.center().x) * 10,
				-ball.velocity.y
			}.setLength(ball.BALL_SPEED);
		}
	}

	void Draw() const
	{
		model.rounded(3).draw(HSV{55});
	}
};
