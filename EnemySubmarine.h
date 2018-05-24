#ifndef __ENEMYSUBMARINE_H__
#define __ENEMYSUBMARINE_H__

#include "Enemy.h"
#include "ModuleTextures.h"
#include "Module.h"
#include "Path.h"

#define NUM_DESTROYABLE_PARTS 5
#define NUM_NONDESTROYED_PARTS 8
#define NUM_TURRETS 8
#define NUM_WAVES 10

class EnemySubmarine : public Enemy
{
private:

	// missile launching relative ---
	/*Animation missileFlashAnimation;
	bool launchMissiles = false;
	bool readyToLaunch = false;
	bool missilesFlash = false;*/
	// ------------------------------

	enum takenDamageIndex
	{
		NORMAL_ANIM,
		DAMAGE_ANIM
	};

//
	SDL_Rect submarineBodyRect;
	SDL_Rect submarineBodyDamageRect;
	Animation destroyedParts[NUM_DESTROYABLE_PARTS];
	//Animation ejectionHatch[2]; // normal and taken damage animations
	//Animation missileLauncherAnim[1][2]; //1 for now until we get the sprites
	Collider* fullBodyColliders[NUM_NONDESTROYED_PARTS];
	Collider* coreCollider;
	//SDL_Rect fullBodyStaticDamage[NUM_NONDESTROYED_PARTS];

	// receiving damage values
	//bool receiveDamage;
	Uint32 start_damage_time;
	Uint32 nowDamagetime;
	Uint32 damageAnimTime = 50;

	struct DestroyableStatic
	{
		Collider* collider = nullptr;
		SDL_Rect normalRect;
		SDL_Rect takenDamageRect;
		int life = 1;
		iPoint position;
		bool destroyed = false;
	};

	struct DestroyableAnimated
	{
		Collider* collider = nullptr;
		Animation anim[2]; // normal and taken damage
		Animation* current_animation = nullptr;
		iPoint position;
		bool destroyed = false;
		bool throwEnemy = false;
		int life = 1;
		bool takenDamage = false;
		Uint32 start_damage_time;
		Uint32 now_damage_time;
		Uint32 damage_anim_time = 50;
		float current_frame;
		bool readyToTakeDamage = true;
		bool readyToEject = true;
		SDL_Rect rect;
		// missiles relative ---
		Animation missileFlashAnim[4]; // max flash canyons
		bool launchMissiles = false;
		bool readyToLaunch = false;
		bool missilesFlash = false;
		int canyons;
		iPoint canyonsPos[4];
		// ---------------------

	};

	struct turrets
	{
		Collider* collider;
		Animation anim[2]; // normal and taken damage
		Animation* current_animation = nullptr; // to swap damage/normal sprites on runtime
		float current_frame;
		SDL_Rect rect;
		iPoint position;
		bool destroyed = false;
		bool shot = false;
		bool takenDamage = false;
		int life = 5;
		// timers --------
		// shooting --
		Uint32 start_shot_time;
		Uint32 now_shot_time;
		Uint32 shot_cadence_timer = 2000;
		// damage --
		Uint32 start_damage_time;
		Uint32 now_damage_time;
		Uint32 damage_anim_time = 50;
		// ---------------
		float angle;
		float distance;

	};

	// gameplay timers ----------------------
	// ejectable enemy
	Uint32 start_ejectable_time;
	Uint32 now_ejectable_time;
	Uint32 ejectable_cadence_timer = 4200;
	// ---
	// missile launching
	Uint32 start_missiles_time;
	Uint32 now_missiles_time;
	Uint32 missiles_cadence_timer = 5500;
	// --------------------------------------

public:

	EnemySubmarine(int x, int y, powerUpTypes type, SDL_Texture* thisTexture);

	~EnemySubmarine();

	void Move();
	void Draw();
	void OnCollision(Collider* collider, Collider* collider2);

	void goTurretsGo();
	void goTurretsAttack();

	const Collider* EnemySubmarine::GetCollider() const;

	int positionPartsX[NUM_DESTROYABLE_PARTS] = {16, 128, 168, 208, 288};
	int positionPartsY[NUM_DESTROYABLE_PARTS] = {84, 80, 65, 19, 56};

	DestroyableStatic nonDestroyedParts[NUM_NONDESTROYED_PARTS];
	DestroyableAnimated ejectionHatch;
	DestroyableAnimated missileLauncher[2];
	turrets submarineTurrets[NUM_TURRETS];
	iPoint submarineTurretsPositions[NUM_TURRETS] = { {33,28}, {65,28}, {97,28}, {145,20}, {177, 4}, {289, -4}, {321, 12}, {353,12} };

	Path submarinePath;

	iPoint original_pos;

	SDL_Texture* submarineWavesTexture = nullptr;

	struct subWaves
	{
		Animation anim;
		iPoint position;
		iPoint originalPos;
		Path up;
		Path down;
	};
	
	subWaves submarineWaves[NUM_WAVES];

	bool launchDiver = false;

};

#endif // __ENEMYPROTATOR__H__
