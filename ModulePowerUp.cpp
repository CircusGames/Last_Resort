#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
//#include "ModuleParticles.h"

#include "ModuleAudio.h"

//#include "ModulePlayer.h"
#include "ModuleCollision.h"
#include "ModulePowerUp.h"
#include "ModuleEnemies.h"

#include "ModulePlayerUnit.h"



ModulePowerUp::ModulePowerUp() 
{

	for (uint i = 0; i < MAX_TYPES; ++i)
		powerUpActives[i] = nullptr;

	//testing purposes rect

	testRect.x = 0;
	testRect.y = 0;
	testRect.w = 31;
	testRect.h = 16;
}

ModulePowerUp::~ModulePowerUp() {}

bool ModulePowerUp::Start()
{
	test = App->textures->Load("assets/Graphics/Player/blueUnitPowerUp.png");
	unitBlue.texture = App->textures->Load("assets/Graphics/Player/blueUnitPowerUp.png");

	return true;
}

update_status ModulePowerUp::Update()
{

	for (uint i = 0; i < MAX_ACTIVES; ++i)
	{
		powerUpTypeBox* p = powerUpActives[i];

		if (p == nullptr)
			continue;

			App->render->Blit(powerUpActives[i]->texture, p->position.x, p->position.y, &testRect);
			
	}
	
	return UPDATE_CONTINUE;
}

bool ModulePowerUp::CleanUp()
{
	//remove powerups and its colliders
	for (uint i = 0; i < MAX_ACTIVES; ++i)
	{
		if (powerUpActives[i] != nullptr)
		{
			powerUpActives[i]->collider->to_delete = true; //delete colliders
			delete powerUpActives[i]; //delete poweUp instance
			powerUpActives[i] = nullptr;
		}
	}
	//unload textures
	if (test != nullptr)
	App->textures->Unload(test);
	if(unitBlue.texture != nullptr)
	App->textures->Unload(test);

	return true;
}

void ModulePowerUp::powerUpSpawn(powerUpTypes type, iPoint coordinate)
{

	if (type == powerUpTypes::UNIT) //force the test for now, work in progress
	{
		// to create the new power up with dynamic memory

		for (uint i = 0; i < MAX_TYPES; ++i)
		{
			if (powerUpActives[i] == nullptr) //if we have room
			{
				powerUpActives[i] = new powerUpTypeBox(unitBlue);
				powerUpActives[i]->collider = App->collision->AddCollider({coordinate.x,coordinate.y,testRect.w,testRect.h}, COLLIDER_POWER_UP, this);
				powerUpActives[i]->position = coordinate;
				powerUpActives[i]->type = type;
				//powerUpActives[i]->texture = unitBlue.texture;
				break;
			}
		}
		
	}
	
}

void ModulePowerUp::OnCollision(Collider* c1, Collider* c2)
{
	for (uint i = 0; i < MAX_TYPES; ++i)
	{
		// and destroy power up when pick up
		if (powerUpActives[i] != nullptr && powerUpActives[i]->collider == c1)
		{

			//add particle or fx, etc
			//decide the event dependent of powerUp type //when all implemented maybe this is a switch case
			if (powerUpActives[i]->type == powerUpTypes::UNIT)
				App->playerUnit->Enable();

		    delete powerUpActives[i];
			powerUpActives[i] = nullptr;
			//delete the collider
			c1->to_delete = true;
			break;
		}
	}
}