#ifndef __ENEMYBIGDADDY_H__
#define __ENEMYBIGDADDY_H__

#include "Enemy.h"
#include "ModuleTextures.h"
#include "Path.h"


class EnemyBigDaddy : public Enemy
{
private:

	enum currentState
	{
		FOREGROUND,
		ONSTAGE,
		GOODBYE
	};

	enum animationType
	{
		NORMAL_ANIM,
		DAMAGE_ANIM
	};

	SDL_Texture* laserTexture = nullptr;
	
	struct midBoss
	{

		Collider* fullBodyCollider = nullptr;
		Collider* damageCollider = nullptr;
		Animation onStageAnim[2]; // normal and taken damage
		Animation foregroundAnim;
		Animation laserFlashAnim;
		Animation* current_animation = nullptr;
		Path onStagePath;
		iPoint position;
		fPoint fposition;
		// timers -----------------
		// foreground time
		Uint32 start_foreground_time;
		Uint32 total_foreground_time;
		Uint32 now_foreground_time;
		// shooting timer
		Uint32 start_shoot_time;
		Uint32 now_shoot_time;
		Uint32 cadence_shoot_time;
		//
		const int maxCyclesOnStage = 4; // num of total attack loops (based on path full loops)
		bool attack = false;
		//
		uint numAlivePlayers = 0; // to num laser shoots logic

	};

	struct laserBeam
	{
		Animation anim[8][5]; // [num max laser angles][num parts anims] -> 1 cap 2 center 1 cap
		float distance[8][5];
		float xSpeed[8][5];
		float ySpeed[8][5];
		float playerAngle[8];
		iPoint position[8][5];
		iPoint instantiationPosition[4]; // one of the 4 boss spawn points
		bool active[8][5] = { false };
		SDL_Rect rect;
	    int	laserPartIndex[5]; // 1 full laser is composed by 4 animated parts, 1 left cap, 3 mid, 1 cap right
	};

	iPoint offset[8][4]; // stores the offsets positions to laser parts instantiation

public:

	EnemyBigDaddy(int x, int y, powerUpTypes type, SDL_Texture* thisTexture);
	~EnemyBigDaddy();

	void Move();
	void Draw();

	midBoss bigDaddy;
	laserBeam laser;  

	

};

#endif // __ENEMYBIGDADDY__H__
