#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleInput.h"
#include "ModuleRender.h"
#include "ModulePlayer.h"
#include "ModulePlayerUnit.h"

ModulePlayerUnit::ModulePlayerUnit()
{
	//needed rects for animations
}

ModulePlayerUnit::~ModulePlayerUnit() {}

bool ModulePlayerUnit::Init()
{

	return true;
}

bool ModulePlayerUnit::Start()
{

	return true;
}

update_status ModulePlayerUnit::Update()
{

	return UPDATE_CONTINUE;
}

bool ModulePlayerUnit::CleanUp()
{

	return true;
}
