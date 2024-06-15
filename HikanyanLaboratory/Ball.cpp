#include "Ball.h"
#include "Player.h"

void Ball::Update(Player& player)
{
	model.moveBy(velocity * Scene::DeltaTime());
	if (model.x < 0 || model.x > 800)
	{
		velocity.x *= -1;
	}
	if (model.y < 0)
	{
		velocity.y *= -1;
	}
	if (model.y > 600)
	{
		model.setPos(400, 400);
		velocity = Vec2(0, -BALL_SPEED);
		player.DecreaseLife();
	}
}
