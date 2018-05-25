#include "Application.h"
#include "EnemyBigFuckingRocket.h"
#include "ModuleCollision.h"
#include "ModuleEnemies.h"

#include "ModuleRender.h"
#include "SDL\include\SDL_timer.h"

EnemyBigFuckingRocket::EnemyBigFuckingRocket(int x, int y, powerUpTypes type, SDL_Texture* thisTexture) : Enemy(x, y)
{
	//links the correct spritesheet texture ----
	enemyTex = thisTexture;
	enemyType = BIGFUCKINGROCKET;
	// Enemy data
	life = 1;
	// -----------------------------------------
	// BIGFUCKINGROCKET full angles animation
	missile.bfrRect[0] = { 235,26,14,10 }; // points left 180
	missile.bfrRect[1] = { 221,26,13,11 }; // points left 157,5
	missile.bfrRect[2] = { 207,26,13,13 }; // points left 135
	missile.bfrRect[3] = { 195,26,11,13 }; // points left 112,5
	missile.bfrRect[4] = { 184,11,10,14 }; // points up 90
	missile.bfrRect[5] = { 195,11,11,13 }; // 
	missile.bfrRect[6] = { 207,11,13,13 };
	missile.bfrRect[7] = { 221,11,13,11 };
	missile.bfrRect[8] = { 236,13,14,10 }; // points right 0
	missile.bfrRect[9] = { 250,26,13,11 }; //
	missile.bfrRect[10] = { 264,26,13,13 };
	missile.bfrRect[11] = { 278,26,11,13 };
	missile.bfrRect[12] = { 290,11,10,14 }; // points down
	missile.bfrRect[13] = { 278,11,11,13 };
	missile.bfrRect[14] = { 264,11,13,13 };
	missile.bfrRect[15] = { 250,11,13,11 };
	// BIGFUCKINGROCKET smoke trail


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
		missile.current_rect = &missile.bfrRect[4];
	}
	else
	{
		missile.ySpeed = 0.0f;
		missile.xSpeed = 0.0f;
		missile.current_rect = &missile.bfrRect[0];
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

void EnemyBigFuckingRocket::Move()
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

void EnemyBigFuckingRocket::Draw()
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
	}


	// MISSILE animation draw -------------------------------------------------------

	//missile.rect = missile.current_animation->GetCurrentFrame();

	//App->render->Blit(enemyTex, position.x - pivotAnimation[pivotIndex + (int)missile.current_animation->current_frame].x, position.y, &missile.rect);

	App->render->Blit(enemyTex, position.x, position.y, missile.current_rect);
	// ------------------------------------------------------------------------------

}


