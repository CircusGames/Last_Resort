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
	// enemy parts / animations data
	// body
	submarineBodyRect = { 0,0,456,112 };
	submarineBodyDamageRect = {0,138,456,112};
	// non destroyed static parts
	// part1
	nonDestroyedParts[0].rect = { 16,112,32,12 };
	nonDestroyedParts[0].position = { 16, 84 };
	// part2
	nonDestroyedParts[1].rect = { 48,113,32,12 };
	nonDestroyedParts[1].position = { 48, 84 };
	// part3
	nonDestroyedParts[2].rect = { 80,112,32,12 };
	nonDestroyedParts[2].position = { 80, 84 };
	// part4
	nonDestroyedParts[3].rect = { 128,112,32,16 };
	nonDestroyedParts[3].position = { 128, 80 };
	// part5
	nonDestroyedParts[4].rect = { 165,112,27,16 };
	nonDestroyedParts[4].position = { 165, 64 };
	// part6 (ejectable enemy part static frame)
	nonDestroyedParts[5].rect = { 457,0,60,32 };
	nonDestroyedParts[5].position = { 196, 16 };
	// part7  (missile launcher part middle position)
	nonDestroyedParts[6].rect = { 459,66,64,32 };
	nonDestroyedParts[6].position = { 208, 48 };
	// part8
	nonDestroyedParts[7].rect = { 288,112,24,8 };
	nonDestroyedParts[7].position = { 288, 56 };
	// part9
	nonDestroyedParts[8].rect = { 304,121,32,16 };
	nonDestroyedParts[8].position = { 304, 64 };
	// part9
	nonDestroyedParts[9].rect = { 336,112,32,16 };
	nonDestroyedParts[9].position = { 336, 72 };


	// destroyed parts animations
	destroyedParts[0].PushBack({ 457,197,96,12 });
	destroyedParts[0].PushBack({ 457,227,96,12 });
	destroyedParts[0].PushBack({ 457,257,96,12 });
	destroyedParts[0].PushBack({ 457,287,96,12 });
	destroyedParts[0].PushBack({ 457,317,96,12 });
	destroyedParts[0].PushBack({ 457,287,96,12 });
	destroyedParts[0].PushBack({ 457,257,96,12 });
	destroyedParts[0].PushBack({ 457,227,96,12 });
	destroyedParts[0].speed = 0.125f;

	destroyedParts[1].PushBack({ 569,193,32,16 });
	destroyedParts[1].PushBack({ 569,223,32,16 });
	destroyedParts[1].PushBack({ 569,253,32,16 });
	destroyedParts[1].PushBack({ 569,283,32,16 });
	destroyedParts[1].PushBack({ 569,313,32,16 });
	destroyedParts[1].PushBack({ 569,283,32,16 });
	destroyedParts[1].PushBack({ 569,253,32,16 });
	destroyedParts[1].PushBack({ 569,223,32,16 });
	destroyedParts[1].speed = 0.125f;

	destroyedParts[2].PushBack({ 609,178,24,15 });
	destroyedParts[2].PushBack({ 609,208,24,15 });
	destroyedParts[2].PushBack({ 609,238,24,15 });
	destroyedParts[2].PushBack({ 609,268,24,15 });
	destroyedParts[2].PushBack({ 609,298,24,15 });
	destroyedParts[2].PushBack({ 609,268,24,15 });
	destroyedParts[2].PushBack({ 609,238,24,15 });
	destroyedParts[2].PushBack({ 609,208,24,15 });
	destroyedParts[2].speed = 0.125f;

	destroyedParts[3].PushBack({ 649,132,48,29 });
	destroyedParts[3].PushBack({ 649,162,48,29 });
	destroyedParts[3].PushBack({ 649,192,48,29 });
	destroyedParts[3].PushBack({ 649,222,48,29 });
	destroyedParts[3].PushBack({ 649,252,48,29 });
	destroyedParts[3].PushBack({ 649,222,48,29 });
	destroyedParts[3].PushBack({ 649,192,48,29 });
	destroyedParts[3].PushBack({ 649,162,48,29 });
	destroyedParts[3].speed = 0.125f;

	destroyedParts[4].PushBack({ 729,169,80,24 });
	destroyedParts[4].PushBack({ 729,199,80,24 });
	destroyedParts[4].PushBack({ 729,229,80,24 });
	destroyedParts[4].PushBack({ 729,259,80,24 });
	destroyedParts[4].PushBack({ 729,289,80,24 });
	destroyedParts[4].PushBack({ 729,259,80,24 });
	destroyedParts[4].PushBack({ 729,229,80,24 });
	destroyedParts[4].PushBack({ 729,199,80,24 });
	destroyedParts[4].speed = 0.125f;

	
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

	position.x = -150;
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


	App->render->Blit(enemyTex, position.x, position.y, &submarineBodyRect);

	// draw destroyed parts
	for (int i = 0; i < NUM_DESTROYABLE_PARTS; ++i)
	{
		App->render->Blit(enemyTex, position.x + positionPartsX[i], position.y + positionPartsY[i], &destroyedParts[i].GetCurrentFrame());
	}

	// draw non destroyed static parts
	for (int i = 0; i < 10; ++i)
	App->render->Blit(enemyTex, position.x + nonDestroyedParts[i].position.x, position.y + nonDestroyedParts[i].position.y , &nonDestroyedParts[i].rect);

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