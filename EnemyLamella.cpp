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

	//starting pivot
	if (nearestTarget == P1)
		pivot = App->player[0]->position.x;

	else if (nearestTarget == P2)
		pivot = App->player[1]->position.x;

	if (pivot < position.x)
	{
		//spawn animation
		for (i = 0; i < 6; i++) // columns
		{
			for (j = 0; j < 6; j++) // rows
			{
				spawnAnim.PushBack({ 40 * j, 40 * i, 40, 40 });

				if (i == 5 && j == 1)
					break;
			}
		}

		//movement animation
		for (i = 2; i < 5; i++)
		{
			moveAnim.PushBack({ 40 * i, 200, 40, 40 });
		}

		//despawn animation
		for (i = 5; i >= 0; i--) // columns
		{
			if (i == 5)
			{
				for (j = 1; j >= 0; j--) // rows
				{
					despawnAnim.PushBack({ 40 * j, 40 * i, 40, 40 });
				}
			}

			else
			{
				for (j = 5; j >= 0; j--) // rows
				{
					despawnAnim.PushBack({ 40 * j, 40 * i, 40, 40 });
				}
			}
		}
	}

	else if (pivot > position.x)
	{
		//spawn animation
		for (i = 0; i < 6; i++) // columns
		{
			for (j = 0; j < 6; j++) // rows
			{
				spawnAnim.PushBack({ 40 * j, 40 * i, -40, 40 });

				if (i == 5 && j == 1)
					break;
			}
		}

		//movement animation
		for (i = 2; i < 5; i++)
		{
			moveAnim.PushBack({ 40 * i, 200, -40, 40 });
		}

		//despawn animation
		for (i = 5; i >= 0; i--) // columns
		{
			if (i == 5)
			{
				for (j = 1; j >= 0; j--) // rows
				{
					despawnAnim.PushBack({ 40 * j, 40 * i, -40, 40 });
				}
			}

			else
			{
				for (j = 5; j >= 0; j--) // rows
				{
					despawnAnim.PushBack({ 40 * j, 40 * i, -40, 40 });
				}
			}
		}
	}
	
	
	spawnAnim.speed = 0.3f;
	spawnAnim.repeat = false;

	moveAnim.speed = 0.15f;
	moveAnim.repeat = false;

	despawnAnim.speed = 0.3f;
	despawnAnim.repeat = false;

	currentAnimation = &spawnAnim;

	originalPos.x = x;
	originalPos.y = y;

	life = 0; //random
	enemyScore = 200; // random
	powerUpType = type;

	
}

void EnemyLamella::Move()
{
	if(collider != nullptr)
		collider->SetPos(position.x,position.y);

	if (spawnAnim.finish)
	{
		currentAnimation = &moveAnim;
		if (moveAnim.finish)
		{
			currentAnimation = &despawnAnim;
			life = 0;
		}
			

		if(collider == nullptr)
			collider = App->collision->AddCollider({ 0, 0, 30, 30 }, COLLIDER_TYPE::COLLIDER_ENEMY, (Module*)App->enemies);

		if (aimed)
		{
			distance = GetNearestPlayerSqrtDistance();
		}

		if (despawnAnim.finish)
		{
			life = 0;
		}
	}

	

	else
		position.x += 1;
}

void EnemyLamella::Draw()
{

	lamellaRect = currentAnimation->GetCurrentFrame();
	App->render->Blit(enemyTex, position.x, position.y, &lamellaRect);

}