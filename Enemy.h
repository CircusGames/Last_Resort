
#ifndef __ENEMY_H__
#define __ENEMY_H__

#define MAX_EXTRA_COLLIDERS 10

//#include "Globals.h"
#include "p2Point.h"
#include "Animation.h"

#include "Player.h"
//#include "ModulePlayer.h"

struct SDL_Texture;
struct Collider;

class Enemy
{
protected:
	Animation * animation = nullptr;
	Collider* collider = nullptr;
	
	

public:
	iPoint position;
	fPoint fposition;
	int life;
	uint enemyScore;
	SDL_Texture* enemyTex = nullptr; //links to enemy spritesheet texture
	Collider* extraColliders[MAX_EXTRA_COLLIDERS] = { nullptr };

	int collisionColliderIndex;

public:
	Enemy(int x, int y, powerUpTypes type = powerUpTypes::NONE);
	

	virtual ~Enemy();

	//~Enemy();

	virtual const Collider* GetCollider() const;

	virtual void Move() {};
	//virtual void Draw(SDL_Texture* sprites);
	virtual void Draw();
	virtual void OnCollision(Collider* collider, Collider* collider2);
	virtual void OnCollisionUnit(Collider* c2, Collider* c1);

	//utilities
	virtual float GetNearestPlayerAngle();
	virtual float GetNearestPlayerSqrtDistance();
	virtual iPoint GetTargetPos();
	//bool restrictionY = false;
	Module* nearestValidPlayer;

	virtual float GetDesiredTargetDistance(Module*);

	//distance needed variables
	float tx;
	float ty;

	enum nearestPlayer
	{
		P1,
		P2
	}nearestTarget;
	
	

	powerUpTypes powerUpType;

	// timers for unit cadence collisions
	Uint32 start_unit_damage_time;
	Uint32 now_unit_damage_time;
	Uint32 cadence_unit_damage_time = 500;
	bool readyToRumble = true; //if the enemy is ready to already taken the unit damage

	//receive damage bool to know if the enemy has to reproduce damage animation frames

	bool receiveDamage = false;
};

#endif // __ENEMY_H__
