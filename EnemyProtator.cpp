#include "Application.h"
#include "EnemyProtator.h"
#include "ModuleCollision.h"
#include "ModuleEnemies.h"

#include "ModulePlayer.h"
#include "ModuleRender.h"

#include "ModuleSceneLvl3.h"

#include "ModulePowerUp.h"

#include "SDL\include\SDL_timer.h"

#include "Player.h"

//#include "Module.h"

EnemyProtator::EnemyProtator(int x, int y, powerUpTypes type, SDL_Texture* thisTexture) : Enemy(x, y)
{
	//links the correct spritesheet texture ----
	enemyTex = thisTexture;
	// -----------------------------------------
	//protator normal animation ----
	protatorAnim.PushBack({ 0,0,32,32 });
	protatorAnim.PushBack({ 33,0,32,30 });
	protatorAnim.PushBack({ 66,0,32,28 });
	protatorAnim.PushBack({ 99,0,32,26 });
	protatorAnim.PushBack({ 132,0,32,26 });
	protatorAnim.PushBack({ 0,33,30,26 });
	protatorAnim.PushBack({ 31,33,32,26 });
	//protatorAnim.PushBack({ 64,33,32,30 });
	//protatorAnim.PushBack({ 97,33,32,26 });
	protatorAnim.PushBack({ 130,33,32,28 });
	protatorAnim.PushBack({ 1,64,32,32 });
	protatorAnim.PushBack({ 34,64,32,32 });
	protatorAnim.PushBack({ 67,64,32,32 });
	protatorAnim.PushBack({ 100,64,32,32 });
	protatorAnim.PushBack({ 133,64,32,32 });
	protatorAnim.speed = 0.125f;
	// ----
	//protator damage animation
	protatorDamageAnim.PushBack({ 0,100,32,32 });
	protatorDamageAnim.PushBack({ 33,100,32,30 });
	protatorDamageAnim.PushBack({ 66,100,32,28 });
	protatorDamageAnim.PushBack({ 99,100,32,26 });
	protatorDamageAnim.PushBack({ 132,100,32,26 });
	protatorDamageAnim.PushBack({ 0,133,30,26 });
	protatorDamageAnim.PushBack({ 31,133,32,26 });
	//protatorAnim.PushBack({ 64,33,32,30 });
	//protatorAnim.PushBack({ 97,33,32,26 });
	protatorDamageAnim.PushBack({ 130,133,32,28 });
	protatorDamageAnim.PushBack({ 1,164,32,32 });
	protatorDamageAnim.PushBack({ 34,164,32,32 });
	protatorDamageAnim.PushBack({ 67,164,32,32 });
	protatorDamageAnim.PushBack({ 100,164,32,32 });
	protatorDamageAnim.PushBack({ 133,164,32,32 });
	protatorDamageAnim.speed = 0.125f;
	// -----------------------

	animation = &protatorAnim; //links animation
	// enemy data ----
	powerUpType = type;
	life = 2;
	enemyScore = 200;
	// ---------------
	fposition.x = x;
	fposition.y = y;

	

	extraColliders[0] = collider = App->collision->AddCollider({ 0, 0, 12, 2 }, COLLIDER_TYPE::COLLIDER_ENEMY, (Module*)App->enemies);
	//lateral colliders
	extraColliders[1] = rightCollider = App->collision->AddCollider({ 0, 0, 16, 30 }, COLLIDER_TYPE::COLLIDER_ENEMY, (Module*)App->enemies);
	extraColliders[2] = leftCollider = App->collision->AddCollider({ 0, 0, 16, 30 }, COLLIDER_TYPE::COLLIDER_ENEMY,(Module*)App->enemies);
	//locked target position
	//targetPos = App->player[0]->position;
	
	//debugWall1 = App->collision->AddCollider({ 0, 200, 50, 300 }, COLLIDER_TYPE::COLLIDER_WALL, (Module*)App->enemies);
	//debugWall2 = App->collision->AddCollider({ 0, 0, 10, 20 }, COLLIDER_TYPE::COLLIDER_WALL, (Module*)App->enemies);

	targetPosReached = false;
	aimed = false;
	propulsion = false;
	goingDown = false;

	maxVelY = -2.5f;

	grounded = true;
	rightCollision = false;
	leftCollision = false;
	ready = false;
	animGrounded = false;
	restartCycle = false;

	current_animation = &protatorAnim;

	preAimedLocalPos = position;

	//timer values
	start_time = SDL_GetTicks();
	aimTime = 800;
	cadence = 500;
	shootSpeed = 2.5f;

	//damage values
	damageAnimTime = 50;

	//substract restriction y variable
	restrictionY = 16;

	//checkValidPlayerY();
	desiredPlayerModule = nullptr;

	toAim = true;
}

