/*#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleContinue.h"
#include "ModuleFadeToBlack.h"
#include "ModuleAudio.h"

#include "ModulePlayer.h"
#include "ModulePlayer2.h"
#include "ModulePlayerUnit.h"
#include "ModulePlayer2Unit.h"

#include "SDL/include/SDL_timer.h"
#include "SDL\include\SDL_render.h"

#define MAX_FRAMES 8 // animations and sprite sheet limits
#define FIRE_FRAMES 14

#define NUMBERS 10

ModuleContinue::ModuleContinue()
{
	//background image
	backgroundRect.x = 0;
	backgroundRect.y = 0;
	backgroundRect.w = SCREEN_WIDTH;
	backgroundRect.h = SCREEN_HEIGHT;

	//continue letters
	continueRect.x = 16;
	continueRect.y = 96;
	continueRect.w = 240;
	continueRect.h = 32;

	//fire anim
	for (int i = 0; i < MAX_FRAMES; i++)
	{
		for (int j = 0; j < FIRE_FRAMES; j++)
		{
			if (j < MAX_FRAMES)
				fireAnim[i].PushBack({ 32 * j, 96, 32, 32 });
			else
				fireAnim[i].PushBack({ 32 * (i - MAX_FRAMES), 128, 32, 32 });
		}
	}

	//numbers anim
	for (int i = 0; i < NUMBERS; i++)
	{
		if (i < MAX_FRAMES)
			numbersAnim.PushBack({ 32 * i, 0, 32, 32 });
		else
			numbersAnim.PushBack({ 32 * (i - MAX_FRAMES), 32, 32, 32 });
	}
}

ModuleContinue::~ModuleContinue()
{ }

bool ModuleContinue::Start()
{
	LOG("-------- Loading continue scene");

	SDL_SetRenderDrawBlendMode(App->render->renderer, SDL_BLENDMODE_ADD);

	//disable
	if (App->player->IsEnabled())
		App->player->Disable();

	if (App->player2->IsEnabled())
		App->player2->Disable();

	if (App->playerUnit->IsEnabled())
		App->playerUnit->Disable();

	if (App->player2Unit->IsEnabled())
		App->player2Unit->Disable();
	

	//graphics
	backgroundTexture = App->textures->Load("assets/Grpahics/Screens/Continue/Background.png");
	continueTexture = App->textures->Load("assets/Graphics/Screens/Continue/Anims.png");

	//audio
	App->audio->LoadAudio("assets/Audio/Music/Continue.ogg", "continueSong", MUSIC);

	return true;
}

update_status ModuleContinue::Update()
{
	float normalized;
}*/