#include "Application.h"
#include "BasicEnemy.h"
#include "ModuleCollision.h"
#include "ModuleEnemies.h"

BasicEnemy::BasicEnemy(int x, int y, powerUpTypes type, SDL_Texture* sprite) : Enemy(x, y)
{

	fly.PushBack({ 0,0,32,16 });
	fly.PushBack({ 0,16,32,15 });
	fly.PushBack({ 0,31,32,16 });
	fly.PushBack({ 0,47,32,15 });
	fly.PushBack({ 0,31,32,16 });
	fly.PushBack({ 0,16,32,15 });
	fly.speed = 0.2f;

	animation = &fly; //links animation

	//on te actual workaround this line is NEEDED to link the sprites to the enemy
	//if we not receive this parameter (called sprite on THIS constructor), links to the general texture
	//called sprites, on moduleEnemies.cpp Start() method.
	//BUT ALWAYS, for now (if you want recieve the texture from the outside):
	//texture = sprite; //THIS LINE IS NEEDED. 
	//links texture ----------------------------------------
	texture = sprite; //THIS LINE IS NEEDED. //links texture ----------------------------------------
	//or another workaround is define the texture here:
	//texture = App->textures->Load("assets/Graphics/Enemies/Level_1/enemy1.png"); //other method to load and link texture
	//and avoid the texture call from AddEnemy method from the scene
	//and avoid define the texture pointer and load methods from moduleEnemie
	// ----------------------------------------------------------------------------------------------
	
	//collider = App->collision->AddCollider({ 0, 0, 24, 24 }, COLLIDER_TYPE::COLLIDER_POWER_UP, (Module*)App->enemies);

	original_y = y;
	fposition.x = x;


	powerUpType = type;

	/*if (type == powerUpTypes::UNIT)
		collider = App->collision->AddCollider({ 0, 0, 24, 24 }, COLLIDER_TYPE::COLLIDER_POWER_UP, (Module*)App->enemies);
	else*/
	collider = App->collision->AddCollider({ 0, 0, 32, 16 }, COLLIDER_TYPE::COLLIDER_ENEMY, (Module*)App->enemies);

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

	//position.y = int(float(original_y) + (25.0f * sinf(wave)));
	fposition.x -= 0.5;
	position.x = fposition.x;
}

