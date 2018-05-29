#include "Application.h"
#include "EnemyLamella.h"
#include "ModuleCollision.h"
#include "ModuleEnemies.h"
#include "ModuleParticles.h"
#include "ModuleRender.h"

#include "SDL\include\SDL_timer.h"

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

	if (pivot > position.x)
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

	else if (pivot < position.x)
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
	
	
	spawnAnim.speed = despawnAnim.speed = 0.3f;
	spawnAnim.repeat = despawnAnim.repeat = false;

	moveAnim.speed = 0.15f;
	moveAnim.repeat = true;

	currentAnimation = &spawnAnim;

	originalPos.x = x;
	originalPos.y = y;

	fposition.y = originalPos.y;
	fposition.x = originalPos.x;

	life = 0; //random
	enemyScore = 200; // random
	powerUpType = type;

	totalTime = 1000;

	position = originalPos;
}

void EnemyLamella::Move()
{
	if (now > totalTime)
		clock = true;

	if (spawnAnim.finish && !targetReached)
	{
		if(once) startTime = SDL_GetTicks();

		now = SDL_GetTicks() - startTime;
		once = false;

		currentAnimation = &moveAnim;

		if (aimed&clock)
		{
			distance = GetNearestPlayerSqrtDistance();
			aimed = false;

			if (nearestTarget == P1) targetPosition = App->player[0]->position;
			else targetPosition = App->player[1]->position;

			if (targetPosition.x >= position.x) toLeft = true;
			if (targetPosition.y >= position.y) toDown = true;
			
			xSpeed = (tx / distance)*chaseSpeed;
			ySpeed = (ty / distance)*chaseSpeed;
		}
		
		//fposition.y += ySpeed;
		//fposition.x += xSpeed;

		if (!yTargetReached)
		{
			if (toDown)
			{
				if (position.y > targetPosition.y)
					yTargetReached = true;
			}
			else
			{
				if (position.y < targetPosition.y)
					yTargetReached = true;
			}
			fposition.y += ySpeed;
		}

		if (!xTargetReached)
		{
			if (toLeft)
			{
				if (position.x > targetPosition.x)
					xTargetReached = true;

			}
			else
			{
				if (position.x < targetPosition.x)
					xTargetReached = true;
			}
			
			fposition.x += xSpeed;
		}
		if (xTargetReached & yTargetReached)
			targetReached = true;

		if (targetReached)
			currentAnimation = &despawnAnim;
			

	}

	targetPosition.x += 1;

	fposition.x += 1;
	position.x = fposition.x;
	position.y = fposition.y;
}

void EnemyLamella::Draw()
{
	// collider
	if (collider == nullptr && spawnAnim.finish && !targetReached)
		collider = App->collision->AddCollider({ 0, 0, 30, 30 }, COLLIDER_TYPE::COLLIDER_ENEMY, (Module*)App->enemies);

   if (collider != nullptr)
		collider->SetPos(position.x, position.y);

   if (targetReached)
   {
	   if (collider != nullptr)
	   {
		   collider->to_delete = true;
		   collider = nullptr;
	   }	
   }
	//print
	lamellaRect = currentAnimation->GetCurrentFrame();

	if (alive)
	{
		App->render->Blit(enemyTex, position.x, position.y, &lamellaRect);
		
		if (despawnAnim.finish)
			alive = false;
	}
}