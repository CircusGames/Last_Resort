#include "Application.h"
#include "EnemyMiniTank.h"
#include "ModuleCollision.h"
#include "Globals.h"
#include "ModuleEnemies.h"
#include "SDL\include\SDL_timer.h"

Enemy_MiniTank::Enemy_MiniTank(int x, int y, powerUpTypes type, SDL_Texture* thisTexture) : Enemy(x, y)
{
	enemyTex = thisTexture;

	move2.PushBack({ 0,1,61,50 });
	move.PushBack({ 61,0,61,50 });
	move.PushBack({ 122,0,61,48 });
	move.speed = 0.2f;
	
	damage2.PushBack({ 0,62,61,50 });
	damage.PushBack({ 61,61,61,50 });
	damage.PushBack({ 122,61,61,48 });
	damage.speed = 0.2f;

	animation = &move;
	shootanimation = &move2;
	shootanimationdamage = &damage2;

	current_animation = &move;
	//Path
	path.PushBack({ -0.1f, 0.0f }, 140, &move);
	path.PushBack({ 1.1f, 0.0f }, 130, &move);
	path.PushBack({ 0.5f, 0.0f }, 30, &move2);
	path.PushBack({ 1.1f, 0.0f }, 10, &move);
	path.PushBack({ -0.1f, 0.0f }, 10, &move);
	path.PushBack({ 1.1f, 0.0f }, 10, &move);
	path.PushBack({ -0.1f, 0.0f }, 140, &move);
	path.PushBack({ 1.1f, 0.0f }, 10, &move);
	path.PushBack({ -0.1f, 0.0f }, 10, &move);
	path.PushBack({ 1.1f, 0.0f }, 70, &move);
	path.PushBack({ 0.5f, 0.0f }, 30, &move2);
	path.PushBack({ 1.1f, 0.0f }, 65, &move);
	path.PushBack({ -0.1f, 0.0f }, 10, &move);
	path.PushBack({ 1.1f, 0.0f }, 10, &move);
	path.PushBack({ -0.1f, 0.0f }, 100, &move);
	path.PushBack({ 0.5f, 0.0f }, 30, &move2);

	collider = App->collision->AddCollider({ 0, 0, 61, 47 }, COLLIDER_TYPE::COLLIDER_ENEMY, (Module*)App->enemies);

	powerUpType = type;

	original_pos.x = x;
	original_pos.y = y;

	life = 1;
}

void Enemy_MiniTank::Move()
{
	position = original_pos + path.GetCurrentSpeed(&animation);
}

void Enemy_MiniTank::Draw()
{
	if (receiveDamage)
	{
		current_frame = current_animation->current_frame;
		current_animation = &damage;
		current_animation->current_frame = current_frame;
		receiveDamage = false;
		start_damage_time = SDL_GetTicks();
	}

	nowDamagetime = SDL_GetTicks() - start_damage_time;

	if (nowDamagetime > damageAnimTime)
	{
		current_frame = current_animation->current_frame;
		current_animation = &move;
		current_animation->current_frame = current_frame;
	}

}