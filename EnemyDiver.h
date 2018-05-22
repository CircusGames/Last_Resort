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
	bool jumping = true;
	bool shoot = false;
	bool spawn = false;

	int shots;

	Uint32 startTime;
	Uint32 now;
	Uint32 totalTime;

	Animation idleLeft;
	Animation idleRight;

	Animation animLeft;
	Animation animRight;

	Animation shootLeft;
	Animation shootRight;

	Animation spawnAnim;

	Animation* currentAnimation;
	Animation* currentShootAnim;

	SDL_Rect diverRect;
	SDL_Rect shootRect;
	SDL_Rect spawnRect;

	iPoint originalPos;

public:

	EnemyDiver(int x, int y, powerUpTypes type, SDL_Texture* thisTexture = nullptr);

	void Move();
	void Draw();

};
#endif // !_ENEMYDIVER_H__
