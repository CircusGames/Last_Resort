#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleContinue.h"
#include "ModuleFadeToBlack.h"
#include "ModuleAudio.h"

#include "SDL/include/SDL_timer.h"
#include "SDL\include\SDL_render.h"

ModuleContinue::ModuleContinue()
{
	//background
	background.x = 0;
	background.y = 0;
	background.w = SCREEN_WIDTH;
	background.h = SCREEN_HEIGHT;



}
	