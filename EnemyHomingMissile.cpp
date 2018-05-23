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
	enemyType = HOMINGMISSILE;
	// Enemy data
	life = 1;
	// -----------------------------------------
	// HOMING MISSILE full angles animation
	missile.anim[0].PushBack({ 0,0,12,8 });  // pointing left cycle - pi radians - 180 degrees
	missile.anim[0].PushBack({ 13,0,16,8 }); 
	
	missile.anim[1].PushBack({ 30,0,11,7 }); // pointing 157,5 degrees - 2,7 aprox pi rad
	missile.anim[1].PushBack({ 42,0,14,10 });

	missile.anim[2].PushBack({ 57,0,10,10 }); // pointing 3pi/4 radians - 135 degrees
	missile.anim[2].PushBack({ 68,0,13,13 });

	missile.anim[3].PushBack({ 82,0,7,11 }); // pointing 112,5 degrees
	missile.anim[3].PushBack({ 90,0,10,14 });

	missile.anim[4].PushBack({ 100,0,6,12 }); // pointing up pi/2 radians - 90 degrees
	missile.anim[4].PushBack({ 107,0,8,16 });

	missile.anim[5].PushBack({ 116,0,7,11 });
	missile.anim[5].PushBack({ 124,0,10,14 });

	missile.anim[6].PushBack({ 149,0,10,10 });
	missile.anim[6].PushBack({ 135,0,13,13 });
	
	missile.anim[7].PushBack({ 160,0,11,7 });
	missile.anim[7].PushBack({ 172,0,14,10 });
	
	missile.anim[8].PushBack({ 204,0,12,8 }); // pointing right 0 & 2pi - 0 degrees
	missile.anim[8].PushBack({ 187,0,16,8 });

	missile.anim[9].PushBack({ 30,23,11,10 }); // 202,5 degree - 3,54 pi rad aprox
	missile.anim[9].PushBack({ 42,23,14,10 });

	missile.anim[10].PushBack({ 57,20,10,13 });
	missile.anim[10].PushBack({ 68,20,13,13 });

	missile.anim[11].PushBack({ 82,19,7,14 });
	missile.anim[11].PushBack({ 90,19,10,14 });
	
	missile.anim[12].PushBack({ 100,17,6,16 }); // pointing down 3pi/2 - 270 degrees
	missile.anim[12].PushBack({ 107,17,8,16 });

	missile.anim[13].PushBack({ 115,19,7,14 });
	missile.anim[13].PushBack({ 123,19,10,14 });

	missile.anim[14].PushBack({ 148,20,10,13 });
	missile.anim[14].PushBack({ 134,20,13,13 });

	missile.anim[15].PushBack({ 159,23,11,10 });
	missile.anim[15].PushBack({ 171,23,14,10 });

	for (int i = 0; i < 16; ++i)
		missile.anim[i].speed = 0.50f;

	// WATER SPLASH animation --------------------------
	waterSplash.PushBack({ 1,126,11,4 });
	waterSplash.PushBack({ 14,105,16,25 });
	waterSplash.PushBack({ 30,99,16,31 });
	waterSplash.PushBack({ 47,98,16,32 });
	waterSplash.PushBack({ 64,98,16,32 });
	waterSplash.PushBack({ 81,99,16,31 });
	waterSplash.PushBack({ 99,101,15,29 });
	waterSplash.PushBack({ 116,104,16,26 });
	waterSplash.speed = 0.23f;
	waterSplash.repeat = false;
	

	animation = &missile.anim[4]; //links animation

	missile.current_animation = &missile.anim[4];

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
		missile.xSpeed = 1.0f;
		// initial animation
		missile.current_animation = &missile.anim[4];
	}
	else
	{
		missile.ySpeed = 0.0f;
		missile.xSpeed = 0.0f;
		missile.current_animation = &missile.anim[0];
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

	// check if the missile is instantiated underWater
	if (missile.fposition.y > waterLevel)
	{
		underWater = true;
	}
	
	
	

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
	//position.x += 1;
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
	{
		chaseThePlayer();
		assignAnim();
		
		if (underWater)
		{
			underWaterSplash();
		}
	}

	
	// MISSILE animation draw -------------------------------------------------------

	missile.rect = missile.current_animation->GetCurrentFrame();
	
	App->render->Blit(enemyTex, position.x - pivotAnimation[pivotIndex+(int)missile.current_animation->current_frame].x, position.y, &missile.rect);

	// ------------------------------------------------------------------------------
	// water splash animation

	if (waterSplashing)
	{
		waterRect = waterSplash.GetCurrentFrame();

		// follow foreground water speed
		followTheFlow += 0.5f;
		waterContactPosition = followTheFlow;

		App->render->Blit(enemyTex, waterContactPosition - 10, waterLevel - waterRect.h, &waterRect);

		if (waterSplash.finish)
			waterSplashing = false;
	}
	// -------------------------------------------------------------------------------

}

