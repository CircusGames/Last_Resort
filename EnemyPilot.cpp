#include "Application.h"
#include "EnemyPilot.h"
#include "ModuleCollision.h"
#include "ModuleEnemies.h"
#include "Path.h"
#include "ModuleRender.h"

EnemyPilot::EnemyPilot(int x, int y, powerUpTypes type, SDL_Texture* thisTexture) : Enemy(x, y)
{
	//links the correct spritesheet texture ----
	enemyTex = thisTexture;
	// -----------------------------------------

	die.PushBack({ 0,0,12,16 });
	die.PushBack({ 12,0,13,16 });
	die.PushBack({ 25,0,14,16 });
	die.PushBack({ 39,0,13,16 });
	die.PushBack({ 52,0,15,16 });
	die.PushBack({ 67,0,12,16 });
	die.PushBack({ 79,0,11,16 });
	die.PushBack({ 90,0,12,16 });
	die.speed = 0.16666666f;
	
	animation = &die; //links animation
	//Path

	path.PushBack({ 0.5f, -1.0f }, 30, &die);
	path.PushBack({ 0.5f, -0.5f }, 5, &die);
	path.PushBack({ 0.5f, -0.2f }, 5, &die);
	path.PushBack({ 0.5f, 0.0f }, 5, &die);
	path.PushBack({ 0.5f, 0.2f }, 5, &die);
	path.PushBack({ 0.5f, 0.5f }, 5, &die);
	path.PushBack({ 0.5f, 1.0f }, 1000, &die);

	original_pos.x = x;
	original_pos.y = y;
}

void EnemyPilot::Move()
{
	position = original_pos + path.GetCurrentSpeed(&animation);

	if (position.y >= SCREEN_SIZE * SCREEN_HEIGHT) {
		killMe = true;
	}

}

void EnemyPilot::Draw() {

	Animation* current_animation;
	current_animation = &die;
	SDL_Rect PilotRect = current_animation->GetCurrentFrame();
	App->render->Blit(enemyTex, position.x, position.y, &PilotRect);

}

/*void EnemyPilot::Suicide() {
	if (position.y >= SCREEN_SIZE*SCREEN_HEIGHT) {
		killMe = true;
	}
}*/
