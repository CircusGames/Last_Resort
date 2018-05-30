#ifndef __ENEMYCOLDMACHINE_H__
#define __ENEMYCOLDMACHINE_H__

#include "Enemy.h"
#include "ModuleTextures.h"


class EnemyColdMachine : public Enemy
{
private:
	

public:

	EnemyColdMachine(int x, int y, powerUpTypes type, SDL_Texture* thisTexture);

	void Move();


};

#endif // __ENEMYCOLDMACHINE_H__
