#ifndef __ENEMYHOMINGMISSILE_H__
#define __ENEMYHOMINGMISSILE_H__

#include "Enemy.h"
#include "ModuleTextures.h"


class EnemyHomingMissile : public Enemy
{
private:
	

public:

	EnemyHomingMissile(int x, int y, powerUpTypes type, SDL_Texture* thisTexture);

	void Move();


};

#endif // __ENEMYHOMINGMISSILE_H__
