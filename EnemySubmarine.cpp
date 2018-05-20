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

#include "ModuleAudio.h"

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
	submarineBodyDamageRect = { 0,138,456,112 };
	// non destroyed static parts ----
	// part1
	nonDestroyedParts[0].normalRect = { 16,112,32,12 };
	nonDestroyedParts[0].takenDamageRect = { 16,250, 32,12 };
	nonDestroyedParts[0].position = { 16, 84 };
	// part2
	nonDestroyedParts[1].normalRect = { 48,113,32,12 };
	nonDestroyedParts[1].takenDamageRect = { 48,251,32,12 };
	nonDestroyedParts[1].position = { 48, 84 };
	// part3
	nonDestroyedParts[2].normalRect = { 80,112,32,12 };
	nonDestroyedParts[2].takenDamageRect = { 80,250,32,12 };
	nonDestroyedParts[2].position = { 80, 84 };
	// part4
	nonDestroyedParts[3].normalRect = { 128,112,32,16 };
	nonDestroyedParts[3].takenDamageRect = { 128,251, 32,16 };
	nonDestroyedParts[3].position = { 128, 80 };
	// part5
	nonDestroyedParts[4].normalRect = { 165,112,27,16 };
	nonDestroyedParts[4].takenDamageRect = { 165,250, 27,16 };
	nonDestroyedParts[4].position = { 165, 64 };
	// part6 (ejectable enemy part static frame)
	//nonDestroyedParts[5].normalRect = { 457,0,60,32 };
	//nonDestroyedParts[5].takenDamageRect = { 457,33,60,32 };
	//nonDestroyedParts[5].position = { 196, 16 };
	//nonDestroyedParts[5].life = 10;
	// part7  (missile launcher part middle position static frame)
	nonDestroyedParts[6].normalRect = { 459,66,64,32 };
	nonDestroyedParts[6].takenDamageRect = { 459,99,64,32 };
	nonDestroyedParts[6].position = { 208, 48 };
	// part8
	nonDestroyedParts[7].normalRect = { 288,112,24,8 };
	nonDestroyedParts[7].takenDamageRect = { 288,250,24,8 };
	nonDestroyedParts[7].position = { 288, 56 };
	// part9
	nonDestroyedParts[8].normalRect = { 304,121,32,16 };
	nonDestroyedParts[8].takenDamageRect = { 304,259,32,16 };
	nonDestroyedParts[8].position = { 304, 64 };
	// part9
	nonDestroyedParts[9].normalRect = { 336,112,32,16 };
	nonDestroyedParts[9].takenDamageRect = { 336,250,32,16 };
	nonDestroyedParts[9].position = { 336, 72 };
	// add colliders to each part
	for (int i = 0; i < NUM_NONDESTROYED_PARTS; ++i)
	{
		if (nonDestroyedParts[i].collider == nullptr)
			nonDestroyedParts[i].collider = extraColliders[i] = App->collision->AddCollider(nonDestroyedParts[i].normalRect, COLLIDER_ENEMY, (Module*)App->enemies);
	}
	// --------------------------------------------------

	// destroyed parts animations -----------------------
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
	// ------------------------------------------------

	// destroyable parts animations ( enemy ejection hatch and missile platforms launchers)
	// ejection hatch anim
	ejectionHatch.anim[NORMAL_ANIM].PushBack({ 457, 0, 60 ,32 });
	ejectionHatch.anim[NORMAL_ANIM].PushBack({ 520, 0, 60 ,32 });
	ejectionHatch.anim[NORMAL_ANIM].PushBack({ 588, 0, 60 ,32 });
	ejectionHatch.anim[NORMAL_ANIM].PushBack({ 656, 0, 60 ,32 }); // max open
	ejectionHatch.anim[NORMAL_ANIM].PushBack({ 588, 0, 60 ,32 });
	ejectionHatch.anim[NORMAL_ANIM].PushBack({ 520, 0, 60 ,32 });
	ejectionHatch.anim[NORMAL_ANIM].PushBack({ 457, 0, 60 ,32 }); // initial frame
	ejectionHatch.anim[NORMAL_ANIM].speed = 0.125f;
	ejectionHatch.anim[NORMAL_ANIM].repeat = false;
	ejectionHatch.anim[DAMAGE_ANIM].PushBack({ 457, 33, 60, 32 });
	ejectionHatch.anim[DAMAGE_ANIM].PushBack({ 520, 33, 60, 32 });
	ejectionHatch.anim[DAMAGE_ANIM].PushBack({ 588, 33, 60, 32 });
	ejectionHatch.anim[DAMAGE_ANIM].PushBack({ 656, 33, 60, 32 }); // max open
	ejectionHatch.anim[DAMAGE_ANIM].PushBack({ 588, 33, 60, 32 });
	ejectionHatch.anim[DAMAGE_ANIM].PushBack({ 520, 33, 60, 32 });
	ejectionHatch.anim[DAMAGE_ANIM].PushBack({ 457, 33, 60, 32 }); // initial frame
	ejectionHatch.anim[DAMAGE_ANIM].speed = 0.125f;
	ejectionHatch.anim[DAMAGE_ANIM].repeat = false;
	ejectionHatch.position = { 196, 16 };
	ejectionHatch.collider = extraColliders[13] = App->collision->AddCollider({0,0, 60,32}, COLLIDER_ENEMY, (Module*)App->enemies);
	ejectionHatch.life = 5;
	// missiles platforms launchers anim
	missileLauncherAnim[0][NORMAL_ANIM].PushBack({ 459,66,64,32 });
	missileLauncherAnim[0][NORMAL_ANIM].PushBack({ 524,66,64,32 });
	missileLauncherAnim[0][NORMAL_ANIM].PushBack({ 589,66,64,32 });
	missileLauncherAnim[0][NORMAL_ANIM].PushBack({ 654,66,64,32 }); // max open
	missileLauncherAnim[0][NORMAL_ANIM].PushBack({ 589,66,64,32 }); // returning to 0 pos
	missileLauncherAnim[0][NORMAL_ANIM].PushBack({ 524,66,64,32 });
	missileLauncherAnim[0][NORMAL_ANIM].PushBack({ 459,66,64,32 });
	missileLauncherAnim[0][NORMAL_ANIM].speed = 0.125f;
	missileLauncherAnim[0][DAMAGE_ANIM].PushBack({ 459,99,64,32 });
	missileLauncherAnim[0][DAMAGE_ANIM].PushBack({ 524,99,64,32 });
	missileLauncherAnim[0][DAMAGE_ANIM].PushBack({ 589,99,64,32 });
	missileLauncherAnim[0][DAMAGE_ANIM].PushBack({ 654,99,64,32 }); // max open
	missileLauncherAnim[0][DAMAGE_ANIM].PushBack({ 589,99,64,32 });
	missileLauncherAnim[0][DAMAGE_ANIM].PushBack({ 524,99,64,32 });
	missileLauncherAnim[0][DAMAGE_ANIM].PushBack({ 459,99,64,32 }); // initial pos
	missileLauncherAnim[0][DAMAGE_ANIM].speed = 0.125f;


	
	//animation = &nameAnim; //links animation
	
	// enemy data ----
	powerUpType = type;
	life = 40; // total core submarine life ( testing value, needs to be counted )
	enemyScore = 1200;
	// ---------------
	//fposition.x = x;
	//fposition.y = y;

	// body colliders
	fullBodyColliders[0] = extraColliders[10] = App->collision->AddCollider({0,100,168,20},COLLIDER_ENEMY, (Module*)App->enemies);
	fullBodyColliders[1] = extraColliders[11] = App->collision->AddCollider({ 0,100,24,39 }, COLLIDER_ENEMY, (Module*)App->enemies);

	coreCollider = extraColliders[12] = App->collision->AddCollider({ 0,0,48,24 }, COLLIDER_ENEMY, (Module*)App->enemies);


	// timers
	start_ejectable_time = SDL_GetTicks();



	//position.x = -150;
}

