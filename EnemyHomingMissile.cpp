#include "Application.h"
#include "EnemyHomingMissile.h"
#include "ModuleCollision.h"
#include "ModuleEnemies.h"

#include "ModuleRender.h"
#include "SDL\include\SDL_timer.h"

EnemyHomingMissile::EnemyHomingMissile(int x, int y, powerUpTypes type, SDL_Texture* thisTexture) : Enemy(x, y)
{
	//links the correct spritesheet texture ----
	enemyTex = thisTexture;
	// -----------------------------------------
	// full angles animation
	missile.anim.PushBack({ 0,0,12,8 });  // pointing left cycle - pi radians - 180 degrees
	missile.anim.PushBack({ 13,0,16,8 }); 
	
	/*missile.anim.PushBack({ 30,0,11,7 }); // pointing 157,5 degrees - 2,7 aprox pi rad
	missile.anim.PushBack({ 42,0,14,10 });

	missile.anim.PushBack({ 57,0,10,10 }); // pointing 3pi/4 radians - 135 degrees
	missile.anim.PushBack({ 68,0,13,13 });

	missile.anim.PushBack({ 82,0,7,11 }); // pointing 112,5 degrees
	missile.anim.PushBack({ 90,0,10,14 });

	missile.anim.PushBack({ 101,0,4,12 }); // pointing up pi/2 radians - 90 degrees
	missile.anim.PushBack({ 106,0,8,16 });

	missile.anim.PushBack({ 115,0,7,11 });
	missile.anim.PushBack({ 123,0,10,14 });

	missile.anim.PushBack({ 148,0,10,10 });
	missile.anim.PushBack({ 134,0,13,13 }); 
	
	missile.anim.PushBack({ 171,0,14,10 });
	missile.anim.PushBack({ 159,0,11,7 });

	missile.anim.PushBack({ 203,0,12,8 }); // pointing right 0 & 2pi - 0 degrees
	missile.anim.PushBack({ 186,0,16,8 });

	missile.anim.PushBack({ 30,23,11,10 }); // 202,5 degree - 3,54 pi rad aprox
	missile.anim.PushBack({ 42,23,14,10 });

	missile.anim.PushBack({ 57,20,10,13 });
	missile.anim.PushBack({ 68,20,13,13 });

	missile.anim.PushBack({ 82,19,7,14 });
	missile.anim.PushBack({ 90,19,10,14 });
	
	missile.anim.PushBack({ 101,18,4,16 }); // pointing down 3pi/2 - 270 degrees
	missile.anim.PushBack({ 106,17,8,16 });

	missile.anim.PushBack({ 115,19,7,14 });
	missile.anim.PushBack({ 123,19,10,14 });

	missile.anim.PushBack({ 148,20,10,13 });
	missile.anim.PushBack({ 134,20,13,13 });

	missile.anim.PushBack({ 159,23,11,10 });
	missile.anim.PushBack({ 171,23,14,10 });*/

	
	missile.anim.speed = 0.50f;

	

	animation = &missile.anim; //links animation

	//original_y = y;
	//fposition.x = x;

	//powerUpType = type;
	//life = 1;
	//enemyScore = 100;

	// search player position before initiate the searching cycle, first assigns a instantiation speed

	missile.distance = GetNearestPlayerSqrtDistance();

	if (nearestTarget == nearestPlayer::P2) missile.playerTargetIndex = 1;

	if (App->player[missile.playerTargetIndex]->position.y < position.y) // submarine initial situation
	{
		missile.ySpeed = -1.0f;
		missile.xSpeed = 1;
	}
	/*if (App->player[index]->position.x < position.x) // boss lvl3 initial speed circunstance
	{
		missile.ySpeed = 0.0f;
		missile.xSpeed = -1.0f;
	}*/
	
	// missiles initial position
	missile.fposition.x = x;
	missile.fposition.y = y;
	//missile.position.x = x;
	//missile.position.y = y;

	// initial timers
	missile.start_cycle_time = SDL_GetTicks();
	
	
	

	// add collider
	collider = App->collision->AddCollider({ 0, 0, 4, 4 }, COLLIDER_TYPE::COLLIDER_ENEMY, (Module*)App->enemies);

}

