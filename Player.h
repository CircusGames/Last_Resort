#ifndef __Player_H__
#define __Player_H__

#include "ModulePlayer.h"

class Player : public ModulePlayer
{
public:

	//Player();
	//bool Start();
	bool Init();
	void checkInput();

	int playerIndex;

};
#endif