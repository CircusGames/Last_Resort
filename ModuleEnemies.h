#ifndef _MODULEENEMIES_H__
#define _MODULEENEMIES_H__

#include "Module.h"
#include "BasicEnemy.h"
<<<<<<< HEAD
=======
#include "Oscilatory.h"
>>>>>>> parent of a3e53bd... Merge branch 'master' of https://github.com/CircusGames/Last_Resort

#define MAX_ENEMIES 100

enum ENEMY_TYPES
{
	NO_TYPE,
<<<<<<< HEAD
	BASIC_ENEMY
=======
	BASIC_ENEMY,
	OSCILATORY
>>>>>>> parent of a3e53bd... Merge branch 'master' of https://github.com/CircusGames/Last_Resort
};

class Enemy;

struct EnemyInfo
{
	ENEMY_TYPES type = ENEMY_TYPES::NO_TYPE;
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

<<<<<<< HEAD
	bool AddEnemy(ENEMY_TYPES type, int x, int y);
=======
	bool AddEnemy(ENEMY_TYPES type, int x, int y, SDL_Texture* texture = nullptr);
>>>>>>> parent of a3e53bd... Merge branch 'master' of https://github.com/CircusGames/Last_Resort

private:

	void SpawnEnemy(const EnemyInfo& info);

private:

	EnemyInfo queue[MAX_ENEMIES];
	Enemy* enemies[MAX_ENEMIES];
	SDL_Texture* sprites;
};

#endif // _MODULEENEMIES_H__