void EnemyProtator::Move()
{

	now = SDL_GetTicks() - start_time;

	//checks if the player are on valid Y before start aiming cycle
	
	checkValidPlayerY();

	if (now > aimTime && !ready && toAim)//(App->player[0]->position.y < position.y - 16 ))
	{
		aimed = true;
		toAim = false;
		start_time = SDL_GetTicks();
	}

	if (aimed) //&& (position.x - App->player[0]->position.x) < 200)
	{

		//checkValidPlayerY();
		/*tx = App->player[0]->position.x - position.x;
		ty = App->player[0]->position.y - position.y ;
		fPoint playerDistance;
		playerDistance.x = App->player[0]->position.x;
		playerDistance.y = App->player[0]->position.y;*/
		targetPos = checkValidPlayerY();
		//get sqrt distance
		if (desiredPlayerModule != nullptr)
			distance = GetDesiredTargetDistance(desiredPlayerModule); //GetNearestPlayerSqrtDistance(); //fposition.DistanceTo(playerDistance);
		else
			distance = GetNearestPlayerSqrtDistance(); //fposition.DistanceTo(playerDistance);


		velX = (tx / distance)*2.5f;
		velY = (ty / distance)*2.5f;

		//lastVelY = -2.0f;//velY;
		aimed = false;
		ready = true;

		current_animation->current_frame = 1;

		//preAimedLocalPos = position;
	}

	if (propulsion) //|| leftCollision || rightCollision)
	{

		if (grounded) grounded = false;

		if (position.y - 10 <= targetPos.y) //position - 20
		{
			targetPosReached = true;
		}

		if (targetPosReached)
		{
			//fposition.x += velX;
			if (velY >= -maxVelY)//-lastVelY)
			{
				velY = -maxVelY;//-lastVelY;
			}
			else
			{
				velY += 0.07f;
				if (!goingDown) goingDown = true;
			}

			fposition.y += velY;
			fposition.x += velX;
		}
		else
		{
			//if (leftCollision) 
				//fposition.x += -velX;
			//else
				fposition.x += velX;
			
			fposition.y += velY;
		}

		
	}

	if (rightCollision)
	{
		fposition.x += -velX;
		fposition.x -= 1.0f;
	}
	else if (leftCollision)
	{
		fposition.x += -velX;
		fposition.x += 1.0f;
	}

	if (!grounded) //&& !rightCollision && !leftCollision) 
		fposition.x += 1.0f;
	else //if (grounded && !rightCollision && !leftCollision)
		fposition.x += 0.5f; //little descompensation because player speed

	position.x = fposition.x;
	position.y = fposition.y;

	//set "ground" collider
	if (collider != nullptr)
	collider->SetPos(position.x + 10, position.y - 2);
	//set laterall colliders
	if (rightCollider != nullptr)
	rightCollider->SetPos(position.x + 16, position.y - 32);
	if (leftCollider != nullptr)
	leftCollider->SetPos(position.x, position.y - 32);

	//debugWall1->SetPos(App->player[0]->position.x - 10, 0);

	// shooting ------------------------------------------------------------------------

	if (propulsion)
	{
		//txShot = App->player[0]->position.x - position.x;
		//tyShot = App->player[0]->position.y - position.y;

		//force update for tx, ty
		/*GetNearestPlayerSqrtDistance();

		float omega = atan2f(ty, tx); //tyShot, txShot

		vx = shootSpeed * cos(omega);
		vy = shootSpeed * sin(omega);*/

		nowShotTime = SDL_GetTicks() - start_shot_time;

		if (nowShotTime >= cadence) attack = true;

		if (attack) {
			
			//force update for tx, ty
			GetNearestPlayerSqrtDistance();

			float omega = atan2f(ty, tx); //tyShot, txShot

			vx = shootSpeed * cos(omega);
			vy = shootSpeed * sin(omega);

			App->particles->AddParticle(App->enemies->beeBullet, position.x, position.y - 16, COLLIDER_ENEMY_SHOT, { (int)vx + 1,(int)vy });

			attack = false;
			start_shot_time = SDL_GetTicks();
		}
	}

}

void EnemyProtator::Draw()
{
	if (receiveDamage)
	{
		current_frame = current_animation->current_frame;
		current_animation = &protatorDamageAnim;
		current_animation->current_frame = current_frame;
		receiveDamage = false;
		start_damage_time = SDL_GetTicks();
	}

	nowDamagetime = SDL_GetTicks() - start_damage_time;

	if (nowDamagetime > damageAnimTime)
	{
		current_frame = current_animation->current_frame;
		current_animation = &protatorAnim;
		current_animation->current_frame = current_frame;
	}

	



	SDL_Rect enemyProRect;

	if (!ready) //&& !animGrounded)
	{	

		enemyProRect = current_animation->frames[0];
		App->render->Blit(enemyTex, position.x,position.y - enemyProRect.h, &enemyProRect);

	}
	else if (ready)
	{
		if (!goingDown)
		{
			if (targetPos.x < preAimedLocalPos.x)
			{
				if (current_animation->current_frame >= 10.8f)
				{
					current_animation->current_frame = 9;
				}
			}
			else
			{
				if (current_animation->current_frame >= 8 && current_animation->current_frame < 11)
				{
					current_animation->current_frame = 11;
				}
				if (current_animation->current_frame >= 12.8f)
				{
					current_animation->current_frame = 11;
				}
			}
			if (!propulsion)
			{
				if (current_animation->current_frame >= 7.87f)
				{
					propulsion = true;
					//targetPos = App->player[0]->position;
					//targetPos = GetTargetPos();
					//targetPos = checkValidPlayerY();
					start_shot_time = SDL_GetTicks();
					//start_time = SDL_GetTicks();//checkValidPlayerY();
					
				}

			}

			enemyProRect = current_animation->GetCurrentFrame();
		}
		else
		{
			if(targetPos.x < preAimedLocalPos.x)
				enemyProRect = current_animation->frames[8];
			else
				enemyProRect = current_animation->frames[0];
		}
		App->render->Blit(enemyTex, position.x, position.y - enemyProRect.h, &enemyProRect);
	}

}

