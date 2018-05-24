#include "Application.h"
#include "EnemyMiniTank.h"
#include "ModuleCollision.h"
#include "Globals.h"
#include "ModuleEnemies.h"
#include "SDL\include\SDL_timer.h"
#include "Path.h"
#include "ModuleRender.h"

Enemy_MiniTank::Enemy_MiniTank(int x, int y, powerUpTypes type, SDL_Texture* thisTexture) : Enemy(x, y)
{

	//Missiles Animation
	/*missilelaunch.PushBack({ 0,110,21,16 });
	missilelaunch.PushBack({ 22,110,21,24 });
	missilelaunch.PushBack({ 44,110,27,29 });
	missilelaunch.PushBack({ 72,110,28,31 });
	missilelaunch.PushBack({ 103,110,30,32 });
	missilelaunch.PushBack({ 134,110,31,32 });
	missilelaunch.PushBack({ 166,110,32,32 });
	missilelaunch.PushBack({ 199,110,32,31 });
	missilelaunch.PushBack({ 232,110,31,30 });
	missilelaunch.PushBack({ 264,110,30,16 });
	missilelaunch.PushBack({ 0,143,19,12 });
	missilelaunch.PushBack({ 25,143,23,15 });

	missileexplode.PushBack({ 0,171,23,19 });
	missileexplode.PushBack({ 24,163,25,17 });
	missileexplode.PushBack({ 50,160,30,30 });
	missileexplode.PushBack({ 114,161,25,29 });
	missileexplode.PushBack({ 140,159,28,31 });
	missileexplode.PushBack({ 170,159,30,31 });
	missileexplode.PushBack({ 201,159,32,31 });
	missileexplode.PushBack({ 233,161,30,29 });
	missileexplode.PushBack({ 264,163,29,27 });*/

	/*missile.PushBack({ 184,11,10,14 });//0º Mira hacia arriba
	missile.PushBack({ 195,11,11,13 });//22'5º
	missile.PushBack({ 207,11,13,13 });//45º
	missile.PushBack({ 221,11,13,11 });//67'5º
	missile.PushBack({ 235,13,14,10 });//90º
	missile.PushBack({ 250,11,13,11 });//112'5º
	missile.PushBack({ 264,11,13,13 });//135º
	missile.PushBack({ 278,11,11,13 });//157'5º
	missile.PushBack({ 290,11,10,14 });//180º
	missile.PushBack({ 278,26,11,13 });//202'5º
	missile.PushBack({ 264,26,13,13 });//225º
	missile.PushBack({ 250,26,13,11 });//247'5º
	missile.PushBack({ 235,26,14,10 });//270º
	missile.PushBack({ 221,26,13,11 });//292'5º
	missile.PushBack({ 207,26,13,13 });//315º
	missile.PushBack({ 195,26,10,14 });//337'5º*/

	/*fire.PushBack({ 221,84,16,16 });
	fire.PushBack({ 238,84,12,12 });
	fire.PushBack({ 251,84,8,8 });
	fire.PushBack({ 260,84,6,6 });
	fire.speed = 0.5f;*/

	/*missilesmoke.PushBack({ 314,164,13,14 });
	missilesmoke.PushBack({ 339,164,15,14 });
	missilesmoke.PushBack({ 366,164,16,16 });
	missilesmoke.PushBack({ 394,164,14,16 });
	missilesmoke.PushBack({ 420,164,15,14 });
	missilesmoke.PushBack({ 447,164,15,14 });*/

	// -----------------------------------------------------------------
	enemyTex = thisTexture; // links enemy to correct texture

	powerUpType = type; // assigns receveid powerup

	//original_pos.x = x;
	//original_pos.y = y;

	life = 17;

	// animations ------------------------------------------------------------------------------
	// 
	// normal anim up 8 frames, 4 and 4 ---
	cartePillar.moveAnim[NORMAL_ANIM].PushBack({61,11,61,48}); // wheels 1 || 4 frames
	cartePillar.moveAnim[NORMAL_ANIM].PushBack({ 122,11,61,48 }); // wheels 2 || 4 frames
	cartePillar.moveAnim[NORMAL_ANIM].PushBack({ 0,11,61,48 }); // wheels down || 4 frames
	cartePillar.moveAnim[NORMAL_ANIM].speed = 0.25f;
	// ------------------------------------
	// shooting animation ---
	cartePillar.shootAnim[NORMAL_ANIM].PushBack({ 301,64,61,52 }); // mid up 4 frames
	cartePillar.shootAnim[NORMAL_ANIM].PushBack({ 301,11,61,52 }); // top up 4 frames
	for (int i = 0; i < 6; ++i)
		cartePillar.shootAnim[NORMAL_ANIM].PushBack({ 301,117,61,52 }); // top down 24 frames
	cartePillar.shootAnim[NORMAL_ANIM].speed = 0.25f;
	cartePillar.shootAnim[NORMAL_ANIM].repeat = false;
	// ------------------------------------
	// dust particles animation 4 frames per each
	cartePillar.dustAnim.PushBack({ 184,40,4,9 });
	cartePillar.dustAnim.PushBack({ 193,44,7,6 });
	cartePillar.dustAnim.PushBack({ 208,40,7,9 });
	cartePillar.dustAnim.PushBack({ 223,40,10,9 });
	cartePillar.dustAnim.PushBack({ 241,40,11,8 });
	cartePillar.dustAnim.PushBack({ 261,40,12,9 });
	cartePillar.dustAnim.PushBack({ 280,40,6,10 });
	cartePillar.dustAnim.speed = 0.25f;
	// ------------------------------------
	// ------------------------------------------------------------------------------------------
	// needed values ----------------------
	// set the initial direction of movement
	cartePillar.moveLeft = true;
	// set start time for the shooting timer
	cartePillar.start_shot_time = SDL_GetTicks();

	// COLLIDERS
	//collider = App->collision->AddCollider({ 0, 0, 61, 48 }, COLLIDER_TYPE::COLLIDER_ENEMY, (Module*)App->enemies);
	cartePillar.leftCol = extraColliders[0] = App->collision->AddCollider({ 0, 0, 30, 20 }, COLLIDER_TYPE::COLLIDER_ENEMY, (Module*)App->enemies);
	cartePillar.rightCol = extraColliders[1] = App->collision->AddCollider({ 0, 0, 30, 20 }, COLLIDER_TYPE::COLLIDER_ENEMY, (Module*)App->enemies);

	// positions ------------------------------------------------
	position.x = x;
	position.y = y;
	// assigns position to cartepillar data
	cartePillar.position = position;
	cartePillar.fposition.x = cartePillar.position.x;
	cartePillar.fposition.y = cartePillar.position.y;
	// 
	cartePillar.initialTravelPosition = cartePillar.position;
	// -----------------------------------------------------------
	cartePillar.start_travel_time = SDL_GetTicks();
	cartePillar.start_shot_time = SDL_GetTicks();

	// assigns first current animation pointer
	cartePillar.current_animation = cartePillar.moveAnim;

}

