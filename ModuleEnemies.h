#ifndef _MODULEENEMIES_H__
#define _MODULEENEMIES_H__

#include "Module.h"
#include "BasicEnemy.h"
#include "EnemyOscilatory.h"
#define MAX_ENEMIES 100

enum ENEMY_TYPES
{
	NO_TYPE,
	BASIC_ENEMY,
	ENEMYOSCILATORY
};

class Enemy;

struct EnemyInfo
{
	ENEMY_TYPES type = ENEMY_TYPES::NO_TYPE;
	int x, y;
	SDL_Texture* texture = nullptr;
	powerUpTypes powerUpType = powerUpTypes::NONE;
};

class ModuleEnemies : public Module
{
public:

	ModuleEnemies();
	~ModuleEnemies();

	bool Start();
	update_status PreUpdate();
	update_status Update();
	update_status PostUpdate();
	bool CleanUp();
	void OnCollision(Collider* c1, Collider* c2);

	bool AddEnemy(ENEMY_TYPES type, int x, int y, powerUpTypes powerUpType = powerUpTypes::NONE, SDL_Texture* texture = nullptr);
	

	//more textures - in public because we call outside this module
	//more enemies textures -------
	SDL_Texture* enemy1Texture;
	SDL_Texture* enemy2Texture;
	// ----------------------------
	

private:

	void SpawnEnemy(EnemyInfo& info);// , powerUpTypes powerUpType = powerUpTypes::NONE, SDL_Texture* texture = nullptr);

private:

	EnemyInfo queue[MAX_ENEMIES];
	Enemy* enemies[MAX_ENEMIES];
	SDL_Texture* sprites; //general spriteSheet texture, used when we call AddEnemy from the scene without 
					      //specificate exclusive texture
};

#endif // _MODULEENEMIES_H__