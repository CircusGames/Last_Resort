#include "Application.h"
#include "EnemyColdMachine.h"
#include "ModuleCollision.h"
#include "ModuleEnemies.h"

EnemyColdMachine::EnemyColdMachine(int x, int y, powerUpTypes type, SDL_Texture* thisTexture) : Enemy(x, y)
{
	//links the correct spritesheet texture ----
	enemyTex = thisTexture;
	// -----------------------------------------
	powerUpType = type;
	life = 1;
	enemyScore = 100;
	// -----------------------------------------
	
	//animation = &blabla; //links animation

	//original_y = y;
	//fposition.x = x;

	

	collider = App->collision->AddCollider({ 0, 0, 32, 16 }, COLLIDER_TYPE::COLLIDER_ENEMY, (Module*)App->enemies);

}

void EnemyColdMachine::Move()
{
	//fposition.x -= 1.35;
	//position.x = fposition.x;

	position.x += 1;
}

