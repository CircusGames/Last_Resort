#ifndef __ModuleRenderer_H__
#define __ModuleRenderer_H__

#include "Module.h"
#include "SDL\include\SDL_rect.h"

struct SDL_Renderer;
struct SDL_Texture;

class ModuleRender : public Module
{
public:
	ModuleRender();
	~ModuleRender();

	bool Init();
	update_status PostUpdate();
	update_status Update();
	update_status PreUpdate();
	bool CleanUp();

	bool Blit(SDL_Texture* texture, int x, int y, SDL_Rect* section, float speedX = 1.0f,float speedY = 1.0f);

public:
	SDL_Renderer* renderer = nullptr;
	SDL_Rect camera;
	float fCameraSpeed;
	float currentCameraPosX;
	//bool scroll = false;
	//int cameraPosX;
};

#endif //__ModuleRenderer_H__