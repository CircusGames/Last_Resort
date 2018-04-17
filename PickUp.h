#ifndef _MODULEPICKUPS_H__
#define _MODULEPICKUOS_H__

#include "Enemy.h"

class PickUp : public Enemy
{
private:
	Animation pickUp_animation;
	bool up;
	bool right;

public:

	PickUp(int x, int y);

};
#endif // !_MODULEPOWERUPS_H__
