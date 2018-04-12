#ifndef __MODULEPARTICLES_H__
#define __MODULEPARTICLES_H__

#include "Module.h"
#include "Animation.h"
#include "Globals.h"
#include "p2Point.h"

#define MAX_ACTIVE_PARTICLES 500

struct SDL_Texture;

struct Particle
{
	Animation* anim;
	SDL_Rect r;
	//uint fx = 0;
	char* fx;
	iPoint position;
	iPoint speed;
	Uint32 born = 0;
	Uint32 life = 0;
	bool fx_played = false;

	Particle();
	Particle(const Particle& p);
	bool Update();
};

class ModuleParticles : public Module
{
public:

	ModuleParticles();
	~ModuleParticles();

	bool Start();
	update_status Update();
	bool CleanUp();

	void AddParticle(const Particle& particle, Animation& sourceAnim, int x, int y, Uint32 delay = 0, iPoint speed = { 0,0 }, Uint32 life = 0, char* fx = nullptr);

private:

	
	
	SDL_Texture* graphics = nullptr;
	Particle* active[MAX_ACTIVE_PARTICLES];

	uint last_particle = 0;

public:

	Particle explosion;

	Animation beamShotAnim;
	
	Particle beamSmoke;
	Animation beamSmokeAnim;

	Particle beam;
};

#endif // __MODULEPARTICLES_H__