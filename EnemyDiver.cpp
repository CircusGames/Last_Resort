#include "Application.h"
#include "EnemyDiver.h"
#include "ModuleCollision.h"
#include "ModuleEnemies.h"
#include "ModuleRender.h"

#include "SDL\include\SDL_timer.h"

EnemyDiver::EnemyDiver(int x, int y, powerUpTypes type, SDL_Texture* thisTexture) : Enemy(x, y)
{
	enemyTex = thisTexture;

	distance = GetNearestPlayerSqrtDistance();

	//starting pivot
	if (nearestTarget == P1)
		pivot = App->player[0]->position.x;

	else if (nearestTarget == P2)
		pivot = App->player[1]->position.x;

	//facing left
	idleLeft.PushBack({ 0, 0, 35, 38 });
	animLeft.PushBack({ 58, 0, 29, 39 });
	animLeft.PushBack({ 110, 0, 29, 43 });
	animLeft.PushBack({ 162, 0, 34, 44 });
	animLeft.PushBack({ 219, 0, 29, 39 });

	//facing right
	idleRight.PushBack({ 0, 0, -35, 38 });
	animRight.PushBack({ 58, 0, -29, 39 });
	animRight.PushBack({ 110, 0, -29, 43 });
	animRight.PushBack({ 162, 0, -34, 44 });
	animRight.PushBack({ 219, 0, -29, 39 });

	animLeft.speed = animRight.speed = 0.1f;
	animLeft.repeat = animRight.repeat = false;

	//starting anim 
	if (pivot < position.x)
		currentAnimation = &idleLeft;

	else if (pivot > position.x)
		currentAnimation = &idleRight;

	//max jump height
	distance = 50;

	originalPos.x = x;
	originalPos.y = y;

	life = 3;
	enemyScore = 200;

	//idle timer
	totalTime = 2000;

	powerUpType = type;

	collider = App->collision->AddCollider({ 0, 0, 30, 40 }, COLLIDER_TYPE::COLLIDER_ENEMY, (Module*)App->enemies);
}

void EnemyDiver::Move()
{
	//height
	if (jumping)
	{
		if ((originalPos.y - position.y) >= distance)
		{
			jumping = false;
			startTime = SDL_GetTicks();
		}
		else
			position.y -= 1;
	}

}

void EnemyDiver::Draw()
{
	position.x += 1;
	//collider 
	if (collider != nullptr)
		collider->SetPos(position.x, position.y);

	//pivot update
	if (nearestTarget == P1)
		pivot = App->player[0]->position.x;

	else if (nearestTarget == P2)
		pivot = App->player[1]->position.x;

	//timer
	now = SDL_GetTicks() - startTime;

	if (now > totalTime)
		clock = true;

	//update animations
	if (!jumping)
	{
		if (pivot < position.x) //Left
		{
			currentAnimation = &idleLeft;
			if (clock)
			{
				currentAnimation = &animLeft;
				if (animLeft.finish);
				;// startTime = SDL_GetTicks();
			}
		}

		if (pivot > position.x) //Right
		{
			currentAnimation = &idleRight;
			if (clock)
			{
				currentAnimation = &animRight;
				if (animRight.finish);
				;// startTime = SDL_GetTicks();
			}
		}
	}

	diverRect = currentAnimation->GetCurrentFrame();
	App->render->Blit(enemyTex, position.x, position.y, &diverRect);
}