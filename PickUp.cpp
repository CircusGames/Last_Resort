#include "Application.h"
#include "PickUp.h"
#include "ModuleCollision.h"
#include "Path.h"

PickUp::PickUp(int x, int y) : Enemy(x, y)
{

	animation = &pickUp_animation;

	position.x = x;
	position.y = y;

	collider = App->collision->AddCollider({ 0, 0, 22, 13 }, COLLIDER_TYPE::COLLIDER_PICKUP, (Module*)App->enemies);

	up = true;
	right = true;

}
