#include "Application.h"
#include "EnemyLamella.h"
#include "ModuleCollision.h"
#include "ModuleEnemies.h"
#include "ModuleParticles.h"
#include "ModuleRender.h"

EnemyLamella::EnemyLamella(int x, int y, powerUpTypes type, SDL_Texture* thisTexture) : Enemy(x, y)
{
	// correct texture link
	enemyTex = thisTexture; 

	// spawn &  move animation
	for (int i = 0; i < 6; i++)
	{
		for (int j = 0; j < 6; j++)
		{
			spawnAnim.PushBack({ 40 * j, i*40, 40, 40 });
		}
	}
	spawnAnim.speed = 0.5f;
	//animation = &spawnAnim; // links first animation

	originalPos.x = x;
	originalPos.y = y;

	life = 3; //random
	enemyScore = 200; // random
	powerUpType = type;

	collider = App->collision->AddCollider({ 0, 14, 26, 18 }, COLLIDER_TYPE::COLLIDER_ENEMY, (Module*)App->enemies);
}

void EnemyLamella::Move()
{
	/*collider->SetPos(position.x, position.y + 7);

	if (going_up)
	{
		if (wave > 1.0f)
			going_up = false;
		else
			wave += 0.08f;
	}
	else
	{
		if (wave < -1.0f)
			going_up = true;
		else
			wave -= 0.08f;
	}

	position.y = original_y + int(20.0f * sinf(wave));*/
	position.x += 1;
}

void EnemyLamella::Draw()
{
	App->render->Blit(enemyTex, position.x, position.y, &spawnAnim.GetCurrentFrame());
}