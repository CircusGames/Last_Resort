#include "Application.h"
#include "EnemyPowerUpBee.h"
#include "ModuleCollision.h"
#include "ModuleEnemies.h"
#include "ModulePlayer.h"
#include "ModuleParticles.h"

#include "SDL\include\SDL_timer.h"

EnemyPowerUpBee::EnemyPowerUpBee(int x, int y, powerUpTypes type, SDL_Texture* thisTexture) : Enemy(x, y)
{
	enemyTex = thisTexture;

	//wave animation
	waveAnim.PushBack({ 222, 5, 32, 26 });
	waveAnim.PushBack({ 264, 5, 32, 26 });
	waveAnim.PushBack({ 308, 5, 32, 26 });
	waveAnim.PushBack({ 352, 5, 32, 26 });
	waveAnim.repeat = true;

	//land and jump animation
	landAnim.PushBack({ 182, 2, 28, 29 });
	landAnim.PushBack({ 146, 8, 24, 23 });
	landAnim.PushBack({ 110, 4, 24, 27 });
	landAnim.repeat = false;

	//walk animation
	moveAnim.PushBack({ 73, 1, 25, 40 });
	moveAnim.PushBack({ 37, 0, 24, 31 });
	moveAnim.PushBack({ 0, 0, 25, 31 });
	moveAnim.repeat = true;

	//inial animation
	animation = &waveAnim;

	//specs
	powerUpType = type;
	life = 1;
	enemyScore = 100;
	original_y = y;

	//collider
	collider = App->collision->AddCollider({ 0,0,32,26 }, COLLIDER_TYPE::COLLIDER_ENEMY, (Module*)App->enemies);
}

void EnemyPowerUpBee::Move()
{
	collider->SetPos(position.x, position.y + 7);

	if (going_up)
	{
		if (wave > 1.0f)
			going_up = false;
		else
			wave += 0.08f;
	}
	else
	{
		if (wave < -1.0f)
			going_up = true;
		else
			wave -= 0.08f;
	}

	position.y = original_y + int(20.0f * sinf(wave));
	position.x -= 1;
}