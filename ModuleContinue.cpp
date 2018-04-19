#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleGameOver.h"
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

#define MAX_ALPHA 255.0f
#define MIN_ALPHA 0.0f

ModuleContinue::ModuleContinue()
{
	//background image
	backgroundRect = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };

	//continue letters
	continueRect = { 0, 64, 240, 32 };

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
		fireAnim[i].speed = 0.33f;
	}

	//numbers 
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
	/*if (App->player->IsEnabled())
		App->player->Disable();

	if (App->player2->IsEnabled())
		App->player2->Disable();

	if (App->playerUnit->IsEnabled())
		App->playerUnit->Disable();

	if (App->player2Unit->IsEnabled())
		App->player2Unit->Disable();*/

	//alpha
	number = 9;
	cycle = true;
	normalized = 2.5f;
	alpha = 255.0f;

	//graphics
	backgroundTexture = App->textures->Load("assets/Graphics/Screens/Continue/Backgrounds.png");
	continueTexture = App->textures->Load("assets/Graphics/Screens/Continue/Anims.png");

	//audio
	App->audio->LoadAudio("assets/Audio/Music/Continue.ogg", "continueSong", MUSIC);
	App->audio->ControlAudio("continueSong", SFX, PLAY);

	return true;
}

update_status ModuleContinue::Update()
{
	// background blink anim
	if (cycle)
	{
		alpha = alpha - normalized;

		if (alpha == MIN_ALPHA)
			cycle = false;

		SDL_SetTextureAlphaMod(backgroundTexture, alpha);
		App->render->Blit(backgroundTexture, 0, 0, &backgroundRect);
	}
	else 
	{
		alpha = alpha + normalized;

		if (alpha == MAX_ALPHA)
			cycle = true;

		SDL_SetTextureAlphaMod(backgroundTexture, alpha);
		App->render->Blit(backgroundTexture, 0, 0, &backgroundRect);
	}

	//fire anim
	for (int i = 0; i <= MAX_FRAMES; i++)
	{
		if (!fireAnim[i].finish)
		{
			App->render->Blit(continueTexture, 21 + 32 * i, 96, &fireAnim[i].GetCurrentFrame());
		}
		else
		{
			App->render->Blit(continueTexture, 253, 96, &fireAnim[i].GetCurrentFrame());			
		}
	}
		
	// continue rect
	App->render->Blit(continueTexture, 16, 96, &continueRect);

	// numbers anim
	App->render->Blit(continueTexture, 256, 96, &numbersAnim.frames[0]);

	if (number < 0)
		App->fade->FadeToBlack(App->continueScreen, App->gameOverScreen, 0.8f);



	if (App->input->keyboard[SDL_SCANCODE_RETURN] == 1)
		App->fade->FadeToBlack(App->continueScreen, App->gameOverScreen, 0.8f);

	return UPDATE_CONTINUE;
}

bool ModuleContinue::CleanUp()
{
	LOG("Unloading continue scene assets");

	App->textures->Unload(backgroundTexture);
	App->textures->Unload(continueTexture);

	App->audio->UnloadAudio("continueSong", MUSIC);

	return true;
}