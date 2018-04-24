#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleSceneLvl1.h"
#include "ModulePlayer.h"
#include "ModulePlayer2.h"
#include "ModuleInput.h"
#include "ModuleFadeToBlack.h"
#include "ModuleContinue.h"
#include "ModuleGameOver.h"
#include "ModuleAudio.h"
#include "ModulePlayerUnit.h"
#include "ModulePlayer2Unit.h"
#include "ModuleParticles.h"
#include "ModuleCollision.h"
#include "ModulePowerUp.h"
#include "ModuleEnemies.h"
#include "ModuleUI.h"

#define STREET_LIGHTS_A 15
#define STREET_LIGHTS_B 13
#define STREET_LIGHTS_FRONT_A 8
#define STREET_LIGHTS_FRONT_B 6
#define TUNNEL_LIGHTS 8
#define BLUE_LASERS 5


ModuleSceneLvl1::ModuleSceneLvl1()
{
	

	//background lvl1 last resort
	bgRect.x = 0;
	bgRect.y = 0;
	bgRect.w = 803;
	bgRect.h = 160;

	//midground lvl1 last resort
	mgRect.x = 0;
	mgRect.y = 0;
	mgRect.w = 1303;
	mgRect.h = 160;

	//foreground lvl1 last resort
	fgRect.x = 0;
	fgRect.y = 0;
	fgRect.w = 4408;
	fgRect.h = 239;

	//streetlights source position rect animation cycle frames
	//Street lights pattern A
	//-----------------------------------------------------------------
	for (int i = 0; i < STREET_LIGHTS_A; ++i)
	{
		streetLightA[i].PushBack({ 0,0,48,65 });
		streetLightA[i].PushBack({ 49,0,48,65 });
		streetLightA[i].PushBack({ 98,0,48,65 });
		streetLightA[i].PushBack({ 147,0,48,65 });
		streetLightA[i].PushBack({ 196,0,48,65 });
		streetLightA[i].PushBack({ 147,0,48,65 });
		streetLightA[i].PushBack({ 98,0,48,65 });
		streetLightA[i].PushBack({ 49,0,48,65 });
		streetLightA[i].speed = 0.143f; //0.16f
	}

	for (int i = 0; i < STREET_LIGHTS_B; ++i)
	{
		streetLightB[i].PushBack({ 196,0,48,65 });
		streetLightB[i].PushBack({ 147,0,48,65 });
		streetLightB[i].PushBack({ 98,0,48,65 });
		streetLightB[i].PushBack({ 49,0,48,65 });
		streetLightB[i].PushBack({ 0,0,48,65 });
		streetLightB[i].PushBack({ 49,0,48,65 });
		streetLightB[i].PushBack({ 98,0,48,65 });
		streetLightB[i].PushBack({ 147,0,48,65 });
		streetLightB[i].speed = 0.143f;
	}
	//------------------------------------------------------------------
	//Street lights Front pattern A
	for (int i = 0; i < STREET_LIGHTS_FRONT_A; ++i)
	{
		streetLightsFrontA[i].PushBack({ 0,66,61, 20 }); 
		streetLightsFrontA[i].PushBack({ 62 ,66 , 61,20 });
		streetLightsFrontA[i].PushBack({ 124 ,66,61,20 });
		streetLightsFrontA[i].PushBack({ 186, 66, 61,20 });
		streetLightsFrontA[i].PushBack({ 0,87,66,20 });
		streetLightsFrontA[i].PushBack({ 186, 66, 61,20 });
		streetLightsFrontA[i].PushBack({ 124 ,66,61,20 });
		streetLightsFrontA[i].PushBack({ 62 ,66 , 61,20 });
		streetLightsFrontA[i].speed = 0.143f;
	}
	//Street lights Front pattern B
	for (int i = 0; i < STREET_LIGHTS_FRONT_B; ++i)
	{
		streetLightsFrontB[i].PushBack({ 0,87,66,20 });
		streetLightsFrontB[i].PushBack({ 186, 66, 61,20 });
		streetLightsFrontB[i].PushBack({ 124 ,66,61,20 });
		streetLightsFrontB[i].PushBack({ 62 ,66 , 61,20 });
		streetLightsFrontB[i].PushBack({ 0,66,61,20 });
		streetLightsFrontB[i].PushBack({ 62 ,66 , 61,20 });
		streetLightsFrontB[i].PushBack({ 124 ,66,61,20 });
		streetLightsFrontB[i].PushBack({ 186, 66, 61,20 });
		streetLightsFrontB[i].speed = 0.143f;
	}
	//tunnel lights
	for (int i = 0; i < TUNNEL_LIGHTS; ++i)
	{
		tunnelLights[i].PushBack({ 1,1,116,167 });
		tunnelLights[i].PushBack({ 118,1,116,167 });
		tunnelLights[i].PushBack({ 235,1,116,167 });
		tunnelLights[i].PushBack({ 352,1,116,167 });
		
		tunnelLights[i].PushBack({ 1,169,116,167 });
		tunnelLights[i].PushBack({ 118,169,116,167 });
		tunnelLights[i].PushBack({ 235,169,116,167 });
		tunnelLights[i].PushBack({ 352,169,116,167 });

		tunnelLights[i].speed = 0.143f;
	}

	//background light patterns----------------------------------
	//building 1
	backgroundLights[0].PushBack({ 1,1,89,78 });
	backgroundLights[0].PushBack({ 91,1,89,78 });
	backgroundLights[0].PushBack({ 181,1,89,78 });
	backgroundLights[0].PushBack({ 271,1,89,78 });
	backgroundLights[0].PushBack({ 361,1,89,78 });
	backgroundLights[0].PushBack({ 1,80,89,78 });
	backgroundLights[0].PushBack({ 91,80,89,78 });
	backgroundLights[0].PushBack({ 181,80,89,78 });
	backgroundLights[0].speed = 0.143f;
	//building 1
	backgroundLights[1].PushBack({ 271,80,12,16 });
	backgroundLights[1].PushBack({ 284,80,12,16 });
	backgroundLights[1].PushBack({ 297,80,12,16 });
	backgroundLights[1].PushBack({ 310,80,12,16 });
	backgroundLights[1].PushBack({ 323,80,12,16 });
	backgroundLights[1].PushBack({ 336,80,12,16 });
	backgroundLights[1].PushBack({ 349,80,12,16 });
	backgroundLights[1].PushBack({ 362,80,12,16 });
	backgroundLights[1].speed = 0.143f;
	//building 1
	backgroundLights[2].PushBack({ 1,161,64,75 });
	backgroundLights[2].PushBack({ 66,161,64,75 });
	backgroundLights[2].PushBack({ 131,161,64,75 });
	backgroundLights[2].PushBack({ 196,161,64,75 });
	backgroundLights[2].PushBack({ 261,161,64,75 });
	backgroundLights[2].PushBack({ 326,161,64,75 });
	backgroundLights[2].PushBack({ 391,161,64,75 });
	backgroundLights[2].PushBack({ 1,239,64,75 });
	backgroundLights[2].speed = 0.143f;
	//building 2 - (texture 1)
	backgroundLights[3].PushBack({ 1,585,31,58 });
	backgroundLights[3].PushBack({ 33,585,31,58 });
	backgroundLights[3].PushBack({ 65,585,31,58 });
	backgroundLights[3].PushBack({ 97,585,31,58 });
	backgroundLights[3].PushBack({ 129,585,31,58 });
	backgroundLights[3].PushBack({ 161,585,31,58 });
	backgroundLights[3].PushBack({ 193,585,31,58 });
	backgroundLights[3].PushBack({ 225,585,31,58 });
	backgroundLights[3].speed = 0.143f;
	//building2 - (texture 2)
	backgroundLights[4].PushBack({ 1,644,47,51, });
	backgroundLights[4].PushBack({ 49,644,47,51 }); 
	backgroundLights[4].PushBack({ 97,644,47,51 });
	backgroundLights[4].PushBack({ 145,644,47,51 });
	backgroundLights[4].PushBack({ 193,644,47,51 });
	backgroundLights[4].PushBack({ 241,644,47,51 });
	backgroundLights[4].PushBack({ 289,644,47,51 });
	backgroundLights[4].PushBack({ 337,644,47,51 });
	backgroundLights[4].speed = 0.143f;

	//building 3
	backgroundLights[5].PushBack({ 1,315,167,89 });
	backgroundLights[5].PushBack({ 169,315,167,89 });
	backgroundLights[5].PushBack({ 337,315,167,89 });
	backgroundLights[5].PushBack({ 1,405,167,89 });
	backgroundLights[5].PushBack({ 169,405,167,89 });
	backgroundLights[5].PushBack({ 337,405,167,89 });
	backgroundLights[5].PushBack({ 1,495,167,89 });
	backgroundLights[5].PushBack({ 169,495,167,89 });
	backgroundLights[5].speed = 0.143f;

	//building lasers
	//blue lasers
	for (int i = 0; i < BLUE_LASERS; ++i)
	{
		buildingLasers[i].PushBack({ 0,0,38,88 });
		buildingLasers[i].PushBack({ 38,0,30,88 });
		buildingLasers[i].PushBack({ 68,0,-5,88 }); //-5
		buildingLasers[i].PushBack({ 73,0,27, 88 });
		buildingLasers[i].PushBack({ 100, 0, 32,79 });
		buildingLasers[i].PushBack({ 73,0,27, 88 });
		buildingLasers[i].PushBack({ 68,0,5,88 });
		buildingLasers[i].PushBack({ 38,0,30,88 });
		buildingLasers[i].speed = 0.143f;
	}

	//orange laser (differents speeds while move,simulated with frame repetition)
	//mid to right
	orangeLaser.PushBack({ 132,0,25,144 });
	orangeLaser.PushBack({ 132,0,0,0 }); //flash
	orangeLaser.PushBack({ 157,0,38,145 });
	orangeLaser.PushBack({ 157,0,0,0 });
	orangeLaser.PushBack({ 195,0,52,145 });
	orangeLaser.PushBack({ 195,0,0,0 });
	orangeLaser.PushBack({ 247,0,65,144 });
	orangeLaser.PushBack({ 247,0,0,0 });
	orangeLaser.PushBack({ 247,0,65,144 });
	orangeLaser.PushBack({ 247,0,0,0 });
	orangeLaser.PushBack({ 312,0,81,145 });
	orangeLaser.PushBack({ 312,0,0,0 });
	orangeLaser.PushBack({ 312,0,81,145 });
	orangeLaser.PushBack({ 312,0,0,0 });
	orangeLaser.PushBack({ 312,0,81,145 });
	orangeLaser.PushBack({ 312,0,0,0 });
	orangeLaser.PushBack({ 393,0,99,145 });
	orangeLaser.PushBack({ 393,0,0,0 });
	orangeLaser.PushBack({ 393,0,99,145 });
	orangeLaser.PushBack({ 393,0,0,0 });
	orangeLaser.PushBack({ 393,0,99,145 });
	orangeLaser.PushBack({ 393,0,0,0 });
	orangeLaser.PushBack({ 0,145,121,144 });
	orangeLaser.PushBack({ 0,145,0,0 });
	orangeLaser.PushBack({ 0,145,121,144 });
	orangeLaser.PushBack({ 0,145,0,0 });
	orangeLaser.PushBack({ 0,145,121,144 });
	orangeLaser.PushBack({ 0,145,0,0 });
	orangeLaser.PushBack({ 121,145,142,142 });
	orangeLaser.PushBack({ 121,145,0,0 });
	orangeLaser.PushBack({ 121,145,142,142 });
	orangeLaser.PushBack({ 121,145,0,0 });
	orangeLaser.PushBack({ 121,145,142,142 });
	orangeLaser.PushBack({ 121,145,0,0 });
	orangeLaser.PushBack({ 121,145,142,142 });
	orangeLaser.PushBack({ 121,145,0,0 });
	orangeLaser.PushBack({ 0,145,121,144 });
	orangeLaser.PushBack({ 0,145,0,0 });
	orangeLaser.PushBack({ 0,145,121,144 });
	orangeLaser.PushBack({ 0,145,0,0 });
	orangeLaser.PushBack({ 0,145,121,144 });
	orangeLaser.PushBack({ 0,145,0,0 });
	orangeLaser.PushBack({ 0,145,121,144 });
	orangeLaser.PushBack({ 0,145,0,0 });
	orangeLaser.PushBack({ 393,0,99,145 });
	orangeLaser.PushBack({ 393,0,0,0 });
	orangeLaser.PushBack({ 393,0,99,145 });
	orangeLaser.PushBack({ 393,0,0,0 });
	orangeLaser.PushBack({ 393,0,99,145 });
	orangeLaser.PushBack({ 393,0,0,0 });
	orangeLaser.PushBack({ 312,0,81,145 });
	orangeLaser.PushBack({ 312,0,0,0 });
	orangeLaser.PushBack({ 312,0,81,145 });
	orangeLaser.PushBack({ 312,0,0,0 });
	orangeLaser.PushBack({ 247,0,65,144 });
	orangeLaser.PushBack({ 247,0,0,0 });
	orangeLaser.PushBack({ 247,0,65,144 });
	orangeLaser.PushBack({ 247,0,0,0 });
	orangeLaser.PushBack({ 195,0,52,145 });
	orangeLaser.PushBack({ 195,0,0,0 });
	orangeLaser.PushBack({ 195,0,52,145 });
	orangeLaser.PushBack({ 195,0,0,0 });
	orangeLaser.PushBack({ 157,0,38,145 });
	orangeLaser.PushBack({ 157,0,0,0 }); 
	//mid to left - flipped
	orangeLaser.PushBack({ 132,0,-25,144 });
	orangeLaser.PushBack({ 132,0,0,0 }); //flash
	orangeLaser.PushBack({ 157,0,-38,145 });
	orangeLaser.PushBack({ 157,0,0,0 });
	orangeLaser.PushBack({ 195,0,-52,145 });
	orangeLaser.PushBack({ 195,0,0,0 });
	orangeLaser.PushBack({ 247,0,-65,144 });
	orangeLaser.PushBack({ 247,0,0,0 });
	orangeLaser.PushBack({ 247,0,-65,144 });
	orangeLaser.PushBack({ 247,0,0,0 });
	orangeLaser.PushBack({ 312,0,-81,145 });
	orangeLaser.PushBack({ 312,0,0,0 });
	orangeLaser.PushBack({ 312,0,-81,145 });
	orangeLaser.PushBack({ 312,0,0,0 });
	orangeLaser.PushBack({ 312,0,-81,145 });
	orangeLaser.PushBack({ 312,0,0,0 });
	orangeLaser.PushBack({ 393,0,-99,145 });
	orangeLaser.PushBack({ 393,0,0,0 });
	orangeLaser.PushBack({ 393,0,-99,145 });
	orangeLaser.PushBack({ 393,0,0,0 });
	orangeLaser.PushBack({ 393,0,-99,145 });
	orangeLaser.PushBack({ 393,0,0,0 });
	orangeLaser.PushBack({ 0,145,-121,144 });
	orangeLaser.PushBack({ 0,145,0,0 });
	orangeLaser.PushBack({ 0,145,-121,144 });
	orangeLaser.PushBack({ 0,145,0,0 });
	orangeLaser.PushBack({ 0,145,-121,144 });
	orangeLaser.PushBack({ 0,145,0,0 });
	orangeLaser.PushBack({ 121,145,-142,142 });
	orangeLaser.PushBack({ 121,145,0,0 });
	orangeLaser.PushBack({ 121,145,-142,142 });
	orangeLaser.PushBack({ 121,145,0,0 });
	orangeLaser.PushBack({ 121,145,-142,142 });
	orangeLaser.PushBack({ 121,145,0,0 });
	orangeLaser.PushBack({ 121,145,-142,142 });
	orangeLaser.PushBack({ 121,145,0,0 });
	orangeLaser.PushBack({ 0,145,-121,144 });
	orangeLaser.PushBack({ 0,145,0,0 });
	orangeLaser.PushBack({ 0,145,-121,144 });
	orangeLaser.PushBack({ 0,145,0,0 });
	orangeLaser.PushBack({ 0,145,-121,144 });
	orangeLaser.PushBack({ 0,145,0,0 });
	orangeLaser.PushBack({ 0,145,-121,144 });
	orangeLaser.PushBack({ 0,145,0,0 });
	orangeLaser.PushBack({ 393,0,-99,145 });
	orangeLaser.PushBack({ 393,0,0,0 });
	orangeLaser.PushBack({ 393,0,-99,145 });
	orangeLaser.PushBack({ 393,0,0,0 });
	orangeLaser.PushBack({ 393,0,-99,145 });
	orangeLaser.PushBack({ 393,0,0,0 });
	orangeLaser.PushBack({ 312,0,-81,145 });
	orangeLaser.PushBack({ 312,0,0,0 });
	orangeLaser.PushBack({ 312,0,-81,145 });
	orangeLaser.PushBack({ 312,0,0,0 });
	orangeLaser.PushBack({ 247,0,-65,144 });
	orangeLaser.PushBack({ 247,0,0,0 });
	orangeLaser.PushBack({ 247,0,-65,144 });
	orangeLaser.PushBack({ 247,0,0,0 });
	orangeLaser.PushBack({ 195,0,-52,145 });
	orangeLaser.PushBack({ 195,0,0,0 });
	orangeLaser.PushBack({ 195,0,-52,145 });
	orangeLaser.PushBack({ 195,0,0,0 });
	orangeLaser.PushBack({ 157,0,-38,145 });
	orangeLaser.PushBack({ 157,0,0,0 });
	
	orangeLaser.speed = 1.0f;

	//midground lights rect1
	midgroundLights[0].PushBack({1,1,96,86});
	midgroundLights[0].PushBack({ 98,1,96,86 });
	midgroundLights[0].PushBack({ 195,1,96,86 });
	midgroundLights[0].PushBack({ 292,1,96,86 });
	midgroundLights[0].PushBack({ 389,1,96,86 });
	midgroundLights[0].PushBack({ 1,88,96,86 });
	midgroundLights[0].PushBack({ 1,1,96,86 });
	midgroundLights[0].PushBack({ 98,88,96,86 });
	midgroundLights[0].speed = 0.143f;

	//midground lights rect2
	midgroundLights[1].PushBack({ 195,114,37,61 });
	midgroundLights[1].PushBack({ 233,114,37,61 });
	midgroundLights[1].PushBack({ 271,114,37,61 });
	midgroundLights[1].PushBack({ 309,114,37,61 });
	midgroundLights[1].PushBack({ 347,114,37,61 });
	midgroundLights[1].PushBack({ 385, 114,37,61 });
	midgroundLights[1].PushBack({ 195,114,37,61 });
	midgroundLights[1].PushBack({ 423,114,37,61 });
	midgroundLights[1].speed = 0.143f;

	//midground lights rect3
	midgroundLights[2].PushBack({ 1,175, 108,47 });
	midgroundLights[2].PushBack({ 110,175,108,47 });
	midgroundLights[2].PushBack({ 219,175,108,47 });
	midgroundLights[2].PushBack({ 328,175,108,47 });
	midgroundLights[2].PushBack({ 1,223,108,47 });
	midgroundLights[2].PushBack({ 110, 223,108,47 });
	midgroundLights[2].PushBack({ 1,175, 108,47 });
	midgroundLights[2].PushBack({ 219,223,108,47 });
	midgroundLights[2].speed = 0.143f;

	//midground lights rect4
	midgroundLights[3].PushBack({ 1,271,15,12 });
	midgroundLights[3].PushBack({ 17,271,15,12 });
	midgroundLights[3].PushBack({ 33,271,15,12 });
	midgroundLights[3].PushBack({ 49,271,15,12 });
	midgroundLights[3].PushBack({ 65,271,15,12 });
	midgroundLights[3].PushBack({ 81,271,15,12 });
	midgroundLights[3].PushBack({ 1,271,15,12 });
	midgroundLights[3].PushBack({ 97,271,15,12 });
	midgroundLights[3].speed = 0.143f;

	//midground lights rect5
	midgroundLights[4].PushBack({ 1,284,48,93 });
	midgroundLights[4].PushBack({ 50,284,48,93 });
	midgroundLights[4].PushBack({ 99,284,48,93 });
	midgroundLights[4].PushBack({ 148,284,48,93 });
	midgroundLights[4].PushBack({ 197,284,48,93 });
	midgroundLights[4].PushBack({ 246,284,48,93 });
	midgroundLights[4].PushBack({ 1,284,48,93 });
	midgroundLights[4].PushBack({ 295,284,48,93 });
	midgroundLights[4].speed = 0.143f;

	//midground lights rect6
	midgroundLights[5].PushBack({ 1,378,61,77 });
	midgroundLights[5].PushBack({ 63,378,61,77 });
	midgroundLights[5].PushBack({ 125,378,61,77 });
	midgroundLights[5].PushBack({ 187,378,61,77 });
	midgroundLights[5].PushBack({ 249,378,61,77 });
	midgroundLights[5].PushBack({ 311,378,61,77 });
	midgroundLights[5].PushBack({ 1,378,61,77 });
	midgroundLights[5].PushBack({ 373,378,61,77 });
	midgroundLights[5].speed = 0.143f;

	//enemy langostas background
	for (int i = 0; i < MAX_BG_SHIPS; ++i) //20 is the index of the animations array, if you need more, increment it in .h
	{
		basicEnemyBgAnim[i].PushBack({ 0, 0, 9, 4 });
		basicEnemyBgAnim[i].PushBack({ 15, 0, 9, 4 });
		basicEnemyBgAnim[i].PushBack({ 30, 0, 9, 4 });
		basicEnemyBgAnim[i].PushBack({ 45, 0, 9, 4 });
		basicEnemyBgAnim[i].PushBack({ 60, 0, 9, 4 });
		basicEnemyBgAnim[i].PushBack({ 75, 0, 9, 4 });
		basicEnemyBgAnim[i].speed = 0.25f;
	}

}

