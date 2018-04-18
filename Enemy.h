
#ifndef __ENEMY_H__
#define __ENEMY_H__

//#include "Globals.h"
#include "p2Point.h"
#include "Animation.h"

struct SDL_Texture;
struct Collider;

enum powerUpTypes
{
	NONE,
	UNIT,
	BOOST,
	MISSILE1,
	MISSILE2,
	RANDOM
};

class Enemy
{
protected:
	Animation * animation = nullptr;
	Collider* collider = nullptr;
	

public:
	iPoint position;

public:
	Enemy(int x, int y, powerUpTypes type = powerUpTypes::NONE, SDL_Texture* texture = nullptr);
	

	virtual ~Enemy();

	const Collider* GetCollider() const;

	virtual void Move() {};
	//virtual void Draw(SDL_Texture* sprites);
	virtual void Draw(SDL_Texture* texture);
	virtual void OnCollision(Collider* collider);
	
	SDL_Texture* texture = nullptr;

	powerUpTypes powerUpType;// = powerUpTypes::NONE;
};

#endif // __ENEMY_H__
