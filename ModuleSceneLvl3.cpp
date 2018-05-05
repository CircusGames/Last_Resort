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

	//background water reflections
	for (int i = 0; i < NUMREFLECTIONS; ++i)
	{
		bgWaterReflectionsAnim[i].PushBack({0,0,256,11});
		bgWaterReflectionsAnim[i].PushBack({ 0,11,256,11 });
		bgWaterReflectionsAnim[i].PushBack({ 0,22,256,11 });
		bgWaterReflectionsAnim[i].PushBack({ 0,33,256,11 });
		bgWaterReflectionsAnim[i].PushBack({ 0,44,256,11 });
		bgWaterReflectionsAnim[i].PushBack({ 0,55,256,11 });
		bgWaterReflectionsAnim[i].PushBack({ 0,66,256,11 });
		bgWaterReflectionsAnim[i].speed = 0.14f;
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
	//enable needed modules ------------------
	App->player->Enable();
	//App->player2->Enable();
	App->particles->Enable();
	App->collision->Enable();
	App->modulePowerUp->Enable();
	App->enemies->Enable();

	//adding enemies to Level
	addEnemiesToLvl3();

	//changes the state of the UI ------------
	App->moduleUI->UI = gameplay_state::SCENE;

	LOG("Starting level 3");

	bgTexture = App->textures->Load("assets/Graphics/Backgrounds/Lvl_3/background_3_fixed.png");
	fgTexture = App->textures->Load("assets/Graphics/Backgrounds/Lvl_3/foreground_3.png");
	fgWavesTexture = App->textures->Load("assets/Graphics/Backgrounds/Lvl_3/seaWavesFixed.png");
	bgWaterReflectionsTexture = App->textures->Load("assets/Graphics/Backgrounds/Lvl_3/seaWaterReflections.png");

	//starting needed background variables
	scroll = true;
	//App->render->camera.x = -30000; //camera trick

	//assigns correct current level stage zone
	currentLevelZone = stage_zone::level;
	
	//load needed audios
	App->audio->LoadAudio("assets/Audio/Music/song_level_3.ogg", "song_lvl3", MUSIC);
	App->audio->ControlAudio("song_lvl3", MUSIC, FADEIN, -1, 1500.0f);

	return true;
}

update_status ModuleSceneLvl3::PreUpdate()
{
	if (scroll)
	{
		App->render->camera.x -= 1 * SCREEN_SIZE;
		//move player position to follow the camera movement
		App->player->position.x += 1;
	}

	

	if (GetCurrentCameraPixelPos() > 5520 - SCREEN_WIDTH - 26.5f) //-26.5f is the offset
	{
		scroll = false;
	}

	//check when player entries boss zone
	if (GetCurrentCameraPixelPos() > 5520 - SCREEN_WIDTH - 300) //-300 is the zone when boss background appears with fade
	{
		scroll = false;
	}


	return UPDATE_CONTINUE;
}

update_status ModuleSceneLvl3::Update()
{
	

	// draw --------------------------------------------------------------------------------
	//jungle background
	App->render->Blit(bgTexture,0,0,&bgRect, 0.25f);

	//sea water reflections
	for (int i = 0; i < NUMREFLECTIONS; ++i)
	{
		App->render->Blit(bgWaterReflectionsTexture, i * 256, 177, &bgWaterReflectionsAnim[i].GetCurrentFrame(), 0.25f);
	}

	//sea waves animations

	for (int i = 0; i < MAXWAVES; ++i)
	{
		App->render->Blit(fgWavesTexture, i * 128, 186, &seaWavesAnim[i].GetCurrentFrame(), 0.50f);
	}
	
	//cave background
	App->render->Blit(fgTexture, 2150, 94, &fgRect, 0.50f);
	
	
	return UPDATE_CONTINUE;
}

bool ModuleSceneLvl3::CleanUp()
{
	//unload textures ---
	App->textures->Unload(bgWaterReflectionsTexture);
	App->textures->Unload(fgWavesTexture);
	App->textures->Unload(fgTexture);
	App->textures->Unload(bgTexture);

	//unload audio ---
	App->audio->UnloadAudio("song_lvl3", MUSIC);
	
	//unload modules
	App->enemies->Disable();
	App->modulePowerUp->Disable();
	App->collision->Disable();
	App->particles->Disable();
	App->player->Disable();



	return true;
}

void ModuleSceneLvl3::addEnemiesToLvl3()
{
	//First Wave
	App->enemies->AddEnemy(ENEMY_TYPES::REDBIRD, 300, 30, NONE);
	App->enemies->AddEnemy(ENEMY_TYPES::REDBIRD, 300, 90, NONE);
	App->enemies->AddEnemy(ENEMY_TYPES::REDBIRD, 342, 30, NONE);
	App->enemies->AddEnemy(ENEMY_TYPES::REDBIRD, 342, 90, NONE);
	App->enemies->AddEnemy(ENEMY_TYPES::REDBIRD, 372, 30, NONE);
	App->enemies->AddEnemy(ENEMY_TYPES::REDBIRD, 372, 90, NONE);
	App->enemies->AddEnemy(ENEMY_TYPES::REDBIRD, 402, 30, NONE);
	App->enemies->AddEnemy(ENEMY_TYPES::REDBIRD, 402, 90, NONE);
	App->enemies->AddEnemy(ENEMY_TYPES::REDBIRD, 432, 30, NONE);
	App->enemies->AddEnemy(ENEMY_TYPES::REDBIRD, 432, 90, NONE);
	App->enemies->AddEnemy(ENEMY_TYPES::REDBIRD, 462, 30, NONE);
	App->enemies->AddEnemy(ENEMY_TYPES::REDBIRD, 462, 90, NONE);
}

float ModuleSceneLvl3::GetCurrentCameraPixelPos()
{
	return (-App->render->camera.x / SCREEN_SIZE * 0.5f); //respect foreground camera pos
}

void ModuleSceneLvl3::bossBackgroundFade()
{

}