#ifndef __OSCILATORY_H__
#define __OSCILATORY_H__
#include "Enemy.h"

class Oscilatory: public Enemy
{
private:
	float wave = -1.0f;
	bool going_up = true;
	int original_y = 0;
	Animation fly;
	iPoint original_pos;

public:

	Oscilatory(int x, int y);

	void Move();

	SDL_Texture* texture = nullptr;
};

#endif
