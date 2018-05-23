#ifndef _ENEMYMINITANK__H_
#define _ENEMYMINITANK__H_

#include "Enemy.h"
#include "Path.h"
#include "ModuleTextures.h"

class Enemy_MiniTank : public Enemy
{
private:
	Path path;
	iPoint original_pos;
	Animation move, move2, damage, damage2;
	Animation * shootanimation;
	Animation* shootanimationdamage;
	Animation * current_animation;
	Uint32 start_damage_time;
	Uint32 nowDamagetime;
	Uint32 damageAnimTime;
	float current_frame;

public:

	Enemy_MiniTank(int x, int y, powerUpTypes type, SDL_Texture * thisTexture = nullptr);

	void Move();
	void Draw();
};


#endif // !_ENEMYMINITANK__H_