void EnemySubmarine::Move()
{
	// update colliders positions
	for (int i = 0; i < NUM_NONDESTROYED_PARTS; ++i)
	{
		if (extraColliders[i] != nullptr)
			extraColliders[i]->SetPos(position.x + nonDestroyedParts[i].position.x, position.y + nonDestroyedParts[i].position.y);
	}

	fullBodyColliders[0]->SetPos(position.x, position.y + 84);
	fullBodyColliders[1]->SetPos(position.x + 168, position.y + 64);

	coreCollider->SetPos(position.x + 208, position.y + 24);

	if(ejectionHatch.collider != nullptr)
		ejectionHatch.collider->SetPos(position.x + ejectionHatch.position.x, position.y + ejectionHatch.position.y);

	position.x += 1;
}

void EnemySubmarine::Draw()
{

	// draw full body without any destroyable part --------------------------------------------------
	App->render->Blit(enemyTex, position.x, position.y, &submarineBodyRect);
	// ----------------------------------------------------------------------------------------------

	// draw destroyed parts animations --------------------------------------------------------------
	for (int i = 0; i < NUM_DESTROYABLE_PARTS; ++i)
	{
		App->render->Blit(enemyTex, position.x + positionPartsX[i], position.y + positionPartsY[i], &destroyedParts[i].GetCurrentFrame());
	}

	// draw non destroyed static parts --------------------------------------------------------------
	for (int i = 0; i < NUM_NONDESTROYED_PARTS; ++i)
	{
		if (!nonDestroyedParts[i].destroyed)
		{
			// checks if the current part is the animated one and are in animated cycle ( only ejection hatch, missiles launcher is not relevant)
			if (i == 5 && ejectionHatch.throwEnemy) continue; // ignore the draw

			App->render->Blit(enemyTex, position.x + nonDestroyedParts[i].position.x,
				position.y + nonDestroyedParts[i].position.y, &nonDestroyedParts[i].normalRect);
		}
	}

	// draw animated parts (ejectable hatch can be destroyed, but missile launchers not

	// ejectable enemy timer and animation -------------------------------

	if (!ejectionHatch.destroyed)
	{
		//Animation* current_hatch_anim;
		SDL_Rect current_hatch_rect;

		// ejectable enemy timer ----------------------------------------------
		now_ejectable_time = SDL_GetTicks() - start_ejectable_time;
		if (now_ejectable_time >= ejectable_cadence_timer)
		{
			ejectionHatch.throwEnemy = true;
		}
		// -------------------------------------------------------------------
		// taken damage timer ----

		if (ejectionHatch.takenDamage)
		{
			ejectionHatch.current_frame = ejectionHatch.current_animation->current_frame;
			ejectionHatch.current_animation = &ejectionHatch.anim[DAMAGE_ANIM];
			ejectionHatch.anim->current_frame = ejectionHatch.current_frame;
			ejectionHatch.takenDamage = false;
			ejectionHatch.start_damage_time = SDL_GetTicks();
			LOG("changing anim to damage anim");

		}

		ejectionHatch.now_damage_time = SDL_GetTicks() - ejectionHatch.start_damage_time;

		if (ejectionHatch.now_damage_time >= ejectionHatch.damage_anim_time)
		{
			ejectionHatch.current_frame = ejectionHatch.anim->current_frame;
 			ejectionHatch.current_animation = &ejectionHatch.anim[NORMAL_ANIM];
			ejectionHatch.current_animation->current_frame = ejectionHatch.current_frame;
			LOG("changing anim to NORMAL anim");
		}
		// -------------------------------------------------------------------

		if (ejectionHatch.throwEnemy)
		{
			//current_hatch_rect = ejectionHatch.anim[NORMAL_ANIM].GetCurrentFrame();
			current_hatch_rect = ejectionHatch.anim->GetCurrentFrame();
			
			if (ejectionHatch.anim->finish)
			{
				ejectionHatch.throwEnemy = false;
				//ejectionHatch.anim[NORMAL_ANIM].current_frame = 0;
				//ejectionHatch.anim[NORMAL_ANIM].finish = false;
				ejectionHatch.anim->current_frame = 0;
				ejectionHatch.anim->finish = false;
				start_ejectable_time = SDL_GetTicks();
			}
		}
		else
		{
			current_hatch_rect = ejectionHatch.anim[NORMAL_ANIM].frames[0];
		}

		App->render->Blit(enemyTex, position.x + ejectionHatch.position.x,
			position.y + ejectionHatch.position.y, &current_hatch_rect);

		
	}




	// damage sprite swap timer  ---------------------------------------------------------------------
	
	nowDamagetime = SDL_GetTicks() - start_damage_time;

	if (nowDamagetime > damageAnimTime)
	{
		receiveDamage = false;
	}

	//if we are taken damage, print only the full body and the alive destroyable parts damage sprite --
	if (receiveDamage)
	{
		App->render->Blit(enemyTex, position.x, position.y, &submarineBodyDamageRect); // full body without destroyable parts

		for (int i = 0; i < NUM_NONDESTROYED_PARTS; ++i) // destroyable alive parts
		{
			if (!nonDestroyedParts[i].destroyed)
				App->render->Blit(enemyTex, position.x + nonDestroyedParts[i].position.x, 
					nonDestroyedParts[i].position.y + position.y, &nonDestroyedParts[i].takenDamageRect);
		}
	}


	// -----------------------------------------------------------------------------------------------
}

