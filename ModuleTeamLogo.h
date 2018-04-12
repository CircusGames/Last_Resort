#ifndef __MODULETEAMLOGO_H__
#define __MODULETEAMLOGO_H__

#include "Module.h"
#include "Animation.h"
#include "Globals.h"

class ModuleTeamLogo : public Module
{
public:

	ModuleTeamLogo();
	~ModuleTeamLogo();
	
	bool Start();
	update_status Update();
	bool CleanUp();

private:
	
	Animation carpaDeCircoAnim;
	SDL_Texture* logoTexture;
	SDL_Texture* provisionalTexture;
	SDL_Texture* carpaDeCirco = nullptr;

	Animation LogoTextAnim;
	SDL_Texture* logoTextTexture;
	SDL_Texture* LogoText = nullptr;

	Uint32 now;
	float start_time;
	float total_time;

};




#endif // !__MODULETEAMLOGO_H__
