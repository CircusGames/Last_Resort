#include "Application.h"
#include "EnemyRedbird.h"
#include "ModuleCollision.h"
#include "ModuleEnemies.h"
#include "ModuleParticles.h"

#include "ModuleRender.h"

EnemyRedbird::EnemyRedbird(int x, int y, powerUpTypes type, SDL_Texture* thisTexture) : Enemy(x, y)
{
	//links correct spritesheet texture
	enemyTex = thisTexture;

	waveAnim.PushBack({ 0,0,26,29 });
	waveAnim.PushBack({ 26,0,26,29 });
	waveAnim.PushBack({ 52,0,26,29 });
	waveAnim.PushBack({ 78,0,26,29 });
	waveAnim.PushBack({ 104,0,26,29 });
	waveAnim.PushBack({ 130,0,26,29 });
	waveAnim.PushBack({ 156,0,27,29 });
	waveAnim.PushBack({ 183,0,26,29 });
	waveAnim.speed = 0.125f;

	animation = &waveAnim;


	powerUpType = type;

	collider = App->collision->AddCollider({ 0, 14, 26, 18 }, COLLIDER_TYPE::COLLIDER_ENEMY, (Module*)App->enemies);

	original_y = y;

	life = 1;
	enemyScore = 100;
}

void EnemyRedbird::Move()
{
	//update collider pos
	collider->SetPos(position.x, position.y + 7);

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

	position.y = original_y + int(20.0f * sinf(wave));
	position.x -= 1;
}

void EnemyRedbird::Draw()
{

	App->render->Blit(enemyTex, position.x, position.y, &waveAnim.GetCurrentFrame());

}