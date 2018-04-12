#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleTeamLogo.h"
#include "ModuleGameTitle.h"
//#include "ModuleInput.h"
#include "ModuleFadeToBlack.h"
#include "ModuleAudio.h"
#include "SDL/include/SDL_timer.h"

#include "SDL\include\SDL_render.h"


ModuleTeamLogo::ModuleTeamLogo(){

	carpaDeCircoAnim.PushBack({ 0,0,150,150 });
	carpaDeCircoAnim.PushBack({ 150,0,150,150 });
	carpaDeCircoAnim.PushBack({ 300,0,150,150 });
	carpaDeCircoAnim.PushBack({ 0,150,150,150 });
	carpaDeCircoAnim.PushBack({ 150,150,150,150 });
	carpaDeCircoAnim.PushBack({ 300,150,150,150 });
	carpaDeCircoAnim.PushBack({ 0,300,150,150 });
	carpaDeCircoAnim.PushBack({ 150,300,150,150 });

	carpaDeCircoAnim.speed = 3.5f;

	LogoTextAnim.PushBack({ 0,0 });


	LogoTextAnim.speed = 3.5f;
}

ModuleTeamLogo::~ModuleTeamLogo(){}

bool ModuleTeamLogo::Start()
{
	LOG("Starting ModuleTeamLogo --------");

	logoTexture = App->textures->Load("assets/intro/circus games/Logo/cut/spritesheet/logo.png");
	provisionalTexture = App->textures->Load("assets/intro/provisional.png");

	logoTextTexture = App->textures->Load("assets/intro/circus games/Text/Cut/Spritesheet/text.png");

	start_time = SDL_GetTicks(); //initializes for logo timer
	total_time = 2000.0f; //logo timer

	carpaDeCirco = App->textures->Load("assets/intro/circus games/Logo/cut/spritesheet/logo.png");

	return true;
}

update_status ModuleTeamLogo::Update()
{

	now = SDL_GetTicks() - start_time;
	//App->render->Blit(blackScreenTexture, 0, 0, NULL);
	//App->render->Blit(logoTexture, 0, 0, &jerry_smith);

	//fill rects with aproppiate color
	SDL_SetRenderDrawColor(App->render->renderer, 255, 255, 255, 255);
	SDL_RenderFillRect(App->render->renderer, NULL);

	//direct rendercopy 
	SDL_Rect logoRect = { 92 * SCREEN_SIZE,52 * SCREEN_SIZE,120 * SCREEN_SIZE,120 * SCREEN_SIZE };
	SDL_Rect provisionalRect = { 67 * SCREEN_SIZE,67 * SCREEN_SIZE,80 * SCREEN_SIZE,10 * SCREEN_SIZE };

	SDL_RenderCopy(App->render->renderer, logoTexture, NULL, &logoRect);
	SDL_RenderCopy(App->render->renderer, provisionalTexture, NULL, &provisionalRect);

	if (now >= total_time)
	{
		App->fade->FadeToBlack(App->teamLogo, App->gameTitle);
	}

	return UPDATE_CONTINUE;
}

bool ModuleTeamLogo::CleanUp()
{
	App->textures->Unload(provisionalTexture);
	App->textures->Unload(logoTexture);

	return true;
}