void EnemyHomingMissile::underWaterSplash()
{

	if (position.y < waterLevel)
	{
		waterContactPosition = position.x;
		followTheFlow = waterContactPosition;
		underWater = false;
		waterSplashing = true;
	}

}

void EnemyHomingMissile::assignAnim()
{

	// LINEAL ANIMS ------------------------------
	// pointing down 
	if (fabs(missile.xSpeed) < 0.5f && (fabs(missile.xSpeed) >= 0.05f) && missile.ySpeed > 0)
	{
		missile.current_animation = &missile.anim[12];
		pivotIndex = 24;
	}
	// pointing up
	if (fabs(missile.xSpeed) < 0.5f && (fabs(missile.xSpeed) >= 0.05f) && missile.ySpeed < 0)
	{
		missile.current_animation = &missile.anim[4];
		pivotIndex = 8;
	}
	// pointing right
	if (fabs(missile.ySpeed) < 0.5f && (fabs(missile.ySpeed) >= 0.00f) && missile.xSpeed > 0) 
	{
		missile.current_animation = &missile.anim[8];
		pivotIndex = 16;
	}
	// pointing left
	if (fabs(missile.ySpeed) < 0.5f && (fabs(missile.ySpeed) >= 0.00f) && missile.xSpeed < 0)
	{
		missile.current_animation = &missile.anim[0];
		pivotIndex = 0;
	}
	// ---------------------------------------------------------------------------
	// TO THE RIGHTS diagonals ---------------------------------------------------
	// UP RIGHT -------------
	//pointing up/right 22.5
	if (missile.xSpeed >= 1.65f && missile.xSpeed <= 1.97f && missile.ySpeed < 0)
	{
		missile.current_animation = &missile.anim[7];
		pivotIndex = 14;
	}
	// pointing up/right 45
	if (missile.xSpeed >= 1.25f && missile.xSpeed <= 1.65f && missile.ySpeed < 0)
	{
		missile.current_animation = &missile.anim[6];
		pivotIndex = 12;
	}
	//pointing up/right 66.5
	if (missile.xSpeed >= 0.45f && missile.xSpeed <= 1.25f && missile.ySpeed < 0)
	{
		missile.current_animation = &missile.anim[5];
		pivotIndex = 10;
	}
	// DOWN/RIGHT  -----------
	//pointing down/right 22.5
	if (missile.xSpeed >= 1.65f && missile.xSpeed <= 1.97f && missile.ySpeed > 0)
	{
		missile.current_animation = &missile.anim[15];
		pivotIndex = 30;
	}
	// pointing down/right 45
	if (missile.xSpeed >= 1.25f && missile.xSpeed <= 1.65f && missile.ySpeed > 0)
	{
		missile.current_animation = &missile.anim[14];
		pivotIndex = 28;
	}
	//pointing down/right 66.5
	if (missile.xSpeed >= 0.45f && missile.xSpeed <= 1.25f && missile.ySpeed > 0)
	{
		missile.current_animation = &missile.anim[13];
		pivotIndex = 26;
	}
	
	//LEFT DIAGONALS ------------------------------------------------------------------
	// UP cases -------------------
	//pointing up/left 22.5
	if (missile.xSpeed <= -1.65f && missile.xSpeed >= -1.97f && missile.ySpeed < 0)
	{
		missile.current_animation = &missile.anim[1];
		pivotIndex = 2;
	}
	// pointing up/left 45
	if (missile.xSpeed <= -1.25f && missile.xSpeed >= -1.65f && missile.ySpeed < 0)
	{
		missile.current_animation = &missile.anim[2];
		pivotIndex = 4;
	}
	//pointing up/left 66.5
	if (missile.xSpeed <= -0.45f && missile.xSpeed >= -1.25f && missile.ySpeed < 0)
	{
		missile.current_animation = &missile.anim[3];
		pivotIndex = 6;
	}
	// --------------------
	// DOWN cases ----------------
	//pointing down/left 22.5
	if (missile.xSpeed <= -1.65f && missile.xSpeed >= -1.97f && missile.ySpeed > 0)
	{
		missile.current_animation = &missile.anim[9];
		pivotIndex = 18;
	}
	// pointing down/left 45
	if (missile.xSpeed <= -1.25f && missile.xSpeed >= -1.65f && missile.ySpeed > 0)
	{
		missile.current_animation = &missile.anim[10];
		pivotIndex = 20;
	}
	//pointing down/left 66.5
	if (missile.xSpeed <= -0.45f && missile.xSpeed >= -1.25f && missile.ySpeed > 0)
	{
		missile.current_animation = &missile.anim[11];
		pivotIndex = 22;
	}

	//LOG("XSPEED: %f", missile.xSpeed);
	//LOG("YSPEED: %f", missile.ySpeed);

}

void EnemyHomingMissile::chaseThePlayer()
{
	fPoint vector;
	fPoint playerPos;
	
	playerPos.x = App->player[missile.playerTargetIndex]->position.x;// + 16;
	playerPos.y = App->player[missile.playerTargetIndex]->position.y;// + 12;

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

