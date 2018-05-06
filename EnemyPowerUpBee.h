#ifndef _POWERUPBEE_H__
#define _POWERUPBEE_H__

#include "Enemy.h"
#include "ModuleTextures.h"

class EnemyPowerUpBee : public Enemy
{
private:
	float wave = -1.0f;
	bool going_up = true;
	int original_y = 0;
	
	Animation waveAnim;
	Animation moveAnim;
	Animation landAnim;

	iPoint original_pos;

public:
	EnemyPowerUpBee(int x, int y, powerUpTypes type, SDL_Texture* thisTexture = nullptr);

	void Move();
};
#endif // !_POWERUPBEE_H__
