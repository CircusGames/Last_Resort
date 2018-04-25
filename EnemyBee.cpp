#include "Application.h"
#include "EnemyBee.h"
#include "ModuleCollision.h"
#include "ModuleEnemies.h"
#include "ModulePlayer.h"
#include "ModuleParticles.h"

#include "SDL\include\SDL_timer.h"

EnemyBee::EnemyBee(int x, int y, powerUpTypes type, SDL_Texture* thisTexture) : Enemy(x, y)
{

	//links correct texture
	enemyTex = thisTexture;
	// --------------------

	//fly to left animation ------------------
	flyToLeft.PushBack({ 0, 0, 48, 45 });
	flyToLeft.PushBack({ 49, 0, 48, 45 });
	flyToLeft.speed = 0.2f;
	// ---------------------------------------
	//fly rotation to right (from left)
	flyRotationRight.PushBack({ 98, 0, 37, 46 });
	flyRotationRight.PushBack({ 147, 0, 39, 46 });
	flyRotationRight.PushBack({ 196, 0, 41, 46 });
	flyRotationRight.PushBack({ 245, 0, 41, 46 });
	flyRotationRight.PushBack({ 294, 0, 48, 46 });
	flyRotationRight.PushBack({ 343, 0, 48, 46 });
	flyRotationRight.PushBack({ 392, 0, 41, 46 });
	flyRotationRight.PushBack({ 441, 0, 41, 46 });

	flyRotationRight.PushBack({ 0, 46, 37, 46 });
	flyRotationRight.PushBack({ 49, 46, 39, 46 });
	flyRotationRight.speed = 0.2f;
	flyRotationRight.repeat = false;

	//plus fixed direction rects
	flyRotationRight.PushBack({ 98, 46, 48, 45 });
	flyRotationRight.PushBack({ 147, 46, 48, 45 });


	//fly to right ---------------------------
	flyToRight.PushBack({ 98, 46, 48, 45 });
	flyToRight.PushBack({ 147, 46, 48, 45 });
	flyToRight.speed = 0.2f;
	// ---------------------------------------
	//fly rotation left (from right)
	flyRotationLeft.PushBack({ 196, 46, 42, 45 });
	flyRotationLeft.PushBack({ 245, 46, 42, 45 });
	flyRotationLeft.PushBack({ 294, 46, 43, 45 });
	flyRotationLeft.PushBack({ 343, 46, 44, 45 });
	flyRotationLeft.PushBack({ 392, 46, 37, 46 });
	flyRotationLeft.PushBack({ 441, 46, 37, 46 });

	flyRotationLeft.PushBack({ 0, 92, 40, 46 });
	flyRotationLeft.PushBack({ 49, 92, 40, 46 });
	flyRotationLeft.PushBack({ 98, 92, 48, 46 });
	flyRotationLeft.PushBack({ 147, 92, 48, 46 });

	flyRotationLeft.PushBack({ 196, 92, 40, 46 });
	flyRotationLeft.PushBack({ 245, 92, 40, 46 });
	flyRotationLeft.PushBack({ 294, 92, 37, 46 });
	flyRotationLeft.PushBack({ 343, 92, 37, 46 });
	flyRotationLeft.PushBack({ 392, 92, 43, 46 });
	flyRotationLeft.PushBack({ 441, 92, 44, 46 });

	flyRotationLeft.PushBack({ 0, 138, 42, 45 });
	flyRotationLeft.PushBack({ 49, 138, 42, 45 });
	flyRotationLeft.speed = 0.4f;
	flyRotationLeft.repeat = false;
	
	

	animation = &flyToLeft; //links first animation


	fposition.x = x;
	fposition.y = y;

	original_y = y;

	powerUpType = type;
	life = 6; //6 points of life original
	enemyScore = 300;

	iSpeed = 60; //speed when are out of the minium distance
	fSpeed = 1.5f; //speed when are at certain proximity distance

	attackRange = 100;
	cadence = 1000;

	start_time = SDL_GetTicks();

	collider = App->collision->AddCollider({ 0, 0, 32, 16 }, COLLIDER_TYPE::COLLIDER_ENEMY, (Module*)App->enemies);

}

