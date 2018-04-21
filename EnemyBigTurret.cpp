/*#include "Application.h"
#include "EnemyBigTurret.h"
#include "ModuleCollision.h"
#include "ModuleEnemies.h"
#include "EnemyTank.h"
#include "Path.h"

EnemyBigTurret::EnemyBigTurret(int x, int y, powerUpTypes type, SDL_Texture* sprite) : Enemy(x, y)
{
	//anims
	rotateAnim.PushBack({ 157, 95, 28, 10 });
	rotateAnim.PushBack({ 185, 95, 26, 12 });
	rotateAnim.PushBack({ 211, 95, 26, 13 });
	rotateAnim.PushBack({ 0, 158, 26, 14 });
	rotateAnim.PushBack({ 26, 158, 26, 14 });
	rotateAnim.PushBack({ 52, 158, 26, 14 });
	rotateAnim.PushBack({ 78, 158, 26, 13 });
	rotateAnim.PushBack({ 104, 158, 26, 12 });
	rotateAnim.PushBack({ 130, 158, 29, 10 });
	
	animation = &rotateAnim;

	texture = sprite;
	powerUpType = type;

	collider = App->collision->AddCollider({ 0, 0, 29, 14 }, COLLIDER_TYPE::COLLIDER_ENEMY, (Module*)App->enemies);
}*/