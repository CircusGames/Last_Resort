#ifndef __ENEMYBIGDADDY_H__
#define __ENEMYBIGDADDY_H__

#include "Enemy.h"
#include "ModuleTextures.h"


class EnemyBigDaddy : public Enemy
{
private:
	

public:

	EnemyBigDaddy(int x, int y, powerUpTypes type, SDL_Texture* thisTexture);

	void Move();

};

#endif // __ENEMYBIGDADDY__H__
