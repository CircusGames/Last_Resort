#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleSceneLvl1.h"
#include "ModuleSceneLvl3.h"
#include "ModulePlayer.h"
//#include "ModulePlayer2.h"
#include "ModuleInput.h"
#include "ModuleFadeToBlack.h"
#include "ModuleContinue.h"
#include "ModuleGameOver.h"
#include "ModuleAudio.h"
#include "ModulePlayerUnit.h"
//#include "ModulePlayer2Unit.h"
#include "ModuleParticles.h"
#include "ModuleCollision.h"
#include "ModulePowerUp.h"
#include "ModuleEnemies.h"
#include "ModuleUI.h"

ModuleSceneLvl3::ModuleSceneLvl3()
{

	//initialize background rects
	bgRect = {0,0,2592,224};
	fgRect = {0,0,3344,130};

	//sea waves animations
	for (int i = 0; i < MAXWAVES; ++i)
	{
		seaWavesAnim[i].PushBack({0,0,128,38});
		seaWavesAnim[i].PushBack({ 0,38,128,38 });
		seaWavesAnim[i].PushBack({ 0,76,128,38 });
		seaWavesAnim[i].PushBack({ 0,114,128,38 });
		seaWavesAnim[i].PushBack({ 0,152,128,38 });
		seaWavesAnim[i].PushBack({ 0,190,128,38 });
		seaWavesAnim[i].PushBack({ 0,228,128,38 });
		seaWavesAnim[i].PushBack({ 0,266,128,38 });
		seaWavesAnim[i].speed = 0.125f;
	}
	
}

ModuleSceneLvl3::~ModuleSceneLvl3()
{}

bool ModuleSceneLvl3::Init()
{


	return true;
}

bool ModuleSceneLvl3::Start()
{

	LOG("Starting level 3");

	bgTexture = App->textures->Load("assets/Graphics/Backgrounds/Lvl_3/background_3.png");
	fgTexture = App->textures->Load("assets/Graphics/Backgrounds/Lvl_3/foreground_3.png");
	fgWavesTexture = App->textures->Load("assets/Graphics/Backgrounds/Lvl_3/seaWavesFixed.png");

	//starting needed background variables
	scroll = true;

	
	return true;
}

update_status ModuleSceneLvl3::PreUpdate()
{
	if (scroll)
	{
		App->render->camera.x -= 1 * SCREEN_SIZE;
	}

	return UPDATE_CONTINUE;
}

update_status ModuleSceneLvl3::Update()
{
	

	// draw --------------------------------------------------------------------------------
	//jungle background
	App->render->Blit(bgTexture,0,0,&bgRect, 0.25f);

	//sea waves animations

	for (int i = 0; i < MAXWAVES; ++i)
	{
		App->render->Blit(fgWavesTexture, i * 128, 186, &seaWavesAnim[i].GetCurrentFrame(), 0.50f);
	}
	
	//cave background
	App->render->Blit(fgTexture, 2100, 94, &fgRect, 0.50f);
	
	
	return UPDATE_CONTINUE;
}

bool ModuleSceneLvl3::CleanUp()
{

	return true;
}
