#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleReady.h"
#include "ModuleGameTitle.h"
#include "ModuleSceneLvl1.h"

#include "SDL/include/SDL_timer.h"

ModuleReady::ModuleReady()
{
	readyRect = { 0, 112, 80, 16 };
}

ModuleReady::~ModuleReady()
{}

bool ModuleReady::Start()
{
	LOG("----- Starting Module Ready");

	readyTexture = App->textures->Load("assets/Graphics/UI/UI.png");

	totalTime = 1000.0f;

	startTime = SDL_GetTicks();

	return true;
}

update_status ModuleReady::Update()
{
	App->render->Blit(readyTexture, 104, 96, &readyRect);



	now = SDL_GetTicks() - startTime;

	if (now >= totalTime)
	{
		App->readyScreen->Disable();
		App->scene_lvl1->Enable();
	}

	return UPDATE_CONTINUE;
}

bool ModuleReady::CleanUp()
{
	App->textures->Unload(readyTexture);

	return 0;
}