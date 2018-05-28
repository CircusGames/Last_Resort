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
		Uint32 cadence_shoot_time = 2000;
		//
		const int maxCyclesOnStage = 4; // num of total attack loops (based on path full loops)
		bool attack = false;
		//
		uint numAlivePlayers = 0; // to num laser shoots logic
		

	};

	struct laserBeam
	{
		Animation anim[8][5]; // [num max laser angles][num parts anims] -> 1 cap 2 center 1 cap
		float distance;//[8][5];
		float xSpeed;//[8][5];
		float ySpeed;//[8][5];
		float playerAngle;//[8];
		iPoint position[8][5];
		iPoint instantiationPosition[4]; // one of the 4 boss spawn points
		bool active[8][5] = { false };
		SDL_Rect rect;
	    int	laserPartIndex[5]; // 1 full laser is composed by 4 animated parts, 1 left cap, 3 mid, 1 cap right
		int laserAxisIndex;//[16]; // indicates wich direction we have to instantiate 0 to 15 ( 16 axis )
		uint instantiationPoint;
	};

	iPoint offset[8][5]; // stores the offsets positions to laser parts instantiation

	int distanceManhattan;

	int maxDistances[5] = { 16,32,48,64,80 };

	SDL_Rect flashAnimRect;
	iPoint pivotFlashAnim[6] = { { 0,0 },{ -1,-1 },{ -3,-3 },{ -5,-5 },{ -3,-3 },{ -1,-1 } };

	//bool noFollow = false;


public:

	EnemyBigDaddy(int x, int y, powerUpTypes type, SDL_Texture* thisTexture);
	~EnemyBigDaddy();

	void Move();
	void Draw();

	void youDecide();

	midBoss bigDaddy;
	laserBeam laser;

	
	float checkInstantiationDistance;

	int maxFarAwayDistances[2]; // only two values we need to check, the cap and the mids

	float otherDistance;
	int blabla;
	

};

#endif // __ENEMYBIGDADDY__H__
