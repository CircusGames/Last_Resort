#include "Application.h"
#include "EnemyProtator.h"
#include "ModuleCollision.h"
#include "ModuleEnemies.h"

#include "ModulePlayer.h"
#include "ModuleRender.h"

#include "ModuleSceneLvl3.h"

//#include "Module.h"

EnemyProtator::EnemyProtator(int x, int y, powerUpTypes type, SDL_Texture* thisTexture) : Enemy(x, y)
{
	//links the correct spritesheet texture ----
	enemyTex = thisTexture;
	// -----------------------------------------
	//protator normal animation ----
	protatorAnim.PushBack({ 0,0,32,32 });
	protatorAnim.PushBack({ 33,0,32,30 });
	protatorAnim.PushBack({ 66,0,32,28 });
	protatorAnim.PushBack({ 99,0,32,26 });
	protatorAnim.PushBack({ 132,0,32,26 });
	protatorAnim.PushBack({ 0,33,30,26 });
	protatorAnim.PushBack({ 31,33,32,26 });
	protatorAnim.PushBack({ 64,33,32,30 });
	protatorAnim.PushBack({ 97,33,32,26 });
	protatorAnim.PushBack({ 130,33,32,28 });
	protatorAnim.PushBack({ 1,64,32,32 });
	protatorAnim.PushBack({ 34,64,32,32 });
	protatorAnim.PushBack({ 67,64,32,32 });
	protatorAnim.PushBack({ 100,64,32,32 });
	protatorAnim.PushBack({ 133,64,32,32 });
	protatorAnim.speed = 0.125f;
	// ----
	//protator damage animation


	animation = &protatorAnim; //links animation
	// enemy data ----
	powerUpType = type;
	life = 1;
	enemyScore = 100;
	// ---------------
	fposition.x = x;
	fposition.y = y;

	

	extraColliders[0] = collider = App->collision->AddCollider({ 0, 0, 32, 32 }, COLLIDER_TYPE::COLLIDER_ENEMY, (Module*)App->enemies);
	//lateral colliders
	extraColliders[1] = rightCollider = App->collision->AddCollider({ 0, 0, 2, 16 }, COLLIDER_TYPE::COLLIDER_ENEMY, (Module*)App->enemies);
	extraColliders[2] = leftCollider = App->collision->AddCollider({ 0, 0, 2, 16 }, COLLIDER_TYPE::COLLIDER_ENEMY,(Module*)App->enemies);
	//locked target position
	//targetPos = App->player->position;
	
	//debugWall1 = App->collision->AddCollider({ 0, 200, 50, 300 }, COLLIDER_TYPE::COLLIDER_WALL, (Module*)App->enemies);
	//debugWall2 = App->collision->AddCollider({ 0, 0, 10, 20 }, COLLIDER_TYPE::COLLIDER_WALL, (Module*)App->enemies);

	targetPosReached = false;
	aimed = false;
	propulsion = false;
	goingDown = false;

	grounded = true;
	rightCollision = false;
	leftCollision = false;


	current_animation = &protatorAnim;

	preAimedLocalPos = position;
}

void EnemyProtator::Move()
{

	

	if (!aimed) //&& (position.x - App->player->position.x) < 200)
	{
		tx = App->player->position.x - position.x;
		ty = App->player->position.y - position.y ;
		fPoint playerDistance;
		playerDistance.x = App->player->position.x;
		playerDistance.y = App->player->position.y;

		//get sqrt distance
		distance = fposition.DistanceTo(playerDistance);

		velX = (tx / distance)*2.5f;
		velY = (ty / distance)*2.5f;

		lastVelY = velY;
		aimed = true;

		current_animation->current_frame = 1;

		//preAimedLocalPos = position;
	}

	if (propulsion) //|| leftCollision || rightCollision)
	{

		if (grounded) grounded = false;

		if (position.y - 20 <= targetPos.y)
		{
			targetPosReached = true;
		}

		if (targetPosReached)
		{
			fposition.x += velX;
			if (velY >= -lastVelY)
			{
				velY = -lastVelY;
			}
			else
			{
				velY += 0.07f;
				if (!goingDown) goingDown = true;
			}

			fposition.y += velY;
		}
		else
		{
			//if (leftCollision) 
				//fposition.x += -velX;
			//else
				fposition.x += velX;
			
			fposition.y += velY;
		}

		
	}

	if (rightCollision)
	{
		fposition.x += -velX;
		fposition.x -= 1.0f;
	}
	else if (leftCollision)
	{
		fposition.x += -velX;
		fposition.x += 1.0f;
	}

	if (!grounded) //&& !rightCollision && !leftCollision) 
		fposition.x += 1.0f;
	else //if (grounded && !rightCollision && !leftCollision)
		fposition.x += 0.5f; //little descompensation because player speed

	position.x = fposition.x;
	position.y = fposition.y;

	//set "ground" collider
	collider->SetPos(position.x, position.y - 32);
	//set laterall colliders
	rightCollider->SetPos(position.x + 32, position.y - 32);
	leftCollider->SetPos(position.x - 2, position.y - 32);

	//debugWall1->SetPos(App->player->position.x - 10, 0);

}

void EnemyProtator::Draw()
{
	

	SDL_Rect enemyProRect;

	if (!aimed)
	{	

		enemyProRect = protatorAnim.frames[0];
		App->render->Blit(enemyTex, position.x,position.y, &enemyProRect);

	}
	else
	{
		if (!goingDown)
		{
			if (targetPos.x < preAimedLocalPos.x)
			{
				if (current_animation->current_frame >= 12.8f)
				{
					current_animation->current_frame = 11;
				}
			}
			else
			{
				if (current_animation->current_frame >= 10 && current_animation->current_frame < 13)
				{
					current_animation->current_frame = 13;
				}
				if (current_animation->current_frame >= 14.8f)
				{
					current_animation->current_frame = 13;
				}
			}
			if (!propulsion)
			{
				if (current_animation->current_frame >= 9.87f)
				{
					propulsion = true;
					targetPos = App->player->position;
				}

			}

			enemyProRect = current_animation->GetCurrentFrame();
		}
		else
		{
			if(targetPos.x < preAimedLocalPos.x)
				enemyProRect = protatorAnim.frames[10];
			else
				enemyProRect = protatorAnim.frames[0];
		}
		App->render->Blit(enemyTex, position.x, position.y - enemyProRect.h, &enemyProRect);
	}


}

void EnemyProtator::OnCollision(Collider* collider, Collider* collider2)
{
	if (!grounded)
	{
		if (collider2 == this->collider)
		{
			LOG("autoCollision");
		}
		if (collider2 == this->leftCollider)
		{
			if (!leftCollision)
			{
				LOG("leftCollision");
				leftCollision = true;
				rightCollision = false;
				targetPosReached = true;
			}
		}
		if (collider2 == this->rightCollider)
		{
			if (!rightCollision)
			{
				LOG("rightCollision");
				rightCollision = true;
				leftCollision = false;
				targetPosReached = true;
			}
		}

		if (collider2 == this->collider)
		{
			rightCollision = false;
			leftCollision = false;
			aimed = false;
			propulsion = false;
			goingDown = false;
			targetPosReached = false;
			grounded = true;
			//fposition.y = collider->rect.y - 1;
			preAimedLocalPos = position;
		}

	}
	
}

const Collider* EnemyProtator::GetCollider() const
{
	return extraColliders[collisionColliderIndex];
}