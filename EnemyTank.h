#ifndef _ENEMYTANK_H__
#define _ENEMYTANK_H__

#include "Enemy.h"
#include "Path.h"
#include "ModuleTextures.h"

class EnemyTank : public Enemy
{
private:

	Path path;
	Animation staticAnim;
	Animation moveAnim;
	Animation boostAnim;
	Animation particlesAnim;
	iPoint originalPos;
	iPoint originalPos2;
	iPoint originalPos3;
	Animation rotateAnimBig;
	Animation rotateAnimSmall;
	Animation* animation2 = nullptr;
	Animation* animation3 = nullptr;
	iPoint position2;
	iPoint position3;

public:

	EnemyTank(int x, int y, powerUpTypes, SDL_Texture* sprite = nullptr);
	void Move();
};

#endif // !_ENEMYTANK_H__
