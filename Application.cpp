#include "Application.h"
#include "ModuleWindow.h"
#include "ModuleRender.h"
#include "ModuleInput.h"
#include "ModuleTextures.h"
#include "ModuleSceneLvl1.h"
#include "ModuleParticles.h"
#include "ModulePlayer.h"
#include "ModulePlayer2.h"
#include "ModulePlayerUnit.h"
#include "ModulePlayer2Unit.h"
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
	modules[i++] = player = new ModulePlayer();
	//modules[i++] = player2 = new ModulePlayer2();
	modules[i++] = playerUnit = new ModulePlayerUnit();
	//modules[i++] = player2Unit = new ModulePlayer2Unit();
	modules[i++] = particles = new ModuleParticles();
	modules[i++] = collision = new ModuleCollision();
	modules[i++] = audio = new ModuleAudio();
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
	//disable modulePlayer at init -------
	//scenes ------------
	teamLogo->Disable();
	gameTitle->Disable();
	//scene_lvl1->Disable();
	gameOverScreen->Disable();
	//other modules -----
	player->Disable();
	//player2->Disable();
	playerUnit->Disable();
	//player2Unit->Disable();
	collision->Disable();
	particles->Disable();
	
	// -----------------------------------
	//all modules have their init
	for(int i = 0; i < NUM_MODULES && ret == true; ++i)
		ret = modules[i]->Init();

	//but only the needed have start
	//for(int i = 0; i < NUM_MODULES && ret == true; ++i)
	for (int i = NUM_MODULES; i >= 0 && ret == true; --i)            //only if the scene is load at first stage
		ret = modules[i]->IsEnabled() ? modules[i]->Start() : true;  //(for debug and testing new functionalities)
	
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