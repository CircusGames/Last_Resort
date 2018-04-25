#include "Application.h"
#include "BasicEnemy.h"
#include "ModuleCollision.h"
#include "ModuleEnemies.h"

BasicEnemy::BasicEnemy(int x, int y, powerUpTypes type, SDL_Texture* thisTexture) : Enemy(x, y)
{
	//links the correct spritesheet texture ----
	enemyTex = thisTexture;
	// -----------------------------------------

	fly.PushBack({ 0,16,32,15 });
	fly.PushBack({ 0,0,32,16 });
	fly.PushBack({ 0,31,32,16 });
	fly.PushBack({ 0,47,32,15 });
	fly.PushBack({ 0,31,32,16 });
	fly.PushBack({ 0,0,32,16 });
	fly.speed = 0.2f;

	animation = &fly; //links animation

	original_y = y;
	fposition.x = x;

	powerUpType = type;
	life = 1;
	enemyScore = 100;

	collider = App->collision->AddCollider({ 0, 0, 32, 16 }, COLLIDER_TYPE::COLLIDER_ENEMY, (Module*)App->enemies);

}

void BasicEnemy::Move()
{
	fposition.x -= 1.35;
	position.x = fposition.x;
}

