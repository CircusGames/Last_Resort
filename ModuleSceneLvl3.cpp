#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleSceneLvl1.h"
#include "ModuleSceneLvl3.h"
//#include "ModulePlayer.h"
//#include "ModulePlayer2.h"
#include "Player.h"
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
	// player modules -------------------
	App->player[0]->Enable();
	App->player[0]->sceneCallback = this;
	App->player[1]->Enable();
	App->player[1]->sceneCallback = this;
	// ----------------------------------
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
	//App->render->camera.x = -10000; //camera trick

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
		//if(App->player[0]->IsEnabled)
		App->player[0]->position.x += 1;
		if (App->player[1]->IsEnabled())
			App->player[1]->position.x += 1;
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
	
	//DEBUG actual colliders in scene
	//LOG("current scene colliders: %d", App->collision->actualColliders);

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
	App->player[0]->Disable();
	if (App->player[1]->IsEnabled())
		App->player[1]->Disable();

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

	//Last Wave
	App->enemies->AddEnemy(ENEMY_TYPES::REDBIRD, 8600, 45, NONE);
	App->enemies->AddEnemy(ENEMY_TYPES::REDBIRD, 8630, 45, NONE);
	App->enemies->AddEnemy(ENEMY_TYPES::REDBIRD, 8660, 45, NONE);
	App->enemies->AddEnemy(ENEMY_TYPES::REDBIRD, 8690, 45, NONE);
	App->enemies->AddEnemy(ENEMY_TYPES::REDBIRD, 8720, 45, NONE);
	App->enemies->AddEnemy(ENEMY_TYPES::REDBIRD, 8750, 45, NONE);

	App->enemies->AddEnemy(ENEMY_TYPES::REDBIRD, 9150, 45, NONE);
	App->enemies->AddEnemy(ENEMY_TYPES::REDBIRD, 9180, 45, NONE);
	App->enemies->AddEnemy(ENEMY_TYPES::REDBIRD, 9210, 45, NONE);
	App->enemies->AddEnemy(ENEMY_TYPES::REDBIRD, 9240, 45, NONE);
	App->enemies->AddEnemy(ENEMY_TYPES::REDBIRD, 9270, 45, NONE);
	App->enemies->AddEnemy(ENEMY_TYPES::REDBIRD, 9300, 45, NONE);
	//-----------------------------------------------------------

	// Enemy POWERUP BEE
	App->enemies->AddEnemy(ENEMY_TYPES::POWERUP_BEE, 3200, 75, BOOST);
	App->enemies->AddEnemy(ENEMY_TYPES::POWERUP_BEE, 4900, 75, BOOST);
	App->enemies->AddEnemy(ENEMY_TYPES::POWERUP_BEE, 5700, 75, BOOST);
	App->enemies->AddEnemy(ENEMY_TYPES::POWERUP_BEE, 6100, 75, BOOST);

	// ----------------------------------------------------------
	// Enemy PROTATORS

	App->enemies->AddEnemy(ENEMY_TYPES::ENEMYPROTATOR, 4658, 139, NONE); //20
	App->enemies->AddEnemy(ENEMY_TYPES::ENEMYPROTATOR, 4754, 139, NONE);

	App->enemies->AddEnemy(ENEMY_TYPES::ENEMYPROTATOR, 4818, 155, NONE);
	App->enemies->AddEnemy(ENEMY_TYPES::ENEMYPROTATOR, 4854, 155, NONE);
	App->enemies->AddEnemy(ENEMY_TYPES::ENEMYPROTATOR, 4886, 155, NONE);
	App->enemies->AddEnemy(ENEMY_TYPES::ENEMYPROTATOR, 4948, 155, NONE);
	App->enemies->AddEnemy(ENEMY_TYPES::ENEMYPROTATOR, 5010, 155, NONE);
	App->enemies->AddEnemy(ENEMY_TYPES::ENEMYPROTATOR, 5074, 155, NONE);

	App->enemies->AddEnemy(ENEMY_TYPES::ENEMYPROTATOR, 5138, 189, NONE);
	App->enemies->AddEnemy(ENEMY_TYPES::ENEMYPROTATOR, 5266, 189, NONE);
	App->enemies->AddEnemy(ENEMY_TYPES::ENEMYPROTATOR, 5298, 189, NONE);
	App->enemies->AddEnemy(ENEMY_TYPES::ENEMYPROTATOR, 5330, 189, NONE);
	App->enemies->AddEnemy(ENEMY_TYPES::ENEMYPROTATOR, 5362, 189, NONE);
	App->enemies->AddEnemy(ENEMY_TYPES::ENEMYPROTATOR, 5394, 189, NONE);
	App->enemies->AddEnemy(ENEMY_TYPES::ENEMYPROTATOR, 5426, 189, NONE);
	App->enemies->AddEnemy(ENEMY_TYPES::ENEMYPROTATOR, 5458, 189, NONE);

	App->enemies->AddEnemy(ENEMY_TYPES::ENEMYPROTATOR, 5490, 112, NONE);
	App->enemies->AddEnemy(ENEMY_TYPES::ENEMYPROTATOR, 5522, 112, NONE);
	App->enemies->AddEnemy(ENEMY_TYPES::ENEMYPROTATOR, 5552, 112, NONE);
	App->enemies->AddEnemy(ENEMY_TYPES::ENEMYPROTATOR, 5584, 112, NONE);

	App->enemies->AddEnemy(ENEMY_TYPES::ENEMYPROTATOR, 5618, 127, NONE);
	App->enemies->AddEnemy(ENEMY_TYPES::ENEMYPROTATOR, 5650, 127, NONE);
	App->enemies->AddEnemy(ENEMY_TYPES::ENEMYPROTATOR, 5682, 127, NONE);

	App->enemies->AddEnemy(ENEMY_TYPES::ENEMYPROTATOR, 5714, 144, NONE);
	App->enemies->AddEnemy(ENEMY_TYPES::ENEMYPROTATOR, 5746, 144, NONE);

	App->enemies->AddEnemy(ENEMY_TYPES::ENEMYPROTATOR, 5810, 189, NONE);
	App->enemies->AddEnemy(ENEMY_TYPES::ENEMYPROTATOR, 5842, 189, NONE);
	App->enemies->AddEnemy(ENEMY_TYPES::ENEMYPROTATOR, 5874, 189, NONE);
	App->enemies->AddEnemy(ENEMY_TYPES::ENEMYPROTATOR, 5906, 189, NONE);
	App->enemies->AddEnemy(ENEMY_TYPES::ENEMYPROTATOR, 5938, 189, NONE);
	App->enemies->AddEnemy(ENEMY_TYPES::ENEMYPROTATOR, 5970, 189, NONE);
	App->enemies->AddEnemy(ENEMY_TYPES::ENEMYPROTATOR, 6002, 189, NONE);
	App->enemies->AddEnemy(ENEMY_TYPES::ENEMYPROTATOR, 6034, 189, NONE);

	App->enemies->AddEnemy(ENEMY_TYPES::ENEMYPROTATOR, 6130, 128, NONE);
	App->enemies->AddEnemy(ENEMY_TYPES::ENEMYPROTATOR, 6162, 128, NONE);
	App->enemies->AddEnemy(ENEMY_TYPES::ENEMYPROTATOR, 6194, 128, NONE);
	App->enemies->AddEnemy(ENEMY_TYPES::ENEMYPROTATOR, 6226, 128, NONE);
	App->enemies->AddEnemy(ENEMY_TYPES::ENEMYPROTATOR, 6258, 128, NONE);

	App->enemies->AddEnemy(ENEMY_TYPES::ENEMYPROTATOR, 6290, 189, NONE);
	App->enemies->AddEnemy(ENEMY_TYPES::ENEMYPROTATOR, 6322, 189, NONE);

	App->enemies->AddEnemy(ENEMY_TYPES::ENEMYPROTATOR, 6354, 185, NONE);
	App->enemies->AddEnemy(ENEMY_TYPES::ENEMYPROTATOR, 6386, 185, NONE);

	App->enemies->AddEnemy(ENEMY_TYPES::ENEMYPROTATOR, 6418, 155, NONE);
	App->enemies->AddEnemy(ENEMY_TYPES::ENEMYPROTATOR, 6482, 155, NONE);

	App->enemies->AddEnemy(ENEMY_TYPES::ENEMYPROTATOR, 6546, 176, NONE);

	App->enemies->AddEnemy(ENEMY_TYPES::ENEMYPROTATOR, 6610, 189, NONE);

	App->enemies->AddEnemy(ENEMY_TYPES::ENEMYPROTATOR, 6674, 112, NONE);
	App->enemies->AddEnemy(ENEMY_TYPES::ENEMYPROTATOR, 6738, 112, NONE);

	App->enemies->AddEnemy(ENEMY_TYPES::ENEMYPROTATOR, 6802, 126, NONE);

	App->enemies->AddEnemy(ENEMY_TYPES::ENEMYPROTATOR, 6866, 144, NONE);
	App->enemies->AddEnemy(ENEMY_TYPES::ENEMYPROTATOR, 6906, 144, NONE);

	App->enemies->AddEnemy(ENEMY_TYPES::ENEMYPROTATOR, 6994, 189, NONE);
	App->enemies->AddEnemy(ENEMY_TYPES::ENEMYPROTATOR, 7058, 189, NONE);
	App->enemies->AddEnemy(ENEMY_TYPES::ENEMYPROTATOR, 7122, 189, NONE);
	App->enemies->AddEnemy(ENEMY_TYPES::ENEMYPROTATOR, 7186, 189, NONE);
	App->enemies->AddEnemy(ENEMY_TYPES::ENEMYPROTATOR, 7250, 189, NONE);

	App->enemies->AddEnemy(ENEMY_TYPES::ENEMYPROTATOR, 7342, 189, NONE);

	App->enemies->AddEnemy(ENEMY_TYPES::ENEMYPROTATOR, 7466, 189, NONE);
	App->enemies->AddEnemy(ENEMY_TYPES::ENEMYPROTATOR, 7546, 189, NONE);
	App->enemies->AddEnemy(ENEMY_TYPES::ENEMYPROTATOR, 7626, 189, NONE);
	App->enemies->AddEnemy(ENEMY_TYPES::ENEMYPROTATOR, 7706, 189, NONE);
	App->enemies->AddEnemy(ENEMY_TYPES::ENEMYPROTATOR, 7786, 189, NONE);
	App->enemies->AddEnemy(ENEMY_TYPES::ENEMYPROTATOR, 7866, 189, NONE);
	App->enemies->AddEnemy(ENEMY_TYPES::ENEMYPROTATOR, 7946, 189, NONE);
	App->enemies->AddEnemy(ENEMY_TYPES::ENEMYPROTATOR, 8026, 189, NONE);
	App->enemies->AddEnemy(ENEMY_TYPES::ENEMYPROTATOR, 8106, 189, NONE);
	App->enemies->AddEnemy(ENEMY_TYPES::ENEMYPROTATOR, 8186, 189, NONE);
	App->enemies->AddEnemy(ENEMY_TYPES::ENEMYPROTATOR, 8266, 189, NONE);
	App->enemies->AddEnemy(ENEMY_TYPES::ENEMYPROTATOR, 8346, 189, NONE);
	App->enemies->AddEnemy(ENEMY_TYPES::ENEMYPROTATOR, 8426, 189, NONE);
	App->enemies->AddEnemy(ENEMY_TYPES::ENEMYPROTATOR, 8506, 189, NONE);
	App->enemies->AddEnemy(ENEMY_TYPES::ENEMYPROTATOR, 8586, 189, NONE);

	App->enemies->AddEnemy(ENEMY_TYPES::ENEMYPROTATOR, 8652, 189, NONE);

	App->enemies->AddEnemy(ENEMY_TYPES::ENEMYPROTATOR, 8734, 189, NONE);
	App->enemies->AddEnemy(ENEMY_TYPES::ENEMYPROTATOR, 8814, 189, NONE);
	App->enemies->AddEnemy(ENEMY_TYPES::ENEMYPROTATOR, 8894, 189, NONE);
	App->enemies->AddEnemy(ENEMY_TYPES::ENEMYPROTATOR, 8974, 189, NONE);

	App->enemies->AddEnemy(ENEMY_TYPES::ENEMYPROTATOR, 9038, 189, NONE);

	App->enemies->AddEnemy(ENEMY_TYPES::ENEMYPROTATOR, 9116, 189, NONE);
	App->enemies->AddEnemy(ENEMY_TYPES::ENEMYPROTATOR, 9194, 189, NONE);

	App->enemies->AddEnemy(ENEMY_TYPES::ENEMYPROTATOR, 9276, 189, NONE);

	App->enemies->AddEnemy(ENEMY_TYPES::ENEMYPROTATOR, 9436, 189, NONE);

	App->enemies->AddEnemy(ENEMY_TYPES::ENEMYPROTATOR, 9564, 189, NONE);
	App->enemies->AddEnemy(ENEMY_TYPES::ENEMYPROTATOR, 9644, 189, NONE);
	App->enemies->AddEnemy(ENEMY_TYPES::ENEMYPROTATOR, 9804, 189, NONE);
	App->enemies->AddEnemy(ENEMY_TYPES::ENEMYPROTATOR, 9884, 189, NONE);
	App->enemies->AddEnemy(ENEMY_TYPES::ENEMYPROTATOR, 9938, 189, NONE);

	//------------------------------------------------------------------

	//Enemy BEE
	App->enemies->AddEnemy(ENEMY_TYPES::ENEMYBEE, 3600, 80, NONE);
	App->enemies->AddEnemy(ENEMY_TYPES::ENEMYBEE, 4000, 80, NONE);
	App->enemies->AddEnemy(ENEMY_TYPES::ENEMYBEE, 4200, 80, NONE);




	






	//App->enemies->AddEnemy(ENEMY_TYPES::ENEMYPROTATOR, 5584, 108, NONE);


	




}

