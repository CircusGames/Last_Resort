#include "Application.h"
#include "EnemyOscilatory.h"
#include "ModuleCollision.h"
#include "ModuleEnemies.h"
#include "ModuleParticles.h"

EnemyOscilatory::EnemyOscilatory(int x, int y, powerUpTypes type, SDL_Texture* sprite) : Enemy(x, y)
{
	waveAnim.PushBack({ 0,0,48,45 });
	waveAnim.PushBack({ 49,0,48,46 });
	waveAnim.PushBack({ 96,0,47,46 });
	waveAnim.PushBack({ 144,0,48,46 });
	waveAnim.PushBack({ 192,0,48,46 });
	waveAnim.PushBack({ 0,47,48,46 });
	waveAnim.PushBack({ 48,47,48,46 });
	waveAnim.PushBack({ 96,47,48,46 });
	waveAnim.PushBack({ 144,47,48,46 });
	waveAnim.PushBack({ 192,47,48,46 });
	waveAnim.PushBack({ 0,95,48,46 });
	waveAnim.PushBack({ 48,95,48,46 });
	waveAnim.PushBack({ 96,95,50,47 });
	waveAnim.PushBack({ 146,95,48,49 });
	waveAnim.PushBack({ 96,95,50,47 });
	waveAnim.PushBack({ 48,95,48,46 });
	waveAnim.PushBack({ 0,95,48,46 });
	waveAnim.PushBack({ 192,47,48,46 });
	waveAnim.PushBack({ 144,47,48,46 });
	waveAnim.PushBack({ 96,47,48,46 });
	waveAnim.PushBack({ 48,47,48,46 });
	waveAnim.PushBack({ 0,47,48,46 });
	waveAnim.PushBack({ 192,0,48,46 });
	waveAnim.PushBack({ 144,0,48,46 });
	waveAnim.PushBack({ 96,0,47,46 });
	waveAnim.PushBack({ 49,0,48,46 });
	waveAnim.speed = 0.05f;

	animation = &waveAnim;
	texture = sprite;

	powerUpType = type;

	collider = App->collision->AddCollider({ 0, 0, 50, 47 }, COLLIDER_TYPE::COLLIDER_ENEMY, (Module*)App->enemies);

	original_y = y;

	life = 5;
}

void EnemyOscilatory::Move()
{
	if (going_up)
	{
		if (wave > 1.2f)
			going_up = false;
		else
			wave += 0.05f;
	}
	else
	{
		if (wave < -1.2f)
			going_up = true;
		else
			wave -= 0.05f;
	}

	position.y = int(float(original_y) + (82.0f * sinf(wave)));
	position.x -= 1;
}

EnemyOscilatory::~EnemyOscilatory()
{
	App->particles->AddParticle(App->particles->explosion, position.x + 30, position.y, COLLIDER_NONE, {}, 0);
	App->particles->AddParticle(App->particles->explosion, position.x+50, position.y - 7, COLLIDER_NONE, {}, 100);
	App->particles->AddParticle(App->particles->explosion, position.x+10, position.y + 30, COLLIDER_NONE,{}, 70);
	App->particles->AddParticle(App->particles->explosion, position.x, position.y - 20, COLLIDER_NONE, {}, 144);
	App->particles->AddParticle(App->particles->explosion, position.x - 10, position.y + 5, COLLIDER_NONE,{}, 29);
	App->particles->AddParticle(App->particles->explosion, position.x - 20, position.y - 8, COLLIDER_NONE,{}, 240);

}