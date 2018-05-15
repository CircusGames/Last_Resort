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

	distance = GetNearestPlayerSqrtDistance();
	if (distance > position.x)
	{

		for (i = 0; i < 6; i++) // columns
		{
			for (j = 0; j < 6; j++) // rows
			{
				spawnAnim.PushBack({ 40 * j, 40 * i, 40, 40 });

				if (i > 4 && j > 1)
					break;
			}
		}

		for (i = 2; i < 6; i++)
		{
			moveAnim.PushBack({ 40 * i, 240, 40, 40 });
		}
	}

	else
	{
		for (i = 0; i < 6; i++) // columns
		{
			for (j = 0; j < 6; j++) // rows
			{
				spawnAnim.PushBack({ 40 * j, 40 * i, -40, 40 });

				if (i > 4 && j > 1)
					break;
			}
		}

		for (i = 2; i < 5; i++)
		{
			moveAnim.PushBack({ 40 * i, 240, -40, 40 });
		}
	}
	
	
	spawnAnim.speed = 0.5f;
	spawnAnim.repeat = false;

	moveAnim.speed = 0.3f;

	currentAnimation = &spawnAnim;

	originalPos.x = x;
	originalPos.y = y;

	life = 3; //random
	enemyScore = 200; // random
	powerUpType = type;

	collider = App->collision->AddCollider({ 0, 0, 15, 9 }, COLLIDER_TYPE::COLLIDER_ENEMY, (Module*)App->enemies);
}

void EnemyLamella::Move()
{
	if (spawnAnim.finish)
	{
		animation = &moveAnim;
		position.x += 1;

		if (aimed)
			distance = GetNearestPlayerSqrtDistance();
	}

	else
		position.x += 1;
}

void EnemyLamella::Draw()
{
	lamellaRect = currentAnimation->GetCurrentFrame();
	App->render->Blit(enemyTex, position.x, position.y, &lamellaRect);
}