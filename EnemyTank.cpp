#include "Application.h"
#include "EnemyTank.h"
#include "ModuleCollision.h"
#include "ModuleEnemies.h"

#define BOOST_FRAMES 4

EnemyTank::EnemyTank(int x, int y, powerUpTypes type, SDL_Texture* sprite) : Enemy(x, y)
{
	// tank movement animation
	moveAnim.PushBack({ 0, 31, 157, 64 });
	moveAnim.PushBack({ 0, 95, 157, 63 });

	// boost animation
	for (int i = 0; i < BOOST_FRAMES; i++)
	{
		if (i < BOOST_FRAMES - 1)
			boostAnim.PushBack({ 0, 0, 31 * i, 31 });

		else
			boostAnim.PushBack({ 0, 0, 30 * i, 30 });
	}

	// movement particles
	particlesAnim.PushBack({ 0, 172, 11, 8 });
	particlesAnim.PushBack({ 11, 172, 12, 9 });
	particlesAnim.PushBack({ 23, 172, 6, 10 });
	particlesAnim.PushBack({ 29, 172, 16, 10 });
	particlesAnim.PushBack({ 45, 172, 16, 11 });
	particlesAnim.PushBack({ 61, 172, 16, 10 });
	particlesAnim.PushBack({ 77, 172, 7, 9 });
	particlesAnim.PushBack({ 84, 172, 10, 9 });

	animation = &moveAnim;
	//animation = &boostAnim;
	//animation = &particlesAnim;

	texture = sprite;
	powerUpType = type;

	original_x = x;
	life = 5;

	collider = App->collision->AddCollider({ 0, 0, 157, 64 }, COLLIDER_TYPE::COLLIDER_ENEMY, (Module*)App->enemies);
}

void EnemyTank::Move()
{
	position.x += 1;
}