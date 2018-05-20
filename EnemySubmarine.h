#ifndef __ENEMYSUBMARINE_H__
#define __ENEMYSUBMARINE_H__

#include "Enemy.h"
#include "ModuleTextures.h"
#include "Module.h"

#define NUM_DESTROYABLE_PARTS 5
#define NUM_NONDESTROYED_PARTS 9

class EnemySubmarine : public Enemy
{
private:

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
	Animation missileLauncherAnim[1][2]; //1 for now until we get the sprites
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
		Animation* current_animation;
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
	};

	// timers ----
	// ejectable enemy
	Uint32 start_ejectable_time;
	Uint32 now_ejectable_time;
	Uint32 ejectable_cadence_timer = 2000;
	// ---


public:

	EnemySubmarine(int x, int y, powerUpTypes type, SDL_Texture* thisTexture);

	~EnemySubmarine();

	void Move();
	void Draw();
	void OnCollision(Collider* collider, Collider* collider2);

	const Collider* EnemySubmarine::GetCollider() const;

	//Collider* rightCollider;
	//Collider* leftCollider;

	Module* desiredPlayerModule = nullptr;

	int positionPartsX[NUM_DESTROYABLE_PARTS] = {16, 128, 168, 208, 288};
	int positionPartsY[NUM_DESTROYABLE_PARTS] = {84, 80, 65, 19, 56};

	DestroyableStatic nonDestroyedParts[NUM_NONDESTROYED_PARTS];
	DestroyableAnimated ejectionHatch;
};

#endif // __ENEMYPROTATOR__H__
