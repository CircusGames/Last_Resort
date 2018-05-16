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
	float distance; // nearest player

	SDL_Rect lamellaRect;

	Animation spawnAnim;
	Animation moveAnim;
	Animation despawnAnim;
	Animation* currentAnimation;

	iPoint originalPos;

public:

	EnemyLamella(int x, int y, powerUpTypes type, SDL_Texture* thisTexture = nullptr);

	void Move();
	void Draw();
};
#endif // !_POWERUPBEE_H__