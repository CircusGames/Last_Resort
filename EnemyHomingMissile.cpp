#include "Application.h"
#include "EnemyHomingMissile.h"
#include "ModuleCollision.h"
#include "ModuleEnemies.h"

EnemyHomingMissile::EnemyHomingMissile(int x, int y, powerUpTypes type, SDL_Texture* thisTexture) : Enemy(x, y)
{
	//links the correct spritesheet texture ----
	enemyTex = thisTexture;
	// -----------------------------------------

	

	//animation = &animation; //links animation

	//original_y = y;
	//fposition.x = x;

	//powerUpType = type;
	//life = 1;
	//enemyScore = 100;

	collider = App->collision->AddCollider({ 0, 0, 32, 16 }, COLLIDER_TYPE::COLLIDER_ENEMY, (Module*)App->enemies);

}

void EnemyHomingMissile::Move()
{
	//fposition.x -= 1.35;
	position.x += 1; //fposition.x;
}

