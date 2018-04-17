#ifndef _MODULEENEMIES_H__
#define _MODULEENEMIES_H__

#include "Module.h"
#include "Path.h"

#define MAX_ENEMIES 100

enum ENEMY_TYPES
{
	NO_TYPE,
	BASIC_ENEMY,



};

enum ENEMY_MOVEMENT
{
	NO_MOVEMENT,
	STAY
};

class Enemy;

struct EnemyInfo
{
	ENEMY_TYPES type = ENEMY_TYPES::NO_TYPE;
	ENEMY_MOVEMENT movement = ENEMY_MOVEMENT::NO_MOVEMENT;
	int x, y;
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

	bool AddEnemy(ENEMY_TYPES type, int x, int y, ENEMY_MOVEMENT movement);

private:

	void SpawnEnemy(const EnemyInfo& info);

private:

	EnemyInfo queue[MAX_ENEMIES];
	Enemy* enemies[MAX_ENEMIES];
	SDL_Texture* sprites;
};

#endif // _MODULEENEMIES_H__