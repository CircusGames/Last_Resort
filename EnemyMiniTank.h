#ifndef _ENEMYMINITANK__H_
#define _ENEMYMINITANK__H_

#include "Enemy.h"
#include "Path.h"
#include "ModuleTextures.h"

class Enemy_MiniTank : public Enemy
{
private:
	Path path;
	iPoint original_pos;
	Animation move, move2;
	Animation * shootanimation;

public:

	Enemy_MiniTank(int x, int y, powerUpTypes type, SDL_Texture * thisTexture = nullptr);

	void Move();
};


#endif // !_ENEMYMINITANK__H_

