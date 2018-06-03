#include <math.h>
#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleParticles.h"
#include "ModuleAudio.h"

#include "ModulePlayer.h"
#include "ModuleCollision.h"
#include "ModuleEnemies.h"

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
	// basic shot "beam" on impact particle
	beamImpactParticle.anim.PushBack({ 35,17,16,16 });
	beamImpactParticle.anim.PushBack({ 18,17,16,16 });
	beamImpactParticle.anim.PushBack({ 14,0,15,15 });
	beamImpactParticle.anim.PushBack({ 0,17,16,16 });
	beamImpactParticle.anim.PushBack({ 29,0,15,15 });
	beamImpactParticle.anim.PushBack({ 45,0,15,15 });
	beamImpactParticle.anim.PushBack({ 0,0,15,15 });
	beamImpactParticle.anim.speed = 0.50f;
	beamImpactParticle.anim.repeat = false;
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
	// unit basic shot impact particle
	unitBasicShotImpact.anim.PushBack({ 35,17,16,16 });
	unitBasicShotImpact.anim.PushBack({ 18,17,16,16 });
	unitBasicShotImpact.anim.PushBack({ 14,0,15,15 });
	unitBasicShotImpact.anim.PushBack({ 0,17,16,16 });
	unitBasicShotImpact.anim.PushBack({ 29,0,15,15 });
	unitBasicShotImpact.anim.PushBack({ 45,0,15,15 });
	unitBasicShotImpact.anim.PushBack({ 0,0,15,15 });
	unitBasicShotImpact.anim.speed = 0.50f;
	unitBasicShotImpact.anim.repeat = false;

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
	explosion.fx = "EnemyDeath2";

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

	// homing missiles
	homingMissile.anim.PushBack({ 2,137,74,18 });
	homingMissile.anim.PushBack({ 76,137,74,14 });
	homingMissile.anim.PushBack({ 150,137,74,18 });
	homingMissile.anim.PushBack({ 2,152,74,18 });
	for (uint i = 0; i < 24; i++)
	{
		homingMissile.anim.PushBack({ 76,152,74,18 });
		homingMissile.anim.PushBack({ 150,152,74,18 });
		homingMissile.anim.PushBack({ 2,170,74,18 });
		homingMissile.anim.PushBack({ 76,170,74,18 });
	}
	homingMissile.anim.speed = 0.25f;
	//homingMissile.anim.repeat = false;
	//homingMissile.life = 3000;
	homingMissile.damage = 2;
	homingMissile.impactPosition = { 80,0 };

	// bombs powerup particle
	bombsUp.anim.PushBack({ 3,40,16,6 });
	bombsUp.anim.PushBack({ 151,100,15,10 });
	bombsUp.anim.PushBack({ 168,100,13,13 });
	bombsUp.anim.PushBack({ 168,100,13,13 });
	bombsUp.anim.PushBack({ 151,115,10,15 });
	for (uint i = 0; i < 24; ++i)
		bombsUp.anim.PushBack({ 163,115,6,16 });
	bombsUp.anim.speed = 0.25f;
	bombsUp.life = 2000;
	bombsUp.damage = 2;

	bombsDown.anim.PushBack({ 3,40,16,6 });
	bombsDown.anim.PushBack({ 3,54,15,10 });
	bombsDown.anim.PushBack({ 4,68,13,13 });
	bombsDown.anim.PushBack({ 6,83,10,15 });
	for (uint i = 0; i < 24; ++i)
		bombsDown.anim.PushBack({ 8,99,6,16 });
	bombsDown.anim.speed = 0.25f;
	bombsDown.life = 2000;
	bombsDown.damage = 2;

	// power up bombs explosion particle
	bombGoodBye.anim.PushBack({ 223,222,32,32 });
	bombGoodBye.anim.PushBack({ 190,222,32,32 });
	bombGoodBye.anim.PushBack({ 0,192,19,21 });
	bombGoodBye.anim.PushBack({ 19,192,19,21 });
	bombGoodBye.anim.PushBack({ 73,192,19,21 });
	bombGoodBye.anim.PushBack({ 157,222,32,32 });
	bombGoodBye.anim.PushBack({ 124,222,32,32 });
	bombGoodBye.anim.PushBack({ 91,222,32,32 });
	bombGoodBye.anim.PushBack({ 58,222,32,32 });
	bombGoodBye.anim.PushBack({ 25,222,32,32 });
	bombGoodBye.anim.PushBack({ 178,190,32,32 });
	bombGoodBye.anim.PushBack({ 145,190,32,32 });
	bombGoodBye.anim.PushBack({ 111,190,32,32 });
	bombGoodBye.anim.PushBack({ 42,190,32,32 });
	bombGoodBye.anim.speed = 0.5f;
	bombGoodBye.anim.repeat = false;
	//bombGoodBye.life = 2000;
	bombGoodBye.damage = 2;


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
	laserTexture = App->textures->Load("assets/Graphics/Player/laser.png");
	beamImpactTexture = App->textures->Load("assets/Graphics/Player/playerShotImpact.png");
	unitBasicShotImpactTexture = App->textures->Load("assets/Graphics/Player/unitBasicShotImpactFixed.png");
	powerUpVFXTexture = App->textures->Load("assets/Graphics/Player/powerUpEffects2.png");
	// ------------------------------------------------
	
	//load and links textures for particles -----------
	beam.texture = graphics;
	beam.onCollisionGeneralParticle = &beamImpactParticle;
	beamImpactParticle.texture = beamImpactTexture;
	unitBasicShot.texture = unitBasicShotTexture;
	unitBasicShot.onCollisionGeneralParticle = &unitBasicShotImpact;
	unitBasicShotImpact.texture = unitBasicShotImpactTexture;
	laser.texture = laserTexture;
	homingMissile.texture = powerUpVFXTexture;
	bombsDown.texture = powerUpVFXTexture;
	bombsUp.texture = powerUpVFXTexture;
	homingMissile.deathParticle = &App->enemies->homingExplosion;
	homingMissile.onCollisionGeneralParticle = &App->enemies->homingExplosion;
	bombGoodBye.texture = powerUpVFXTexture;
	bombsDown.onCollisionGeneralParticle = &bombGoodBye;
	bombsUp.onCollisionGeneralParticle = &bombGoodBye;
	//bombGoodBye.deathParticle = &bombGoodBye;
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
	App->textures->Unload(powerUpVFXTexture);
	App->textures->Unload(beamImpactTexture);
	App->textures->Unload(unitBasicShotImpactTexture);
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
			if (active[i]->deathParticle != nullptr)
				AddParticle(*active[i]->deathParticle, active[i]->position.x, //+ active[i]->impactPosition.x,
					active[i]->position.y , COLLIDER_ENEMY_SHOT);

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
				{
					if (active[i]->impactPosition.x != NULL || active[i]->impactPosition.y != NULL)
					{
						AddParticle(*active[i]->onCollisionWallParticle, active[i]->position.x + active[i]->impactPosition.x, 
							active[i]->position.y + active[i]->impactPosition.y, COLLIDER_NONE, { 0,0 }, 0);
					}
					else
						AddParticle(*active[i]->onCollisionWallParticle, active[i]->position.x, active[i]->position.y, COLLIDER_NONE, { 0,0 }, 0);
				}
			}
			//if (c2->type != COLLIDER_WALL) // anything collider
			//{
				if (active[i]->onCollisionGeneralParticle != nullptr)
					AddParticle(*active[i]->onCollisionGeneralParticle, active[i]->position.x + active[i]->impactPosition.x,
						active[i]->position.y + active[i]->impactPosition.y, COLLIDER_NONE, { 0,0 }, 0);
			//}

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
	damage(p.damage), onCollisionGeneralParticle(p.onCollisionGeneralParticle), onCollisionWallParticle(p.onCollisionWallParticle),
	impactPosition(p.impactPosition), deathParticle(p.deathParticle)
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
	else if (position.x < (abs(App->render->camera.x) / SCREEN_SIZE) - MARGIN - 150)
		ret = false;

	position.x += speed.x;
	position.y += speed.y;

	if (collider != nullptr)
		collider->SetPos(position.x, position.y);

	return ret;
}
