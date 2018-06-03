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
		F1TOF2,
		FASE2,
		TOEXPLODE
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
		// eye timers
		Uint32 start_eye_time;
		Uint32 now_eye_time;
		Uint32 time_between_eye = 2500;
		// -----------------------
		Uint32 start_shuriken_time;
		Uint32 now_shuriken_time;
		Uint32 shuriken_cadenece_time = 500;
		Uint32 shuriken_waves_time = 2000;
		int numShurikens = 0;
		// -----------------------
		Uint32 start_glass_cannon_time;
		Uint32 now_glass_cannon_time;
		Uint32 time_waiting_for_glass = 2000;

		bool destroyed = false;
		int life = 70;

		iPoint missileCanyonsPos[4] = { { 36, 78 },{ 36, 72},{ 42, 64 },{ 42, 56 } };

		//
		bool throwShuriken = false;
		bool throwGlassCannon = false;
		bool shootedGlass = false;
		bool instantiatedGlass = false;

	};

	struct shipBombs
	{
		Collider* collider = nullptr;
		Animation anim;
		iPoint position;
		bool throwBombs = false;
		bool instantiate = false;

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
		Uint32 kneeBeam_cadence_time = 4000;
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
		SDL_Rect armShotgunRect; // 0
		iPoint shotGunPivots[9] = { { 136,-15 },{ 116,0 },{ 91,8 },{ 91,8 },{ 91,8 },{ 91,8 },{ 116,0 },{ 136,-15 },{ 136,-15 } }; //{110,-24}, {90,0 }, {65,0}, {90,0} };
		iPoint missileCanyonsPos[4] = { { -22, 52},{ -12, 52 },{ -22, 60 },{ -12, 60 } };

		bool destroyed = false;
		bool destroyedHip = false; // for f1 to f2 transition
		int life = 70;

		

	};

	struct pathAnims
	{
		Path foot;
		Path lowerLeg;
		Path knee;
		Path upperLeg;
		Path hip;
		Path arm;
		Path chest;
	};

	struct boss
	{
		Collider* chestCollider = nullptr;
		Collider* legCollider = nullptr;
		Collider* upEyeCollider = nullptr;
		Collider* kneeCollider = nullptr;
		iPoint position;
		fPoint fposition;
		Animation* current_animation = nullptr;
		// parts struct ----
		upperPart chest;
		bottomPart legs;
		// -----------------
		pathAnims firstContact; // damp animation with particles
		pathAnims f1Tof2Path;

		bossState state;
		// timers --------------------
		// general cycle timer
		Uint32 start_cycle_time;
		Uint32 now_cycle_time;
		Uint32 total_enemy_time;
		Uint32 total_firstContact_time = 1500;
		Uint32 fase1_total_time = 30000; //2000;//30000;
		Uint32 fase2_total_time = 60000;
		// fase 2 timers
		Uint32 start_corner_time;
		Uint32 now_corner_time;
		Uint32 total_corner_time = 5000;
		bool leftCorner = false;
		bool rightCorner = false;
		bool moveToLeft = true;
		bool move = false;// true; // cold machine falls and direct left move
		//bool
		// general damage timers (all parts)
		Uint32 start_damage_time;
		Uint32 now_damage_time;
		Uint32 total_damage_time = 50;
		// ---------------------------
		Uint32 start_exploding_time;
		Uint32 now_exploding_time;
		Uint32 time_exploding = 1000;

		bool destroyed = false;
		bool stopAnimations = false;

		int total_life;
		swapAnimType current_sprite_type = swapAnimType::NORMAL_ANIM;
		SDL_Rect rect;

		float ySpeed = 0.0f;
		float xSpeed = 0.0f;
		
		shipBombs bombardier;

		iPoint f1Tof1ParticlePoints[6] = { { 20,160 },{ 30,170 },{ 50,160 },{ 20,200 },{ 36,186 },{ 60,194 } }; // 10
		int f1Tof1ParticlesDelay[6] = { 0,250,0,20,0,0};// 16
		
		bool destroyedFase1 = false;
		bool destroyedFase2 = false;
	};

	struct originalPos
	{
		iPoint foot;
		iPoint lowerLeg;
		iPoint knee;
		iPoint upperLeg;
		iPoint hip;
		iPoint arm;
		iPoint chest;

	};

	originalPos original;

	int scrollSpeed = 0;

	// sinusoidal movement fase2
	float wave = 1.0f;
	bool going_up = false;

	

public:

	EnemyColdMachine(int x, int y, powerUpTypes type, SDL_Texture* thisTexture);
	~EnemyColdMachine();

	void Move();
	void Draw();
	void OnCollision(Collider* collider, Collider* collider2);
	const Collider* EnemyColdMachine::GetCollider() const;

	SDL_Rect& returnRect(Animation* anim);
	void decelerationToFloor();
	void firstContactAnimation();
	void addBossParticles();
	void F1ToF2Transition();
	void updateOriginalPositions();

	// FASE1 functions
	void missilesLogic();
	void kneeBeamLogic();
	// FASE2 functions
	void fase2MovementLogic();
	void fase2AttackManager();
	// to explode
	void toExplode();

	boss coldMachine;

	

};

#endif // __ENEMYCOLDMACHINE_H__
