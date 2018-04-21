#ifndef __MODULESCENELVL1_H__
#define __MODULESCENELVL1_H__

#include "Module.h"
#include "Animation.h"
#include "Globals.h"

#include "p2Point.h"

#define QTY_BACK_LIGHTS 18 //max streetlights for each pattern (max)
#define QTY_FRONT_LIGHTS 8
#define MAX_BG_SHIPS 20
//#define MAX 14

struct SDL_Texture;
struct Collider;

class ModuleSceneLvl1 : public Module
{

public:

	ModuleSceneLvl1();
	~ModuleSceneLvl1();

	bool Init(); //to define needed values
	bool Start();
	update_status PreUpdate();
	update_status Update();

	bool CleanUp();

public:
	
	//bg textures---------------------------
	SDL_Texture* bg = nullptr; //background
	SDL_Texture* mg = nullptr; //midground
	SDL_Texture* fg = nullptr; //foreground(road lvl and tunnel)
	SDL_Texture* roadLights = nullptr;
	SDL_Texture* tunelLights = nullptr;
	SDL_Texture* bgLights = nullptr;
	SDL_Texture* boss = nullptr;
	SDL_Texture* buildingLasersTexture = nullptr;
	SDL_Texture* midgroundLightsTexture = nullptr;
	
	//basic enemy background texture
	SDL_Texture* basicEnemyBgTexture = nullptr;
	
	
	SDL_Rect bgRect;
	SDL_Rect fgRect;
	SDL_Rect mgRect;
	//road streetLights and spots RECTS
	SDL_Rect streetLights;

	//other vars --------------------------
	bool updatePos; //bool to wait X frameUpdates
	
	bool scrollX = false;
	float cameraSpeed;
	int streetLightsQtyRender;
	//array patterns for store distribution of street lights spawn points
	//streetlights back
	int positionsArrayPatternA[15] = { -24, 104, 168, 360, 488, 616, 680, 808, 872, 1000, 1192, 1320, 1384, 1512, 1640 }; //= {nullptr}; //12 streetlights with animation pattern A
	int positionsArrayPatternB[13] = { 40, 232 , 296, 424,  552, 744, 936, 1064, 1128, 1256, 1448, 1576, 1704 };
	//streetLights front (big spot)
	int positionArrayFrontA[8] = { -7, 249, 377, 505, 889, 1273, 1529, 1657 };
	int positionArrayFrontB[6] = { 121, 633, 761, 1017, 1145, 1401 };
	//tunnel lights
	int positionArrayTunnel[8] = { 2048, 2304, 2560, 2816, 3072, 3328, 3584, 3840 };
	//blue lasers pivot texture positions
	int pivotArrayBlueLasersPosition[8] = { 38,30,1,1,1,1,5,30 };
	//blue lasers position array X
	int positionArrayBlueLasersX[5] = {200,712,792,856,1224};
	int positionArrayBlueLasersY[5] = { 16,16,48,0,16 };
	//orange laser pivot x array
	int pivotArrayOrangeLaser[128] = { 
		1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,
		1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,
		25,0,38,0,52,0,65,0,65,0,81,0,81,0,81,0,99,0,99,0,99,0,121,0,121,0,121,0,
		142,0,142,0,142,0,142,0,121,0,121,0,121,0,121,0,99,0,99,0,99,0,81,0,81,0,
		65,0,65,0,52,0,52,0,38,0 };

	bool notDefined = false; //if not defined spawn positions of each

	int nextStreetLightPosition;

	struct movY //struct for follow backgroundY camera mov
	{
		bool move = false;
		//conditions ----------
		bool up = true; //on first level the first move is down
		bool down = false; 
		//events
		bool moveUp = false;
		bool moveDown = false;

		//speeds --------------
		float speedMg;
		float speedfg;

		//positions -----------
		int mg_y;
		int fg_y;
		float mgTemp;
		float fgTemp;

		//foreground positions -
		bool fgRendezvous = false;
		int fgTargetUp;
		int fgTargetDown;
		int fgMidPosition;
		//midground positions
		bool mgRendezvous = false;
		int mgTargetUp;
		int mgTargetDown;
		int mgMidPosition;

		//lastloop needed variables for the last center camera before tunnel
		int maxLoops;// = 12; //13 == midposition
		int currentLoops;
		bool lastLoop = false; //condition wich force go to midposition when last loop reached

		int distanceWaitToMov; //distance between cycles of up/down
		int lastMovPosX; //stores last x value of last cycle up/down

	}bgMovY;

	//animations ----------------------------------

	Animation streetLightA[QTY_BACK_LIGHTS];
	Animation streetLightB[QTY_BACK_LIGHTS];
	Animation streetLightsFrontA[QTY_FRONT_LIGHTS];
	Animation streetLightsFrontB[QTY_FRONT_LIGHTS];
	Animation tunnelLights[QTY_FRONT_LIGHTS];
	Animation buildingLasers[5];
	Animation orangeLaser;
	Animation backgroundLights[6]; //6 "rects" for total background animations
	Animation midgroundLights[6];
	
	//basic enemy background animation
	Animation basicEnemyBgAnim[MAX_BG_SHIPS];
	int basicEnemyBgPositionsX[MAX_BG_SHIPS] = { 50,100,150,75,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 };
	int basicEnemyBgPositionsY[MAX_BG_SHIPS] = { 20,20,30,40,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 };
	//---------------------------------------------

	float foregroundSpeed;
	float midgroundSpeed;
	float backgroundSpeed;
};

#endif //! _MODULESCENELVL1_H__