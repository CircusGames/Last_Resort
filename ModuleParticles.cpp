#include <math.h>
#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleParticles.h"
#include "ModuleAudio.h"

#include "SDL/include/SDL_timer.h"

ModuleParticles::ModuleParticles()
{
	for (uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i)
		active[i] = nullptr;
}

ModuleParticles::~ModuleParticles()
{}

// Load assets
bool ModuleParticles::Start()
{
	LOG("Loading particles");
	graphics = App->textures->Load("assets/player1_incomplete.png");

	//smoke Beam Particle 
	beamSmokeAnim.PushBack({ 128,126,10,9 });
	beamSmokeAnim.PushBack({ 115,124,13,12 });
	beamSmokeAnim.speed = 0.2f;
	//beamSmoke.anim = &beamSmokeAnim; //links particle anim pointer to animation

	//beam particle
	//beamShotAnim.PushBack({148,127,15,7}); // ---
	//beam.anim = &beamShotAnim;
	beam.anim.PushBack({ 148,127,15,7 });
	beam.speed.x = 6;
	beam.life = 1000;

	return true;
}

// Unload assets
bool ModuleParticles::CleanUp()
{
	LOG("Unloading particles");
	App->textures->Unload(graphics);

	for (uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i)
	{
		if (active[i] != nullptr)
		{
			delete active[i];
			active[i] = nullptr;
		}
	}

	return true;
}

// Update: draw background
update_status ModuleParticles::Update()
{
	for (uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i)
	{
		Particle* p = active[i];

		if (p == nullptr)
			continue;

		if (p->Update() == false)
		{
			delete p;
			active[i] = nullptr;
		}
		else if (SDL_GetTicks() >= p->born)
		{
			
			//p->r = p->anim->GetCurrentFrame(); ---
			//App->render->Blit(graphics, p->position.x, p->position.y, &(p->r)); // ---
			App->render->Blit(graphics, p->position.x, p->position.y, &(p->anim.GetCurrentFrame()));
			if (p->fx_played == false)
			{
				p->fx_played = true;
				// Play particle fx here
				App->audio->ControlAudio(p->fx,SFX,PLAY);


			}
		}
	}

	return UPDATE_CONTINUE;
}

//void ModuleParticles::AddParticle(const Particle& particle, Animation& sourceAnim, int x, int y, Uint32 delay, iPoint speed, Uint32 life, char* name)
void ModuleParticles::AddParticle(const Particle& particle, int x, int y, char* name, Uint32 delay )
{
	Particle* p = new Particle(particle);
	//p->anim = &sourceAnim;
	p->fx = name;

	//checks if the new particle has the index on non 0 value and change for correct cycle
	//if (p.anim->current_frame == 0) p->anim->current_frame = 0; // ---
	// -----
	p->born = SDL_GetTicks() + delay;
	p->position.x = x;
	p->position.y = y;
	
	//p->speed = speed; // ---
	//p->life = life; // ---

	active[last_particle++] = p;
}

// -------------------------------------------------------------
// -------------------------------------------------------------

Particle::Particle()
{
	position.SetToZero();
	speed.SetToZero();
}

Particle::Particle(const Particle& p) :
	anim(p.anim), position(p.position), speed(p.speed),
	fx(p.fx), born(p.born), life(p.life)
{}

bool Particle::Update()
{
	bool ret = true;

	if (life > 0)
	{
		if ((SDL_GetTicks() - born) > life)
			ret = false;
	}
	else
		if (anim.finish)
		ret = false;

	position.x += speed.x;
	position.y += speed.y;

	return ret;
}
