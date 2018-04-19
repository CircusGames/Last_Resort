#ifndef __APPLICATION_H__
#define __APPLICATION_H__

#include "Globals.h"

#define NUM_MODULES 17

class ModuleWindow;
class ModuleInput;
class ModuleTextures;
class ModuleRender;
class ModuleParticles;
class ModuleTeamLogo;
class ModuleGameTitle;
class ModuleSceneLvl1;
class ModuleGameOver;
class ModulePlayer;
class ModulePlayer2;
class ModulePlayerUnit;
class ModulePlayer2Unit;
class Module;
class ModuleAudio;
class ModuleCollision;
class ModuleFadeToBlack;
class ModulePowerUp;
class ModuleUI;

class ModuleEnemies;

// dont forget to increase the NUM_MODULES variable whenever you add a new module
class Application
{
public:

	Module * modules[NUM_MODULES] = { nullptr };
	ModuleWindow* window = nullptr;
	ModuleRender* render = nullptr;
	ModuleInput* input = nullptr;
	ModuleTextures* textures = nullptr;
	ModuleParticles* particles = nullptr;
	ModuleTeamLogo* teamLogo = nullptr;
	ModuleGameTitle* gameTitle = nullptr;
	ModuleSceneLvl1* scene_lvl1 = nullptr;
	ModuleGameOver* gameOverScreen = nullptr;
	ModulePlayer* player = nullptr;
	ModulePlayer2* player2 = nullptr;
	ModulePlayerUnit* playerUnit = nullptr;
	ModulePlayer2Unit* player2Unit = nullptr;
	ModulePowerUp* modulePowerUp = nullptr;
	ModuleEnemies* enemies = nullptr;
	ModuleCollision* collision = nullptr;
	ModuleAudio* audio = nullptr;
	ModuleUI* moduleUI = nullptr;
	ModuleFadeToBlack* fade = nullptr;

	
	
	

public:

	Application();
	~Application();

	bool Init();
	update_status Update();
	bool CleanUp();

};

// Global var made extern for Application ---
extern Application* App;

#endif // __APPLICATION_H__