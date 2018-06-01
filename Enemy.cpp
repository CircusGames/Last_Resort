#include "Application.h"
#include "Enemy.h"
#include "ModuleCollision.h"
#include "ModuleParticles.h"
#include "ModuleRender.h"
//#include "ModulePowerUp.h"
//#include "ModuleAudio.h"
//#include "Globals.h"

#include "ModulePlayerUnit.h"
//#include "ModuleEnemies.h"

Enemy::Enemy(int x, int y, powerUpTypes type) : position(x, y)
{}

Enemy::~Enemy()
{
	if (collider != nullptr)
	{
		
		//iPoint position, COLLIDER_TYPE collider_type, powerUpTypes type, iPoint speed)
		collider->to_delete = true;

		for (int i = 0; i < MAX_EXTRA_COLLIDERS; ++i)
		{
			if (extraColliders[i] != nullptr)
			{
				extraColliders[i]->to_delete = true;
				extraColliders[i] = nullptr;
			}
		}
		
		if (life <= 0 && enemyType != HOMINGMISSILE && enemyType != BIGFUCKINGROCKET) //only spawn powerup if the enemy is really death
		{
			App->modulePowerUp->SpawnPowerUp(position, powerUpType);
			//App->player[0]->playerScore += enemyScore;
			App->particles->AddParticle(App->particles->explosion, position.x, position.y, COLLIDER_NONE);
			App->enemies->AddEnemy(ENEMY_TYPES::ENEMYPILOT, position.x, position.y, NONE);
		}

		if (enemyType == HOMINGMISSILE || enemyType == BIGFUCKINGROCKET)
		{
			App->particles->AddParticle(App->enemies->homingExplosion, position.x, position.y, COLLIDER_NONE);
		}
	}
	
	
}

const Collider* Enemy::GetCollider() const
{
	return collider;
}

void Enemy::Draw()
{
	//check if the texture is correctly linked, if not, you probably miss the link parameter on especific enemy constructor
	if (enemyTex == nullptr)
		LOG("incorrect enemy texture link");

	if (collider != nullptr) //while the enemy is alive
	{
		collider->SetPos(position.x, position.y); //update collider pos
		App->render->Blit(enemyTex, position.x, position.y, &(animation->GetCurrentFrame())); //and draw texture
	}


	
}

void Enemy::OnCollision(Collider* collider, Collider* collider2) //receives the collider wich its colliding (player,shot etc)
{
	//App->particles->AddParticle(App->particles->explosion, position.x, position.y,COLLIDER_NONE);

}

void Enemy::OnCollisionUnit(Collider* c2, Collider* c1) //receives the collider wich its colliding (player,shot etc)
{

	if (readyToRumble == true) { readyToRumble = false; receiveDamage = true; }
	else
	{
		now_unit_damage_time = SDL_GetTicks() - start_unit_damage_time;
		
		if (now_unit_damage_time >= cadence_unit_damage_time)
			readyToRumble = true;
	}

}

float Enemy::GetNearestPlayerAngle()
{
	LOG("getting nearest player angle");

	float omega = 1.0f;

	return omega;

}

float Enemy::GetNearestPlayerSqrtDistance(fPoint sourcePosition)
{
	//LOG("getting nearest player distance");

	fPoint playerDistance;
	float distanceToNearest;

	player_state playerstate;

	playerDistance.x = App->player[0]->position.x;
	playerDistance.y = App->player[0]->position.y;
	playerstate = App->player[0]->player_step;

	if (sourcePosition.x != NULL && sourcePosition.y != NULL) // if we receive the source position to calculate
	{
		distanceToNearest = sourcePosition.DistanceTo(playerDistance);
	}
	else
		distanceToNearest = fposition.DistanceTo(playerDistance);

	if (App->player[1]->IsEnabled() && App->player[1]->player_step != died) //&& playerstate != player_state::died)
	{
		float distanceToP2;

		playerDistance.x = App->player[1]->position.x;
		playerDistance.y = App->player[1]->position.y;

		if (sourcePosition.x != NULL && sourcePosition.y != NULL)
		{
			distanceToP2 = sourcePosition.DistanceTo(playerDistance);
		}
		else
			distanceToP2 = fposition.DistanceTo(playerDistance);

		if (distanceToP2 < distanceToNearest || App->player[0]->player_step == player_state::died)
		{
			if (App->player[0]->player_step == player_state::died)
				numActivePlayers = 1;//LOG("P2 ENABLED, P1 is death");
			if (App->player[0]->player_step != player_state::died)
				numActivePlayers = 2;//LOG("Player 2 is enabled and are nearest than P1");

			//LOG("P1 distance: %f, P2 distance: %f", distanceToNearest, distanceToP2);

			distanceToNearest = distanceToP2;
			

			// and assign tx,ty

			tx = App->player[1]->position.x - position.x;
			ty = App->player[1]->position.y - position.y;

			// assign enum nearest player, if we need for getTargetPos function
			nearestTarget = nearestPlayer::P2;

			//playerstate = App->player[1]->player_step;

		}
		else//if (playerstate == player_state::died);//two players are in scene, but p1 is nearest than p2
		{
			//LOG("P2 is active, but P1 is nearest than P2");
			//LOG("P1 distance: %f, P2 distance: %f", distanceToNearest, distanceToP2);
			
			//and assign tx,ty
			tx = App->player[0]->position.x - position.x;
			ty = App->player[0]->position.y - position.y;

			// assign enum nearest player, if we need for getTargetPos function
			nearestTarget = nearestPlayer::P1;
			numActivePlayers = 2;
		}

	}
	else //only player1 is active
	{
		//LOG("Only player1 is enabled, distanceToP1: %f", distanceToNearest);
		
		//and assign tx,ty distances and desired module
		tx = App->player[0]->position.x - position.x;
		ty = App->player[0]->position.y - position.y;
		
		// assign enum nearest player, if we need for getTargetPos function
		nearestTarget = nearestPlayer::P1;
		numActivePlayers = 1;
	}

	
	
	return distanceToNearest;

}

float Enemy::GetDesiredTargetDistance(Module* desiredTarget)
{
	float ret;
	fPoint playerDistance;

	if (desiredTarget == App->player[0] ) //|| App->player[1]->player_step != died)
	{
		playerDistance.x = App->player[0]->position.x;
		playerDistance.y = App->player[0]->position.y;

		tx = App->player[0]->position.x - position.x;
		ty = App->player[0]->position.y - position.y;

		ret = fposition.DistanceTo(playerDistance);
	}
	if (desiredTarget == App->player[1] )//|| App->player[0]->player_step != died)
	{
		playerDistance.x = App->player[1]->position.x;
		playerDistance.y = App->player[1]->position.y;

		tx = App->player[1]->position.x - position.x;
		ty = App->player[1]->position.y - position.y;

		ret = fposition.DistanceTo(playerDistance);
	}
	

	return ret;
}

iPoint Enemy::GetTargetPos()
{
	iPoint targetPos;

	GetNearestPlayerSqrtDistance();

	if (nearestTarget == nearestPlayer::P1) targetPos = App->player[0]->position;
	else targetPos = App->player[1]->position;

	return targetPos;
}