#include "Application.h"
#include "Enemy.h"
#include "ModuleCollision.h"
#include "ModuleParticles.h"
#include "ModuleRender.h"
#include "ModulePowerUp.h"
//#include "ModuleAudio.h"
//#include "Globals.h"

#include "ModulePlayerUnit.h"

Enemy::Enemy(int x, int y, powerUpTypes type, SDL_Texture* texture) : position(x, y)
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

void Enemy::Draw(SDL_Texture* sprites)
{
	if (collider != nullptr)
		collider->SetPos(position.x, position.y);

	//if (animation != nullptr)
		App->render->Blit(sprites, position.x, position.y, &(animation->GetCurrentFrame()));
}

void Enemy::OnCollision(Collider* collider) //receives the collider wich its colliding (player,shot etc)
{
	App->particles->AddParticle(App->particles->explosion, position.x, position.y,COLLIDER_NONE);
	
}
