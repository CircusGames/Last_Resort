#include "Application.h"
#include "Enemy.h"
#include "ModuleCollision.h"
#include "ModuleParticles.h"
#include "ModuleRender.h"
#include "ModulePowerUp.h"
//#include "ModuleAudio.h"
//#include "Globals.h"

#include "ModulePlayerUnit.h"

Enemy::Enemy(int x, int y, powerUpTypes type) : position(x, y)
{}

Enemy::~Enemy()
{
	if (collider != nullptr)
	{
		
		//iPoint position, COLLIDER_TYPE collider_type, powerUpTypes type, iPoint speed)
		collider->to_delete = true;
		
		if (life <= 0) //only spawn powerup if the enemy is really death
		{
			App->modulePowerUp->SpawnPowerUp(position, powerUpType);
			App->player->playerScore += enemyScore;
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

void Enemy::OnCollision(Collider* collider) //receives the collider wich its colliding (player,shot etc)
{
	App->particles->AddParticle(App->particles->explosion, position.x, position.y,COLLIDER_NONE);
	
}
