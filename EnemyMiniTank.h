#ifndef _ENEMYMINITANK__H_
#define _ENEMYMINITANK__H_

#include "Enemy.h"
#include "Path.h"
#include "ModuleTextures.h"

class Enemy_MiniTank : public Enemy
{
private:
	/*Path path;
	iPoint original_pos;
	Animation move, move2, damage, damage2;
	Animation * shootanimation = nullptr;
	Animation* shootanimationdamage = nullptr;
	Animation * current_animation = nullptr;
	Animation missilelaunch;
	Animation missileexplode;
	Animation missile;
	Animation fire;
	Animation missilesmoke;
	Uint32 start_time;
	Uint32 start_damage_time;
	Uint32 nowDamagetime;
	Uint32 damageAnimTime;
	float current_frame;*/

	// --------------------------------------------

	enum swapAnimType
	{
		NORMAL_ANIM,
		DAMAGE_ANIM
	};

	struct miniTank
	{

		Collider* leftCol = nullptr;
		Collider* rightCol = nullptr;
		Animation moveAnim[2]; // normal and take damage
		Animation shootAnim[2]; // normal and take damage
		Animation dustAnim; // particles of wheel chains
		Animation shotSmokeAnim; // particles when enemy shoots
		Animation* current_animation = nullptr;
		const int maxTravelDistance = 100;
		int currentTraveledDistance;
		bool travelDone = false;
		// timers
		Uint32 start_shot_time;
		Uint32 now_shot_time;
		Uint32 cadence_between_shots = 2000; // testing value
		float current_frame;

	};

public:

	Enemy_MiniTank(int x, int y, powerUpTypes type, SDL_Texture * thisTexture = nullptr);

	void Move();
	void Draw();
	void OnCollision(Collider* collider, Collider* collider2);

	miniTank cartePillar;
};


#endif // !_ENEMYMINITANK__H_

