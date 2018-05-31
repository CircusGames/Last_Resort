#include "Application.h"
#include "ModuleInput.h"
#include "ModuleRender.h"
#include "ModuleEnemies.h"
#include "ModuleParticles.h"
#include "ModuleTextures.h"

//#include "Enemy.h"
#include "BasicEnemy.h"
#include "EnemyOscilatory.h"
#include "EnemyTank.h"
#include "EnemyBee.h"
#include "EnemyRedbird.h"
#include "EnemyPowerUpBee.h"
#include "EnemyProtator.h"
#include "EnemyLamella.h"
#include "EnemyMiniTank.h"
#include "EnemyDiver.h"
#include "EnemyPilot.h"
#include "EnemyHomingMissile.h"
#include "EnemyBigFuckingRocket.h"
#include "EnemyBigDaddy.h"
#include "EnemyColdMachine.h"

#include "ModulePowerUp.h"
#include "ModuleAudio.h"

#include "ModulePlayerUnit.h"
//#include "Player.h"


#define SPAWN_MARGIN 15*SCREEN_SIZE


ModuleEnemies::ModuleEnemies()
{
	for (uint i = 0; i < MAX_ENEMIES; ++i)
		enemies[i] = nullptr;

	//PARTICLES -------------------------------------------
	//Enemy Bee  -----------------------------
	beeBullet.anim.PushBack({1,0,5,5});
	beeBullet.anim.PushBack({13,0,5,5});
	beeBullet.anim.PushBack({ 25,0,5,5 });
	beeBullet.anim.PushBack({ 36,0,5,5 });
	beeBullet.anim.speed = 0.2f;
	beeBullet.damage = 1;
	beeBullet.life = 1500;
	// ---------------------------------------

	// TANK shot particles --------------------
	//bigShot Particle ---------
	tankBigShot.anim.PushBack({ 123,0,13,13 });
	tankBigShot.anim.PushBack({ 136,0,13,13 });
	tankBigShot.anim.PushBack({ 149,0,13,13 });
	tankBigShot.anim.PushBack({ 162,0,13,13 });
	tankBigShot.anim.speed = 0.3f;
	tankBigShot.damage = 1;
	tankBigShot.life = 1500;
	// --------------------------
	// small shot particle
	tankSmallShot.anim.PushBack({175,0,5,5});
	tankSmallShot.anim.PushBack({180,0,5,5 });
	tankSmallShot.anim.PushBack({ 185,0,5,5 });
	tankSmallShot.anim.PushBack({ 190,0,5,5 });
	tankSmallShot.anim.speed = 0.3f;
	tankSmallShot.damage = 1;
	tankSmallShot.life = 1500;
	// ----------------------------

	// HOMING MISSILE EXPLOSION
	homingExplosion.anim.PushBack({5,40,21,19});
	homingExplosion.anim.PushBack({ 32,35,27,27 });
	homingExplosion.anim.PushBack({ 65,35,30,30 });
	homingExplosion.anim.PushBack({ 103,35,32,31 });
	homingExplosion.anim.PushBack({ 143,35,28,31 });
	homingExplosion.anim.PushBack({ 177,35,31,31 });
	homingExplosion.anim.PushBack({ 4,66,31,31 });
	homingExplosion.anim.PushBack({ 39,66,30,31 });
	homingExplosion.anim.PushBack({ 75,66,31,29 });
	homingExplosion.anim.PushBack({ 112,66,29,27 });
	homingExplosion.anim.speed = 0.25f;
	homingExplosion.anim.repeat = false;

	// -----------------------------------------------------

	// DIVER LASER BEAMS
	diverBeamLeft.anim.PushBack({ 0, 0, 24, 7 });
	diverBeamLeft.anim.PushBack({ 48, 0, 48, 7 });

	diverBeamRight.anim.PushBack({ 0, 8, 48, 7 });
	diverBeamRight.anim.PushBack({ 48, 8, 48, 7 });

	diverBeamLeft.anim.speed = diverBeamRight.anim.speed = 0.2f;
	diverBeamLeft.damage = diverBeamRight.damage = 1;
	diverBeamLeft.damage = diverBeamRight.damage = 1500;

	// COLD MACHINE, BOSS LEVEL 3 needed particles
	// foot "explosion" when landing
	coldMachineFootFire.anim.PushBack({ 223,314,32,18 });
	coldMachineFootFire.life = 200;
	// foot smoke after explosion
	coldMachineFootSmoke.anim.PushBack({ 60,300,30,32 });
	coldMachineFootSmoke.anim.PushBack({ 92,300,31,32 });
	coldMachineFootSmoke.anim.PushBack({ 123,300,28,31 });
	coldMachineFootSmoke.anim.PushBack({ 152,300,24,32 });
	coldMachineFootSmoke.anim.PushBack({ 177,300,22,16 });
	coldMachineFootSmoke.anim.speed = 0.125f;
	coldMachineFootSmoke.anim.repeat = false;
	// between pieces smoke
	coldMachinePiecesSmoke.anim.PushBack({ 67,170,10,24 });
	coldMachinePiecesSmoke.anim.PushBack({ 33,160,15,32 });
	coldMachinePiecesSmoke.anim.PushBack({ 16,160,14,32 });
	coldMachinePiecesSmoke.anim.PushBack({ 50,160,14,31 });
	coldMachinePiecesSmoke.anim.PushBack({ 80,160,8,30 });
	coldMachinePiecesSmoke.anim.PushBack({ 91,160,6,16 });
	coldMachinePiecesSmoke.anim.speed = 0.125f;
	coldMachinePiecesSmoke.anim.repeat = false;


}

