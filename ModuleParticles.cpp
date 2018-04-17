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

	//beam bullet particle and animation -------------------
	beam.anim.PushBack({ 148,127,15,7 });
	beam.speed.x = 6;
	beam.life = 1000;
	beam.fx = "shot";
	// -----------------------------------------------------
	//Unit basic shot particle-------------------
	unitBasicShot.anim.PushBack({ 1,1,13,13 });
	unitBasicShot.anim.PushBack({ 16,1,13,13 });
	unitBasicShot.anim.PushBack({ 1,16,13,13 });
	unitBasicShot.anim.PushBack({ 16,16,13,13 });
	unitBasicShot.anim.PushBack({ 1,31,13,13 });
	unitBasicShot.anim.PushBack({ 16,31,13,13 });
	unitBasicShot.anim.PushBack({ 1,46,13,13 });
	unitBasicShot.anim.PushBack({ 16,46,13,13 });
	unitBasicShot.anim.speed = 0.3f;
	unitBasicShot.life = 2000;
	// ------------------------------------------

	//Explosion TEST--------------------
	explosion.anim.PushBack({ 274, 296, 33, 30 });
	explosion.anim.PushBack({ 313, 296, 33, 30 });
	explosion.anim.PushBack({ 346, 296, 33, 30 });
	explosion.anim.PushBack({ 382, 296, 33, 30 });
	explosion.anim.PushBack({ 419, 296, 33, 30 });
	explosion.anim.PushBack({ 457, 296, 33, 30 });
	explosion.anim.repeat = false;
	explosion.anim.speed = 0.3f;
}

ModuleParticles::~ModuleParticles()
{}

// Load assets
bool ModuleParticles::Start()
{
	LOG("Loading particles");
	
	//load textures and links pointers to -------------
	graphics = App->textures->Load("assets/Graphics/Player/player1_incomplete.png");
	unitBasicShotTexture = App->textures->Load("assets/Graphics/Player/unitBasicShot.png");
	// ------------------------------------------------

	//load and links textures for particles -----------
	beam.texture = graphics;
	unitBasicShot.texture = unitBasicShotTexture;
	// ------------------------------------------------

	//load specific Wavs effects for particles --------
	App->audio->LoadAudio("assets/Audio/SFX/Player/shot04.wav", "shot", SFX);
	// ------------------------------------------------


	//TEST PARTICLES
	test = App->textures->Load("assets/Graphics/player/particles.png");


	return true;
}

// Unload assets
bool ModuleParticles::CleanUp()
{
	LOG("Unloading particles");
	App->textures->Unload(graphics);


	App->textures->Unload(test);
	//removing active particles
	for (uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i)
	{
		if (active[i] != nullptr)
		{
			delete active[i];
			active[i] = nullptr;
		}
	}
	//removing particles FX audio
	App->audio->UnloadAudio("shot", SFX);

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
			App->render->Blit(p->texture, p->position.x, p->position.y, &(p->anim.GetCurrentFrame()));
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
void ModuleParticles::AddParticle(const Particle& particle, int x, int y, COLLIDER_TYPE collider_type,iPoint speed,Uint32 delay )
{
	for (uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i)
	{
		if (active[i] == nullptr)
		{
			Particle* p = new Particle(particle);
			p->born = SDL_GetTicks() + delay;
			p->position.x = x;
			p->position.y = y;
			if (speed.x != 0 || speed.y != 0) //if we send specific speed, defines it
			{
				p->speed = speed;
			}
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
	anim(p.anim), position(p.position), speed(p.speed), fx(p.fx), born(p.born), life(p.life),texture(p.texture)
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
	
	position.x += speed.x;
	position.y += speed.y;

	if (collider != nullptr)
		collider->SetPos(position.x, position.y);

	return ret;
}
