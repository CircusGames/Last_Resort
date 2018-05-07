#ifndef __ENEMYPROTATOR_H__
#define __ENEMYPROTATOR_H__

#include "Enemy.h"
#include "ModuleTextures.h"

#include "Module.h"


class EnemyProtator : public Enemy
{
private:

	Animation protatorAnim;
	Animation protatorDamageAnim;

	iPoint targetPos;
	bool targetPosReached;
	bool aimed;
	float tx;
	float ty;
	float velX;
	float velY;
	float distance;
	float lastVelY;
	Animation* current_animation;

	iPoint preAimedLocalPos;

	bool propulsion;
	bool goingDown;
	bool grounded;
	bool rightCollision;
	bool leftCollision;
	

public:

	EnemyProtator(int x, int y, powerUpTypes type, SDL_Texture* thisTexture);

	void Move();
	void Draw();
	void OnCollision(Collider* collider, Collider* collider2);

	const Collider* EnemyProtator::GetCollider() const;

	Collider* rightCollider;
	Collider* leftCollider;

	Collider* debugWall1;
	Collider* debugWall2;
	
};

#endif // __ENEMYPROTATOR__H__
