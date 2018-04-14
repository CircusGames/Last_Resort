#include <math.h>
#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleParticles.h"
#include "ModuleAudio.h"

#include "ModulePlayer.h"

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
	//beamSmokeAnim.PushBack({ 128,126,10,9 });
	//beamSmokeAnim.PushBack({ 115,124,13,12 });
	//beamSmokeAnim.speed = 0.2f;
	//beamSmoke.anim = &beamSmokeAnim; //links particle anim pointer to animation

	//beam particle
	//beamShotAnim.PushBack({148,127,15,7}); // ---
	//beam.anim = &beamShotAnim;

	//beam bullet particle and animation
	beam.anim.PushBack({ 148,127,15,7 });
	beam.speed.x = 6;
	beam.life = 1000;

	//beam flash smoke
	beamSmoke.anim.PushBack({ 128,126,10,9 });
	beamSmoke.anim.PushBack({ 115,124,13,12 });
	beamSmoke.anim.speed = 0.2f;
	//beamSmoke.position = App->player->position;
	beamSmoke.followPlayerPos = true;
	beamSmoke.lockX = 16; //offsets to lock to
	beamSmoke.lockY = -7;
	
	beamSmoke.anim.repeat = false;
	//beamSmoke.life = 200;

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
	//p->anim = &sourceAnim; // links pointer particle anim to animation
	p->fx = name;

	// -----
	p->born = SDL_GetTicks() + delay;
	p->position.x = x;
	p->position.y = y;

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
	fx(p.fx), born(p.born), life(p.life),
	//lock particles to player pos + offsets
	followPlayerPos(p.followPlayerPos), lockX(p.lockX), lockY(p.lockY)
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

	if (followPlayerPos)
	{
		position.x = App->player->position.x + lockX;
		//check pivots when Y animation changes
		//if (App->player->frameIncrement > 2) lockY = -3;
		//else if (App->player->frameIncrement < 2) lockY = -5;
		//else if (App->player->frameIncrement == 2) lockY = -20;
		position.y = App->player->position.y + lockY;
	}
	else
	{
		position.x += speed.x;
		position.y += speed.y;
	}

	return ret;
}
