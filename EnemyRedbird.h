#ifndef __ENEMYREDBIRD_H__
#define __ENEMYREDBIRD_H__

#include "Enemy.h"
#include "ModuleTextures.h"

class EnemyRedbird: public Enemy
{
private:
	float wave = -1.0f;
	bool going_up = true;
	int original_y = 0;
	Animation waveAnim;
	iPoint original_pos;

public:

	EnemyRedbird(int x, int y, powerUpTypes type, SDL_Texture * thisTexture = nullptr);

	void Move();

};
#endif __ENEMYREDBIRD_H__