void EnemyProtator::OnCollision(Collider* collider, Collider* collider2)
{

	if (collider->type == COLLIDER_PLAYER_SHOT)
		receiveDamage = true;


	if (!grounded && collider->type != COLLIDER_PLAYER_SHOT)
	{
		if (collider2 == this->collider)
		{
			LOG("autoCollision");
		}
		if (collider2 == this->leftCollider)
		{
			if (!leftCollision)
			{
				LOG("leftCollision");
				leftCollision = true;
				rightCollision = false;
				targetPosReached = true;
			}
		}
		if (collider2 == this->rightCollider)
		{
			if (!rightCollision)
			{
				LOG("rightCollision");
				rightCollision = true;
				leftCollision = false;
				targetPosReached = true;
			}
		}

		if (collider2 == this->collider)
		{
			rightCollision = false;
			leftCollision = false;
			aimed = false;
			propulsion = false;
			goingDown = false;
			targetPosReached = false;
			grounded = true;

			if (collider->callback == App->scene_lvl3) //if collider pertains a scenelvl3 == walls,floor etc
				fposition.y = collider->rect.y;  //- 1//update the enemy position to avoid false onCollisions

			preAimedLocalPos = position;

			//start_time = SDL_GetTicks();
			ready = false;

			//animGrounded = true;
		}

	}
	
}

const Collider* EnemyProtator::GetCollider() const
{
	return extraColliders[collisionColliderIndex];
}

EnemyProtator::~EnemyProtator()
{
	if (collider != nullptr)
	{
		collider->to_delete = true;

		for (int i = 0; i < MAX_EXTRA_COLLIDERS; ++i)
		{
			if (extraColliders[i] != nullptr)
			{
				extraColliders[i]->to_delete = true;
				extraColliders[i] = nullptr;
			}
		}

		if (life <= 0) //only spawn powerup if the enemy is really death
		{
			position.y -= 30;
			position.x += 16;
			App->modulePowerUp->SpawnPowerUp(position, powerUpType);
			App->player[0]->playerScore += enemyScore;
			App->particles->AddParticle(App->particles->explosion, position.x - 8, position.y, COLLIDER_NONE);
			collider = nullptr; //avoid double enemy destructor heritance
		}

		//delete this->enemyTex;
		//enemyTex = nullptr;
	}

}

iPoint EnemyProtator::checkValidPlayerY()
{
	
	iPoint ret;// = targetPos;
	
	toAim = false;

	//if player 2 is disabled and position of player1 is valid and not death return P1 position
	if (!App->player[1]->IsEnabled() && App->player[0]->position.y < position.y - 16 && App->player[0]->player_step != died)
	{
		ret = App->player[0]->position;
		desiredPlayerModule = App->player[0];
		toAim = true;
	}
	else if (App->player[1]->IsEnabled()) //&& App->player[1]->player_step != player_state::died)
	{

		if (App->player[0]->position.y < position.y - 16 && App->player[1]->position.y > position.y - 16)
		{
			if (App->player[0]->player_step != died)
			{
				ret = App->player[0]->position;
				desiredPlayerModule = App->player[0];
				toAim = true;
			}
			else
			{
				ret = GetTargetPos();//App->player[0]->position;
				desiredPlayerModule = nullptr;
			}
		}
		if (App->player[1]->position.y < position.y - 16 && App->player[0]->position.y > position.y - 16)
		{
			if (App->player[1]->player_step != died)
			{
			ret = App->player[1]->position;
			desiredPlayerModule = App->player[1];
			toAim = true;
			}
			else
			{
				ret = GetTargetPos();//App->player[0]->position;
				desiredPlayerModule = nullptr;
			}
			//toAim = true;
		}
		//else
			//toAim = false;

		if (App->player[0]->position.y > position.y - 16 && (App->player[1]->position.y > position.y - 16)) //ok
		{
			toAim = false;
		}
		if (App->player[0]->position.y < position.y - 16 && (App->player[1]->position.y < position.y - 16)) //ok
		{
			ret = GetTargetPos();
			desiredPlayerModule = nullptr;
			toAim = true;
		}
	}
	else
		toAim = false;

	return ret;

}