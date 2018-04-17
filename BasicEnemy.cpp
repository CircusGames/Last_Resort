#include "Application.h"
#include "BasicEnemy.h"
#include "ModuleCollision.h"
#include "ModuleEnemies.h"

BasicEnemy::BasicEnemy(int x, int y, SDL_Texture* sprite) : Enemy(x, y)
{
	/*fly.PushBack({ 5,6,24,24 });
	fly.PushBack({ 38, 6, 24, 24 });
	fly.PushBack({ 71, 6, 24, 24 });
	fly.PushBack({ 104, 6, 24, 24 });
	fly.PushBack({ 137, 6, 24, 24 });
	fly.PushBack({ 170, 6, 24, 24 });
	fly.PushBack({ 203, 6, 24, 24 });
	fly.PushBack({ 236, 6, 24, 24 });
	fly.speed = 0.2f;*/
	fly.PushBack({ 0,0,32,16 });
	fly.PushBack({ 0,16,32,15 });
	fly.PushBack({ 0,31,32,16 });
	fly.PushBack({ 0,47,32,15 });
	fly.speed = 0.2f;

	//texture = (Module*)App->enemies->

	animation = &fly;

	//on te actual workaround this line is NEEDED to link the sprites to te enemy
	//if we not send this parameter (called sprite on THIS constructor), links to the general texture
	//called sprites, on moduleEnemies.cpp Start() method.
	//BUT ALWAYS, for now:
	texture = sprite; //THIS LINE IS NEEDED.
	// ----------------------------------------------------------------------------------------------
	

	collider = App->collision->AddCollider({ 0, 0, 24, 24 }, COLLIDER_TYPE::COLLIDER_ENEMY, (Module*)App->enemies);

	original_y = y;
}

void BasicEnemy::Move()
{
	if (going_up)
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
	}

	position.y = int(float(original_y) + (25.0f * sinf(wave)));
	position.x -= 0;
}