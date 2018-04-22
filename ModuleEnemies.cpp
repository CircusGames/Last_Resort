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
#include "ModulePowerUp.h"
#include "ModuleAudio.h"


#define SPAWN_MARGIN 15*SCREEN_SIZE

ModuleEnemies::ModuleEnemies()
{
	for (uint i = 0; i < MAX_ENEMIES; ++i)
		enemies[i] = nullptr;
}

// Destructor
ModuleEnemies::~ModuleEnemies()
{
}

bool ModuleEnemies::Start()
{
	// Create a prototype for each enemy available so we can copy them around
	//sprites texture pointer is used as "general purpose" texture spritesheet now --------
	//if you want to add a specific texture to specific enemy, see basic_enemy.cpp
	//and scenelvl1 start() method.
	sprites = App->textures->Load("assets/Graphics/Enemies/Level_1/enemy1.png"); //general purpose texture
	//
	//texture to pass in scene, when calls AddEnemy(); method. -----------------------------
	enemy1Texture = App->textures->Load("assets/Graphics/Enemies/Level_1/enemy1.png");
	enemy2Texture = App->textures->Load("assets/Graphics/Enemies/Level_1/oscilator.png");
	enemyTankTexture = App->textures->Load("assets/Graphics/Enemies/Level_1/Tank.png");
	//Audio
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
		if (enemies[i] != nullptr) enemies[i]->Draw(enemies[i]->texture);

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

	App->textures->Unload(sprites);
	App->textures->Unload(enemy1Texture);
	App->textures->Unload(enemy2Texture);
	App->textures->Unload(enemyTankTexture);
	App->audio->UnloadAudio("EnemyDeath",SFX);

	for (uint i = 0; i < MAX_ENEMIES; ++i)
	{
		if (enemies[i] != nullptr)
		{
			delete enemies[i];
			enemies[i] = nullptr;
		}
	}

	return true;
}

bool ModuleEnemies::AddEnemy(ENEMY_TYPES type,  int x, int y, powerUpTypes powerUp, SDL_Texture* texture)
{
	bool ret = false;

	for (uint i = 0; i < MAX_ENEMIES; ++i)
	{
		if (queue[i].type == ENEMY_TYPES::NO_TYPE)
		{
			if(texture != nullptr)
				queue[i].texture = texture;
			else queue[i].texture = sprites;

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
			enemies[i] = new BasicEnemy(info.x, info.y,info.powerUpType,info.texture);
			break;
		case ENEMY_TYPES::ENEMYOSCILATORY:
			enemies[i] = new EnemyOscilatory(info.x, info.y, info.powerUpType, info.texture);
			break;
		case ENEMY_TYPES::TANK:
			enemies[i] = new EnemyTank(info.x, info.y, info.powerUpType, info.texture);
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