ModuleSceneLvl1::~ModuleSceneLvl1()
{}

bool ModuleSceneLvl1::Init()
{

	//cameraSpeed = 0.5f * SCREEN_SIZE;

	bgMovY.maxLoops = 12; //13 is to go to mid pos
	bgMovY.currentLoops = 1;

	updatePos = true;
	bgMovY.mg_y = 32; //midground y coordinate value = maxPixelOnTexture(mg) + spawnPointFirstBuildingOnGame

	//speeds for up and down moves
	bgMovY.speedMg = 0.23f;// 0.18
	bgMovY.speedfg = 0.5f;//0.41

	bgMovY.fgTemp = 0; //defines correct temp values foreground y (stores the floating increment to further cast int)
	bgMovY.mgTemp = bgMovY.mg_y;//defines correct temp values midground y

	bgMovY.fgTargetDown = 16; //target position of foreground texture max/up y value
	bgMovY.fgTargetUp = -15;
	bgMovY.fgMidPosition = 0;

	bgMovY.mgTargetDown = 40;
	bgMovY.mgTargetUp = 25;
	bgMovY.mgMidPosition = 32;

	bgMovY.distanceWaitToMov = -91;// *SCREEN_SIZE; //distance between activate movements

	scrollX = true; //activates x scroll

	return true;
}

