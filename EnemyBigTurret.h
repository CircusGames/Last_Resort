#ifndef _ENEMYBIGTURRET_H__
#define _ENEMYBIGTURRET_H__

#include "Enemy.h"
#include "Path.h"
#include "ModuleTextures.h"

class EnemyBigTurret : public Enemy
{
private:

	Path path;
	Animation rotateAnim;
	iPoint originalPos;

public:

	EnemyBigTurret(int x, int y, powerUpTypes, SDL_Texture* sprite = nullptr);
	void Move();
};

#endif // !_ENEMYSMALLTURRET_H__