#include "Application.h"
#include "EnemyDiver.h"
#include "ModuleCollision.h"
#include "ModuleEnemies.h"
#include "ModuleRender.h"
#include "ModuleParticles.h"

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

	for (int i = 0; i < 4; i++)
		shootLeft.PushBack({ 32 * i, 48, 32, 16 });

	//facing right
	idleRight.PushBack({ 0, 0, -35, 38 });
	animRight.PushBack({ 58, 0, -29, 39 });
	animRight.PushBack({ 110, 0, -29, 43 });
	animRight.PushBack({ 162, 0, -34, 44 });
	animRight.PushBack({ 219, 0, -29, 39 });

	for (int i = 0; i < 4; i++)
		shootRight.PushBack({ 32 * i, 48, -32, 16 });

	//spawn anim
	for (int i = 0; i < 6; i++)
		spawnAnim.PushBack({ 80 * i, 80, 80, 104 });

	for (int i = 0; i < 2; i++)
		spawnAnim.PushBack({ 80 * i, 184, 80, 104 });

	//features
	animLeft.speed = animRight.speed = 0.143f;
	animLeft.repeat = animRight.repeat = false;

	shootLeft.speed = shootRight.speed = 0.143f;
	shootLeft.repeat = shootRight.repeat = false;

	spawnAnim.speed = 0.1f;
	spawnAnim.repeat = false;

	//starting anim & shoot anim pushbacks
	if (pivot < position.x)
	{
		currentAnimation = &idleLeft;
		currentShootAnim = &shootLeft;
	}

	else if (pivot > position.x)
	{
		currentAnimation = &idleRight;
		currentShootAnim = &shootRight;
	}

	//max jump height
	distance = 50;

	originalPos.x = x;
	originalPos.y = y;

	life = 3;
	enemyScore = 200;

	//idle timer
	totalTime = 500;

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

	else
		clock = false;

	//shoot anim timer
	if ((currentAnimation->current_frame > 2)&&!shoot)
		shoot = true;

	if (currentShootAnim->finish)
	{
		shoot = false;
		bullet = true;
	}

	//spawn timer
	if (position.y > 88)
		spawn = true;

	//update animations --------------------------------------------------------

	// check if we are not in jump state (spawn state?)
	if (!jumping)
	{	// permits the pivot check only if the current animation condition is true (only idle)
		if (currentAnimation->repeat == true) 
		{
			if (pivot < position.x) left = true;
			else left = false;
		}
	}
	// movement
	if (left)
	{
		if (clock) currentAnimation = &animLeft;
		else 
			currentAnimation = &idleLeft;
	}
	else
	{
		if (clock) currentAnimation = &animRight;
		else
			currentAnimation = &idleRight;
	}
	// shot animation
	if (shoot)
	{
		if(left)
			currentShootAnim = &shootLeft;
		else
			currentShootAnim = &shootRight;
	}
	else
	{
		currentShootAnim->finish = false;
		currentShootAnim->current_frame = 0;
	}
	// resets "movement animations"
	if (currentAnimation->finish)
	{
		startTime = SDL_GetTicks();
		currentAnimation->finish = false;
		currentAnimation->current_frame = 0;
	}
	// ----------------------------------------------------------------------------	


		/*if (pivot < position.x) //Left
		{
			left = true;
			right = false;
		
				currentAnimation = &idleLeft;

				if (clock)
				{
					currentAnimation = &animLeft;
					//currentStateAnim = true;

					if (shoot)
					{
						currentShootAnim = &shootLeft;
					}

					else
					{
						currentShootAnim->finish = false;
						currentShootAnim->current_frame = 0;
						//currentStateAnim = false;
					}

					if (animLeft.finish)
					{
						startTime = SDL_GetTicks();
						animLeft.finish = false;
						animLeft.current_frame = 0;
						//currentStateAnim = false;
					}
				}
			
			
		}

		else if (pivot > position.x) //Right
		{
			right = true;
			left = false;

			currentAnimation = &idleRight;
			if (clock)
			{
					currentAnimation = &animRight;
				
					if (shoot)
					{
						currentShootAnim = &shootRight;
						//currentStateAnim = true;
					}

				else
				{
					currentShootAnim->finish = false;
					currentShootAnim->current_frame = 0;
					//currentStateAnim = false;

				}

				if (animRight.finish)
				{
					startTime = SDL_GetTicks();
					animRight.finish = false;
					animRight.current_frame = 0;
					//currentStateAnim = false;
				}
			}
		}
	}*/

	diverRect = currentAnimation->GetCurrentFrame();
	shootRect = currentShootAnim->GetCurrentFrame();
	spawnRect = spawnAnim.GetCurrentFrame();

	currentStepAnim = currentAnimation;

	if (shoot && bullet)
	{
		if (left)
			App->particles->AddParticle(App->enemies->diverBeamLeft, position.x - 11, position.y + 23, COLLIDER_ENEMY_SHOT, { -1, 0 });

		if (!left)
			App->particles->AddParticle(App->enemies->diverBeamRight, position.x + 13, position.y + 23, COLLIDER_ENEMY_SHOT, { 2, 0 });

		bullet = false;
	}

	App->render->Blit(enemyTex, position.x, position.y, &diverRect);

	if(spawn)
		App->render->Blit(enemyTex, position.x - 22, 88, &spawnRect);

	if (shoot )
	{
		if (left)
			App->render->Blit(enemyTex, position.x - 31, position.y + 18, &shootRect); //32

		else if (right)
			App->render->Blit(enemyTex, position.x + 33, position.y + 18, &shootRect);

		
	}

	

}