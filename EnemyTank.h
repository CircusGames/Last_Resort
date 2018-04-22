#ifndef _ENEMYTANK_H__
#define _ENEMYTANK_H__

#include "Enemy.h"
#include "Path.h"
#include "ModuleTextures.h"

class EnemyTank : public Enemy
{
private:

	Path path;
	Animation moveAnim;
	Animation boostAnim;
	Animation particlesAnim;
	iPoint originalPos;

	int original_x = NULL;

public:

	EnemyTank(int x, int y, powerUpTypes, SDL_Texture* sprite = nullptr);
	void Move();
};
#endif // !_ENEMYTANK_H__
