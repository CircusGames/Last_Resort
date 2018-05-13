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

	collider = App->collision->AddCollider({ 0, 0, 61, 47 }, COLLIDER_TYPE::COLLIDER_ENEMY, (Module*)App->enemies);

	powerUpType = type;

	original_pos.x = x;
	original_pos.y = y;
}

void Enemy_MiniTank::Move()
{
	position = original_pos + path.GetCurrentSpeed(&animation);
}
