#ifndef __MODULESCENELVL3_H__
#define __MODULESCENELVL3_H__

#include "Module.h"
#include "Animation.h"
#include "Globals.h"

#include "p2Point.h"

#define MAXWAVES 17
#define NUMREFLECTIONS 4
#define MAX_SCENE_COLLIDERS 20

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
	update_status PostUpdate(); // sea waves

	bool CleanUp();


	bool spawnOnce = true;
	Uint32 wave = 1;
	bool midBossSpawn = false;


	//void spawnEnemies(int x, int y);
	void addEnemiesToLvl3();
	void AddColliders();
	void setCollidersToScenePos();

	float GetCurrentCameraPixelPos();
	void bossBackgroundFade();

public:

	//bg textures------------------------------------
	SDL_Texture* bgTexture = nullptr; //background
	SDL_Texture* fgTexture = nullptr; //foreground(cave)
	SDL_Texture* fgWavesTexture = nullptr;
	SDL_Texture* bgWaterReflectionsTexture = nullptr;
	SDL_Texture* bossBgTexture = nullptr;
	SDL_Texture* wavesCapTexture = nullptr;
	//SDL_Texture* submarineWavesTexture = nullptr;

	//background needed rects
	SDL_Rect bgRect;
	SDL_Rect fgRect;

	//background animations
	Animation bgWaterReflectionsAnim[NUMREFLECTIONS];
	Animation seaWavesAnim[MAXWAVES];
	Animation wavesCapAnim;

	// background logic variables ---------------------
	bool scroll = false;
	stage_zone currentLevelZone = stage_zone::level;
	//float currenCameraPixelPos;
	float currentCameraPixelPos;
	// values for boss background fade ---
	Uint32 start_time;
	Uint32 total_time;
	Uint32 now;
	// -----------------------------------
	bool faded = false;
	// ------------------------------------------------

	//set colliders scene correct speeds
	Collider* sceneColliders[MAX_SCENE_COLLIDERS] = { nullptr };
	int lastCameraPosX;

	// debug colliders
	Collider* debugColRight = nullptr;
	Collider* debugColLeft = nullptr;
	Collider* debugColCenter = nullptr;
	Collider* debugColumn = nullptr;
};

#endif //! _MODULESCENELVL3_H__