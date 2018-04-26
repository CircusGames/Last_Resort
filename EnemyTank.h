#ifndef _ENEMYTANK_H__
#define _ENEMYTANK_H__

#include "Enemy.h"
#include "Path.h"
#include "ModuleTextures.h"


class EnemyTank : public Enemy
{
private:

	Path path;
	Animation staticAnim;
	Animation moveAnim;
	Animation boostAnim;
	Animation particlesAnim;
	iPoint originalPos;
	iPoint originalPos2;
	iPoint originalPos3;
	Animation bigTurretAnim;
	Animation smallTurretAnim;
	Animation* animation2 = nullptr;
	Animation* animation3 = nullptr;
	//iPoint position2;
	//iPoint position3;

	Collider* smallTurretCollider = nullptr;
	Collider* bigTurretCollider = nullptr;

	//turret pivots
	int bigTurretPivot[9] = { 2,0,0,0,0,0,0,0,0 };
	int smallTurretPivots[7] = { 2,0,0,0,0,0,0 };
	iPoint bigTurretPosition;
	iPoint smallTurretPosition;
	float omega;
	float angleX;
	float angleY;

public:

	EnemyTank(int x, int y, powerUpTypes, SDL_Texture* thisTexture = nullptr);
	void Move();
	void Draw();
};

#endif // !_ENEMYTANK_H__