// Destructor
ModuleEnemies::~ModuleEnemies()
{
}

bool ModuleEnemies::Start()
{
	// ENEMY TEXTURES ---------------------------------------------------------------------
	//sprites = App->textures->Load("assets/Graphics/Enemies/Level_1/enemies.png");
	enemy1Texture = App->textures->Load("assets/Graphics/Enemies/Level_1/enemy1.png");
	enemy2Texture = App->textures->Load("assets/Graphics/Enemies/Level_1/oscilator.png");
	enemyTankTexture = App->textures->Load("assets/Graphics/Enemies/Level_1/Tank.png");
	enemyBeeTexture = App->textures->Load("assets/Graphics/Enemies/Level_1/Bee.png");
	enemyRedbirdTexture = App->textures->Load("assets/Graphics/Enemies/Level_3/Redbird.png");
	enemyPowerBeeTexture = App->textures->Load("assets/Graphics/Enemies/Level_3/power_bee.png");
	enemyProtatorTexture = App->textures->Load("assets/Graphics/Enemies/Level_3/protator.png");
	enemyLamellaTexture = App->textures->Load("assets/Graphics/Enemies/Level_3/lamella.png");
	enemyMiniTankTexture = App->textures->Load("assets/Graphics/Enemies/Level_3/MiniTank.png");
	enemySubmarineTexture = App->textures->Load("assets/Graphics/Enemies/Level_3/submarine.png");
	enemyDiverTexture = App->textures->Load("assets/Graphics/Enemies/Level_3/diver.png");
	enemyPilotTexture = App->textures->Load("assets/Graphics/Enemies/Pilot.png");
	enemyHomingMissileTexture = App->textures->Load("assets/Graphics/Enemies/Level_3/homingMissile.png");
	enemyBigDaddyTexture = App->textures->Load("assets/Graphics/Enemies/Level_3/mid_boss.png");
	enemyColdMachineTexture = App->textures->Load("assets/Graphics/Enemies/Level_3/boss.png");
	
	// -------------------------------------------------------------------------------------
	// ENEMY PARTICLES ---------------------------------------------------------------------
	// textures ----------
	beeBulletTexture = App->textures->Load("assets/Graphics/Enemies/Level_1/bee_bullet.png");
	beeBullet.texture = beeBulletTexture; //link texture to particle

	enemyDiverBeamTexture = App->textures->Load("assets/Graphics/Enemies/Level_3/diverShot.png");
	diverBeamLeft.texture = diverBeamRight.texture = enemyDiverBeamTexture;

	//TANK shot particles
	tankBigShot.texture = enemyTankTexture;
	tankSmallShot.texture = enemyTankTexture;
	// HOMING missile particle to texture link
	homingExplosion.texture = enemyHomingMissileTexture;
	// COLD MACHINE, BOSS LEVEL 3 particle to texture links
	coldMachineFootFire.texture = enemyColdMachineTexture;
	coldMachineFootSmoke.texture = enemyColdMachineTexture;
	coldMachinePiecesSmoke.texture = enemyColdMachineTexture;
	// -------------------------------------------------------------------------------------
	// AUDIO FX ----------------------------------------------------------------------------
	App->audio->LoadAudio("assets/Audio/SFX/enemies/Enemy_Explosion.wav", "EnemyDeath", SFX);

	return true;
}