void Enemy_MiniTank::Move()
{
	
	

	// checks the direction and assigns movement speed
	if (!cartePillar.shoot)
	{
		if (cartePillar.moveLeft)
		{
			//cartePillar.fposition.x += 1; // scroll speed compensation
			cartePillar.fposition.x -= cartePillar.xSpeed; // moves to the left with -1 ( scroll ) + xSpeed
		}
		else
		{
			cartePillar.fposition.x += 1; // scroll speed compensation
			cartePillar.fposition.x += cartePillar.xSpeed + 0.6f; // + 1 for scroll speed
		}
	}

	// swaps direction when max travel distance is reached - with the scroll this workaround is meh -----
	// changed distance to time check, changed already to false distance
	if (cartePillar.currentTraveledDistance > cartePillar.maxTravelDistance || cartePillar.leftCollision || cartePillar.rightCollision)
	{
		if (cartePillar.moveLeft) cartePillar.moveLeft = false;
		else
			cartePillar.moveLeft = true;

		if (cartePillar.leftCollision || cartePillar.rightCollision)
		{
			if (cartePillar.firstCollision)
				cartePillar.currentTraveledDistance = cartePillar.maxTravelDistance - 10; // to retrocess movement falsification
			else
				cartePillar.currentTraveledDistance = 0;
		}
		else
			cartePillar.currentTraveledDistance = 0;

		// deactivate the collisions
		cartePillar.leftCollision = false;
		cartePillar.rightCollision = false;
		
	}
	// --------------------------------------------------------------------------------------------------

	//cartePillar.currentTraveledDistance += 1.0f; // false travel distance to avoid scroll descompensation...
	//cartePillar.position.x = cartePillar.fposition.x;

	// updates general position
	if (!cartePillar.shoot) // while move
	{
		if (cartePillar.moveLeft)
			cartePillar.currentTraveledDistance += 1.0f; // false travel distance to avoid scroll descompensation...
		if(!cartePillar.moveLeft)
			cartePillar.currentTraveledDistance += 1.6f; // 1 for compensate scroll + 0.6 per speed
		cartePillar.position.x = cartePillar.fposition.x;
		position.x = cartePillar.position.x;
	}
	else // while shooting
	{	// travel distance is equal to foreground speed
		cartePillar.currentTraveledDistance -= 0.5f; // false travel distance to avoid scroll descompensation...
		cartePillar.fposition.x += 0.5f; // foreground speed "static" to it
		position.x = cartePillar.fposition.x;
		cartePillar.position = position;
	}

	LOG("travelDistance: %f", cartePillar.currentTraveledDistance);

	// shoot timer ------------------------
	cartePillar.now_shot_time = SDL_GetTicks() - cartePillar.start_shot_time;
	if (cartePillar.now_shot_time > cartePillar.cadence_between_shots)
	{
		cartePillar.shoot = true;
	}


	// update collider position
	if (collider != nullptr)
		collider->SetPos(position.x, position.y);
	if (cartePillar.leftCol != nullptr)
		cartePillar.leftCol->SetPos(position.x, position.y - 30);
	if (cartePillar.rightCol != nullptr)
		cartePillar.rightCol->SetPos(position.x + 31, position.y - 30);

}


