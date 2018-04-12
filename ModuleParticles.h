#ifndef __MODULEPARTICLES_H__
#define __MODULEPARTICLES_H__

#include "Module.h"
#include "Animation.h"
#include "Globals.h"
#include "p2Point.h"

#define MAX_ACTIVE_PARTICLES 100

struct SDL_Texture;

struct Particle
{
	Animation anim;
	uint fx = 0;
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
<<<<<<< HEAD
	ModuleParticles();
	~ModuleParticles();

=======

	ModuleParticles();
	~ModuleParticles();
	
>>>>>>> ba1d69368494de56008eb5593df8b895a2bebd54
	bool Start();
	update_status Update();
	bool CleanUp();

	void AddParticle(const Particle& particle, int x, int y, Uint32 delay = 0);

private:

	SDL_Texture* graphics = nullptr;
	Particle* active[MAX_ACTIVE_PARTICLES];
<<<<<<< HEAD
	uint last_particle = 0;

public:

	Particle explosion;
};

#endif // __MODULEPARTICLES_H__
=======
	uint lastParticle = 0;
		
public:

	Particle beam;
};
#endif
>>>>>>> ba1d69368494de56008eb5593df8b895a2bebd54
