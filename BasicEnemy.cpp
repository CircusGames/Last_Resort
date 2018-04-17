#include "Application.h"
#include "BasicEnemy.h"
#include "ModuleCollision.h"
#include "Path.h"

BasicEnemy::BasicEnemy(int x, int y) : Enemy(x, y)
{

	fly.PushBack({ 5, 72, 21, 22 });
	fly.speed = 0.2f;

	cookie.PushBack({ -2,0 }, 500);
	cookie.PushBack({ -2,4 }, 100);
	cookie.PushBack({ -2,0 }, 500);
	cookie.PushBack({ -2,0 }, 500);


	animation = &fly;

	collider = App->collision->AddCollider({ 0, 0, 24, 24 }, COLLIDER_TYPE::COLLIDER_ENEMY, (Module*)App->enemies);

	original_y = y;
	original_pos = position;


}

void Enemy_Brown_Cookie::Move()
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

	position = original_pos + cookie.GetCurrentPosition();
	/*position.y = int(float(original_y) + (25.0f * sinf(wave)));
	position.x -= 1;*/
}
