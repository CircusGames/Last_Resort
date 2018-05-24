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
	for (int i = 1; i >= 0; --i)
		spawnAnim.PushBack({ 80 * i, 184, 80, 104 });
	for (int i = 5; i >= 0; --i)
		spawnAnim.PushBack({ 80 * i, 80, 80, 104 });

	

	//features
	animLeft.speed = animRight.speed = 0.25f;
	animLeft.repeat = animRight.repeat = false;

	shootLeft.speed = shootRight.speed = 0.25f;
	shootLeft.repeat = shootRight.repeat = false;

	spawnAnim.speed = 0.125f;
	spawnAnim.repeat = false;

	//starting anim & shoot anim pushbacks
	if (pivot <= position.x) // in case of distance 0, prevail left animation
	{
		currentAnimation = &idleLeft;
		currentShootAnim = &shootLeft;
	}

	else if (pivot > position.x)
	{
		currentAnimation = &idleRight;
		currentShootAnim = &shootRight;
	}

	originalPos.x = x;
	originalPos.y = y;

	fposition.y = originalPos.y;
	fposition.x = originalPos.x;

	// assigns jump height based on instantate y
	//max jump height
	if (originalPos.y > waterLevel)
		distance = 120;
	else
		distance = 50;
	// water splash spawn checker
	if (originalPos.y > waterLevel)
		spawn = true;

	life = 1;
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
			decelerate = true;
		}
		
		if (decelerate)
		{
			jumpSpeed -= 0.07f;
			if (jumpSpeed <= -0.5f)
				jumping = false;
		}
		
		fposition.y -= jumpSpeed;
		position.y = fposition.y;
	}

	if (!jumping)
	{
		if (currentAnimation->repeat != false)
		{
			distance = GetNearestPlayerSqrtDistance();

			xSpeed = (tx / distance)*chaseSpeed;
			ySpeed = (ty / distance)*chaseSpeed;

			fposition.x += xSpeed;
			fposition.y += ySpeed;
		}
	}

	fposition.x += 1;
	position.x = fposition.x;
	position.y = fposition.y;
}

void EnemyDiver::Draw()
{
	
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
	// -----------------------------

	//update animations --------------------------------------------------------

	// check if we are not in jump state (spawn state?)
	if (!jumping)
	{	// permits the pivot check only if the current animation repeat condition is true (only idle in this case)
		if (currentAnimation->repeat == true && !shootingFlash) 
		{
			if (pivot < position.x) left = true;
			else left = false;
		}
	}
	// movement
	if (left && !jumping)
	{
		if (clock) currentAnimation = &animLeft;
		else 
			currentAnimation = &idleLeft;
	}
	else if (!left && !jumping)
	{
		if (clock) currentAnimation = &animRight;
		else
			currentAnimation = &idleRight;
	}
	// shot animation
	if (shootingFlash)
	{
		if (left) 
			currentShootAnim = &shootLeft;
		else 
			currentShootAnim = &shootRight;
			
	}
	// resets "movement animations"
	if (currentAnimation->finish)
	{
		startTime = SDL_GetTicks();
		currentAnimation->finish = false;
		currentAnimation->current_frame = 0;
	}
	// ----------------------------------------------------------------------------	

	diverRect = currentAnimation->GetCurrentFrame();
	shootRect = currentShootAnim->GetCurrentFrame();
	spawnRect = spawnAnim.GetCurrentFrame();

	// ----------------------------------------------------------------------------
	// checks correct frame for instantiate shooting effect
	if ((int)currentAnimation->current_frame == 3 && !shootingFlash)
	{
		shootingFlash = true;
		shootParticle = true;
	}
	
	if (shootParticle)
	{
		if (left)
			App->particles->AddParticle(App->enemies->diverBeamLeft, position.x - 11, position.y + 23, COLLIDER_ENEMY_SHOT, { -1, 0 });

		if (!left)
			App->particles->AddParticle(App->enemies->diverBeamRight, position.x + 13, position.y + 23, COLLIDER_ENEMY_SHOT, { 2, 0 });

		shootParticle = false;
	}

	// enemy draw
	App->render->Blit(enemyTex, position.x, position.y, &diverRect);

	// water splash effect
	if (spawn)
	{
		App->render->Blit(enemyTex, position.x - 22, 88, &spawnRect);
		if (spawnAnim.finish) spawn = false;
	}

	if (shootingFlash)
	{
		if (left)
			App->render->Blit(enemyTex, position.x - 25 , position.y + 19, &shootRect);

		else if (!left)
			App->render->Blit(enemyTex, position.x + 27, position.y + 19, &shootRect);
		
		if (currentShootAnim->finish)
		{
			shootingFlash = false;
			currentShootAnim->finish = false;
			currentShootAnim->current_frame = 0;
		}
	}

	

}