
#ifndef __ENEMY_H__
#define __ENEMY_H__

//#include "Globals.h"
#include "p2Point.h"
#include "Animation.h"

#include "Player.h"

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
	Collider* extraColliders[10] = { nullptr };

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
	
	

	powerUpTypes powerUpType;
};

#endif // __ENEMY_H__
