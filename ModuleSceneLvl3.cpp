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

	//wave caps animation (reflection to water layer)
	wavesCapAnim.PushBack({0,0,28,14});
	wavesCapAnim.PushBack({ 30,0,29,14 });
	wavesCapAnim.PushBack({ 0,14,29,14 });
	wavesCapAnim.PushBack({ 30,14,29,14 });
	wavesCapAnim.PushBack({ 0,28,29,14 });
	wavesCapAnim.PushBack({ 30,28,27,14 });
	wavesCapAnim.PushBack({ 0,42,26,14 });
	wavesCapAnim.speed = 0.14f;
	
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
	App->player->sceneCallback = this;
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
	bossBgTexture = App->textures->Load("assets/Graphics/Backgrounds/Lvl_3/bossBg.png");
	wavesCapTexture = App->textures->Load("assets/Graphics/Backgrounds/Lvl_3/lvl3WavesCapAnim.png");

	//starting needed background variables
	scroll = true;
	//App->render->camera.x = -27000; //camera trick

	//assigns correct current level stage zone
	currentLevelZone = stage_zone::level;
	
	//load needed audios
	App->audio->LoadAudio("assets/Audio/Music/song_level_3.ogg", "song_lvl3", MUSIC);
	App->audio->ControlAudio("song_lvl3", MUSIC, FADEIN, -1, 1500.0f);

	//boss background fade values
	faded = false;
	total_time = 2500; //fade time

	//add wall colliders to scene
	AddColliders();

	//correct camera position
	App->render->camera.x = 0;
	


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

	if (currentLevelZone == stage_zone::level) // if we entry on boss zone and still not faded the boss background
	{
		//check when player entries boss zone
		if (GetCurrentCameraPixelPos() > 5520 - SCREEN_WIDTH - 360) //-360 is the zone when boss background appears with fade
		{
			start_time = SDL_GetTicks();
			currentLevelZone = stage_zone::boss_zone; //change level current zone
		}

	}

	//set colliders to follow correct foreground speed
	setCollidersToScenePos();

	return UPDATE_CONTINUE;
}

update_status ModuleSceneLvl3::Update()
{

	// draw --------------------------------------------------------------------------------
	//jungle background
	App->render->Blit(bgTexture,0,0,&bgRect, 0.25f);

	//checks if we have to draw boss background
	if (currentLevelZone == stage_zone::boss_zone)
	{
		//draw background
		App->render->Blit(bossBgTexture, 0, 0, NULL, 0.0f);
			
		if (!faded)
		{
			bossBackgroundFade();
		}
	}

	//sea water cap (finish the sea water reflections layer) ---------------------------------

	App->render->Blit(wavesCapTexture, 1024 , 177, &wavesCapAnim.GetCurrentFrame(), 0.25f);
		
	//sea water reflections
	
	for (int i = 0; i < NUMREFLECTIONS; ++i)
	{
		App->render->Blit(bgWaterReflectionsTexture, i * 256, 177, &bgWaterReflectionsAnim[i].GetCurrentFrame(), 0.25f);
	}

	// ----------------------------------------------------------------------------------------

	//sea waves animations (foreground waves)

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
	App->textures->Unload(wavesCapTexture);
	App->textures->Unload(bossBgTexture);
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

	//reposition the camera
	App->render->camera.x = 0;

	//send to moduleUI new stage
	App->moduleUI->UI = gameplay_state::NO;



	return true;
}

