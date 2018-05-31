#ifndef _MODULEENEMIES_H__
#define _MODULEENEMIES_H__

#include "Module.h"
#include "EnemyTank.h"
#include "BasicEnemy.h"
#include "EnemyOscilatory.h"
#include "EnemyBee.h"
#include "EnemyRedbird.h"
#include "EnemyLamella.h"
#include "EnemyMiniTank.h"
#include "EnemySubmarine.h"
#include "EnemyDiver.h"
#include "EnemyPilot.h"
#include "ModuleParticles.h"

//#include "Enemy.h"


#define MAX_ENEMIES 300

enum ENEMY_TYPES
{
	NO_TYPE,
	BASIC_ENEMY,
	ENEMYOSCILATORY,
	REDBIRD,
	TANK,
	ENEMYBEE,
	POWERUP_BEE,
	ENEMYPROTATOR,
	LAMELLA,
	MINITANK,
	SUBMARINE,
	DIVER,
	ENEMYPILOT,
	HOMINGMISSILE,
	BIGFUCKINGROCKET,
	BIGDADDY,
	COLDMACHINE,
	COLDMACHINEBOMBARDIER
};

//class Enemy;
//struct SDL_Texture;

struct EnemyInfo
{
	ENEMY_TYPES type = ENEMY_TYPES::NO_TYPE;
	int x, y;
	//SDL_Texture* texture;
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

	bool AddEnemy(ENEMY_TYPES type, int x, int y, powerUpTypes powerUpType);

	//void pleaseKillMe(Enemy*);
	

	//more textures - in public because we call outside this module
	//more enemies textures -------
	SDL_Texture* enemy1Texture = nullptr;
	SDL_Texture* enemy2Texture = nullptr;
	SDL_Texture* enemyTankTexture = nullptr;
	SDL_Texture* enemyBeeTexture = nullptr;
	SDL_Texture* beeBulletTexture = nullptr;
	SDL_Texture* enemyRedbirdTexture = nullptr;
	SDL_Texture* enemyPowerBeeTexture = nullptr;
	SDL_Texture* enemyProtatorTexture = nullptr;
	SDL_Texture* enemyLamellaTexture = nullptr;
	SDL_Texture* enemyMiniTankTexture = nullptr;
	SDL_Texture* enemySubmarineTexture = nullptr;
	SDL_Texture* enemyDiverTexture = nullptr;
	SDL_Texture* enemyPilotTexture = nullptr;
	SDL_Texture* enemyHomingMissileTexture = nullptr;
	SDL_Texture* enemyDiverBeamTexture = nullptr;
	SDL_Texture* enemyBigDaddyTexture = nullptr;
	SDL_Texture* enemyColdMachineTexture = nullptr;
	// ----------------------------
	//ENEMY PARTICLES
	Particle beeBullet;
	Particle tankBigShot;
	Particle tankSmallShot;
	Particle homingExplosion;
	Particle diverBeamLeft;
	Particle diverBeamRight;
	// particles boss level 3 - Cold Machine
	Particle coldMachineFootFire;
	Particle coldMachineFootSmoke;
	Particle coldMachinePiecesSmoke;
	Particle coldMachineLegMissileFlash;
	Particle coldMachineKneeLaser;
	Particle coldMachineKneeLaserShotEffect;
	Particle coldMachineArmShootSmoke;
	// bombardier relatives
	Particle bombardierBomb;


private:

	void SpawnEnemy(EnemyInfo& info);// , powerUpTypes powerUpType = powerUpTypes::NONE, SDL_Texture* texture = nullptr);

private:

	EnemyInfo queue[MAX_ENEMIES];
	Enemy* enemies[MAX_ENEMIES];
	SDL_Texture* sprites; //general spriteSheet texture, used when we call AddEnemy from the scene without 
					      //specificate exclusive texture
};

#endif // _MODULEENEMIES_H__