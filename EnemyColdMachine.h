#ifndef __ENEMYCOLDMACHINE_H__
#define __ENEMYCOLDMACHINE_H__

#include "Enemy.h"
#include "ModuleTextures.h"

#include "Path.h"


class EnemyColdMachine : public Enemy
{
private:

	enum bossState
	{
		LANDING,
		FIRSTCONTACT, // inmediately afet landing
		FASE1,
		FASE2
	};
	
	enum swapAnimType
	{
		NORMAL_ANIM,
		DAMAGE_ANIM
	};

	struct staticPieces
	{
		iPoint position;
		SDL_Rect rect[2]; // normal and damage
	};

	struct upperPart // only the top body block
	{
		Collider* collider = nullptr;
		iPoint position;
		fPoint fposition;
		// static pieces --------
		staticPieces chestPiece;
		// ----------------------
		// normal and damage // ONLY can receive damage when the part is open
		// enemy on this fase can be damaged ONLY on the eye, and the rest of parts swaps too to the damage
		Animation eyeAnim[2]; 
		Animation shoulderLauncherAnim[2];
		Animation chestCannonAnim[2];
		Animation shurikenLauncherAnim[2];
		Animation * current_animation = nullptr;
		float current_frame; // stores the current frame of the actual animation, for swaps between damage/normal
		// -----------------------
		// timers
		Uint32 upper_fase_time = 20000; // total time lasts the upper part boss fase
		Uint32 now_upper_fase_time;
		// -----------------------

		bool destroyed = false;
		int life = 70;

	};

	struct bottomPart // with arm, the arm is destroyed when the legs too
	{
		Collider* collider = nullptr;
		iPoint generalPosition;
		iPoint kneePos;
		fPoint fposition;
		// static pieces
		staticPieces footPiece;
		staticPieces lowerLegPiece;
		staticPieces kneePiece;
		staticPieces upperLegPiece;
		staticPieces hipPiece;
		// animations
		Animation kneeAnim[2];
		Animation missileLauncherAnim[2];
		Animation armShootgunAnim[2];
		Animation kneeFlashReflectionAnim;
		Animation* current_animation = nullptr;
		float current_frame;
		// timers ---------------------
		// general start cycle timer are on boss struct
		Uint32 bottom_fase_time = 20000;
		Uint32 now_bottom_fase_time;
		// missiles timers
		Uint32 start_missiles_time;
		Uint32 now_missiles_time;
		Uint32 missiles_cadence_time = 1000; // when each cycle starts (opens missile launcher gate)
		Uint32 time_between_missiles = 500; // time between each missile
		Uint32 start_missiles_wave; // time when starts one wave
		Uint32 now_missile_wave_time;
		Uint32 start_launch_time;
		Uint32 current_missile_time;
		Uint32 time_between_waves = 2500; // time between cycle waves (2 waves of 4 missiles, aproximated)
		//Uint32 time_throwing_missiles = 5000;
		uint missilesCount = 0; // each wave contains 4 missiles
		uint missilesWaveCount = 0;
		// knee laser
		Uint32 start_kneeBeam_time;
		Uint32 now_kneeBeam_time;
		Uint32 kneeBeam_cadence_time = 2000;
		//Uint32 kneBeam_reflection_time = 1000; // time since max open to close again and restart cycle
		// arm shooting
		Uint32 start_armShooting_time;
		Uint32 now_armShooting_time;
		Uint32 armShooting_cadence_time = 2000;
		// timer relative bools
		bool throwMissiles = false;
		bool shootedMissile = false;

		bool throwKneeBeam = false;
		bool shootedLaserBeam = false;
		bool playReflection = false;

		bool throwArmShoot = false;
		bool kneeFlashShoot = false;
		// ---------------------------
		SDL_Rect armShotgunRect;
		iPoint shotGunPivots[4] = { { 136,-15 },{ 116,0 },{ 91,0 },{ 116,0 } }; //{110,-24}, {90,0 }, {65,0}, {90,0} };
		iPoint missileCanyonsPos[4] = { { -22, 52},{ -12, 52 },{ -22, 60 },{ -12, 60 } };

		bool destroyed = false;
		int life = 70;

	};

	struct pathAnims
	{
		Path lowerLeg;
		Path knee;
		Path upperLeg;
		Path hip;
		Path arm;
		Path chest;
	};

	struct boss
	{
		Collider* bodyCollider = nullptr;
		iPoint position;
		fPoint fposition;
		Animation* current_animation = nullptr;
		// parts struct ----
		upperPart chest;
		bottomPart legs;
		// -----------------
		pathAnims firstContact; // damp animation with particles

		bossState state;
		// timers --------------------
		// general cycle timer
		Uint32 start_cycle_time;
		Uint32 now_cycle_time;
		Uint32 total_enemy_time;
		Uint32 total_firstContact_time = 2000;
		// general damage timers (all parts)
		Uint32 start_damage_time;
		Uint32 now_damage_time;
		Uint32 total_damage_time = 50;
		// ---------------------------

		bool destroyed = false;
		bool stopAnimations = false;

		int total_life;
		swapAnimType current_sprite_type = swapAnimType::NORMAL_ANIM;
		SDL_Rect rect;

		float ySpeed = 0.0f;
		float xSpeed = 0.0f;
		
	};

	struct originalPos
	{
		iPoint lowerLeg;
		iPoint knee;
		iPoint upperLeg;
		iPoint hip;
		iPoint arm;
		iPoint chest;

	};

	originalPos original;

	int scrollSpeed = 1;

	

public:

	EnemyColdMachine(int x, int y, powerUpTypes type, SDL_Texture* thisTexture);

	void Move();
	void Draw();
	SDL_Rect& returnRect(Animation* anim);
	void decelerationToFloor();
	void firstContactAnimation();
	void addBossParticles();

	// FASE1 functions
	void missilesLogic();
	void kneeBeamLogic();

	boss coldMachine;

	

};

#endif // __ENEMYCOLDMACHINE_H__