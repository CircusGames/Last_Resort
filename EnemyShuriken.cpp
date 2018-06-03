#include "Application.h"
#include "EnemyShuriken.h"
#include "ModuleCollision.h"
#include "ModuleEnemies.h"

#include "ModuleRender.h"
#include "SDL\include\SDL_timer.h"
#include "ModuleSceneLvl3.h" // for check if we are on boss zone, to instantiate the missiles always in horizontal left way

EnemyShuriken::EnemyShuriken(int x, int y, powerUpTypes type, SDL_Texture* thisTexture) : Enemy(x, y)
{
	//links the correct spritesheet texture ----
	enemyTex = thisTexture;
	enemyType = SHURIKEN;
	// Enemy data
	life = 1;
	// -----------------------------------------
	missile.anim[0].PushBack({ 0,529,40,40 });
	missile.anim[0].PushBack({ 40,529,40,40 });
	missile.anim[0].PushBack({ 80,529,40,40 });
	missile.anim[0].PushBack({ 120,529,40,40 });
	missile.anim[0].PushBack({ 160,529,40,40 });
	missile.anim[0].PushBack({ 200,529,40,40 });
	missile.anim[0].PushBack({ 240,529,40,40 });
	missile.anim[0].PushBack({ 280,529,40,40 });
	missile.anim[0].PushBack({ 320,529,40,40 });
	missile.anim[0].PushBack({ 360,529,40,40 });
	missile.anim[0].PushBack({ 400,529,40,40 });
	missile.anim[0].PushBack({ 440,529,40,40 });
	missile.anim[0].PushBack({ 480,529,40,40 });
	missile.anim[0].PushBack({ 520,529,40,40 });
	missile.anim[0].PushBack({ 560,529,40,40 });
	missile.anim[0].PushBack({ 600,529,40,40 });
	missile.anim[0].PushBack({ 640,529,40,40 });
	missile.anim[0].PushBack({ 680,529,40,40 });
	missile.anim[0].PushBack({ 720,529,40,40 });
	missile.anim[0].PushBack({ 760,529,40,40 });
	missile.anim[0].PushBack({ 800,529,40,40 });
	missile.anim[0].speed = 0.50f;
	missile.anim[0].repeat = false;

	// looping animation
	missile.anim[1].PushBack({ 614,598,40,40 });
	missile.anim[1].PushBack({ 657,598,40,40 });
	missile.anim[1].PushBack({ 700,598,40,40 });
	missile.anim[1].PushBack({ 743,598,40,40 });
	missile.anim[1].PushBack({ 786,598,40,40 });
	missile.anim[1].PushBack({ 829,598,40,40 });
	missile.anim[1].PushBack({ 872,598,40,40 });
	missile.anim[1].speed = 0.25f;

	// disappear anim
	/*missile.anim[2].PushBack({ 840,529,40,40 });
	missile.anim[2].PushBack({ 880,529,40,40 });
	missile.anim[2].PushBack({ 920,529,40,40 });
	missile.anim[2].PushBack({ 960,529,40,40 });
	missile.anim[2].speed = 0.25f;
	missile.anim[2].repeat = false;*/

	//animation = &missile.anim[4]; //links animation

	//missile.current_animation = &missile.anim[4];

	//original_y = y;
	//fposition.x = x;

	//powerUpType = type;
	//life = 1;
	//enemyScore = 100;

	// search player position before initiate the searching cycle, first assigns a instantiation speed

	missile.distance = GetNearestPlayerSqrtDistance();

	if (nearestTarget == nearestPlayer::P2) missile.playerTargetIndex = 1;

	
		missile.ySpeed = -1.0f;
		missile.xSpeed = 1.0f;
		// initial animation
		missile.current_animation = &missile.anim[0];
	
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
	collider = App->collision->AddCollider({ 0, 0, 20, 20 }, COLLIDER_TYPE::COLLIDER_ENEMY, (Module*)App->enemies);

}

void EnemyShuriken::Move()
{
	// update collider position
	if (collider != nullptr)
		collider->SetPos(position.x +10, position.y + 10 );

	// updates fpositions
	missile.fposition.x += missile.xSpeed + scrollSpeed; // plus update with the current player follow camera speed
	missile.fposition.y += missile.ySpeed;

	// updates missile position
	missile.position.x = missile.fposition.x;
	missile.position.y = missile.fposition.y;

	position.x = missile.position.x;
	position.y = missile.position.y;
	//position.x += 1;
}

void EnemyShuriken::Draw()
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
		//scrollSpeed = 1; // for the moment assigns scroll speed here
	}

	if (missile.now_alive_time >= missile.search_life_time)
		killMe = true;
		//missile.current_animation = &missile.anim[2];

	//if (missile.anim[2].finish)
		//killMe = true; // destroy missile

	// ---------------------------------------------------------------------------------------------------

	 // movement logic call

	if (missile.searching)
	{
		chaseThePlayer();
		
	}


	// MISSILE animation draw -------------------------------------------------------

	if (missile.anim[0].finish && !notSwaped)
	{
		missile.current_animation = &missile.anim[1];
		
		notSwaped = true;
	}

	missile.rect = missile.current_animation->GetCurrentFrame();

	App->render->Blit(enemyTex, position.x  , position.y, &missile.rect);

	// ------------------------------------------------------------------------------
	
	// -------------------------------------------------------------------------------

}



void EnemyShuriken::chaseThePlayer()
{
	fPoint vector;
	fPoint playerPos;

	playerPos.x = App->player[missile.playerTargetIndex]->position.x;// + 16;
	playerPos.y = App->player[missile.playerTargetIndex]->position.y;// + 12;

	missile.distance = missile.fposition.DistanceTo(playerPos);

	//if (abs((int)missile.xSpeed) <= 0) // if we are approximating of player position

	if (missile.distance <= 5 && !missile.targetReached) // if the player are very close, round it
	{
		//LOG("missile xSpeed VERY LOW: %f", missile.xSpeed);
		missile.targetReached = true;

		missile.ySpeed = 0;

		// initial values to round it
		// x
		if (playerPos.x > position.x)
			missile.targetSpeedX = //-projectileSpeed + missile.xSpeed;
			missile.targetSpeedX = -turnAroundSpeed;//-2.0f; //- missile.xSpeed;
		else
			missile.targetSpeedX = turnAroundSpeed;//2.0f;
												   // y
		if (playerPos.y > position.y)
			missile.targetSpeedY = turnAroundSpeed;//2.0f;
		else
			missile.targetSpeedY = -turnAroundSpeed;//-2.0f;



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


		if (missile.distance >= 56)
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

