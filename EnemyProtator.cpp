#include "Application.h"
#include "EnemyProtator.h"
#include "ModuleCollision.h"
#include "ModuleEnemies.h"

EnemyProtator::EnemyProtator(int x, int y, powerUpTypes type, SDL_Texture* thisTexture) : Enemy(x, y)
{
	//links the correct spritesheet texture ----
	enemyTex = thisTexture;
	// -----------------------------------------
	//protator normal animation ----
	protatorAnim.PushBack({ 0,0,32,32 });
	/*protatorAnim.PushBack({ 33,0,32,30 });
	protatorAnim.PushBack({ 66,0,32,28 });
	protatorAnim.PushBack({ 99,0,32,26 });
	protatorAnim.PushBack({ 132,0,32,26 });
	protatorAnim.PushBack({ 0,33,30,26 });
	protatorAnim.PushBack({ 31,33,32,26 });
	protatorAnim.PushBack({ 64,33,32,30 });
	protatorAnim.PushBack({ 97,33,32,26 });
	protatorAnim.PushBack({ 130,33,32,28 });
	protatorAnim.PushBack({ 1,64,32,32 });
	protatorAnim.PushBack({ 34,64,32,32 });
	protatorAnim.PushBack({ 67,64,32,32 });
	protatorAnim.PushBack({ 100,64,32,32 });
	protatorAnim.PushBack({ 133,64,32,32 });*/
	protatorAnim.speed = 0.125f;
	// ----
	//protator damage animation

	protatorAnim.speed = 0.2f;

	animation = &protatorAnim; //links animation

	original_y = y;
	fposition.x = x;

	powerUpType = type;
	life = 1;
	enemyScore = 100;

	collider = App->collision->AddCollider({ 0, 0, 32, 16 }, COLLIDER_TYPE::COLLIDER_ENEMY, (Module*)App->enemies);

}

void EnemyProtator::Move()
{
	//fposition.x -= 1.35;
	position.x += 1;//fposition.x;




}

