#include "Application.h"
#include "EnemyTank.h"
#include "ModuleCollision.h"
#include "ModuleEnemies.h"
#include "Path.h"

#define BOOST_FRAMES 4

EnemyTank::EnemyTank(int x, int y, powerUpTypes type, SDL_Texture* thisTexture) : Enemy(x, y)
{
	//links correct spritesheet texture
	enemyTex = thisTexture;
	// -------------------------------

	// tank movement animation
	staticAnim.PushBack({ 0,31,157,64 });
	moveAnim.PushBack({ 0, 31, 157, 64 });
	moveAnim.PushBack({ 0, 95, 157, 63 });
	moveAnim.speed = 0.3f;

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

	path.PushBack({ 0.5f, 0.0f }, 640, &staticAnim);
	path.PushBack({ 1.5f, 0 }, 304, &moveAnim);
	path.PushBack({ 1,0 }, 1600, &moveAnim);

	powerUpType = type;

	originalPos.x = x;
	originalPos.y = y;
	life = 5;

	collider = App->collision->AddCollider({ 0, 0, 157, 64 }, COLLIDER_TYPE::COLLIDER_ENEMY, (Module*)App->enemies);

	//Big Turret
	rotateAnimBig.PushBack({ 157, 95, 28, 10 });
	rotateAnimBig.PushBack({ 185, 95, 26, 12 });
	rotateAnimBig.PushBack({ 211, 95, 26, 13 });
	rotateAnimBig.PushBack({ 0, 158, 26, 14 });
	rotateAnimBig.PushBack({ 26, 158, 26, 14 });
	rotateAnimBig.PushBack({ 52, 158, 26, 14 });
	rotateAnimBig.PushBack({ 78, 158, 26, 13 });
	rotateAnimBig.PushBack({ 104, 158, 26, 12 });
	rotateAnimBig.PushBack({ 130, 158, 29, 10 });
	rotateAnimBig.speed = 0.05f;

	animation2 = &rotateAnimBig;

	collider = App->collision->AddCollider({ 0, 0, 29, 14 }, COLLIDER_TYPE::COLLIDER_ENEMY, (Module*)App->enemies);

	path.PushBack({ 0.5f, 0.0f }, 540, &rotateAnimBig);
	path.PushBack({ 1.5f, 0 }, 304, &rotateAnimBig);
	path.PushBack({ 1,0 }, 1600, &rotateAnimBig);
	originalPos2.x = x;
	originalPos2.y = y;

	//Small Turret
	rotateAnimSmall.PushBack({ 159, 158, 15, 6 });
	rotateAnimSmall.PushBack({ 174, 158, 13, 8 });
	rotateAnimSmall.PushBack({ 187, 158, 13, 9 });
	rotateAnimSmall.PushBack({ 200, 158, 13, 9 });
	rotateAnimSmall.PushBack({ 213, 158, 13, 9 });
	rotateAnimSmall.PushBack({ 226, 158, 13, 9 });
	rotateAnimSmall.PushBack({ 239, 158, 14, 6 });
	rotateAnimSmall.speed = 0.05f;

	animation3 = &rotateAnimSmall;

	path.PushBack({ 0.5f, 0.0f }, 470, &rotateAnimSmall);
	path.PushBack({ 1.5f, 0 }, 304, &rotateAnimSmall);
	path.PushBack({ 1,0 }, 1700, &rotateAnimSmall);
	originalPos3.x = x;
	originalPos3.y = y;

	collider = App->collision->AddCollider({ 0, 0, 15, 9 }, COLLIDER_TYPE::COLLIDER_ENEMY, (Module*)App->enemies);
}

void EnemyTank::Move()
{
	position = originalPos + path.GetCurrentSpeed(&animation);
	position2 = originalPos2 + path.GetCurrentSpeed(&animation2);
	position3 = originalPos3 + path.GetCurrentSpeed(&animation3);
	//when tank appears it remains inmobile until it reaches the left collider, after that it goes 0,5 faster than
	//the camera speed until it reaches the right side of the screen(no margins) and it follows the camera speed until
	//it reaches the broken bridge
}