#ifndef _ENEMYDIVER_H__
#define _ENEMYDIVER_H__

#include "Enemy.h"
#include "ModuleTextures.h"

class EnemyDiver : public Enemy
{

private:

	float distance;
	float pivot;

	bool clock = false;
	bool swap = false;
	bool jumping = true;

	int shots;

	Uint32 startTime;
	Uint32 now;
	Uint32 totalTime;

	Animation idleLeft;
	Animation idleRight;

	Animation animLeft;
	Animation animRight;

	Animation* currentAnimation;

	SDL_Rect diverRect;

	iPoint originalPos;

public:

	EnemyDiver(int x, int y, powerUpTypes type, SDL_Texture* thisTexture = nullptr);

	void Move();
	void Draw();

};
#endif // !_ENEMYDIVER_H__