// Load assets
bool ModuleSceneLvl1::Start()
{

	LOG("Loading background assets");
	bool ret = true;

	//enable modules --------------
	App->player->Enable();
	//App->player2->Enable();
	//App->playerUnit->Enable();
	App->particles->Enable();
	App->collision->Enable();
	App->modulePowerUp->Enable();
	App->enemies->Enable();
	//changes the state of the UI
	App->moduleUI->UI = gameplay_state::SCENE;

	//enemy definitions -------------------------------------------------------------------------------
	App->enemies->AddEnemy(ENEMY_TYPES::BASIC_ENEMY, 555, 72 ,NONE);
	App->enemies->AddEnemy(ENEMY_TYPES::BASIC_ENEMY, 585, 90, NONE);
	App->enemies->AddEnemy(ENEMY_TYPES::BASIC_ENEMY, 615, 72, NONE);
	App->enemies->AddEnemy(ENEMY_TYPES::BASIC_ENEMY, 615, 138, NONE); //no powerup
	App->enemies->AddEnemy(ENEMY_TYPES::BASIC_ENEMY, 655, 31, NONE);
	App->enemies->AddEnemy(ENEMY_TYPES::BASIC_ENEMY, 670, 138, NONE);
	App->enemies->AddEnemy(ENEMY_TYPES::BASIC_ENEMY, 685, 31, NONE);
	App->enemies->AddEnemy(ENEMY_TYPES::BASIC_ENEMY, 715, 31, NONE);
	App->enemies->AddEnemy(ENEMY_TYPES::BASIC_ENEMY, 745, 31, NONE);
	App->enemies->AddEnemy(ENEMY_TYPES::BASIC_ENEMY, 775, 31, LASER);//10 - L
	App->enemies->AddEnemy(ENEMY_TYPES::BASIC_ENEMY, 800, 164, NONE);
	App->enemies->AddEnemy(ENEMY_TYPES::BASIC_ENEMY, 830, 164, NONE);
	App->enemies->AddEnemy(ENEMY_TYPES::BASIC_ENEMY, 860, 164, NONE);
	App->enemies->AddEnemy(ENEMY_TYPES::BASIC_ENEMY, 890, 164, NONE);
	App->enemies->AddEnemy(ENEMY_TYPES::BASIC_ENEMY, 920, 164, BOOST);//15 - S
	App->enemies->AddEnemy(ENEMY_TYPES::BASIC_ENEMY, 929, 115, NONE);
	App->enemies->AddEnemy(ENEMY_TYPES::BASIC_ENEMY, 957, 131, NONE);
	App->enemies->AddEnemy(ENEMY_TYPES::BASIC_ENEMY, 958, 60, NONE);
	App->enemies->AddEnemy(ENEMY_TYPES::BASIC_ENEMY, 984, 114, NONE);
	App->enemies->AddEnemy(ENEMY_TYPES::BASIC_ENEMY, 986, 75, NONE);
	App->enemies->AddEnemy(ENEMY_TYPES::BASIC_ENEMY, 1013, 59, NONE);
	App->enemies->AddEnemy(ENEMY_TYPES::BASIC_ENEMY, 1041, 74, NONE);
	App->enemies->AddEnemy(ENEMY_TYPES::BASIC_ENEMY, 1110, 52, NONE);
	App->enemies->AddEnemy(ENEMY_TYPES::BASIC_ENEMY, 1113, 162, NONE);
	App->enemies->AddEnemy(ENEMY_TYPES::BASIC_ENEMY, 1135, 52, NONE);
	App->enemies->AddEnemy(ENEMY_TYPES::BASIC_ENEMY, 1138, 162, NONE);
	App->enemies->AddEnemy(ENEMY_TYPES::BASIC_ENEMY, 1160, 52, NONE);
	App->enemies->AddEnemy(ENEMY_TYPES::BASIC_ENEMY, 1163, 162, NONE);
	App->enemies->AddEnemy(ENEMY_TYPES::BASIC_ENEMY, 1185, 52, NONE);
	App->enemies->AddEnemy(ENEMY_TYPES::BASIC_ENEMY, 1188, 162, NONE);
	App->enemies->AddEnemy(ENEMY_TYPES::BASIC_ENEMY, 1210, 52, MISSILES);//31 - H
	App->enemies->AddEnemy(ENEMY_TYPES::BASIC_ENEMY, 1213, 162, LASER);//32 - L
	//little pause during middle boss 
	App->enemies->AddEnemy(ENEMY_TYPES::BASIC_ENEMY, 2200, 40, NONE);
	App->enemies->AddEnemy(ENEMY_TYPES::BASIC_ENEMY, 2228, 72, NONE);
	App->enemies->AddEnemy(ENEMY_TYPES::BASIC_ENEMY, 2256, 104, NONE);
	App->enemies->AddEnemy(ENEMY_TYPES::BASIC_ENEMY, 2284, 136, NONE);
	App->enemies->AddEnemy(ENEMY_TYPES::BASIC_ENEMY, 2312, 168, NONE);
	App->enemies->AddEnemy(ENEMY_TYPES::BASIC_ENEMY, 2337, 168, NONE);
	App->enemies->AddEnemy(ENEMY_TYPES::BASIC_ENEMY, 2362, 168, NONE);
	App->enemies->AddEnemy(ENEMY_TYPES::BASIC_ENEMY, 2387, 168, NONE);
	App->enemies->AddEnemy(ENEMY_TYPES::BASIC_ENEMY, 2412, 168, BOOST); //41 - S
	//little pause during oscillers
	App->enemies->AddEnemy(ENEMY_TYPES::BASIC_ENEMY, 3400, 103, NONE);
	App->enemies->AddEnemy(ENEMY_TYPES::BASIC_ENEMY, 3425, 55, NONE);
	App->enemies->AddEnemy(ENEMY_TYPES::BASIC_ENEMY, 3427, 95, NONE);
	App->enemies->AddEnemy(ENEMY_TYPES::BASIC_ENEMY, 3429, 152, NONE);
	App->enemies->AddEnemy(ENEMY_TYPES::BASIC_ENEMY, 3453, 64, NONE);
	App->enemies->AddEnemy(ENEMY_TYPES::BASIC_ENEMY, 3455, 104, NONE);
	App->enemies->AddEnemy(ENEMY_TYPES::BASIC_ENEMY, 3457, 144, NONE);
	App->enemies->AddEnemy(ENEMY_TYPES::BASIC_ENEMY, 3482, 56, NONE);
	App->enemies->AddEnemy(ENEMY_TYPES::BASIC_ENEMY, 3485, 152, NONE);
	//little pause
	App->enemies->AddEnemy(ENEMY_TYPES::BASIC_ENEMY, 3735, 160, NONE);
	App->enemies->AddEnemy(ENEMY_TYPES::BASIC_ENEMY, 3763, 128, NONE);
	App->enemies->AddEnemy(ENEMY_TYPES::BASIC_ENEMY, 3791, 96, NONE);
	App->enemies->AddEnemy(ENEMY_TYPES::BASIC_ENEMY, 3819, 64, NONE);
	App->enemies->AddEnemy(ENEMY_TYPES::BASIC_ENEMY, 3844, 64, NONE);
	App->enemies->AddEnemy(ENEMY_TYPES::BASIC_ENEMY, 3869, 64, NONE);
	App->enemies->AddEnemy(ENEMY_TYPES::BASIC_ENEMY, 3894, 64, NONE);
	App->enemies->AddEnemy(ENEMY_TYPES::BASIC_ENEMY, 3919, 64, NONE);
	App->enemies->AddEnemy(ENEMY_TYPES::BASIC_ENEMY, 3944, 64, BOOST); //59 - S
	//tunel pause
	App->enemies->AddEnemy(ENEMY_TYPES::BASIC_ENEMY, 8150, 105, NONE);
	App->enemies->AddEnemy(ENEMY_TYPES::BASIC_ENEMY, 8178, 54, NONE);
	App->enemies->AddEnemy(ENEMY_TYPES::BASIC_ENEMY, 8205, 121, NONE);
	App->enemies->AddEnemy(ENEMY_TYPES::BASIC_ENEMY, 8233, 65, NONE);
	App->enemies->AddEnemy(ENEMY_TYPES::BASIC_ENEMY, 8288, 105, NONE);
	App->enemies->AddEnemy(ENEMY_TYPES::BASIC_ENEMY, 8313, 105, NONE);
	App->enemies->AddEnemy(ENEMY_TYPES::BASIC_ENEMY, 8338, 105, NONE);
	App->enemies->AddEnemy(ENEMY_TYPES::BASIC_ENEMY, 8341, 177, NONE);
	App->enemies->AddEnemy(ENEMY_TYPES::BASIC_ENEMY, 8363, 105, NONE);
	App->enemies->AddEnemy(ENEMY_TYPES::BASIC_ENEMY, 8367, 153, NONE);
	App->enemies->AddEnemy(ENEMY_TYPES::BASIC_ENEMY, 8374, 41, NONE);
	App->enemies->AddEnemy(ENEMY_TYPES::BASIC_ENEMY, 8388, 105, NONE);
	App->enemies->AddEnemy(ENEMY_TYPES::BASIC_ENEMY, 8401, 163, NONE);
	//little pause
	App->enemies->AddEnemy(ENEMY_TYPES::BASIC_ENEMY, 9100, 40, NONE);
	App->enemies->AddEnemy(ENEMY_TYPES::BASIC_ENEMY, 9128, 72, NONE);
	App->enemies->AddEnemy(ENEMY_TYPES::BASIC_ENEMY, 9156, 104, NONE);
	App->enemies->AddEnemy(ENEMY_TYPES::BASIC_ENEMY, 9184, 136, NONE);
	App->enemies->AddEnemy(ENEMY_TYPES::BASIC_ENEMY, 9211, 168, NONE);
	App->enemies->AddEnemy(ENEMY_TYPES::BASIC_ENEMY, 9238, 168, NONE);
	App->enemies->AddEnemy(ENEMY_TYPES::BASIC_ENEMY, 9265, 168, NONE);
	App->enemies->AddEnemy(ENEMY_TYPES::BASIC_ENEMY, 9292, 168, NONE);
	App->enemies->AddEnemy(ENEMY_TYPES::BASIC_ENEMY, 9319, 168, BOMBS); //last - G

	//Enemy Oscilatory ----------------------------------------------------
	//First Wave
	App->enemies->AddEnemy(ENEMY_TYPES::ENEMYOSCILATORY, 2550, 90, NONE);
	App->enemies->AddEnemy(ENEMY_TYPES::ENEMYOSCILATORY, 2600, 90, NONE);
	App->enemies->AddEnemy(ENEMY_TYPES::ENEMYOSCILATORY, 2650, 90, NONE);
	App->enemies->AddEnemy(ENEMY_TYPES::ENEMYOSCILATORY, 2700, 90, NONE);
	App->enemies->AddEnemy(ENEMY_TYPES::ENEMYOSCILATORY, 2750, 90, NONE);
	App->enemies->AddEnemy(ENEMY_TYPES::ENEMYOSCILATORY, 2800, 90, NONE);
	App->enemies->AddEnemy(ENEMY_TYPES::ENEMYOSCILATORY, 2850, 90, NONE);
	App->enemies->AddEnemy(ENEMY_TYPES::ENEMYOSCILATORY, 2900, 90, NONE);
	App->enemies->AddEnemy(ENEMY_TYPES::ENEMYOSCILATORY, 2950, 90, NONE);
	App->enemies->AddEnemy(ENEMY_TYPES::ENEMYOSCILATORY, 3000, 90, NONE);
	App->enemies->AddEnemy(ENEMY_TYPES::ENEMYOSCILATORY, 3050, 90, NONE);

	//Second Wave
	App->enemies->AddEnemy(ENEMY_TYPES::ENEMYOSCILATORY, 5750, 90, NONE);
	App->enemies->AddEnemy(ENEMY_TYPES::ENEMYOSCILATORY, 5800, 90, NONE);
	App->enemies->AddEnemy(ENEMY_TYPES::ENEMYOSCILATORY, 5850, 120, NONE);
	App->enemies->AddEnemy(ENEMY_TYPES::ENEMYOSCILATORY, 5900, 120, NONE);
	App->enemies->AddEnemy(ENEMY_TYPES::ENEMYOSCILATORY, 5950, 120, NONE);
	App->enemies->AddEnemy(ENEMY_TYPES::ENEMYOSCILATORY, 6000, 120, NONE);
	App->enemies->AddEnemy(ENEMY_TYPES::ENEMYOSCILATORY, 6050, 120, NONE);

	//Third Wave
	App->enemies->AddEnemy(ENEMY_TYPES::ENEMYOSCILATORY, 6200, 65, NONE);
	App->enemies->AddEnemy(ENEMY_TYPES::ENEMYOSCILATORY, 6299, 65, NONE);
	App->enemies->AddEnemy(ENEMY_TYPES::ENEMYOSCILATORY, 6398, 65, NONE);
	App->enemies->AddEnemy(ENEMY_TYPES::ENEMYOSCILATORY, 6497, 65, NONE);

	//Tank
	/*//App->enemies->AddEnemy(ENEMY_TYPES::TANK, 6100, 150, NONE, App->enemies->enemyTankTexture);
	App->enemies->AddEnemy(ENEMY_TYPES::BIG_TURRET, 6200, 146, NONE, App->enemies->enemyTankTexture);
	App->enemies->AddEnemy(ENEMY_TYPES::SMALL_TURRET, 6270, 152, NONE, App->enemies->enemyTankTexture);
	//App->enemies->AddEnemy(ENEMY_TYPES::TANK, 400, 150, NONE, App->enemies->enemyTankTexture);
	App->enemies->AddEnemy(ENEMY_TYPES::BIG_TURRET, 500, 146, NONE, App->enemies->enemyTankTexture);
	App->enemies->AddEnemy(ENEMY_TYPES::SMALL_TURRET, 570, 152, NONE, App->enemies->enemyTankTexture);*/
	
	//BEE's, very alpha
	App->enemies->AddEnemy(ENEMY_TYPES::ENEMYBEE, 5000, 70, NONE);
	App->enemies->AddEnemy(ENEMY_TYPES::ENEMYBEE, 5500, 30, NONE);
	App->enemies->AddEnemy(ENEMY_TYPES::ENEMYBEE, 4900, 60, NONE);
	App->enemies->AddEnemy(ENEMY_TYPES::ENEMYBEE, 5200, 70, NONE);
	App->enemies->AddEnemy(ENEMY_TYPES::ENEMYBEE, 6000, 100, NONE);
	App->enemies->AddEnemy(ENEMY_TYPES::ENEMYBEE, 4798, 90, NONE);

	//lvl1 background textures --------------------------------------------------------------------------------
	bg = App->textures->Load("assets/Graphics/Backgrounds/Lvl_1/lvl1_bg.png");
	mg = App->textures->Load("assets/Graphics/Backgrounds/Lvl_1/lvl1_mg.png");
	fg = App->textures->Load("assets/Graphics/Backgrounds/Lvl_1/lvl1_fg.png");
	boss = App->textures->Load("assets/Graphics/Backgrounds/Lvl_1/lvl1_boss.png");
	roadLights = App->textures->Load("assets/Graphics/Backgrounds/Lvl_1/lvl1_streetLightsAndSpots.png");
	tunelLights = App->textures->Load("assets/Graphics/Backgrounds/Lvl_1/tunnelLights.png");
	bgLights = App->textures->Load("assets/Graphics/Backgrounds/Lvl_1/bg_lights.png");
	midgroundLightsTexture = App->textures->Load("assets/Graphics/Backgrounds/Lvl_1/midgroundLights.png");
	buildingLasersTexture = App->textures->Load("assets/Graphics/Backgrounds/Lvl_1/lvl1_buildingLasers.png");
	//Enemy ships langostas texture
	basicEnemyBgTexture = App->textures->Load("assets/Graphics/Backgrounds/Lvl_1/bgShips.png");

	//loading music and fx -------------------------------------------------------------------------------------
	App->audio->LoadAudio("assets/Audio/Music/song_level_1.ogg", "song_lvl1", MUSIC);
	App->audio->ControlAudio("song_lvl1", MUSIC, FADEIN, -1, 1500.0f); //type, playMode, loops, fadeIn, fadeOut

	// ----------------------------

	//assign or reassign currentCameraPosX to camera.x, restart lvl at init position
	App->render->currentCameraPosX = 0; //App->render->camera.x;

	//assign scene ground move positions to start position ------
	bgMovY.currentLoops = 1;
	bgMovY.mg_y = 32; //midground y coordinate value = maxPixelOnTexture(mg) + spawnPointFirstBuildingOnGame
	bgMovY.fg_y = 0;
	bgMovY.fgTemp = 0; //defines correct temp values foreground y (stores the floating increment to further cast int)
	bgMovY.mgTemp = bgMovY.mg_y;//defines correct temp values midground y
	bgMovY.lastMovPosX = 0; //App->render->currentCameraPosX; //returns lastMovPosX to correct value
	
	//correct bools to start level conditions (no checkpoints contempled on this workaround)--------------------
	bgMovY.up = true; //on first level the first move is down
	bgMovY.down = false;
	bgMovY.fgRendezvous = false;
	bgMovY.mgRendezvous = false;
	//events
	bgMovY.move = false;
	bgMovY.moveUp = false;
	bgMovY.moveDown = false;
	bgMovY.lastLoop = false;
	//checker condition
	updatePos = true;
	//scroll true, if the game played before arrives at boss lvl1, next start -> scroll
	scrollX = true;

	//-----------------------------------------------------------------------------------------------------------

	foregroundSpeed = 0.5f;
	midgroundSpeed = 0.25f;
	backgroundSpeed = 0.125f;

	return ret;

}

