#ifndef __MODULESCENELVL3_H__
#define __MODULESCENELVL3_H__

#include "Module.h"
#include "Animation.h"
#include "Globals.h"

#include "p2Point.h"

#define MAXWAVES 17
#define NUMREFLECTIONS 4

struct SDL_Texture;
struct Collider;

enum stage_zone
{
	level,
	boss_zone
};

class ModuleSceneLvl3 : public Module
{

public:

	ModuleSceneLvl3();
	~ModuleSceneLvl3();

	bool Init(); //to define needed values
	bool Start();
	update_status PreUpdate();
	update_status Update();

	bool CleanUp();

	//void spawnEnemies(int x, int y);
	void addEnemiesToLvl3();

	float GetCurrentCameraPixelPos();

public:

	//bg textures---------------------------
	SDL_Texture* bgTexture = nullptr; //background
	SDL_Texture* fgTexture = nullptr; //foreground(cave)
	SDL_Texture* fgWavesTexture = nullptr;
	SDL_Texture* bgWaterReflectionsTexture = nullptr;
	//SDL_Texture* submarineWavesTexture = nullptr;

	//background needed rects
	SDL_Rect bgRect;
	SDL_Rect fgRect;

	//background animations
	Animation bgWaterReflectionsAnim[NUMREFLECTIONS];
	Animation seaWavesAnim[MAXWAVES];

	//background logic variables
	bool scroll = false;
	stage_zone currentLevelZone = stage_zone::level;
	float currenCameraPixelPos;


	
};

#endif //! _MODULESCENELVL3_H__