void ModuleSceneLvl3::addEnemiesToLvl3()
{
	//First Wave
	App->enemies->AddEnemy(ENEMY_TYPES::REDBIRD, 300, 35, NONE);
	App->enemies->AddEnemy(ENEMY_TYPES::REDBIRD, 300, 90, NONE);
	App->enemies->AddEnemy(ENEMY_TYPES::REDBIRD, 342, 35, NONE);
	App->enemies->AddEnemy(ENEMY_TYPES::REDBIRD, 342, 90, NONE);
	App->enemies->AddEnemy(ENEMY_TYPES::REDBIRD, 372, 35, NONE);
	App->enemies->AddEnemy(ENEMY_TYPES::REDBIRD, 372, 90, NONE);
	App->enemies->AddEnemy(ENEMY_TYPES::REDBIRD, 402, 35, NONE);
	App->enemies->AddEnemy(ENEMY_TYPES::REDBIRD, 402, 90, NONE);
	App->enemies->AddEnemy(ENEMY_TYPES::REDBIRD, 432, 35, NONE);
	App->enemies->AddEnemy(ENEMY_TYPES::REDBIRD, 432, 90, NONE);
	App->enemies->AddEnemy(ENEMY_TYPES::REDBIRD, 462, 35, BOMBS);
	App->enemies->AddEnemy(ENEMY_TYPES::REDBIRD, 462, 90, NONE);

	//Second Wave
	App->enemies->AddEnemy(ENEMY_TYPES::REDBIRD, 680, 35, NONE);
	App->enemies->AddEnemy(ENEMY_TYPES::REDBIRD, 710, 35, NONE);
	App->enemies->AddEnemy(ENEMY_TYPES::REDBIRD, 740, 35, NONE);
	App->enemies->AddEnemy(ENEMY_TYPES::REDBIRD, 770, 35, NONE);
	App->enemies->AddEnemy(ENEMY_TYPES::REDBIRD, 800, 35, NONE);
	App->enemies->AddEnemy(ENEMY_TYPES::REDBIRD, 830, 35, NONE);

	//Third Wave
	App->enemies->AddEnemy(ENEMY_TYPES::REDBIRD, 1170, 90, NONE);
	App->enemies->AddEnemy(ENEMY_TYPES::REDBIRD, 1200, 90, NONE);
	App->enemies->AddEnemy(ENEMY_TYPES::REDBIRD, 1230, 90, NONE);
	App->enemies->AddEnemy(ENEMY_TYPES::REDBIRD, 1260, 90, NONE);
	App->enemies->AddEnemy(ENEMY_TYPES::REDBIRD, 1290, 90, NONE);
	App->enemies->AddEnemy(ENEMY_TYPES::REDBIRD, 1320, 90, BOOST);

	//-----------------------------------------------------------

	App->enemies->AddEnemy(ENEMY_TYPES::POWERUP_BEE, 3200, 75, BOOST);
	App->enemies->AddEnemy(ENEMY_TYPES::POWERUP_BEE, 4900, 75, BOOST);
	App->enemies->AddEnemy(ENEMY_TYPES::POWERUP_BEE, 5700, 75, BOOST);
	App->enemies->AddEnemy(ENEMY_TYPES::POWERUP_BEE, 6100, 75, BOOST);



}

void ModuleSceneLvl3::AddColliders() 
{
	sceneColliders[0] = App->collision->AddCollider({0, 192, 1256, 33}, COLLIDER_TYPE::COLLIDER_WALL, this);
	//sceneColliders[1] = App->collision->AddCollider({ 300, 50, 50, 70 }, COLLIDER_TYPE::COLLIDER_WALL, this); //test
	//sceneColliders[2] = App->collision->AddCollider({ 350, 70, 50, 70 }, COLLIDER_TYPE::COLLIDER_WALL, this); //test
	//sceneColliders[3] = App->collision->AddCollider({0, 20, 50, 70 }, COLLIDER_TYPE::COLLIDER_WALL, this); //test

}

void ModuleSceneLvl3::setCollidersToScenePos()
{
	currentCameraPixelPos = GetCurrentCameraPixelPos();

	for (int i = 0; i < MAX_SCENE_COLLIDERS; ++i)
	{
		if (sceneColliders[i] == nullptr) continue;

		lastCameraPosX = GetCurrentCameraPixelPos();
		
		if (currentCameraPixelPos != lastCameraPosX)
		{
			sceneColliders[i]->rect.x += 1;
			
		}
		
		sceneColliders[i]->SetPos(sceneColliders[i]->rect.x, sceneColliders[i]->rect.y);
		
	}

}

float ModuleSceneLvl3::GetCurrentCameraPixelPos()
{
	return (-App->render->camera.x / SCREEN_SIZE * 0.5f); //respect foreground camera pos
}

void ModuleSceneLvl3::bossBackgroundFade()
{
	SDL_Rect bossBgRect = { 0,0,304 * SCREEN_SIZE, 224 * SCREEN_SIZE };
	
	//fade
	if (!faded)
	{
		now = SDL_GetTicks() - start_time;

		float normalized = MIN(1.0f, (float)now / (float)total_time);
		normalized = 1.0f - normalized;
		//blending alpha
		SDL_SetRenderDrawBlendMode(App->render->renderer, SDL_BLENDMODE_BLEND);
		SDL_SetRenderDrawColor(App->render->renderer, 0, 0, 0,(Uint8)(normalized * 255.0f));
		SDL_RenderFillRect(App->render->renderer, &bossBgRect);

		if (now >= total_time)
			faded = true;
	}
}