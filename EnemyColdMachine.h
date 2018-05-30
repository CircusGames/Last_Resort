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
		staticPieces fullChest;
		// ----------------------
		// normal and damage // ONLY can receive damage when the part is open
		// enemy on this fase can be damaged ONLY on the eye, and the rest of parts swaps too to the damage
		Animation eyeAnim[2]; 
		Animation shoulderLauncher[2];
		Animation chestCannon[2];
		Animation shurikenLauncher[2];
		Animation * current_animation = nullptr;
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
		// animations
		Animation kneeAnim[2];
		Animation missileLauncher[2];
		Animation armShootgun[2];
		Animation* current_animation = nullptr;
		// timers ----
		Uint32 bottom_fase_time = 20000;
		Uint32 now_bottom_fase_time;
		// -----------
		Uint32 start_damage_time;
		Uint32 now_damage_time;
		Uint32 total_damage_time = 50;


		bool destroyed = false;
		int life = 70;

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
		Path spawn; // damp animation with particles

		bossState state;
		// timers -----
		Uint32 start_cycle_time;
		Uint32 total_enemy_time;
		// ------------

		bool destroyed = false;

		int total_life;
	};



public:

	EnemyColdMachine(int x, int y, powerUpTypes type, SDL_Texture* thisTexture);

	void Move();
	void Draw();

	boss coldMachine;


};

#endif // __ENEMYCOLDMACHINE_H__
