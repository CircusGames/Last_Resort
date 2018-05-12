#ifndef _ENEMYLAMELLA_H__
#define _ENEMYLAMELLA_H__

#include "Enemy.h"
#include "ModuleTextures.h"

class EnemyLamella : public Enemy
{
private:

	float wave = -1.0f;
	bool going_up = true;
	int original_y = 0;

	Animation spawnAnim;
	Animation moveAnim;

	iPoint originalPos;
	iPoint finalPos;

public:

	EnemyLamella(int x, int y, powerUpTypes type, SDL_Texture* thisTexture = nullptr);

	void Move();
	void Draw();
};
#endif // !_POWERUPBEE_H__