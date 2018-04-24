#ifndef __ENEMY_BROWN_COOKIE_H__
#define __ENEMY_BROWN_COOKIE_H__

#include "Enemy.h"
#include "ModuleTextures.h"


class BasicEnemy : public Enemy
{
private:
	float wave = -1.0f;
	bool going_up = true;
	int original_y = 0;
	Animation fly;
	iPoint original_pos;

public:

	BasicEnemy(int x, int y, powerUpTypes type,SDL_Texture* thisTexture);
	
	//OnCollision

	void Move();


};

#endif // __ENEMY__H__
