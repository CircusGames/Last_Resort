#include "Application.h"
#include "EnemySubmarine.h"
#include "ModuleCollision.h"
#include "ModuleEnemies.h"
//#include "ModulePlayer.h"
#include "ModuleRender.h"

#include "ModuleSceneLvl3.h"

#include "ModulePowerUp.h"

#include "SDL\include\SDL_timer.h"

#include "Player.h"

EnemySubmarine::EnemySubmarine(int x, int y, powerUpTypes type, SDL_Texture* thisTexture) : Enemy(x, y)
{
	// assigns type to despawn check of moduleEnemies
	enemyType = ENEMY_TYPES::SUBMARINE;
	//links the correct spritesheet texture ----
	enemyTex = thisTexture;
	// -----------------------------------------
	// enemy parts / animations
	submarineBodyRect = { 0,0,456,112 };
	submarineBodyDamageRect = {0,138,456,112};


	
	//animation = &nameAnim; //links animation
	
	// enemy data ----
	powerUpType = type;
	life = 1;
	enemyScore = 1200;
	// ---------------
	//fposition.x = x;
	//fposition.y = y;

	//extraColliders[0] = collider = App->collision->AddCollider({ 0, 0, 12, 2 }, COLLIDER_TYPE::COLLIDER_ENEMY, (Module*)App->enemies);
	//lateral colliders
	//extraColliders[1] = rightCollider = App->collision->AddCollider({ 0, 0, 16, 30 }, COLLIDER_TYPE::COLLIDER_ENEMY, (Module*)App->enemies);
	//extraColliders[2] = leftCollider = App->collision->AddCollider({ 0, 0, 16, 30 }, COLLIDER_TYPE::COLLIDER_ENEMY, (Module*)App->enemies);
}

void EnemySubmarine::Move()
{



	position.x += 1;
}

void EnemySubmarine::Draw()
{
	/*if (receiveDamage)
	{
		current_frame = current_animation->current_frame;
		current_animation = &damageAnim;
		current_animation->current_frame = current_frame;
		receiveDamage = false;
		start_damage_time = SDL_GetTicks();
	}

	nowDamagetime = SDL_GetTicks() - start_damage_time;

	if (nowDamagetime > damageAnimTime)
	{
		current_frame = current_animation->current_frame;
		current_animation = &normalAnim;
		current_animation->current_frame = current_frame;
	}*/


	App->render->Blit(enemyTex, position.x,0, &submarineBodyRect);

}

void EnemySubmarine::OnCollision(Collider* collider, Collider* collider2)
{

	//if (collider->type == COLLIDER_PLAYER_SHOT)
		// structure data -> receiveDamage = true;
}

const Collider* EnemySubmarine::GetCollider() const
{
	return extraColliders[collisionColliderIndex];
}

EnemySubmarine::~EnemySubmarine()
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
			//position.y -= 30;
			//position.x += 16;
			//App->player[0]->playerScore += enemyScore;
			//App->particles->AddParticle(App->particles->explosion, position.x - 8, position.y, COLLIDER_NONE);
			//collider = nullptr; //avoid double enemy destructor heritance
		}

		//delete this->enemyTex;
		//enemyTex = nullptr;
	}

}