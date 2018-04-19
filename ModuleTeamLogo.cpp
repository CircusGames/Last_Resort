#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleTeamLogo.h"
#include "ModuleGameTitle.h"
#include "ModuleInput.h"
#include "ModuleFadeToBlack.h"
#include "ModuleAudio.h"
#include "Animation.h"

#include "SDL/include/SDL_timer.h"

#include "SDL\include\SDL_render.h"


ModuleTeamLogo::ModuleTeamLogo(){

	circusCarpAnim.PushBack({ 0,0,150,150 });
	circusCarpAnim.PushBack({ 150,0,150,150 });
	circusCarpAnim.PushBack({ 300,0,150,150 });
	circusCarpAnim.PushBack({ 0,150,150,150 });
	circusCarpAnim.PushBack({ 150,150,150,150 });
	circusCarpAnim.PushBack({ 300,150,150,150 });
	circusCarpAnim.PushBack({ 0,300,150,150 });
	circusCarpAnim.PushBack({ 150,300,150,150 });

	circusCarpAnim.speed = 0.3f;

	LogoTextAnim.PushBack({ 178,64,5,16 });
	LogoTextAnim.PushBack({ 168,64,9,16 });
	LogoTextAnim.PushBack({ 152,64,15,16 });
	LogoTextAnim.PushBack({ 131,64,20,16 });
	LogoTextAnim.PushBack({ 108,64,22,16 });
	LogoTextAnim.PushBack({ 77,64,30,16 });
	LogoTextAnim.PushBack({ 0,64,40,16 });
	LogoTextAnim.PushBack({ 467,48,45,16 });
	LogoTextAnim.PushBack({ 419,48,47,16 });
	LogoTextAnim.PushBack({ 363,48,55,16 });
	LogoTextAnim.PushBack({ 302,48,60,16 });
	LogoTextAnim.PushBack({ 236,48,65,16 });
	LogoTextAnim.PushBack({ 165,48,70,16 });
	LogoTextAnim.PushBack({ 91,48,73,16 });
	LogoTextAnim.PushBack({ 0,48,90,16 });
	LogoTextAnim.PushBack({ 430,32,95,16 });
	LogoTextAnim.PushBack({ 330,32,99,16 });
	LogoTextAnim.PushBack({ 224,32,105,16 });
	LogoTextAnim.PushBack({ 113,32,110,16 });
	LogoTextAnim.PushBack({ 0,32,112,16 });
	LogoTextAnim.PushBack({ 393,16,120,16 });
	LogoTextAnim.PushBack({ 267,16,125,16 });
	LogoTextAnim.PushBack({ 136,16,130,16 });
	LogoTextAnim.PushBack({ 0,16,135,16 });
	LogoTextAnim.PushBack({ 297,0,138,16 });
	LogoTextAnim.PushBack({ 151,0,145,16 });
	LogoTextAnim.PushBack({ 0,0,150,16 });
	LogoTextAnim.repeat = false;
	LogoTextAnim.speed = 0.3f;
}

ModuleTeamLogo::~ModuleTeamLogo(){}

bool ModuleTeamLogo::Start()
{
	LOG("Starting ModuleTeamLogo --------");

	logoTexture = App->textures->Load("assets/Graphics/Screens/intro/circus games/Logo/cut/spritesheet/logo.png");

	logoTextTexture = App->textures->Load("assets/Graphics/Screens/intro/circus games/Text/Cut/Spritesheet/text.png");

	start_time = SDL_GetTicks(); //initializes for logo timer
	total_time = 2000.0f; //logo timer

	circusCarp = App->textures->Load("assets/Graphics/Screens/intro/circus games/Logo/cut/spritesheet/logo.png");

	//upload Logo Audio
	//App->audio->LoadAudio("assets/Audio/Music/LogoMusic.ogg", "titleSong", MUSIC);
	//App->audio->ControlAudio("titleSong", MUSIC, FADEIN, 0, 1000.0f);
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
	SDL_Rect logoRect = { 117 * SCREEN_SIZE,52 * SCREEN_SIZE,70 * SCREEN_SIZE,70 * SCREEN_SIZE };
	SDL_Rect provisionalRect = { 57 * SCREEN_SIZE,67 * SCREEN_SIZE,80 * SCREEN_SIZE,10 * SCREEN_SIZE };

	SDL_RenderCopy(App->render->renderer, logoTexture, &circusCarpAnim.GetCurrentFrame(), &logoRect );
	//SDL_RenderCopy(App->render->renderer, logoTextTexture, &LogoTextAnim.GetCurrentFrame(), &provisionalRect);

	App->render->Blit(logoTextTexture, 77, 140, &LogoTextAnim.GetCurrentFrame());

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

	//Mix_FadeOutMusic(500);
	//App->audio->UnloadAudio("titleSong", MUSIC);

	return true;
}