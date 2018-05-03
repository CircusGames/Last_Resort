#include "Application.h"
#include "ModuleInput.h"
#include "ModuleRender.h"
#include "ModuleEnemies.h"
#include "ModuleParticles.h"
#include "ModuleTextures.h"
#include "Enemy.h"
#include "BasicEnemy.h"
#include "EnemyOscilatory.h"
#include "EnemyTank.h"
#include "EnemyBee.h"
#include "EnemyRedbird.h"
#include "ModulePowerUp.h"
#include "ModuleAudio.h"


#define SPAWN_MARGIN 15*SCREEN_SIZE


ModuleEnemies::ModuleEnemies()
{
	for (uint i = 0; i < MAX_ENEMIES; ++i)
		enemies[i] = nullptr;

	//PARTICLES -------------------------------------------
	//Enemy Bee  -----------------------------
	beeBullet.anim.PushBack({0,0,5,5});
	beeBullet.anim.PushBack({12,0,5,5});
	beeBullet.anim.PushBack({ 24,0,5,5 });
	beeBullet.anim.PushBack({ 35,0,5,5 });
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
	// -----------------------------------------------------
}

// Destructor
ModuleEnemies::~ModuleEnemies()
{
}

bool ModuleEnemies::Start()
{
	// ENEMY TEXTURES ---------------------------------------------------------------------
	sprites = App->textures->Load("assets/Graphics/Enemies/Level_1/enemies.png");
	enemy1Texture = App->textures->Load("assets/Graphics/Enemies/Level_1/enemy1.png");
	enemy2Texture = App->textures->Load("assets/Graphics/Enemies/Level_1/oscilator.png");
	enemyTankTexture = App->textures->Load("assets/Graphics/Enemies/Level_1/Tank.png");
	enemyBeeTexture = App->textures->Load("assets/Graphics/Enemies/Level_1/Bee.png");
	enemyRedbirdTexture = App->textures->Load("assets\Graphics/Enemies/Level_3/Redbird.png");
	// -------------------------------------------------------------------------------------
	// ENEMY PARTICLES ---------------------------------------------------------------------
	// textures ----------
	beeBulletTexture = App->textures->Load("assets/Graphics/Enemies/Level_1/bee_bullet.png");
	beeBullet.texture = beeBulletTexture; //link texture to particle
	//TANK shot particles
	tankBigShot.texture = enemyTankTexture;
	tankSmallShot.texture = enemyTankTexture;
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
		if (enemies[i] != nullptr)
		{
			//if (enemies[i]->position.x * SCREEN_SIZE < (App->render->camera.x) - SPAWN_MARGIN)
			if(enemies[i]->position.x < (abs(App->render->camera.x) / SCREEN_SIZE) - 100)
			{
				LOG("DeSpawning enemy at %d", enemies[i]->position.x * SCREEN_SIZE);
				delete enemies[i];
				enemies[i] = nullptr;
			}
		}
	}

	return UPDATE_CONTINUE;
}

// Called before quitting
bool ModuleEnemies::CleanUp()
{
	LOG("Freeing all enemies");
	
	//unloading loaded textures

	App->textures->Unload(beeBulletTexture);
	App->textures->Unload(enemyBeeTexture);
	App->textures->Unload(enemyTankTexture);
	App->textures->Unload(enemy2Texture);
	App->textures->Unload(enemy1Texture);
	App->textures->Unload(enemyRedbirdTexture);
	App->textures->Unload(sprites);
	
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
		}
	}
}

void ModuleEnemies::OnCollision(Collider* c1, Collider* c2)
{
	for (uint i = 0; i < MAX_ENEMIES; ++i)
	{
		if (enemies[i] != nullptr && enemies[i]->GetCollider() == c1)
		{
			enemies[i]->OnCollision(c2);
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
	}
}