update_status ModuleSceneLvl1::PreUpdate()
{

	if (App->render->currentCameraPosX <= -4408)
	{
		scrollX = false;
		App->fade->FadeToBlack(this, (Module*)App->winScreen);
	}

	//check if scroll
	if (scrollX)
	{
		//move player position to follow the camera movement
		App->player->position.x += 1;
		//App->player2->position.x += 1;
		//camera speed relative to its size
		App->render->camera.x -= 1 * SCREEN_SIZE;
		//returns original pixel position x values foreground
		App->render->currentCameraPosX = (App->render->camera.x / SCREEN_SIZE) * foregroundSpeed;

		//debugValue = - App->render->camera.x / SCREEN_SIZE;

	}

	//-------------------background up and down movement -------------------------------
	//distance activation checker

	if ((App->render->currentCameraPosX - bgMovY.lastMovPosX <= bgMovY.distanceWaitToMov) && updatePos &&
		bgMovY.currentLoops <= bgMovY.maxLoops)
	{
		bgMovY.lastMovPosX = App->render->currentCameraPosX;
		updatePos = false;
		bgMovY.move = true;

		++bgMovY.currentLoops;
		if (bgMovY.currentLoops >= bgMovY.maxLoops)
			bgMovY.lastLoop = true;
	}

	if (bgMovY.move) //movement logic
	{

		if (bgMovY.up)
		{
			bgMovY.down = false; //updates the next move bool
			bgMovY.moveUp = true; //activates the update camera position
			bgMovY.up = false;

		}
		if (bgMovY.down)
		{

			bgMovY.up = false;
			bgMovY.moveDown = true;
			bgMovY.down = false;
		}
	}

	//updates sprite position
	if (bgMovY.moveUp)
	{
		if (!bgMovY.fgRendezvous)
		{
			bgMovY.fgTemp -= bgMovY.speedfg;
			bgMovY.fg_y = (int)bgMovY.fgTemp;
		}
		if (bgMovY.fg_y <= bgMovY.fgTargetUp) //check if foreground reach the target position
		{
			bgMovY.fgRendezvous = true;
		}
		if (!bgMovY.mgRendezvous)
		{
			bgMovY.mgTemp -= bgMovY.speedMg; //midground speed
			bgMovY.mg_y = (int)bgMovY.mgTemp;
		}
		if (bgMovY.mg_y <= bgMovY.mgTargetUp)
		{
			bgMovY.mgRendezvous = true;
		}

		if (bgMovY.fgRendezvous && bgMovY.mgRendezvous)
		{
			bgMovY.lastMovPosX = App->render->currentCameraPosX;//App->render->camera.x; //updates the last x positiond
			updatePos = true;
			bgMovY.down = true; //and the next mov will be down
			bgMovY.move = false;
			bgMovY.moveUp = false;

			bgMovY.fgRendezvous = false; //prepare for next call, no rendezvous
			bgMovY.mgRendezvous = false;
		}
	}

	if (bgMovY.moveDown)
	{
		if (!bgMovY.fgRendezvous)
		{
			bgMovY.fgTemp += bgMovY.speedfg;
			bgMovY.fg_y = (int)bgMovY.fgTemp;
		}
		if (bgMovY.fg_y >= bgMovY.fgTargetDown) //check if foreground reach the target position
		{
			bgMovY.fgRendezvous = true;
		}
		if (!bgMovY.mgRendezvous)
		{
			bgMovY.mgTemp += bgMovY.speedMg; //midground speed
			bgMovY.mg_y = (int)bgMovY.mgTemp;
		}
		if (bgMovY.mg_y >= bgMovY.mgTargetDown)
		{
			bgMovY.mgRendezvous = true;
		}

		if (bgMovY.fgRendezvous && bgMovY.mgRendezvous) //when midground and foreground reaches its target...
		{
			bgMovY.lastMovPosX = App->render->currentCameraPosX;//App->render->camera.x; //updates the last x position
			updatePos = true;
			bgMovY.up = true; //and the next mov will be down
			bgMovY.move = false;
			bgMovY.moveDown = false;

			bgMovY.fgRendezvous = false; //cleanup before next call
			bgMovY.mgRendezvous = false;
		}

	}

	//last loop = before tunnel position
	if (bgMovY.lastLoop && (App->render->currentCameraPosX - bgMovY.lastMovPosX <= bgMovY.distanceWaitToMov))//!bgMovY.move) //lastLoop in this specific case, always occurrs when we go up
	{			//foreground move
		if (!bgMovY.fgRendezvous)
		{
			bgMovY.fgTemp -= bgMovY.speedfg;
			bgMovY.fg_y = (int)bgMovY.fgTemp;			
		}
		if (bgMovY.fg_y <= 0) // 0= midposition
		{
			bgMovY.fgRendezvous = true;
			bgMovY.lastLoop = false;
		}
		//midground move //ON THE ORIGINAL GAME, the midground is stuck before tunnel lastTravel (don't move)
		/*if (!bgMovY.mgRendezvous)
		{
		bgMovY.mgTemp -= bgMovY.speedMg;
		bgMovY.mg_y = (int)bgMovY.mgTemp;
		}
		if (bgMovY.mg_y <= 32) // 32 = midground start level y coord.
		{
		bgMovY.mgRendezvous = true;
		}*/

	}

	return UPDATE_CONTINUE;

	//----------------------------------------------------------------------------------------------------
}

