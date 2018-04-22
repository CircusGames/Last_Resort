#ifndef _ENEMYSMALLTURRET_H__
#define _ENEMYSMALLTURRET_H__

#include "Enemy.h"
#include "Path.h"
#include "ModuleTextures.h"

class EnemySmallTurret : public Enemy
{
private:

	Path path;
	Animation rotateAnim;
	iPoint originalPos;

public:

	EnemySmallTurret(int x, int y, powerUpTypes, SDL_Texture* sprite = nullptr);
	void Move();
};

#endif // !_ENEMYSMALLTURRET_H__*/