update_status ModuleEnemies::PreUpdate()
{
	// check camera position to decide what to spawn
	for (uint i = 0; i < MAX_ENEMIES; ++i)
	{
		if (queue[i].type != ENEMY_TYPES::NO_TYPE)
		{
			
			//if (queue[i].x * SCREEN_SIZE > App->render->camera.x - (App->render->camera.w * SCREEN_SIZE) + SPAWN_MARGIN)
			if (-queue[i].x * SCREEN_SIZE > App->render->camera.x - (App->render->camera.w * SCREEN_SIZE) - SPAWN_MARGIN)
			{
				SpawnEnemy(queue[i]);
				queue[i].type = ENEMY_TYPES::NO_TYPE;
				//queue[i].powerUpType = powerUpTypes::NONE;
				LOG("Spawning enemy at %d", queue[i].x * SCREEN_SIZE);
			}
		}
	} 

	return UPDATE_CONTINUE;
}

// Called before render is available
update_status ModuleEnemies::Update()
{
	for (uint i = 0; i < MAX_ENEMIES; ++i)
		if (enemies[i] != nullptr) enemies[i]->Move();

	for (uint i = 0; i < MAX_ENEMIES; ++i)
		//enemies[i].
		if (enemies[i] != nullptr) enemies[i]->Draw();

	return UPDATE_CONTINUE;
}

update_status ModuleEnemies::PostUpdate()
{
	// check camera position to decide what to spawn
	for (uint i = 0; i < MAX_ENEMIES; ++i)
	{
		if (enemies[i] != nullptr && enemies[i]->enemyType != ENEMY_TYPES::SUBMARINE)
		{
			//if (enemies[i]->position.x * SCREEN_SIZE < (App->render->camera.x) - SPAWN_MARGIN)
			if(enemies[i]->position.x < (abs(App->render->camera.x) / SCREEN_SIZE) - 100)
			{
				LOG("DeSpawning enemy at %d", enemies[i]->position.x * SCREEN_SIZE);
				delete enemies[i];
				enemies[i] = nullptr;
			}
		}

		if (enemies[i] != nullptr && enemies[i]->killMe)
		{
			LOG("the wish of one enemy is death");
			delete enemies[i];
			enemies[i] = nullptr;
		}
	}

	return UPDATE_CONTINUE;
}

// Called before quitting
bool ModuleEnemies::CleanUp()
{
	LOG("Freeing all enemies");
	
	//unloading loaded textures
	// INVERSE ORDER
	App->textures->Unload(enemyColdMachineTexture);
	App->textures->Unload(enemyBigDaddyTexture);
	App->textures->Unload(enemyDiverBeamTexture);
	App->textures->Unload(enemyHomingMissileTexture);
	App->textures->Unload(enemyPilotTexture);
	App->textures->Unload(enemyDiverTexture);
	App->textures->Unload(enemySubmarineTexture);
	App->textures->Unload(enemyMiniTankTexture);
	App->textures->Unload(enemyLamellaTexture);
	App->textures->Unload(enemyProtatorTexture);
	App->textures->Unload(enemyPowerBeeTexture);
	App->textures->Unload(beeBulletTexture);
	App->textures->Unload(enemyRedbirdTexture);
	App->textures->Unload(enemyBeeTexture);
	App->textures->Unload(enemyTankTexture);
	App->textures->Unload(enemy2Texture);
	App->textures->Unload(enemy1Texture);
	//App->textures->Unload(sprites);
	
	//Unloading loaded audio's

	App->audio->UnloadAudio("EnemyDeath",SFX);

	//removing spawned enemies

	for (uint i = 0; i < MAX_ENEMIES; ++i)
	{
		if (enemies[i] != nullptr)
		{
			delete enemies[i];
			enemies[i] = nullptr;
		}
	}

	//removing queue enemies
	for (uint i = 0; i < MAX_ENEMIES; ++i)
	{
		if (queue[i].type != ENEMY_TYPES::NO_TYPE) //if we have on queue some enemy with explicit type
		{
		  queue[i].type = ENEMY_TYPES::NO_TYPE; //with no type defined, function addEnemy can overWrite the needed values
		}
	}

	return true;
}

