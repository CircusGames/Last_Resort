#ifndef __ENEMYSUBMARINE_H__
#define __ENEMYSUBMARINE_H__

#include "Enemy.h"
#include "ModuleTextures.h"
#include "Module.h"

class EnemySubmarine : public Enemy
{
private:

//

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

};

#endif // __ENEMYPROTATOR__H__
