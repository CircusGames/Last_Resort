#ifndef __ENEMYPILOT_H__
#define __ENEMYPILOT_H__

#include "Enemy.h"
#include "ModuleTextures.h"
#include "Path.h"

class EnemyPilot: public Enemy
{
private:
	Path path;
	Animation die;
	iPoint original_pos;

public:

	EnemyPilot(int x, int y, powerUpTypes type, SDL_Texture* thisTexture);

	void Move();
	void Draw();
	void Suicide();
};

#endif // __ENEMY__H__

