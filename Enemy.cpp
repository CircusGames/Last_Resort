#include "Application.h"
#include "Enemy.h"
#include "ModuleCollision.h"
#include "ModuleParticles.h"
#include "ModuleRender.h"
#include "ModulePowerUp.h"
//#include "Globals.h"

#include "ModulePlayerUnit.h"

Enemy::Enemy(int x, int y, powerUpTypes type, SDL_Texture* texture) : position(x, y)
{}

Enemy::~Enemy()
{
	if (collider != nullptr)
		collider->to_delete = true;
}

const Collider* Enemy::GetCollider() const
{
	return collider;
}

void Enemy::Draw(SDL_Texture* sprites)
{
	if (collider != nullptr)
		collider->SetPos(position.x, position.y);

	if (animation != nullptr)
		App->render->Blit(sprites, position.x, position.y, &(animation->GetCurrentFrame()));
}

void Enemy::OnCollision(Collider* collider)
{
	App->particles->AddParticle(App->particles->explosion, position.x, position.y,COLLIDER_NONE);
	//powerUpType = this->powerUpType;
	App->modulePowerUp->powerUpSpawn(powerUpType, position);
	
}
