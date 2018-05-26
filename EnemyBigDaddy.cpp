#include "Application.h"
#include "EnemyBigDaddy.h"
#include "ModuleCollision.h"
#include "ModuleEnemies.h"

EnemyBigDaddy::EnemyBigDaddy(int x, int y, powerUpTypes type, SDL_Texture* thisTexture) : Enemy(x, y)
{
	//links the correct spritesheet texture ----
	enemyTex = thisTexture;
	// -----------------------------------------
	powerUpType = type;
	life = 1;
	enemyScore = 100;

	collider = App->collision->AddCollider({ 0, 0, 32, 16 }, COLLIDER_TYPE::COLLIDER_ENEMY, (Module*)App->enemies);

}

void EnemyBigDaddy::Move()
{
	//fposition.x -= 1.35;
	//position.x = fposition.x;
}