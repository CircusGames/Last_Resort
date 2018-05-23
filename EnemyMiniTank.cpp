#include "Application.h"
#include "EnemyMiniTank.h"
#include "ModuleCollision.h"
#include "Globals.h"
#include "ModuleEnemies.h"
#include "SDL\include\SDL_timer.h"
#include "Path.h"
#include "ModuleRender.h"

Enemy_MiniTank::Enemy_MiniTank(int x, int y, powerUpTypes type, SDL_Texture* thisTexture) : Enemy(x, y)
{
	enemyTex = thisTexture;

	move.PushBack({ 0,12,61,47 });
	move.PushBack({ 61,11,61,48 });
	move.PushBack({ 122,11,61,48 });
	move.speed = 0.25f;
	
	damage.PushBack({ 0,62,61,47 });
	damage.PushBack({ 61,61,61,48 });
	damage.PushBack({ 122,61,61,48 });
	damage.speed = 0.25f;


	//Missing Sprites of Shooting Animation
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

	collider = App->collision->AddCollider({ 0, 0, 61, 48 }, COLLIDER_TYPE::COLLIDER_ENEMY, (Module*)App->enemies);

	powerUpType = type;

	original_pos.x = x;
	original_pos.y = y;

	start_time = SDL_GetTicks();
	damageAnimTime = 50;

	life = 1;

	//Missiles Animation
	missilelaunch.PushBack({ 0,110,21,16 });
	missilelaunch.PushBack({ 22,110,21,24 });
	missilelaunch.PushBack({ 44,110,27,29 });
	missilelaunch.PushBack({ 72,110,28,31 });
	missilelaunch.PushBack({ 103,110,30,32 });
	missilelaunch.PushBack({ 134,110,31,32 });
	missilelaunch.PushBack({ 166,110,32,32 });
	missilelaunch.PushBack({ 199,110,32,31 });
	missilelaunch.PushBack({ 232,110,31,30 });
	missilelaunch.PushBack({ 264,110,30,16 });
	missilelaunch.PushBack({ 0,143,19,12 });
	missilelaunch.PushBack({ 25,143,23,15 });

	missileexplode.PushBack({ 0,171,23,19 });
	missileexplode.PushBack({ 24,163,25,17 });
	missileexplode.PushBack({ 50,160,30,30 });
	missileexplode.PushBack({ 114,161,25,29 });
	missileexplode.PushBack({ 140,159,28,31 });
	missileexplode.PushBack({ 170,159,30,31 });
	missileexplode.PushBack({ 201,159,32,31 });
	missileexplode.PushBack({ 233,161,30,29 });
	missileexplode.PushBack({ 264,163,29,27 });
}

void Enemy_MiniTank::Move()
{
	position = original_pos + path.GetCurrentSpeed(&animation);
}


void Enemy_MiniTank::Draw()
{
	collider->SetPos(position.x, position.y);
	SDL_Rect MiniTankRect = move.GetCurrentFrame();
	App->render->Blit(enemyTex, position.x, position.y, &MiniTankRect);
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

void Enemy_MiniTank::OnCollision(Collider* collider, Collider* collider2)
{

	if (collider->type == COLLIDER_PLAYER_SHOT)
		receiveDamage = true;
}