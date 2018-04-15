#include <math.h>
#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleParticles.h"
#include "ModuleAudio.h"

#include "ModulePlayer.h"
#include "ModuleCollision.h"

#include "SDL/include/SDL_timer.h"

ModuleParticles::ModuleParticles()
{
	for (uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i)
		active[i] = nullptr;

	//animations for particles, avoiding repeat animations pushback rects
	//beam bullet particle and animation
	beam.anim.PushBack({ 148,127,15,7 });
	beam.speed.x = 6;
	beam.life = 1000;
	beam.fx = "shot";

	//beam flash smoke
	beamSmoke.anim.PushBack({ 128,126,10,9 });
	beamSmoke.anim.PushBack({ 115,124,13,12 });
	beamSmoke.anim.PushBack({ 0,0,0,0 });
	beamSmoke.anim.PushBack({ 0,0,0,0 });
	beamSmoke.anim.PushBack({ 0,0,0,0 });
	beamSmoke.anim.PushBack({ 128,126,10,9 });
	beamSmoke.anim.PushBack({ 115,124,13,12 });
	beamSmoke.anim.PushBack({ 115,124,13,12 });
	beamSmoke.anim.speed = 0.5f;
	beamSmoke.followPlayerPos = true;
	beamSmoke.lockX = 16; //offsets to lock to
	beamSmoke.lockY = -7;
	beamSmoke.anim.repeat = false;
}

ModuleParticles::~ModuleParticles()
{}

// Load assets
bool ModuleParticles::Start()
{
	LOG("Loading particles");
	graphics = App->textures->Load("assets/Graphics/Player/player1_incomplete.png");
	
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
void ModuleParticles::AddParticle(const Particle& particle, int x, int y, COLLIDER_TYPE collider_type,Uint32 delay )
{
	for (uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i)
	{
		if (active[i] == nullptr)
		{
			Particle* p = new Particle(particle);
			p->born = SDL_GetTicks() + delay;
			p->position.x = x;
			p->position.y = y;
			if (collider_type != COLLIDER_NONE)
				p->collider = App->collision->AddCollider(p->anim.GetCurrentFrame(), collider_type, this);
			active[i] = p;
			break;
		}
	}
}

// -------------------------------------------------------------
void ModuleParticles::OnCollision(Collider* c1, Collider* c2)
{
	for (uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i)
	{
		// Always destroy particles that collide
		if (active[i] != nullptr && active[i]->collider == c1)
		{
			//AddParticle(explosion, active[i]->position.x, active[i]->position.y);
			delete active[i];
			active[i] = nullptr;
			break;
		}
	}
}

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

Particle::~Particle()
{
	if (collider != nullptr)
		collider->to_delete = true;
}

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

	if (collider != nullptr)
		collider->SetPos(position.x, position.y);

	return ret;
}
