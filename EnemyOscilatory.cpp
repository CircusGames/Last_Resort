#include "Application.h"
#include "EnemyOscilatory.h"
#include "ModuleCollision.h"
#include "ModuleEnemies.h"

EnemyOscilatory::EnemyOscilatory(int x, int y, powerUpTypes type, SDL_Texture* sprite) : Enemy(x, y)
{
	waveAnim.PushBack({ 0,0,48,45 });
	waveAnim.PushBack({ 49,0,48,46 });
	waveAnim.PushBack({ 96,0,47,46 });
	waveAnim.PushBack({ 144,0,48,46 });
	waveAnim.PushBack({ 192,0,48,46 });
	waveAnim.PushBack({ 0,47,48,46 });
	waveAnim.PushBack({ 48,47,48,46 });
	waveAnim.PushBack({ 96,47,48,46 });
	waveAnim.PushBack({ 144,47,48,46 });
	waveAnim.PushBack({ 192,47,48,46 });
	waveAnim.PushBack({ 0,95,48,46 });
	waveAnim.PushBack({ 48,95,48,46 });
	waveAnim.PushBack({ 96,95,50,47 });
	waveAnim.PushBack({ 146,95,48,49 });
	waveAnim.PushBack({ 96,95,50,47 });
	waveAnim.PushBack({ 48,95,48,46 });
	waveAnim.PushBack({ 0,95,48,46 });
	waveAnim.PushBack({ 192,47,48,46 });
	waveAnim.PushBack({ 144,47,48,46 });
	waveAnim.PushBack({ 96,47,48,46 });
	waveAnim.PushBack({ 48,47,48,46 });
	waveAnim.PushBack({ 0,47,48,46 });
	waveAnim.PushBack({ 192,0,48,46 });
	waveAnim.PushBack({ 144,0,48,46 });
	waveAnim.PushBack({ 96,0,47,46 });
	waveAnim.PushBack({ 49,0,48,46 });
	waveAnim.speed = 0.05f;

	animation = &waveAnim;
	texture = sprite;

	powerUpType = type;

	collider = App->collision->AddCollider({ 0, 0, 50, 47 }, COLLIDER_TYPE::COLLIDER_ENEMY, (Module*)App->enemies);

	original_y = y;

	life = 2;
}

void EnemyOscilatory::Move()
{
	if (going_up)
	{
		if (wave > 1.25f)
			going_up = false;
		else
			wave += 0.05f;
	}
	else
	{
		if (wave < -1.25f)
			going_up = true;
		else
			wave -= 0.05f;
	}

	position.y = int(float(original_y) + (80.0f * sinf(wave)));
	position.x -= 1;
}