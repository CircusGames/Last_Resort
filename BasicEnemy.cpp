/*
#include "Application.h"
#include "BasicEnemy.h"
#include "ModuleCollision.h"

BasicEnemy::BasicEnemy(int x, int y) : Enemy(x, y)
{

	fly.PushBack({ 5, 72, 21, 22 });
	fly.speed = 0.2f;

	animation = &fly;

	collider = App->collision->AddCollider({ 0, 0, 24, 24 }, COLLIDER_TYPE::COLLIDER_ENEMY, (Module*)App->enemies);

	original_y = y;
	original_pos = position;


}
*/