void EnemyBigFuckingRocket::assignAnim()
{

	// LINEAL ANIMS ------------------------------
	// pointing down 
	if (fabs(missile.xSpeed) < 0.5f && (fabs(missile.xSpeed) >= 0.05f) && missile.ySpeed > 0)
	{
		missile.current_rect = &missile.bfrRect[12];
		//pivotIndex = 24;
	}
	// pointing up
	if (fabs(missile.xSpeed) < 0.5f && (fabs(missile.xSpeed) >= 0.05f) && missile.ySpeed < 0)
	{
		missile.current_rect = &missile.bfrRect[4];
		//pivotIndex = 8;
	}
	// pointing right
	if (fabs(missile.ySpeed) < 0.5f && (fabs(missile.ySpeed) >= 0.00f) && missile.xSpeed > 0)
	{
		missile.current_rect = &missile.bfrRect[8];
		//pivotIndex = 16;
	}
	// pointing left
	if (fabs(missile.ySpeed) < 0.5f && (fabs(missile.ySpeed) >= 0.00f) && missile.xSpeed < 0)
	{
		missile.current_rect = &missile.bfrRect[0];
		//pivotIndex = 0;
	}
	// ---------------------------------------------------------------------------
	// TO THE RIGHTS diagonals ---------------------------------------------------
	// UP RIGHT -------------
	//pointing up/right 22.5
	if (missile.xSpeed >= 1.65f && missile.xSpeed <= 1.97f && missile.ySpeed < 0)
	{
		missile.current_rect = &missile.bfrRect[7];
		//pivotIndex = 14;
	}
	// pointing up/right 45
	if (missile.xSpeed >= 1.25f && missile.xSpeed <= 1.65f && missile.ySpeed < 0)
	{
		missile.current_rect = &missile.bfrRect[6];
		//pivotIndex = 12;
	}
	//pointing up/right 66.5
	if (missile.xSpeed >= 0.45f && missile.xSpeed <= 1.25f && missile.ySpeed < 0)
	{
		missile.current_rect = &missile.bfrRect[5];
		//pivotIndex = 10;
	}
	// DOWN/RIGHT  -----------
	//pointing down/right 22.5
	if (missile.xSpeed >= 1.65f && missile.xSpeed <= 1.97f && missile.ySpeed > 0)
	{
		missile.current_rect = &missile.bfrRect[15];
		//pivotIndex = 30;
	}
	// pointing down/right 45
	if (missile.xSpeed >= 1.25f && missile.xSpeed <= 1.65f && missile.ySpeed > 0)
	{
		missile.current_rect = &missile.bfrRect[14];
		//pivotIndex = 28;
	}
	//pointing down/right 66.5
	if (missile.xSpeed >= 0.45f && missile.xSpeed <= 1.25f && missile.ySpeed > 0)
	{
		missile.current_rect = &missile.bfrRect[13];
		//pivotIndex = 26;
	}

	//LEFT DIAGONALS ------------------------------------------------------------------
	// UP cases -------------------
	//pointing up/left 22.5
	if (missile.xSpeed <= -1.65f && missile.xSpeed >= -1.97f && missile.ySpeed < 0)
	{
		missile.current_rect = &missile.bfrRect[1];
		//pivotIndex = 2;
	}
	// pointing up/left 45
	if (missile.xSpeed <= -1.25f && missile.xSpeed >= -1.65f && missile.ySpeed < 0)
	{
		missile.current_rect = &missile.bfrRect[2];
		//pivotIndex = 4;
	}
	//pointing up/left 66.5
	if (missile.xSpeed <= -0.45f && missile.xSpeed >= -1.25f && missile.ySpeed < 0)
	{
		missile.current_rect = &missile.bfrRect[3];
		//pivotIndex = 6;
	}
	// --------------------
	// DOWN cases ----------------
	//pointing down/left 22.5
	if (missile.xSpeed <= -1.65f && missile.xSpeed >= -1.97f && missile.ySpeed > 0)
	{
		missile.current_rect = &missile.bfrRect[9];
		//pivotIndex = 18;
	}
	// pointing down/left 45
	if (missile.xSpeed <= -1.25f && missile.xSpeed >= -1.65f && missile.ySpeed > 0)
	{
		missile.current_rect = &missile.bfrRect[10];
		//pivotIndex = 20;
	}
	//pointing down/left 66.5
	if (missile.xSpeed <= -0.45f && missile.xSpeed >= -1.25f && missile.ySpeed > 0)
	{
		missile.current_rect = &missile.bfrRect[11];
		//pivotIndex = 22;
	}

	//LOG("XSPEED: %f", missile.xSpeed);
	//LOG("YSPEED: %f", missile.ySpeed);

}

void EnemyBigFuckingRocket::chaseThePlayer()
{
	fPoint vector;
	fPoint playerPos;

	playerPos.x = App->player[missile.playerTargetIndex]->position.x;// + 16;
	playerPos.y = App->player[missile.playerTargetIndex]->position.y;// + 12;

	missile.distance = missile.fposition.DistanceTo(playerPos);

	//if (abs((int)missile.xSpeed) <= 0) // if we are approximating of player position

	if (missile.distance <= 5 && !missile.targetReached) // if the player are very close, round it
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