void Enemy_MiniTank::Draw()
{

	if (cartePillar.shoot)
	{
		cartePillar.current_animation = cartePillar.shootAnim;
	}
	else
		cartePillar.current_animation = cartePillar.moveAnim;

	// checks if the shoot anim is finish and swaps
	if (cartePillar.shootAnim->finish)
	{
		cartePillar.current_animation = cartePillar.moveAnim;
		cartePillar.shoot = false;
		cartePillar.start_shot_time = SDL_GetTicks();
		// restart values for shot animation
		cartePillar.shootAnim->current_frame = 0;
		cartePillar.shootAnim->finish = false;
	}

	cartePillar.rect = cartePillar.current_animation->GetCurrentFrame();

	App->render->Blit(enemyTex, position.x, position.y - cartePillar.rect.h, &cartePillar.rect);
	
}

const Collider* Enemy_MiniTank::GetCollider() const
{
	return extraColliders[collisionColliderIndex];
}

void Enemy_MiniTank::OnCollision(Collider* collider, Collider* collider2)
{
	// left collision detection
	if (collider2 == cartePillar.leftCol && collider->type == COLLIDER_WALL)
	{
		LOG("LEFT COLLISION");
		cartePillar.leftCollision = true;
		if (cartePillar.firstCollision) cartePillar.firstCollision = false;
		else cartePillar.firstCollision = true;

		cartePillar.fposition.x = collider->rect.x + collider->rect.w + 3; // some position trick to avoid false collisions
	}
	// right collision detection
	if (collider2 == cartePillar.rightCol && collider->type == COLLIDER_WALL)
	{
		LOG("RIGHT COLLISION");
		cartePillar.rightCollision = true;
		if (cartePillar.firstCollision) cartePillar.firstCollision = false;
		else cartePillar.firstCollision = true;

		cartePillar.fposition.x = collider->rect.x - 64; // some position trick to avoid false collisions
	}



}