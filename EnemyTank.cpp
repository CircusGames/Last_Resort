#include "Application.h"
#include "EnemyTank.h"
#include "ModuleCollision.h"
#include "ModuleEnemies.h"
#include "Path.h"
#include "ModuleRender.h"
#include "ModulePlayer.h"

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
	moveAnim.speed = 0.33f;

	// boost animation
	for (int i = 0; i < BOOST_FRAMES; i++)
	{
		if (i < BOOST_FRAMES - 1)
			boostAnim.PushBack({ 0, 0, 31 * i, 31 });

		else
			boostAnim.PushBack({ 0, 0, 30 * i, 30 });
	}

	/*// movement particles --> WHERE? spritesheet limit y is 172... ?
	particlesAnim.PushBack({ 0, 172, 11, 8 });
	particlesAnim.PushBack({ 11, 172, 12, 9 });
	particlesAnim.PushBack({ 23, 172, 6, 10 });
	particlesAnim.PushBack({ 29, 172, 16, 10 });
	particlesAnim.PushBack({ 45, 172, 16, 11 });
	particlesAnim.PushBack({ 61, 172, 16, 10 });
	particlesAnim.PushBack({ 77, 172, 7, 9 });
	particlesAnim.PushBack({ 84, 172, 10, 9 }); */

	animation = &moveAnim;
	//animation = &boostAnim;
	//animation = &particlesAnim;

	path.PushBack({ 0.5f, 0.0f }, 640, &staticAnim);
	path.PushBack({ 1.5f, 0 }, 304, &moveAnim);
	path.PushBack({ 1,0 }, 1600, &moveAnim);

	powerUpType = type;

	//originalPos.x = x;
	//originalPos.y = y;
	life = 5;

	collider = App->collision->AddCollider({ 0, 0, 100, 64 }, COLLIDER_TYPE::COLLIDER_ENEMY, (Module*)App->enemies);

	//Big Turret
	bigTurretAnim.PushBack({ 157, 95, 28, 10 });
	bigTurretAnim.PushBack({ 185, 95, 26, 12 });
	bigTurretAnim.PushBack({ 211, 95, 26, 13 });
	bigTurretAnim.PushBack({ 0, 158, 26, 14 });
	bigTurretAnim.PushBack({ 26, 158, 26, 14 });
	bigTurretAnim.PushBack({ 52, 158, 26, 14 });
	bigTurretAnim.PushBack({ 78, 158, 26, 13 });
	bigTurretAnim.PushBack({ 104, 158, 26, 12 });
	bigTurretAnim.PushBack({ 130, 158, 29, 10 });
	bigTurretAnim.speed = 0.05f;

	animation2 = &bigTurretAnim;

	bigTurretCollider = App->collision->AddCollider({ 0, 0, 29, 14 }, COLLIDER_TYPE::COLLIDER_ENEMY, (Module*)App->enemies);

	bigTurretPosition.x = position.x;

	//path.PushBack({ 0.5f, 0.0f }, 540, &rotateAnimBig);
	//path.PushBack({ 1.5f, 0 }, 304, &rotateAnimBig);
	//path.PushBack({ 1,0 }, 1600, &rotateAnimBig);
	//originalPos2.x = x;
	//originalPos2.y = y;

	//Small Turret
	smallTurretAnim.PushBack({ 159, 158, 15, 6 });
	smallTurretAnim.PushBack({ 174, 158, 13, 8 });
	smallTurretAnim.PushBack({ 187, 158, 13, 9 });
	smallTurretAnim.PushBack({ 200, 158, 13, 9 });
	smallTurretAnim.PushBack({ 213, 158, 13, 9 });
	smallTurretAnim.PushBack({ 226, 158, 13, 9 });
	smallTurretAnim.PushBack({ 239, 158, 14, 6 });
	smallTurretAnim.speed = 0.05f;

	animation3 = &smallTurretAnim;

	//path.PushBack({ 0.5f, 0.0f }, 470, &rotateAnimSmall);
	//path.PushBack({ 1.5f, 0 }, 304, &rotateAnimSmall);
	//path.PushBack({ 1,0 }, 1700, &rotateAnimSmall);
	//originalPos3.x = x;
	//originalPos3.y = y;

	smallTurretCollider = App->collision->AddCollider({ 0, 0, 15, 9 }, COLLIDER_TYPE::COLLIDER_ENEMY, (Module*)App->enemies);

	

}

