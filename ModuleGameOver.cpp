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

//#include "SDL/include/SDL_timer.h"

//#include "SDL/include/SDL_render.h"

ModuleGameOver::ModuleGameOver()
{
	gameOverRect = { 0,320,234,132 };

}

ModuleGameOver::~ModuleGameOver()
{}

bool ModuleGameOver::Start()
{
	LOG("---- Starting Module Game Over");

	gameOverTexture = App->textures->Load("assets/GameOver.png");

	//loading music
	App->audio->LoadMUS("assets/Continue.ogg", "continueSong");
	App->audio->ControlAudio("continueSong", MUSIC, FADEIN, 500.0f);

	return true;
}

update_status ModuleGameOver::Update()
{

	App->render->Blit(gameOverTexture, 35,46, &gameOverRect);

	if (App->input->keyboard[SDL_SCANCODE_RETURN] == 1)
		App->fade->FadeToBlack(App->gameOverScreen, App->gameTitle, 0.8f);

	return UPDATE_CONTINUE;
}

bool ModuleGameOver::CleanUp()
{
	//unload textures
	App->textures->Unload(gameOverTexture);

	//unload music
	//Mix_FadeOutMusic(250);
	//App->audio->UnloadMus("continueSong");

	return true;
}