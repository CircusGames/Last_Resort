#include "Application.h"
#include "BasicEnemy.h"
#include "ModuleCollision.h"

BasicEnemy::BasicEnemy(int x, int y) : Enemy(x, y)
{
	/*fly.PushBack({ 5,6,24,24 });
	fly.PushBack({ 38, 6, 24, 24 });
	fly.PushBack({ 71, 6, 24, 24 });
	fly.PushBack({ 104, 6, 24, 24 });
	fly.PushBack({ 137, 6, 24, 24 });
	fly.PushBack({ 170, 6, 24, 24 });
	fly.PushBack({ 203, 6, 24, 24 });
	fly.PushBack({ 236, 6, 24, 24 });*/
	fly.PushBack({ 5,72,21,22 });
	fly.speed = 0.2f;

	BasicPath.PushBack({ -2,0 }, 20);
	BasicPath.PushBack({ -2,1 }, 15);
	BasicPath.PushBack({ -2,-1 }, 15);



	animation = &fly;

	collider = App->collision->AddCollider({ 0, 0, 24, 24 }, COLLIDER_TYPE::COLLIDER_ENEMY, (Module*)App->enemies);

	//original_y = y;
	original_pos = position;
}

void BasicEnemy::Move()
{
	/*if (going_up)
	{
	if (wave > 1.0f)
	going_up = false;
	else
	wave += 0.05f;
	}
	else
	{
	if (wave < -1.0f)
	going_up = true;
	else
	wave -= 0.05f;
	}*/

	//position.y = int(float(original_y) + (25.0f * sinf(wave)));
	//position.x -= 1;

	position = original_pos + BasicPath.GetCurrentPosition();
}
