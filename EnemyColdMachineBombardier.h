#ifndef __ENEMYCOLDMACHINEBOMBARDIER_H__
#define __ENEMYCOLDMACHINEBOMBARDIER_H__

#include "Enemy.h"
#include "ModuleTextures.h"


class EnemyColdMachineBombardier : public Enemy
{
private:
	
	Animation fly;

	bool throwBomb = false;

public:

	EnemyColdMachineBombardier(int x, int y, powerUpTypes type, SDL_Texture* thisTexture);

	void Move();
	void Draw();



};

#endif // __ENEMYCOLDMACHINEBOMBARDIER__H__
