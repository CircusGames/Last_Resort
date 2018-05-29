#ifndef _ENEMYLAMELLA_H__
#define _ENEMYLAMELLA_H__

#include "Enemy.h"
#include "ModuleTextures.h"

class EnemyLamella : public Enemy
{

private:

	int i, j;

	bool aimed = true;
	bool finalPos = false;

	bool alive = true;
	bool clock = false;
	bool once = true;

	Uint32 startTime;
	Uint32 now;
	Uint32 totalTime;

	float pivot;
	float distance;

	float xSpeed;
	float ySpeed;

	float chaseSpeed = 1.43f;

	bool xTargetReached = false;
	bool yTargetReached = false;
	bool targetReached = false;

	iPoint targetPosition;

	bool toLeft = false;
	bool toDown = false;

	SDL_Rect lamellaRect;

	Animation spawnAnim;
	Animation moveAnim;
	Animation despawnAnim;

	Animation* currentAnimation = nullptr;

	iPoint originalPos;

public:

	EnemyLamella(int x, int y, powerUpTypes type, SDL_Texture* thisTexture = nullptr);

	void Move();
	void Draw();
};
#endif // !_POWERUPBEE_H__