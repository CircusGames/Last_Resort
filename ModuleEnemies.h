#ifndef _MODULEENEMIES_H__
#define _MODULEENEMIES_H__

#include "Module.h"
<<<<<<< HEAD
#include "Path.h"
=======
#include "BasicEnemy.h"
#include "Oscilatory.h"
>>>>>>> 8ac76136c29a69e4439dd6295233b145c274fd96

#define MAX_ENEMIES 100

enum ENEMY_TYPES
{
	NO_TYPE,
	BASIC_ENEMY,
<<<<<<< HEAD



};

enum ENEMY_MOVEMENT
{
	NO_MOVEMENT,
	STAY
=======
	OSCILATORY
>>>>>>> 8ac76136c29a69e4439dd6295233b145c274fd96
};

class Enemy;

struct EnemyInfo
{
	ENEMY_TYPES type = ENEMY_TYPES::NO_TYPE;
	ENEMY_MOVEMENT movement = ENEMY_MOVEMENT::NO_MOVEMENT;
	int x, y;
	SDL_Texture* texture = nullptr;
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

<<<<<<< HEAD
	bool AddEnemy(ENEMY_TYPES type, int x, int y, ENEMY_MOVEMENT movement);
=======
	bool AddEnemy(ENEMY_TYPES type, int x, int y, SDL_Texture* texture = nullptr);
>>>>>>> 8ac76136c29a69e4439dd6295233b145c274fd96

private:

	void SpawnEnemy(const EnemyInfo& info);

private:

	EnemyInfo queue[MAX_ENEMIES];
	Enemy* enemies[MAX_ENEMIES];
	SDL_Texture* sprites;

	//more textures
	SDL_Texture* enemy1Texture;
};

#endif // _MODULEENEMIES_H__