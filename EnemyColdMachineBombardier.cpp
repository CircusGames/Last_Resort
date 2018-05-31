#include "Application.h"
#include "EnemyColdMachineBombardier.h"
#include "ModuleCollision.h"
#include "ModuleEnemies.h"

#include "ModuleRender.h"

EnemyColdMachineBombardier::EnemyColdMachineBombardier(int x, int y, powerUpTypes type, SDL_Texture* thisTexture) : Enemy(x, y)
{
	//links the correct spritesheet texture ----
	enemyTex = thisTexture;
	// -----------------------------------------

	// bombardier ship animation
	fly.PushBack({ 988,0,36,24 }); // start //drop bomb
	fly.PushBack({ 800,26,63,24 }); // more fire, still not really open the bombs gate
	fly.PushBack({ 924,0,63,22 });
	fly.PushBack({ 800,0,64,21 });
	fly.PushBack({ 865,0,58,22 });
	fly.PushBack({ 800,0,64,21 });
	fly.PushBack({ 924,0,63,22 }); // end, then drop another bomb/restart cycle
	fly.speed = 0.25f;
	fly.repeat = false;

	//animation = &blabla; //links animation

	//original_y = y;
	//fposition.x = x;

	powerUpType = type;
	life = 1;
	enemyScore = 100;

	collider = App->collision->AddCollider({ 0, 0, 38, 12 }, COLLIDER_TYPE::COLLIDER_ENEMY, (Module*)App->enemies);

	throwBomb = true;

}

void EnemyColdMachineBombardier::Move()
{
	//fposition.x -= 1.35;
	//position.x = fposition.x;

	//position.x -= 1;

	if (collider != nullptr)
		collider->SetPos(position.x, position.y + 6);
}

void EnemyColdMachineBombardier::Draw()
{
	
	if (fly.finish)
	{
		// throw next bomb
		throwBomb = true;
		// resets animation data
		fly.finish = false;
		fly.current_frame = 0;
	}

	// throw bombs
	if (throwBomb)
	{	
		// instantiate particle
		App->particles->AddParticle(App->enemies->bombardierBomb, position.x + 7, position.y + 14, COLLIDER_ENEMY_SHOT, {0,2}, 0);
		throwBomb = false;
	}

	App->render->Blit(enemyTex, position.x, position.y, &fly.GetCurrentFrame());
	
}