void EnemyTank::Move()
{

	// update turrets position to tank position
	bigTurretPosition.x = position.x + 50;
	smallTurretPosition.x = position.x + 86;


	// update collider position ------------------------------------
	//tank
	collider->SetPos(position.x + 30 ,position.y);
	//big turret from tank pos
	bigTurretCollider->SetPos(position.x + 49,position.y - 7);
	//small turret from tank pos
	smallTurretCollider->SetPos(position.x + 100 , position.y );
	// --------------------------------------------------------------




	position.x += 1;
	fposition.x = position.x;
	fposition.y = position.y;

	/*position = originalPos + path.GetCurrentSpeed(&animation);
	position2 = originalPos2 + path.GetCurrentSpeed(&animation2);
	position3 = originalPos3 + path.GetCurrentSpeed(&animation3);*/
	//when tank appears it remains inmobile until it reaches the left collider, after that it goes 0,5 faster than
	//the camera speed until it reaches the right side of the screen(no margins) and it follows the camera speed until
	//it reaches the broken bridge

	float distance = GetNearestPlayerSqrtDistance();

}

void EnemyTank::Draw()
{
	Animation* current_animation;
	current_animation = &moveAnim;
	SDL_Rect tankRect = current_animation->GetCurrentFrame();
	
	// draw tank -------------------------------------------------------------------------------------------------
	App->render->Blit(enemyTex, position.x, position.y + 64 - tankRect.h, &tankRect); //and draw texture

	// big turret ------------------------------------------------------------------------------------------------
	// big turret 0.4f radians per frame

	current_animation = &bigTurretAnim;
	SDL_Rect bigTurretRect; //= current_animation->GetCurrentFrame();

	float vectorX =  bigTurretPosition.x - 14 - App->player[0]->position.x + 16; //16 middle player pos, 14 middle bigturretposx
	float vectorY = position.y - App->player[0]->position.y;// -tankRect.h - (70) - bigTurretRect.h;

	omega = atan2f(vectorY, vectorX);// * 180 / 3.14f;
	
	if (omega < 0 || omega < 0.39f)
	{
		bigTurretRect = current_animation->frames[0];
		current_animation->current_frame = 0;
	}
	if (omega > 0.39f && omega < 0.785f)
	{
		bigTurretRect = current_animation->frames[1];
		current_animation->current_frame = 1;
	}
	if (omega > 0.785f && omega < 1.18f)
	{
		bigTurretRect = current_animation->frames[2];
		current_animation->current_frame = 2;
	}
	if (omega > 1.18f && omega < 1.57f)
	{
		bigTurretRect = current_animation->frames[3];
		current_animation->current_frame = 3;
	}
	if (omega > 1.57f && omega < 1.96f)
	{
		bigTurretRect = current_animation->frames[4];
		current_animation->current_frame = 4;
	}
	if (omega > 1.96f && omega < 2.35f)
	{
		bigTurretRect = current_animation->frames[5];
		current_animation->current_frame = 5;
	}
	if (omega > 2.35f && omega < 2.74f)
	{
		bigTurretRect = current_animation->frames[6];
		current_animation->current_frame = 6;
	}
	if (omega > 2.74f && omega < 3.13f)
	{
		bigTurretRect = current_animation->frames[7];
		current_animation->current_frame = 7;
	}
	if (omega > 3.13f && omega && omega < 3.52f)
	{
		bigTurretRect = current_animation->frames[8];
		current_animation->current_frame = 8;
	}

	
	//angleX = cosf(omega);// / M_PI * 180);
	//angleY = sinf(omega);
	
	LOG("omega: %f", omega);
	//LOG("angleX: %f", angleX);

	//position.x + 49 

	App->render->Blit(this->enemyTex, bigTurretPosition.x - bigTurretPivot[(int)current_animation->current_frame], position.y - tankRect.h + (70)- bigTurretRect.h, &bigTurretRect);

	// small turret ----------------------------------------------------------------------------------------------

	current_animation = &smallTurretAnim;
	SDL_Rect smallTurretRect = current_animation->GetCurrentFrame();

	App->render->Blit(this->enemyTex, smallTurretPosition.x - smallTurretPivots[(int)current_animation->current_frame] , 
		position.y - tankRect.h + (72) - smallTurretRect.h, 
		&smallTurretRect);
}