void EnemySubmarine::OnCollision(Collider* collider, Collider* collider2)
{
	// taken damage, submarine only takes damage and plays damage animation when the core is reached/damaged
	if (collider2 == coreCollider && !receiveDamage)
	{
		receiveDamage = true;
		start_damage_time = SDL_GetTicks();
		life -= collider->damage; // substract the damage taken by the damage amount of particle/collider associated to core life
	}

	// taken damage for ejection hatch
	if (collider2 == ejectionHatch.collider)//nonDestroyedParts[5].collider)
	{
		ejectionHatch.takenDamage = true;
		ejectionHatch.start_damage_time = SDL_GetTicks();
		
		LOG("ejectionHatch damaged");
	}

	// substract life to each part
	for (int i = 0; i < MAX_EXTRA_COLLIDERS; ++i)
	{
		if (extraColliders[i] == nullptr) continue;

		if (collider2 == nonDestroyedParts[i].collider) // destroyable static parts
		{
			if (readyToRumble && collider->type == COLLIDER_UNIT) // if the collider is the Unit and is ready to already take damage of it
				nonDestroyedParts[i].life -= collider->damage; // substract collider unit charged/normal damage
			else if (collider->type != COLLIDER_UNIT)
				nonDestroyedParts[i].life -= collider->damage;

			if (nonDestroyedParts[i].life <= 0)
			{
				nonDestroyedParts[i].destroyed = true;
				extraColliders[i]->to_delete = true;
				extraColliders[i] = nullptr;
				nonDestroyedParts[i].collider = nullptr;

				// play audio fx
				App->audio->ControlAudio("EnemyDeath", SFX, PLAY);
				// instantiate explosion particle
				App->particles->AddParticle(App->particles->explosion, position.x + nonDestroyedParts[i].position.x + nonDestroyedParts[i].normalRect.w / 2, 
					position.y + nonDestroyedParts[i].position.y, COLLIDER_NONE);

			}
			else
			{
				// instantiate bullet impact particle 
			}

			if (collider2 == ejectionHatch.collider) // destroyable ejection hatch
			{
				if (readyToRumble && collider->type == COLLIDER_UNIT) // if the collider is the Unit and is ready to already take damage of it
					ejectionHatch.life -= collider->damage; // substract collider unit charged/normal damage
				else if (collider->type != COLLIDER_UNIT)
					ejectionHatch.life -= collider->damage;

				if (ejectionHatch.life <= 0)
				{
					ejectionHatch.destroyed = true;
					extraColliders[13]->to_delete = true;
					extraColliders[13] = nullptr;
					ejectionHatch.collider = nullptr;

					// play audio fx
					App->audio->ControlAudio("EnemyDeath", SFX, PLAY);
					// instantiate explosions particles
					App->particles->AddParticle(App->particles->explosion, position.x + ejectionHatch.position.x + 60 / 2,
						position.y + ejectionHatch.position.y, COLLIDER_NONE);

				}
			}
		}
	}
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

	for (int i = 0; i < MAX_EXTRA_COLLIDERS; ++i)
	{
		if (extraColliders[i] != nullptr)
		{
			extraColliders[i]->to_delete = true;
			extraColliders[i] = nullptr;
		}
	}

}