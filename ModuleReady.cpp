#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleReady.h"
#include "ModuleGameTitle.h"
#include "ModuleSceneLvl1.h"
#include "ModuleSceneLvl3.h"
#include "ModuleContinue.h"
#include "ModuleUI.h"

#include "SDL/include/SDL_timer.h"

//#include "ModulePlayer.h"

#include "Player.h"

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

	App->render->Blit(readyTexture, 112, 104, &readyRect);

	now = SDL_GetTicks() - startTime;

	if (now >= totalTime)
	{
		App->readyScreen->Disable();
		if (App->player[0]->sceneCallback != nullptr)
			App->player[0]->sceneCallback->Enable();
		else
			App->scene_lvl3->Enable();//App->scene_lvl1->Enable();


	}

	return UPDATE_CONTINUE;
}

bool ModuleReady::CleanUp()
{
	App->textures->Unload(readyTexture);

	return true;
}