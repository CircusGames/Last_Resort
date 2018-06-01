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

#define MARGIN 20

ModuleParticles::ModuleParticles()
{
	for (uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i)
		active[i] = nullptr;

	//animations for particles, avoiding repeat animations pushback rects

	//beam bullet particle and animation -------------------
	beam.anim.PushBack({ 148,127,15,7 });
	beam.speed.x = 12;
	beam.life = 1000;
	//beam.fx = "shot";
	beam.damage = 1;
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
	unitBasicShot.life = 1500;
	unitBasicShot.damage = 1;
	// ------------------------------------------

	//Explosion TEST --------------------
	explosion.anim.PushBack({ 101, 16, 16, 16 });
	explosion.anim.PushBack({ 124, 14, 20, 20 });
	explosion.anim.PushBack({ 151, 11, 25, 25 });
	explosion.anim.PushBack({ 181, 11, 26, 26 });
	explosion.anim.PushBack({ 211, 7, 32, 32 });
	explosion.anim.PushBack({ 248, 7, 32, 32 });
	explosion.anim.PushBack({ 285, 7, 32, 32 });
	explosion.anim.PushBack({ 318, 7, 32, 32 });
	explosion.anim.PushBack({ 351, 7, 32, 32 });
	explosion.anim.PushBack({ 387, 7, 32, 32 });
	explosion.anim.PushBack({ 420, 5, 31, 32 });
	explosion.anim.PushBack({ 452, 7, 30, 28 });
	explosion.anim.PushBack({ 485, 5, 30, 26 });
	explosion.anim.repeat = false;
	explosion.anim.speed = 0.3f;

	//laser
	laser.anim.PushBack({ 27,11,16,3 });
	laser.anim.PushBack({ 1,11,24,3 });
	laser.anim.PushBack({ 45,11,32,3 });
	laser.anim.PushBack({ 67,6,40,3 });
	laser.anim.PushBack({ 59,1,48,3 });
	laser.anim.PushBack({ 1,1,56,3 });
	laser.anim.PushBack({ 1,6,56,3 });
	laser.anim.speed = 0.6f;
	laser.anim.repeat = false;
	laser.speed.x = 6;
	laser.damage = 2;
	laser.life = 1500;
	//laser.fx = "laser";

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
	laserTexture = App->textures->Load("assets/Graphics/Player/laser.png");;
	// ------------------------------------------------
	
	//load and links textures for particles -----------
	beam.texture = graphics;
	unitBasicShot.texture = unitBasicShotTexture;
	laser.texture = laserTexture;
	// ------------------------------------------------

	//load specific Wavs effects for particles --------
	App->audio->LoadAudio("assets/Audio/SFX/Player/shot04.wav", "shot", SFX);
	App->audio->LoadAudio("assets/Audio/SFX/Player/laser.wav", "laser", SFX);
	// ------------------------------------------------
	laser.fx = "laser";
	beam.fx = "shot";

	//TEST PARTICLES
	test = App->textures->Load("assets/Graphics/Enemies/explosions.png");
	explosion.texture = test;


	return true;
}

// Unload assets
bool ModuleParticles::CleanUp()
{
	LOG("Unloading particles");

	//unloading graphics
	App->textures->Unload(test); //remember erase this and its texture etc
	App->textures->Unload(laserTexture);
	App->textures->Unload(unitBasicShotTexture);
	App->textures->Unload(graphics);

	//restoring pointers
	beam.texture = nullptr;
	unitBasicShot.texture = nullptr;
	laser.texture = nullptr;

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
	App->audio->UnloadAudio("laser", SFX);


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
			//p->texture = nullptr;
			delete p;
			active[i] = nullptr;
			
		}
		else if (SDL_GetTicks() >= p->born)
		{
			
			//p->r = p->anim->GetCurrentFrame(); ---
			//App->render->Blit(graphics, p->position.x, p->position.y, &(p->r)); // ---
			App->render->Blit(p->texture, p->position.x, p->position.y, &(p->anim.GetCurrentFrame()));
			if (p->fx_played == false && p->fx != nullptr)
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
				p->collider = App->collision->AddCollider(p->anim.GetCurrentFrame(), collider_type, this, p->damage);
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
			// checks if we are collisioning on walls, or anything else

			if (c2->type == COLLIDER_WALL) // if collider wall...
			{
				if (active[i]->onCollisionWallParticle != nullptr)
					AddParticle(*active[i]->onCollisionWallParticle, active[i]->position.x, active[i]->position.y, COLLIDER_NONE, {0,0},0);
			}
			if (c2->type != COLLIDER_WALL) // anything collider
			{
				if (active[i]->onCollisionGeneralParticle != nullptr)
					AddParticle(*active[i]->onCollisionGeneralParticle, active[i]->position.x, active[i]->position.y, COLLIDER_NONE, { 0,0 }, 0);
			}

			//active[i]->texture = nullptr;
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
	anim(p.anim), position(p.position), speed(p.speed), fx(p.fx), born(p.born), life(p.life),texture(p.texture),
	damage(p.damage), onCollisionGeneralParticle(p.onCollisionGeneralParticle), onCollisionWallParticle(p.onCollisionWallParticle)
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
	else if (anim.finish && (SDL_GetTicks() - born) > life)
				ret = false;
	
	//destroy particles respect camera position margins
	if (position.x > (abs(App->render->camera.x) / SCREEN_SIZE) + SCREEN_WIDTH - MARGIN)
		ret = false;
	else if (position.x < (abs(App->render->camera.x) / SCREEN_SIZE) - MARGIN)
		ret = false;

	position.x += speed.x;
	position.y += speed.y;

	if (collider != nullptr)
		collider->SetPos(position.x, position.y);

	return ret;
}
