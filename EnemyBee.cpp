#include "Application.h"
#include "EnemyBee.h"
#include "ModuleCollision.h"
#include "ModuleEnemies.h"
#include "ModulePlayer.h"

EnemyBee::EnemyBee(int x, int y, powerUpTypes type, SDL_Texture* sprite) : Enemy(x, y)
{
	flyToLeft.PushBack({ 0,16,32,15 });
	flyToLeft.PushBack({ 0,0,32,16 });
	flyToLeft.PushBack({ 0,31,32,16 });
	flyToLeft.PushBack({ 0,47,32,15 });
	flyToLeft.PushBack({ 0,31,32,16 });
	flyToLeft.PushBack({ 0,0,32,16 });
	flyToLeft.speed = 0.2f;

	animation = &flyToLeft; //links animation


	texture = sprite;


	fposition.x = x;
	fposition.y = y;

	powerUpType = type;
	life = 1; //6 points of life original
	enemyScore = 300;

	iSpeed = 40;
	//fSpeed = 50;
	fSpeed = 47.3f;

	collider = App->collision->AddCollider({ 0, 0, 32, 16 }, COLLIDER_TYPE::COLLIDER_ENEMY, (Module*)App->enemies);

}

void EnemyBee::Move()
{

	fposition.x += ((float)App->player->position.x - fposition.x) / fSpeed;
	fposition.y += ((float)App->player->position.y - fposition.y) / fSpeed;

	position.x = fposition.x + 1;
	position.y = fposition.y;

}