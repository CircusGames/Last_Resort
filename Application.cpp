#include "Application.h"
#include "ModuleWindow.h"
#include "ModuleRender.h"
#include "ModuleInput.h"
#include "ModuleTextures.h"
#include "ModuleSceneLvl1.h"
#include "ModuleParticles.h"
#include "ModulePlayer.h"
#include "ModulePlayerUnit.h"
#include "ModuleCollision.h"
#include "ModuleAudio.h"
#include "ModuleFadeToBlack.h"
#include "ModuleTeamLogo.h"
#include "ModuleGameTitle.h"
#include "ModuleGameOver.h"

Application::Application()
{
	int i = 0;
	modules[i++] = window = new ModuleWindow();
	modules[i++] = render = new ModuleRender();
	modules[i++] = input = new ModuleInput();
	modules[i++] = textures = new ModuleTextures();
	modules[i++] = teamLogo = new ModuleTeamLogo();
	modules[i++] = scene_lvl1 = new ModuleSceneLvl1();
	modules[i++] = gameTitle = new ModuleGameTitle();
	modules[i++] = gameOverScreen = new ModuleGameOver();
	modules[i++] = particles = new ModuleParticles();
	modules[i++] = player = new ModulePlayer();
	modules[i++] = playerUnit = new ModulePlayerUnit();
	modules[i++] = audio = new ModuleAudio();
	modules[i++] = collision = new ModuleCollision();
	modules[i++] = fade = new ModuleFadeToBlack();
	

}	

Application::~Application()
{
	for(int i = NUM_MODULES - 1; i >= 0; --i)
		delete modules[i];
}

bool Application::Init()
{
	bool ret = true;
	
	//desactivate Modules ----------------
	//disable modulePlayer at init
	scene_lvl1->Disable();
	player->Disable();
	playerUnit->Disable();
	collision->Disable();
	//particles->Disable();
	//disable the scenes wich i dont need at start/init
	//teamLogo->Disable();
	gameTitle->Disable();
	
	gameOverScreen->Disable();
	// -----------------------------------
	//all modules have their init
	for(int i = 0; i < NUM_MODULES && ret == true; ++i)
		ret = modules[i]->Init();

	//but only the needed have start
	for(int i = 0; i < NUM_MODULES && ret == true; ++i)
		ret = modules[i]->IsEnabled() ? modules[i]->Start() : true;

	return ret;
}

update_status Application::Update()
{
	update_status ret = UPDATE_CONTINUE;

	for(int i = 0; i < NUM_MODULES && ret == UPDATE_CONTINUE; ++i)
		ret = modules[i]->IsEnabled() ? modules[i]->PreUpdate() : UPDATE_CONTINUE;

	for(int i = 0; i < NUM_MODULES && ret == UPDATE_CONTINUE; ++i)
		ret = modules[i]->IsEnabled() ? modules[i]->Update() : UPDATE_CONTINUE;

	for(int i = 0; i < NUM_MODULES && ret == UPDATE_CONTINUE; ++i)
		ret = modules[i]->IsEnabled() ? modules[i]->PostUpdate() : UPDATE_CONTINUE;

	return ret;
}

bool Application::CleanUp()
{
	bool ret = true;

	for(int i = NUM_MODULES - 1; i >= 0 && ret == true; --i)
		ret = modules[i]->CleanUp();

	return ret;
}