bool ModuleEnemies::AddEnemy(ENEMY_TYPES type,  int x, int y, powerUpTypes powerUp)
{
	bool ret = false;

	for (uint i = 0; i < MAX_ENEMIES; ++i)
	{
		if (queue[i].type == ENEMY_TYPES::NO_TYPE)
		{
			queue[i].powerUpType = powerUp;
			queue[i].type = type;
			queue[i].x = x;
			queue[i].y = y;
			ret = true;
			break;
		}
	}

	return ret;
}

void ModuleEnemies::SpawnEnemy(EnemyInfo& info)
{
	// find room for the new enemy
	uint i = 0;
	for (; enemies[i] != nullptr && i < MAX_ENEMIES; ++i);

	if (i != MAX_ENEMIES)
	{
		switch (info.type)
		{
		case ENEMY_TYPES::BASIC_ENEMY:
			enemies[i] = new BasicEnemy(info.x, info.y,info.powerUpType, enemy1Texture);
			break;
		case ENEMY_TYPES::ENEMYOSCILATORY:
			enemies[i] = new EnemyOscilatory(info.x, info.y, info.powerUpType, enemy2Texture);
			break;
		case ENEMY_TYPES::TANK:
			enemies[i] = new EnemyTank(info.x, info.y, info.powerUpType, enemyTankTexture);
			break;
		case ENEMY_TYPES::ENEMYBEE:
			enemies[i] = new EnemyBee(info.x, info.y, info.powerUpType, enemyBeeTexture);
			break;
		case ENEMY_TYPES::REDBIRD:
			enemies[i] = new EnemyRedbird(info.x, info.y, info.powerUpType, enemyRedbirdTexture);
			break;
		case ENEMY_TYPES::POWERUP_BEE:
			enemies[i] = new EnemyPowerUpBee(info.x, info.y, info.powerUpType, enemyPowerBeeTexture);
			break;
		case ENEMY_TYPES::ENEMYPROTATOR:
			enemies[i] = new EnemyProtator(info.x, info.y, info.powerUpType, enemyProtatorTexture);
			break;
		case ENEMY_TYPES::LAMELLA:
			enemies[i] = new EnemyLamella(info.x, info.y, info.powerUpType, enemyLamellaTexture);
			break;
		case ENEMY_TYPES::MINITANK:
			enemies[i] = new Enemy_MiniTank(info.x, info.y, info.powerUpType, enemyMiniTankTexture);
			break;
		case ENEMY_TYPES::SUBMARINE:
			enemies[i] = new EnemySubmarine(info.x, info.y, info.powerUpType, enemySubmarineTexture);
			break;
		case ENEMY_TYPES::DIVER:
			enemies[i] = new EnemyDiver(info.x, info.y, info.powerUpType, enemyDiverTexture);
			break;
		case ENEMY_TYPES::ENEMYPILOT:
			enemies[i] = new EnemyPilot(info.x, info.y, info.powerUpType, enemyPilotTexture);
			break;
		case ENEMY_TYPES::HOMINGMISSILE:
			enemies[i] = new EnemyHomingMissile(info.x, info.y, info.powerUpType, enemyHomingMissileTexture);
			break;
		case ENEMY_TYPES::BIGFUCKINGROCKET:
			enemies[i] = new EnemyBigFuckingRocket(info.x, info.y, info.powerUpType, enemyMiniTankTexture);
			break;
		case ENEMY_TYPES::BIGDADDY:
			enemies[i] = new EnemyBigDaddy(info.x, info.y, info.powerUpType, enemyBigDaddyTexture);
			break;
		case ENEMY_TYPES::COLDMACHINE:
			enemies[i] = new EnemyColdMachine(info.x, info.y, info.powerUpType, enemyColdMachineTexture);
			break;
		}
	}
}

