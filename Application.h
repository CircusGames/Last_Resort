#ifndef __APPLICATION_H__
#define __APPLICATION_H__

#include "Globals.h"

#define NUM_MODULES 11

class ModuleWindow;
class ModuleInput;
class ModuleTextures;
class ModuleRender;
class ModuleSceneIntro;
class ModuleBackground;
class ModuleGameOver;
class ModulePlayer;
class ModulePlayerUnit;
class Module;
class ModuleAudio;
class ModuleFadeToBlack;


class Application
{
public:

	Module * modules[NUM_MODULES] = { nullptr };
	ModuleWindow* window = nullptr;
	ModuleRender* render = nullptr;
	ModuleInput* input = nullptr;
	ModuleTextures* textures = nullptr;
	ModuleSceneIntro* introScreen = nullptr;
	ModuleBackground* background = nullptr;
	ModuleGameOver* gameOverScreen = nullptr;
	ModulePlayer* player = nullptr;
	ModulePlayerUnit* playerUnit = nullptr;
	ModuleAudio* audio = nullptr;
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