void ModuleSceneLvl3::AddColliders() 
{
	sceneColliders[0] = App->collision->AddCollider({0, 189, 15000, 50}, COLLIDER_TYPE::COLLIDER_WALL, this);
	sceneColliders[1] = App->collision->AddCollider({ 2169,176,64,50 }, COLLIDER_TYPE::COLLIDER_WALL, this);
	sceneColliders[2] = App->collision->AddCollider({ 2393,176,64,50 }, COLLIDER_TYPE::COLLIDER_WALL, this);
	sceneColliders[3] = App->collision->AddCollider({ 2453,139,95,50 }, COLLIDER_TYPE::COLLIDER_WALL, this);
	sceneColliders[4] = App->collision->AddCollider({ 2548,155,163,50 }, COLLIDER_TYPE::COLLIDER_WALL, this);
	sceneColliders[5] = App->collision->AddCollider({ 2916,112,64,100 }, COLLIDER_TYPE::COLLIDER_WALL, this);
	sceneColliders[6] = App->collision->AddCollider({ 2980,127,34,100 }, COLLIDER_TYPE::COLLIDER_WALL, this);
	sceneColliders[7] = App->collision->AddCollider({ 3010,144,50,50 }, COLLIDER_TYPE::COLLIDER_WALL, this);
	sceneColliders[8] = App->collision->AddCollider({ 3200,140,20,50 }, COLLIDER_TYPE::COLLIDER_WALL, this);
	sceneColliders[9] = App->collision->AddCollider({ 3220,128,83,100 }, COLLIDER_TYPE::COLLIDER_WALL, this);
	sceneColliders[10] = App->collision->AddCollider({ 3376,154,55,50 }, COLLIDER_TYPE::COLLIDER_WALL, this);
	sceneColliders[11] = App->collision->AddCollider({ 3430,176,32,30 }, COLLIDER_TYPE::COLLIDER_WALL, this);
	sceneColliders[12] = App->collision->AddCollider({ 3493,112,64,100 }, COLLIDER_TYPE::COLLIDER_WALL, this);
	sceneColliders[13] = App->collision->AddCollider({ 3557,126,34,100 }, COLLIDER_TYPE::COLLIDER_WALL, this);
	sceneColliders[14] = App->collision->AddCollider({ 3591,144,49,100 }, COLLIDER_TYPE::COLLIDER_WALL, this);
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