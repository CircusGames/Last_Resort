#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleGameTitle.h"
//#include "ModuleBackground.h"
#include "ModuleGameOver.h"
#include "ModuleInput.h"
#include "ModuleFadeToBlack.h"
#include "ModuleAudio.h"
#include "SDL/include/SDL_timer.h"
#include "Player.h"
//#include "ModulePlayer.h"
//#include "ModulePlayer2.h"
#include "Module.h"
//#include "ModulePlayer2Unit.h"

#include "SDL/include/SDL_render.h"

ModuleGameOver::ModuleGameOver()
{
	gameOverFirstRect = { 0,0,260,160 };
	gameOverMidRect = { 0, 160, 260, 160};
	gameOverRect = { 0,320,234,132 };

}

ModuleGameOver::~ModuleGameOver()
{}

bool ModuleGameOver::Start()
{
	LOG("---- Starting Module Game Over");

	gameOverTexture = App->textures->Load("assets/Graphics/Screens/Game_Over/GameOver.png");
	//loading music
	App->audio->LoadAudio("assets/Audio/Music/Game_Over.wav", "continueSong", SFX);
	App->audio->ControlAudio("continueSong", SFX, PLAY);

	return true;
}

update_status ModuleGameOver::Update()
{
	//current_step = intro_step::firstSecuence; //<------ If you put this, the first Game Over is ok but the secuence don't continue to the Fade to White and last Game Over
	//App->render->Blit(gameOverTexture, 25, 36, &gameOverFirstRect);
	//App->render->Blit(gameOverTexture, 25, 36, &gameOverMidRect);
	App->render->Blit(gameOverTexture, 35,46, &gameOverRect);
	/*if (current_step == intro_step::firstSecuence)
	{
		App->render->Blit(blackScreenTexture, 0, 0, NULL);
		App->render->Blit(gameOverTexture, 25, 36, &gameOverFirstRect);
		//App->render->Blit(gameOverTexture, 25,36, &gameOverFirstRect);
		SDL_RenderFillRect(App->render->renderer, NULL);
		// ---
		total_time += total_time;
		start_time = SDL_GetTicks();
		total_time = 500.0f;
		lastFadeFromWhiteTime = 3000.0f;
		current_step = intro_step::fade_to_white;

	}

	else if (current_step == intro_step::fade_to_white ||
		current_step == intro_step::fade_from_white ||
		current_step == intro_step::time_in_white)
	{
		now = SDL_GetTicks() - start_time;
		float normalized;
		if (current_step == intro_step::fade_from_white) normalized = MIN(1.0f, (float)now / (float)lastFadeFromWhiteTime);
		else normalized = MIN(1.0f, (float)now / (float)total_time);

		if (current_step == intro_step::fade_to_white)
		{
			if (now >= total_time)
			{

				App->render->Blit(blackScreenTexture, 0, 0, NULL);
				App->render->Blit(gameOverTexture, 35, 46, NULL);

				SDL_SetRenderDrawColor(App->render->renderer, 255, 255, 255, (Uint8)(normalized * 255.0f));
				SDL_RenderFillRect(App->render->renderer, NULL);
				// ---
				total_time += total_time;
				start_time = SDL_GetTicks();
				current_step = intro_step::time_in_white;

			}
		}
		else if (current_step == intro_step::time_in_white)
		{
			timeInWhite = 500;
			if (now >= timeInWhite)
			{
				current_step = intro_step::fade_from_white;
				normalized = 1.0f;
				start_time = SDL_GetTicks();
			}
		}

		else if (current_step == intro_step::fade_from_white)
		{

			App->render->Blit(blackScreenTexture, 0, 0, NULL);
			App->render->Blit(gameOverTexture, 35, 46, &gameOverRect);
			normalized = 1.0f - normalized;

			if (now >= lastFadeFromWhiteTime)
				current_step = intro_step::lastgameover;
		}
		SDL_SetRenderDrawColor(App->render->renderer, 255, 255, 255, (Uint8)(normalized * 255.0f));
		SDL_RenderFillRect(App->render->renderer, NULL);
		SDL_SetRenderDrawColor(App->render->renderer, 0, 0, 0, (Uint8)(0.0f));
		SDL_RenderFillRect(App->render->renderer, NULL);
	}
	else if (current_step == intro_step::lastgameover)
	{
		//SDL_SetRenderDrawColor(App->render->renderer, 0, 0, 0, (Uint8)(0.0f));
		//SDL_RenderFillRect(App->render->renderer, NULL);
		App->render->Blit(gameOverTexture, 35, 46, &gameOverRect);
	}*/

	if (App->input->keyboard[SDL_SCANCODE_RETURN] == 1) //&& App->player->lives > 0)
	{
		App->fade->FadeToBlack(App->gameOverScreen, (Module*)App->winScreen, 0.8f);

		//when player dies, go to level 1
		App->player[0]->sceneCallback = (Module*)App->scene_lvl1;
	}

		
	return UPDATE_CONTINUE;
}
	

bool ModuleGameOver::CleanUp()
{
	//unload textures
	App->textures->Unload(gameOverTexture);


	//unload music
	//Mix_FadeOutMusic(250);
	App->audio->UnloadAudio("continueSong",SFX);

	return true;
}