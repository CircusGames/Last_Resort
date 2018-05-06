#ifndef __ENEMYPROTATOR_H__
#define __ENEMYPROTATOR_H__

#include "Enemy.h"
#include "ModuleTextures.h"


class EnemyProtator : public Enemy
{
private:
	bool going_up = true;
	int original_y = 0;
	Animation protatorAnim;
	Animation protatorDamageAnim;
	iPoint original_pos;

public:

	EnemyProtator(int x, int y, powerUpTypes type, SDL_Texture* thisTexture);

	//OnCollision

	void Move();


};

#endif // __ENEMYPROTATOR__H__
