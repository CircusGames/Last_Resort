#ifndef __ENEMYOSCILATORY_H__
#define __ENEMYOSCILATORY_H__

#include "Enemy.h"
#include "ModuleTextures.h"

class EnemyOscilatory : public Enemy
{
private:
	float wave = -1.0f;
	bool going_up = true;
	int original_y = 0;
	Animation waveAnim;
	iPoint original_pos;

	~EnemyOscilatory();

public:

	EnemyOscilatory(int x, int y, powerUpTypes type, SDL_Texture * sprite=nullptr);

	void Move();

};
#endif