// Update: draw background
update_status ModuleSceneLvl1::Update()
{
	/*if (App->input->keyboard[SDL_SCANCODE_Q] == KEY_STATE::KEY_DOWN)
	{
		spawn = true;
	}
	if (spawn == true)
	{
		App->player2->Enable();
		spawn = false;
	}*/
	// Draw everything --------------------------------------
	
	App->render->Blit(bg, 0, 0, &bgRect, backgroundSpeed); //bg1 last resort----------------------
	
	//background draw -------------------------------------------------------------------------

	//only repeats twice (on two occasions), we don't need to create and array of patterns etc...
	//the reason to multiply for 4 the screen size is because we pass a parameter speed 4times little
	//foreground pass a parallax speed of 1.0, background 0.25

	//background building 1 - 3 texture lights ------------------------------------------------

	if (App->render->currentCameraPosX >= -146 * 4) //while the desired target is not seen
	{
		App->render->Blit(bgLights, -8, 0, &(backgroundLights[0].GetCurrentFrame()), backgroundSpeed);
		App->render->Blit(bgLights, 122, 10, &(backgroundLights[1].GetCurrentFrame()), backgroundSpeed);
		App->render->Blit(bgLights, 88, 50, &(backgroundLights[2].GetCurrentFrame()), backgroundSpeed);
		
	}
	else
	{
		App->render->Blit(bgLights, 504, 0, &(backgroundLights[0].GetCurrentFrame()), backgroundSpeed);
		App->render->Blit(bgLights, 634, 10, &(backgroundLights[1].GetCurrentFrame()), backgroundSpeed);
		App->render->Blit(bgLights, 600, 50, &(backgroundLights[2].GetCurrentFrame()), backgroundSpeed);
	}

	//background building 2 - 2 textures
	//texture 1

	if (App->render->currentCameraPosX >= -300 * 4)
	{
		App->render->Blit(bgLights, 169, 0, &(backgroundLights[3].GetCurrentFrame()), backgroundSpeed);
		
	}
	else
	{
		App->render->Blit(bgLights, 682, 0, &(backgroundLights[3].GetCurrentFrame()), backgroundSpeed);
	}

	//texture 2

	App->render->Blit(bgLights, 240, 32, &(backgroundLights[4].GetCurrentFrame()), backgroundSpeed);

	//only one (building "3") - 1 texture
	App->render->Blit(bgLights, 321, 0, &(backgroundLights[5].GetCurrentFrame()), backgroundSpeed);

	//------------------------------------------------------------------------------------------

	//orange laser

	Animation* current_animation = &orangeLaser;
	SDL_Rect r = current_animation->GetCurrentFrame();
	App->render->Blit(buildingLasersTexture, 334 - pivotArrayOrangeLaser[(int)current_animation->current_frame] + 1, 0, &r, backgroundSpeed);

	//Enemy ships langostas Background ----------------------------------------------------------------
	for (int i = 0; i < MAX_BG_SHIPS; ++i)
	{
		App->render->Blit(basicEnemyBgTexture, basicEnemyBgPositionsX[i], basicEnemyBgPositionsY[i], &(basicEnemyBgAnim[i].GetCurrentFrame()), -1.0f);
	}
	// ------------------------------------------------------------------------------------------------

	//boss

	if (App->render->currentCameraPosX <= -3824) //desired target pixels
		App->render->Blit(boss, 0, 0, NULL, 0.0f);

	//midground and foreground layer -----------------------------------------------------------
	//blue lasers
	for (int i = 0; i < BLUE_LASERS; ++i)
	{
		Animation* current_animation = &buildingLasers[i];
		SDL_Rect r = current_animation->GetCurrentFrame();
		App->render->Blit(buildingLasersTexture, positionArrayBlueLasersX[i] - pivotArrayBlueLasersPosition[(int)current_animation->current_frame] + 1, bgMovY.mg_y + positionArrayBlueLasersY[i] - r.h, &r, midgroundSpeed);
	}

	App->render->Blit(mg, 0, bgMovY.mg_y, &mgRect, midgroundSpeed); //midground lvl1 last resort -----
	
	//midground lights -------------------------------------- from top texture midgroundTexture + initial height
	if (App->render->currentCameraPosX >= -246 * 2)
	{
		App->render->Blit(midgroundLightsTexture, 40, bgMovY.mg_y + 28, &(midgroundLights[0].GetCurrentFrame()), midgroundSpeed);
		App->render->Blit(midgroundLightsTexture, 184, bgMovY.mg_y + 18, &(midgroundLights[1].GetCurrentFrame()), midgroundSpeed);
	}
	else if (App->render->currentCameraPosX >= -749 * 2) //while the desired target is not seen
	{
	App->render->Blit(midgroundLightsTexture, 552, bgMovY.mg_y + 28, &(midgroundLights[0].GetCurrentFrame()), midgroundSpeed);
	App->render->Blit(midgroundLightsTexture, 696, bgMovY.mg_y + 18, &(midgroundLights[1].GetCurrentFrame()), midgroundSpeed);
	}
	else
	{
		App->render->Blit(midgroundLightsTexture, 1064, bgMovY.mg_y + 28, &(midgroundLights[0].GetCurrentFrame()), midgroundSpeed);
	}

	//-------------

	if (App->render->currentCameraPosX >= -440 * 2) //while the desired target is not seen
	{
		App->render->Blit(midgroundLightsTexture, 234, bgMovY.mg_y + 97, &(midgroundLights[2].GetCurrentFrame()), midgroundSpeed);
		App->render->Blit(midgroundLightsTexture, 329, bgMovY.mg_y + 2, &(midgroundLights[3].GetCurrentFrame()), midgroundSpeed);
		App->render->Blit(midgroundLightsTexture, 392, bgMovY.mg_y + 50, &(midgroundLights[4].GetCurrentFrame()), midgroundSpeed);
		
	}
	else
	{
		App->render->Blit(midgroundLightsTexture, 746, bgMovY.mg_y + 97, &(midgroundLights[2].GetCurrentFrame()), midgroundSpeed);
		App->render->Blit(midgroundLightsTexture, 841, bgMovY.mg_y + 2, &(midgroundLights[3].GetCurrentFrame()), midgroundSpeed);
		App->render->Blit(midgroundLightsTexture, 904, bgMovY.mg_y + 50, &(midgroundLights[4].GetCurrentFrame()), midgroundSpeed);
	}

	//-------------
	
	if (App->render->currentCameraPosX >= -540 * 2) //while the desired target is not seen
	{
		App->render->Blit(midgroundLightsTexture, 471, bgMovY.mg_y + 36, &(midgroundLights[5].GetCurrentFrame()), midgroundSpeed);
	}
	else
	{
		App->render->Blit(midgroundLightsTexture, 983, bgMovY.mg_y + 36, &(midgroundLights[5].GetCurrentFrame()), midgroundSpeed);
		
	}
	//-----------------------------------------------------------------------------------------------------------
	
	App->render->Blit(fg, 0, bgMovY.fg_y, &fgRect, foregroundSpeed); //foreground lvl1 last resort

	//tunnel lights draw ----------------------------------------------------------------------------
	//tunnel lights are speed dependent of foreground, only screen size multiplier (and fg speed parallax multiplier)
	if (App->render->currentCameraPosX <= -1740)
	{
		for (int i = 0; i < TUNNEL_LIGHTS; ++i)
		{
			App->render->Blit(tunelLights, positionArrayTunnel[i], bgMovY.fg_y, &(tunnelLights[i].GetCurrentFrame()), foregroundSpeed);
		}
	}

	//back street lights draw------------------------------------------------------------------------

	for (int i = 0; i < STREET_LIGHTS_A; ++i)
	{
		App->render->Blit(roadLights, positionsArrayPatternA[i], bgMovY.fg_y + 136, &(streetLightA[i].GetCurrentFrame()), foregroundSpeed);
	}
	for (int i = 0; i < STREET_LIGHTS_B; ++i)
	{
		App->render->Blit(roadLights, positionsArrayPatternB[i], bgMovY.fg_y + 136, &(streetLightB[i].GetCurrentFrame()), foregroundSpeed);
	}

	//-----------------------------------------------------------------------------------------------
	//front street lights draw ----------------------------------------------------------------------
	//(217 is y from top screen to desired point ---
	//PATTERN A

	for (int i = 0; i < STREET_LIGHTS_FRONT_A; ++i)
	{
		App->render->Blit(roadLights, positionArrayFrontA[i], bgMovY.fg_y + 217, &(streetLightsFrontA[i].GetCurrentFrame()), foregroundSpeed);
	}
	//PATTERN B
	for (int i = 0; i < STREET_LIGHTS_FRONT_B; ++i)
	{
		App->render->Blit(roadLights, positionArrayFrontB[i], bgMovY.fg_y + 217, &(streetLightsFrontB[i].GetCurrentFrame()), foregroundSpeed);
	}

	//-----------------------------------------------------------------------------------------------
	
	//App->render->Blit(App->textures->textures[6], 0, bgMovY.fg_y, &fgRect, 1.0f); //testing purposes


	//SCENE SWITCHING

	if (App->input->keyboard[SDL_SCANCODE_RETURN] == KEY_DOWN)
		App->fade->FadeToBlack(this, App->continueScreen);
	if(App->input->keyboard[SDL_SCANCODE_U] == KEY_DOWN)
		App->fade->FadeToBlack(this, (Module*)App->winScreen);
	if(App->input->keyboard[SDL_SCANCODE_O] == KEY_DOWN)
		App->fade->FadeToBlack(this, (Module*)App->gameOverScreen);

	return UPDATE_CONTINUE;
}