void ModuleEnemies::OnCollision(Collider* c1, Collider* c2)
{
	for (uint i = 0; i < MAX_ENEMIES; ++i)
	{
		for (int k = 0; k < MAX_EXTRA_COLLIDERS ; ++k) //10 = extraColliders array max index
		{
			if (enemies[i] != nullptr && enemies[i]->extraColliders[k] != nullptr)
			{
				if (c1 == enemies[i]->extraColliders[k])
					enemies[i]->collisionColliderIndex = k;
			}
		}
		if (enemies[i] != nullptr && enemies[i]->GetCollider() == c1 && c2->type != COLLIDER_UNIT)
		{
			enemies[i]->OnCollision(c2, c1);

			if(enemies[i]->enemyType != SUBMARINE && enemies[i]->enemyType != BIGDADDY)
 				enemies[i]->life -= c2->damage; //particle damage

			if (c2->type == COLLIDER_PLAYER)
				--enemies[i]->life; //by default, player collider substract 1 to enemy life
			
 			if (enemies[i]->life <= 0)
			{
				App->audio->ControlAudio("EnemyDeath", SFX, PLAY);

				delete enemies[i];
				enemies[i] = nullptr;
				break;
			}
			
		}
		// if collision pertains to unit
		else if (enemies[i] != nullptr && enemies[i]->GetCollider() == c1 && c2->type == COLLIDER_UNIT)
		{
			if (enemies[i]->readyToRumble)
			{
				enemies[i]->start_unit_damage_time = SDL_GetTicks();

				//if the unit can't destroy the enemy at once, return state
				/*if (enemies[i]->life > c2->damage)
				{
					if (c2->callback == App->playerUnit[0] && App->playerUnit[0]->this_state != actualState::LINKED) 
						App->playerUnit[0]->this_state = actualState::RETURN;
					if (c2->callback == App->playerUnit[1] && App->playerUnit[0]->this_state != actualState::LINKED) 
						App->playerUnit[1]->this_state = actualState::RETURN;
				}*/

				if(enemies[i]->enemyType != SUBMARINE && enemies[i]->enemyType != MINITANK)// && enemies[i]->enemyType != BIGDADDY)
				enemies[i]->life -= c2->damage; //receive unit damage respect the actual unit damage (charged or not amount)
			}
			// second check if the readyToRumbe is false, and the unit needs to be returnted too
			if (enemies[i]->life <= 0)enemies[i]->life = 0; // protection
			if (enemies[i]->life > c2->damage)
			{
				if (c2->callback == App->playerUnit[0] && App->playerUnit[0]->this_state != actualState::LINKED &&
					App->playerUnit[0]->this_state != actualState::POSITIONING)
					App->playerUnit[0]->this_state = actualState::RETURN;
				if (c2->callback == App->playerUnit[1] && App->playerUnit[0]->this_state != actualState::LINKED &&
					App->playerUnit[0]->this_state != actualState::POSITIONING)
					App->playerUnit[1]->this_state = actualState::RETURN;
			}

			if (enemies[i]->enemyType == SUBMARINE || enemies[i]->enemyType == MINITANK)
				enemies[i]->OnCollision(c2, c1);
			
			enemies[i]->OnCollisionUnit(c2, c1);

			if (enemies[i]->life <= 0)
			{
				App->audio->ControlAudio("EnemyDeath", SFX, PLAY);

				delete enemies[i];
				enemies[i] = nullptr;
				break;
			}
		}

	}
}

/*void ModuleEnemies::pleaseKillMe(Enemy* thisEnemy)
{
	for (int i = 0; i < MAX_ENEMIES; ++i)
	{
		if (enemies[i] == thisEnemy)
		{
			thisEnemy->~Enemy();
			delete enemies[i];
			enemies[i] = nullptr;
			break;
		}
	}
}*/