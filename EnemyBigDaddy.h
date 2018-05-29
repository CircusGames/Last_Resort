#ifndef __ENEMYBIGDADDY_H__
#define __ENEMYBIGDADDY_H__

#include "Enemy.h"
#include "ModuleTextures.h"
#include "Path.h"

#define MAX_NUM_LASERS 4


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
		Uint32 cadence_shoot_time = 1000;
		//
		const int maxCyclesOnStage = 4; // num of total attack loops (based on path full loops)
		bool attack = false;
		//
		//uint numAlivePlayers = 0; // to num laser shoots logic
		iPoint instantiationPosition[4]; // one of the 4 boss spawn points
		

	};

	struct laserBeam
	{
		Animation anim[8][5]; // [num max laser angles][num parts anims] -> 1 cap 2 center 1 cap
		float distance;//[8][5];
		float xSpeed;//[8][5];
		float ySpeed;//[8][5];
		float playerAngle;//[8];
		iPoint position[8][5];
		fPoint fposition[8][5];
		//iPoint instantiationPosition[4]; // one of the 4 boss spawn points
		bool active[8][5] = { false };
		SDL_Rect rect;
	    int	laserPartIndex[5]; // 1 full laser is composed by 4 animated parts, 1 left cap, 3 mid, 1 cap right
		int laserAxisIndex;//[16]; // indicates wich direction we have to instantiate 0 to 15 ( 16 axis )
		uint instantiationPoint;
		uint part;
	};

	iPoint offset[8][5]; // stores the offsets positions to laser parts instantiation

	int distanceManhattan;

	// distances respect the instatiation part (cap) of the laser, to activate the rest
	int maxDistances[5] = { 16,32,48,64,80 };

	SDL_Rect flashAnimRect;
	iPoint pivotFlashAnim[6] = { { 0,0 },{ -1,-1 },{ -3,-3 },{ -5,-5 },{ -3,-3 },{ -1,-1 } };

	//bool noFollow = false;

	int instantiationIndex;

	int numActiveLasers = 2; // always have 2 lasers active, 2 players 4 lasers

	// timer for destroy all the lasers at once
	Uint32 start_all_shoots_time;
	Uint32 now_all_shoots_time;
	Uint32 time_to_destroy = 1000;


public:

	EnemyBigDaddy(int x, int y, powerUpTypes type, SDL_Texture* thisTexture);
	~EnemyBigDaddy();

	void Move();
	void Draw();

	void youDecide();
	void assignAxis(uint index);

	midBoss bigDaddy;
	laserBeam laser[4]; // max lasers count situation

	
	float checkInstantiationDistance;

	int maxFarAwayDistances[2]; // only two values we need to check, the cap and the mids

	float otherDistance;
	int blabla;
	

};

#endif // __ENEMYBIGDADDY__H__
