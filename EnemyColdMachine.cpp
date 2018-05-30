#include "Application.h"
#include "EnemyColdMachine.h"
#include "ModuleCollision.h"
#include "ModuleEnemies.h"

#include "ModuleRender.h"

EnemyColdMachine::EnemyColdMachine(int x, int y, powerUpTypes type, SDL_Texture* thisTexture) : Enemy(x, y)
{
	//links the correct spritesheet texture ----
	enemyTex = thisTexture;
	// -----------------------------------------
	powerUpType = type;
	life = 140;
	enemyScore = 100;
	// -----------------------------------------
	
	//animation = &blabla; //links animation

	//original_y = y;
	//fposition.x = x;

	// STATIC PIECES RECTS ---------------------
	// chest statics ---
	coldMachine.chest.fullChest.rect[NORMAL_ANIM] = { 212,361,183,168 };


	

	collider = App->collision->AddCollider({ 0, 0, 32, 16 }, COLLIDER_TYPE::COLLIDER_ENEMY, (Module*)App->enemies);

	// sets the first boss state
	coldMachine.state = bossState::LANDING;

	position.y = 20;

}

void EnemyColdMachine::Move()
{
	//fposition.x -= 1.35;
	//position.x = fposition.x;

	position.x += 1;
}

void EnemyColdMachine::Draw()
{


	App->render->Blit(enemyTex, position.x, position.y, coldMachine.chest.fullChest.rect);
}

