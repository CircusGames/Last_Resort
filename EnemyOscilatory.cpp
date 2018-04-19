#include "Application.h"
#include "EnemyOscilatory.h"
#include "ModuleCollision.h"
#include "ModuleEnemies.h"

EnemyOscilatory::EnemyOscilatory(int x, int y, powerUpTypes type, SDL_Texture* sprite) : Enemy(x, y)
{
	waveAnim.PushBack({ 0,0,48,46 });
	waveAnim.speed = 0.2f;

	animation = &waveAnim;
	texture = sprite;

	powerUpType = type;

	collider = App->collision->AddCollider({ 0, 0, 48, 46 }, COLLIDER_TYPE::COLLIDER_ENEMY, (Module*)App->enemies);

	original_y = y;

	life = 2;
}

void EnemyOscilatory::Move()
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