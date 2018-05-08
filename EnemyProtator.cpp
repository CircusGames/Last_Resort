#include "Application.h"
#include "EnemyProtator.h"
#include "ModuleCollision.h"
#include "ModuleEnemies.h"

#include "ModulePlayer.h"
#include "ModuleRender.h"

#include "ModuleSceneLvl3.h"

#include "ModulePowerUp.h"

#include "SDL\include\SDL_timer.h"

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
	//targetPos = App->player->position;
	
	//debugWall1 = App->collision->AddCollider({ 0, 200, 50, 300 }, COLLIDER_TYPE::COLLIDER_WALL, (Module*)App->enemies);
	//debugWall2 = App->collision->AddCollider({ 0, 0, 10, 20 }, COLLIDER_TYPE::COLLIDER_WALL, (Module*)App->enemies);

	targetPosReached = false;
	aimed = false;
	propulsion = false;
	goingDown = false;

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

}

void EnemyProtator::Move()
{

	now = SDL_GetTicks() - start_time;

	if (now > aimTime && !ready && App->player->position.y < position.y - 16)
	{
		aimed = true;
		start_time = SDL_GetTicks();
	}

	

	if (aimed) //&& (position.x - App->player->position.x) < 200)
	{
		tx = App->player->position.x - position.x;
		ty = App->player->position.y - position.y ;
		fPoint playerDistance;
		playerDistance.x = App->player->position.x;
		playerDistance.y = App->player->position.y;

		//get sqrt distance
		distance = fposition.DistanceTo(playerDistance);

		velX = (tx / distance)*2.5f;
		velY = (ty / distance)*2.5f;

		lastVelY = velY;
		aimed = false;
		ready = true;

		current_animation->current_frame = 1;

		//preAimedLocalPos = position;
	}

	if (propulsion) //|| leftCollision || rightCollision)
	{

		if (grounded) grounded = false;

		if (position.y - 20 <= targetPos.y)
		{
			targetPosReached = true;
		}

		if (targetPosReached)
		{
			fposition.x += velX;
			if (velY >= -lastVelY)
			{
				velY = -lastVelY;
			}
			else
			{
				velY += 0.07f;
				if (!goingDown) goingDown = true;
			}

			fposition.y += velY;
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
	collider->SetPos(position.x + 10, position.y - 2);
	//set laterall colliders
	rightCollider->SetPos(position.x + 16, position.y - 32);
	leftCollider->SetPos(position.x, position.y - 32);

	//debugWall1->SetPos(App->player->position.x - 10, 0);

	// shooting ------------------------------------------------------------------------

	if (propulsion)
	{
		txShot = App->player->position.x - position.x;
		tyShot = App->player->position.y - position.y;

		float omega = atan2f(tyShot, txShot);

		vx = shootSpeed * cos(omega);
		vy = shootSpeed * sin(omega);

		nowShotTime = SDL_GetTicks() - start_shot_time;

		if (nowShotTime >= cadence) attack = true;

		if (attack) {

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
					targetPos = App->player->position;
					start_shot_time = SDL_GetTicks();
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

		for (int i = 0; i < 10; ++i)
		{
			if (extraColliders[i] != nullptr)
				extraColliders[i]->to_delete = true;
		}

		if (life <= 0) //only spawn powerup if the enemy is really death
		{
			position.y -= 32;
			App->modulePowerUp->SpawnPowerUp(position, powerUpType);
			App->player->playerScore += enemyScore;
		}
	}

}