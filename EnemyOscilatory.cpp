#include "Application.h"
#include "EnemyOscilatory.h"
#include "ModuleCollision.h"
#include "ModuleEnemies.h"

Oscilatory::Oscilatory(int x, int y, powerUpTypes type, SDL_Texture* sprite) : Enemy(x, y)
{
	fly.PushBack({ 0,0,48,46 });
	fly.speed = 0.2f;

	animation = &fly;
	texture = sprite;

	powerUpType = type;
	collider = App->collision->AddCollider({ 0, 0, 48, 46 }, COLLIDER_TYPE::COLLIDER_ENEMY, (Module*)App->enemies);

	original_y = y;
}

void Oscilatory::Move()
{
	if (going_up)
	{
		if (wave > 1.0f)
			going_up = false;
		else
			wave += 0.05f;
	}
	else
	{
		if (wave < -1.0f)
			going_up = true;
		else
			wave -= 0.05f;
	}

	position.y = int(float(original_y) + (25.0f * sinf(wave)));
	position.x -= 1;
}