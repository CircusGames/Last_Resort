#include "Application.h"
#include "EnemyMiniTank.h"
#include "ModuleCollision.h"
#include "Globals.h"
#include "ModuleEnemies.h"

Enemy_MiniTank::Enemy_MiniTank(int x, int y, powerUpTypes type, SDL_Texture* thisTexture) : Enemy(x, y)
{
	enemyTex = thisTexture;

	move.PushBack({ 0,0,61,47 });
	animation = &move;
	shootanimation = &move2;

	//Path
	path.PushBack({ -0.1f, 0.0f }, 140, &move);
	path.PushBack({ 1.1f, 0.0f }, 130, &move);
	path.PushBack({ 0.5f, 0.0f }, 30, &move2);
	path.PushBack({ 1.1f, 0.0f }, 10, &move);
	path.PushBack({ -0.1f, 0.0f }, 10, &move);
	path.PushBack({ 1.1f, 0.0f }, 10, &move);
	path.PushBack({ -0.1f, 0.0f }, 140, &move);
	path.PushBack({ 1.1f, 0.0f }, 10, &move);
	path.PushBack({ -0.1f, 0.0f }, 10, &move);
	path.PushBack({ 1.1f, 0.0f }, 70, &move);
	path.PushBack({ 0.5f, 0.0f }, 30, &move2);
	path.PushBack({ 1.1f, 0.0f }, 65, &move);
	path.PushBack({ -0.1f, 0.0f }, 10, &move);
	path.PushBack({ 1.1f, 0.0f }, 10, &move);
	path.PushBack({ -0.1f, 0.0f }, 100, &move);
	path.PushBack({ 0.5f, 0.0f }, 30, &move2);

	collider = App->collision->AddCollider({ 0, 0, 61, 47 }, COLLIDER_TYPE::COLLIDER_ENEMY, (Module*)App->enemies);

	powerUpType = type;

	original_pos.x = x;
	original_pos.y = y;

	life = 1;
}

void Enemy_MiniTank::Move()
{
	position = original_pos + path.GetCurrentSpeed(&animation);
}
