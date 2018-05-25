#ifndef _ENEMYMINITANK__H_
#define _ENEMYMINITANK__H_

#include "Enemy.h"
#include "Path.h"
#include "ModuleTextures.h"

#define NUM_ROCKETS 2

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

	struct smokeShoot
	{
		Animation anim;
		SDL_Rect rect;
		iPoint position;
		bool playPipeSmoke = false;
	};

	struct miniTank
	{

		Collider* leftCol = nullptr;
		Collider* rightCol = nullptr;
		Animation moveAnim[2]; // normal and take damage
		Animation shootAnim[2]; // normal and take damage
		Animation dustAnim; // particles of wheel chains
		//Animation shotSmokeAnim; // particles when enemy shoots
		Animation* current_animation = nullptr;
		// timers ------
		Uint32 start_shot_time;
		Uint32 now_shot_time;
		Uint32 cadence_between_shots = 2400; // testing value
		// travel timers --- with distance points with the scroll... meh
		Uint32 start_travel_time;
		Uint32 now_travel_time;
		Uint32 time_travelling = 2000;
		// damage timers ---
		Uint32 start_damage_time;
		Uint32 now_damage_time;
		Uint32 duration_damage_time = 50;
		// ----------
		float current_frame;
		bool moveLeft = false;
		//bool moveRight = false;
		iPoint position;
		fPoint fposition;
		float xSpeed = 0.4f;
		// travel values
		iPoint initialTravelPosition;
		fPoint targetTravelPosition;
		const int maxTravelDistance = 110;
		float currentTraveledDistance;
		bool travelDone = false;
		bool shoot = false;
		SDL_Rect rect;
		bool leftCollision = false;
		bool rightCollision = false;
		bool firstCollision = false;
		//bool playPipeSmoke = false;
		smokeShoot pipeSmoke[NUM_ROCKETS];
		bool takeDamage = false;
	};

	

public:

	Enemy_MiniTank(int x, int y, powerUpTypes type, SDL_Texture * thisTexture = nullptr);
	~Enemy_MiniTank();

	void Move();
	void Draw();
	void OnCollision(Collider* collider, Collider* collider2);
	const Collider* GetCollider() const;

	miniTank cartePillar;
	//smokeShoot pipeSmoke[NUM_ROCKETS];
};


#endif // !_ENEMYMINITANK__H_