bool ModuleSceneLvl1::CleanUp()
{
	LOG("Unloading lvl1 textures");
	//unloading graphics textures

	App->textures->Unload(basicEnemyBgTexture);
	App->textures->Unload(buildingLasersTexture);
	App->textures->Unload(midgroundLightsTexture);
	App->textures->Unload(bgLights);
	App->textures->Unload(tunelLights);
	App->textures->Unload(roadLights);
	App->textures->Unload(boss);
	App->textures->Unload(fg);
	App->textures->Unload(mg);
	App->textures->Unload(bg);

	//changes the state of the UI
	App->moduleUI->UI = gameplay_state::NO;

	App->collision->Disable();
	App->particles->Disable();
	App->enemies->Disable();

	App->player->Disable();
	/*if (App->player2->IsEnabled())
		App->player2->Disable();
	if (App->player2Unit->IsEnabled())
		App->player2Unit->Disable();*/
	App->playerUnit->Disable();
	App->modulePowerUp->Disable();

	

	LOG("Return correct camera values");
	//returns correct value for next cameraPosition on camera.x position for next scene
	//if we have checkpoints on level, nail more this event (save the checkpoint position etc
	//on game loop before cleanUp)
	App->render->camera.x = 0;
	App->render->camera.y = 0;

	LOG("Unloading level music and fx");
	if (Mix_PausedMusic()) Mix_HaltMusic();//Mix_ResumeMusic();
	Mix_FadeOutMusic(250);
	App->audio->UnloadAudio("song_lvl1", MUSIC);
	return true;
}