void EnemyBee::Move()
{

	// movement logic -------------------------------------------------------------

	//delta calculations
	Uint32 tick_now = SDL_GetTicks();
	if (tick_now > last_tick)
	{
		delta_time = tick_now - last_tick;
		last_tick = tick_now;
	}

	float beeOrbitSpeed = 3.0f; //when are very aprox, orbit player

	//angle += (int)beeOrbitSpeed * (delta_time / 1000);

	tx = (App->player->position.x + 16)  - (position.x + 20);
	ty = (App->player->position.y + 8) - (position.y + 23);
	fPoint playerDistance;
	playerDistance.x = App->player->position.x;
	playerDistance.y = App->player->position.y;

	//get sqrt distance
	distance = fposition.DistanceTo(playerDistance);

	//////////////////


	/////////////////

	if (distance > 100) //follow player at fixed speed
	{
		velX = (tx / distance)*fSpeed;
		velY = (ty / distance)*fSpeed;

		fposition.x += velX;
		fposition.y += velY;
	}
	else //slow down movement speed when player is close 
	{
		fposition.x += tx / iSpeed;

		fposition.y += ty / iSpeed;

	}

	//check entry of rotation
	//if player are on right , rotate +
	//if player are on left, rotate -
	//only 1 time per direction closeup

	if (distance < 50 && rotEntryDir ==  true) //if we are very close, adds orbital movement
	{
		if (tx > 0) //if bee are aproximating for the right side of the player
		{
			rotateClock = true;
			rotateCounterClock = false;
			angle = 0;
		}
		
		else if (tx < 0) //if bee are aproximating for the left side of the player
		{
			rotateCounterClock = true;
			rotateClock = false;
			angle = 3.14f;
		}
		if (ty > 0)
		{
			angle = 4.71f; //test
		}
		else if (ty < 0)
		{
			angle = 1.57f; //test
		}

		rotEntryDir = false;
	}
	else if (distance > 50)
	{
		rotEntryDir = true;
		//lastX = position.x;
		//lastY = position.y;
	}

	if (rotateClock)
	{
		angle += (int)beeOrbitSpeed * (delta_time / 1000);
	}
	else if (rotateCounterClock)
	{
	    angle -= (int)beeOrbitSpeed * (delta_time / 1000);
	}

	fposition.x += cos(angle) * 0.4f;
	fposition.y -= sin(angle) * 0.7f;
	


	fposition.x += 1; //x compensation for player speed movement (follow camera +1)
	position.x = fposition.x;
	position.y = fposition.y; 

	// ---------------------------------------------------------------------------------

	//animation logic ------------------------------------------------------------------
	Animation* current_animation =  animation;
	SDL_Rect currentRect;
	currentRect = current_animation->frames[(int)animation->current_frame];

	if (playerDistance.x > position.x)
	{
		flyRotationLeft.current_frame = 0;
		//animation = &flyToRight;
		animation = &flyRotationRight;
		if (animation->current_frame >= animation->last_frame)
			animation = &flyToRight;

		firstEncounter = false;
	}
	else
	{
		flyRotationRight.current_frame = 0;

		if(firstEncounter)
		animation = &flyToLeft;
		else
		{
			animation = &flyRotationLeft;
		}
		if (animation->current_frame >= animation->last_frame)
			animation = &flyToLeft;

	}


	// ---------------------------------------------------------------------------------



	/*int dirx = App->player->position.x - position.x;
	int diry = App->player->position.y - position.y;

	length = sqrt(dirx*dirx + diry*diry);

	/*dirx /= length; //normalize vector (make 1 unit length)
	diry /= length;
	dirx *= 1; //scale to our speed
	diry *= 1; */


	/*now = SDL_GetTicks() - start_time;

	if (now >= cadence) attack = true;

	if (attack) {
		if (abs(distance) < attackRange)
			App->particles->AddParticle(App->particles->beam, position.x, position.y, COLLIDER_ENEMY_SHOT, { dirx,diry });
		attack = false;
		start_time = SDL_GetTicks();
	}*/

}