void EnemyHomingMissile::Move()
{
	// update collider position
	if (collider != nullptr)
		collider->SetPos(position.x, position.y);

	// updates fpositions
	missile.fposition.x += missile.xSpeed + scrollSpeed; // plus update with the current player follow camera speed
	missile.fposition.y += missile.ySpeed;

	// updates missile position
	missile.position.x = missile.fposition.x;
	missile.position.y = missile.fposition.y;

	position.x = missile.position.x;
	position.y = missile.position.y;

}

void EnemyHomingMissile::Draw()
{

	// timers -------------------------------------------------------------------------------------------
	// wait to search on born time
	if (!missile.searching) // if still not search
		missile.now_alive_time = SDL_GetTicks() - missile.start_cycle_time; // its born time cycle
	else
		missile.now_alive_time = SDL_GetTicks() - missile.start_cycle_time; // its destruction is coming

	// check to start search the nearest targeted player
	if (missile.now_alive_time >= missile.instantiate_time && !missile.searching)
	{
		missile.searching = true;
		missile.start_cycle_time = SDL_GetTicks();
		scrollSpeed = 1; // for the moment assigns scroll speed here
	}

	if (missile.now_alive_time >= missile.search_life_time)
		killMe = true; // destroy missile

	// ---------------------------------------------------------------------------------------------------
	
	// movement logic call

	if (missile.searching)
		chaseThePlayer();

	App->render->Blit(enemyTex, position.x, position.y, &missile.anim.GetCurrentFrame());
}

void EnemyHomingMissile::chaseThePlayer()
{
	fPoint vector;
	fPoint playerPos;
	
	playerPos.x = App->player[missile.playerTargetIndex]->position.x + 16;
	playerPos.y = App->player[missile.playerTargetIndex]->position.y + 12;

	missile.distance = missile.fposition.DistanceTo(playerPos);

	//if (abs((int)missile.xSpeed) <= 0) // if we are approximating of player position
	
	if(missile.distance <= 5 && !missile.targetReached) // if the player are very close, round it
	{
		LOG("missile xSpeed VERY LOW: %f", missile.xSpeed);
		missile.targetReached = true;

		missile.ySpeed = 0;

		// initial values to round it
		// x
		if (playerPos.x > position.x)
			missile.targetSpeedX = //-projectileSpeed + missile.xSpeed;
			missile.targetSpeedX = -2.0f; //- missile.xSpeed;
		else
			missile.targetSpeedX = 2.0f;
		// y
		if (playerPos.y > position.y)
			missile.targetSpeedY = 2.0f;
		else
			missile.targetSpeedY = -2.0f;

	

	}

	if (missile.targetReached)
	{
		// x speed deceleration
		if (missile.targetSpeedX < missile.xSpeed)
			missile.xSpeed -= decX;
		else
			missile.xSpeed += decX;

		if ((int)missile.xSpeed == (int)missile.targetSpeedX)
		{
			missile.targetSpeedX = -missile.targetSpeedX;
		}

		// y speed deceleration
		if (missile.targetSpeedY < missile.ySpeed)
			missile.ySpeed -= decY;
		else
			missile.ySpeed += decY;

		if ((int)missile.ySpeed == (int)missile.targetSpeedY)
		{
			missile.targetSpeedY = -missile.targetSpeedY;
		}
	

		if (missile.distance >= 90)
			missile.targetReached = false;
	}

	if (!missile.targetReached) // while the player is far away, chase it
	{
		vector.x = playerPos.x - missile.position.x;
		vector.y = playerPos.y - missile.position.y;


		missile.xSpeed = (vector.x / missile.distance) * projectileSpeed;
		missile.ySpeed = (vector.y / missile.distance) * projectileSpeed;
	}

	





}

