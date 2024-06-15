#pragma once

class Player;

class Ball
{
public:
	double BALL_SPEED = 480.0;

	Vec2 velocity;
	Circle model;

	Ball() : velocity(0, -BALL_SPEED), model{400, 400, 10}
	{
	}

	void Update(Player& player);

	void Draw() const
	{
		model.draw();
	}
};
