#ifndef __ENEMYSUBMARINE_H__
#define __ENEMYSUBMARINE_H__

#include "Enemy.h"
#include "ModuleTextures.h"
#include "Module.h"

#define NUM_DESTROYABLE_PARTS 5
#define NUM_NONDESTROYABLE_PARTS 10

class EnemySubmarine : public Enemy
{
private:

//
	SDL_Rect submarineBodyRect;
	SDL_Rect submarineBodyDamageRect;
	Animation destroyedParts[NUM_DESTROYABLE_PARTS];
	//SDL_Rect nonDestroyedParts[NUM_NONDESTROYABLE_PARTS];

	struct Destroyable
	{
		Collider* collider = nullptr;
		SDL_Rect rect;
		int life = 1;
		iPoint position;
		bool destroyed = false;
	};

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

	Destroyable nonDestroyedParts[NUM_NONDESTROYABLE_PARTS];

};

#endif // __ENEMYPROTATOR__H__
