#ifndef __ENEMYPROTATOR_H__
#define __ENEMYPROTATOR_H__

#include "Enemy.h"
#include "ModuleTextures.h"

#include "Module.h"

//#include "ModulePlayer.h"



class EnemyProtator : public Enemy
{
private:

	Animation protatorAnim;
	Animation protatorDamageAnim;

	iPoint targetPos;
	bool targetPosReached;
	bool aimed;
	//float tx;
	//float ty;
	float velX;
	float velY;
	float distance;
	float lastVelY;
	float maxVelY;
	Animation* current_animation;

	iPoint preAimedLocalPos;

	bool ready;
	bool propulsion;
	bool goingDown;
	bool grounded;
	bool rightCollision;
	bool leftCollision;
	bool animGrounded;
	bool restartCycle;

	Uint32 start_time;
	Uint32 now;
	Uint32 aimTime;

	//shooting needed variables
	float vx;
	float vy;
	float shootSpeed;
	int cadence;
	bool attack;
	Uint32 start_shot_time;
	Uint32 nowShotTime;
	int txShot;
	int tyShot;
	// ------------------------
	// receiving damage values
	//bool receiveDamage;
	Uint32 start_damage_time;
	Uint32 nowDamagetime;
	Uint32 damageAnimTime;
	float current_frame;

	//
	int restrictionYvalue;
	bool restrictionY;
	iPoint checkValidPlayerY();
	//iPoint nearestValidPlayerY;
	int nearestValidPlayerPosition;
	bool toAim = false;
	

public:

	EnemyProtator(int x, int y, powerUpTypes type, SDL_Texture* thisTexture);

	~EnemyProtator();
	//~Enemy();

	void Move();
	void Draw();
	void OnCollision(Collider* collider, Collider* collider2);

	const Collider* EnemyProtator::GetCollider() const;

	Collider* rightCollider;
	Collider* leftCollider;

	Collider* debugWall1;
	Collider* debugWall2;

	Module* desiredPlayerModule = nullptr;
	
};

#endif // __ENEMYPROTATOR__H__