//DEBUG MODE: SPAWN ENEMIES
void ModuleSceneLvl1::spawnEnemies(int x, int y)
{
	int positionX, positionY;
	//int width, height;

	positionY = y / SCREEN_SIZE;
	positionX = x / SCREEN_SIZE - App->render->camera.x / SCREEN_SIZE;

	LOG("Spawn Enemy at position x:%d y:%d ", positionX, positionY);

	if (App->input->keyboard[SDL_SCANCODE_1] == KEY_REPEAT)
	{
		//for now calculated center position manually, until fix it (access to animation frame)
		positionX -= 32 / 2;
		positionY -= 16 / 2;
		App->enemies->AddEnemy(ENEMY_TYPES::BASIC_ENEMY, positionX,  positionY, NONE);
	}
	if (App->input->keyboard[SDL_SCANCODE_2] == KEY_REPEAT)
	{
		//for now calculated center position manually, until fix it (access to animation frame)
		positionX -= 48 / 2;
		positionY -= 46 / 2;
		App->enemies->AddEnemy(ENEMY_TYPES::ENEMYOSCILATORY, positionX, positionY, NONE);
	}
	if (App->input->keyboard[SDL_SCANCODE_3] == KEY_REPEAT)
	{
		//for now calculated center position manually, until fix it (access to animation frame)
		positionX -= 157 / 2;
		positionY -= 64 / 2;
		App->enemies->AddEnemy(ENEMY_TYPES::TANK, positionX, positionY, NONE);
	}
	if (App->input->keyboard[SDL_SCANCODE_4] == KEY_REPEAT)
	{
		//for now calculated center position manually, until fix it (access to animation frame)
		positionX -= 30 / 2;
		positionY -= 30 / 2;
		App->enemies->AddEnemy(ENEMY_TYPES::ENEMYBEE, positionX, positionY, NONE);
	}
}