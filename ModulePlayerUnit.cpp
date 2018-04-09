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
	playerUnitAnim.PushBack({88,212,22,17 });
	playerUnitAnim.PushBack({ 66,212 , 22,17 });
	playerUnitAnim.PushBack({ 44,212 , 22,17 });
	playerUnitAnim.PushBack({ 22,212 , 22,17 });
	playerUnitAnim.PushBack({ 0,212 , 22,17 });
	playerUnitAnim.PushBack({ 229,189 , 22,17 });
	playerUnitAnim.PushBack({ 207,189 , 22,17 });
	playerUnitAnim.PushBack({ 185,189 , 22,17 });
	playerUnitAnim.PushBack({ 164,189 , 21,21 });
	playerUnitAnim.PushBack({ 143,189 , 21,21 });
	playerUnitAnim.PushBack({ 122,189 , 21,21 });
	playerUnitAnim.PushBack({ 101,189 , 21,21 });
	playerUnitAnim.PushBack({ 80,189 , 21,21 });
	playerUnitAnim.PushBack({ 59,189 , 21,21 });
	playerUnitAnim.PushBack({ 38,189 , 21,21 });
	playerUnitAnim.PushBack({ 17,189 , 21,21 });
	playerUnitAnim.PushBack({ 0,189 , 17,23 });
	playerUnitAnim.PushBack({ 230,166 , 17,23 });
	playerUnitAnim.PushBack({ 213,166 , 17,23 });
	playerUnitAnim.PushBack({ 196,166 , 17,23 });
	playerUnitAnim.PushBack({ 179,166 , 17,23 });
	playerUnitAnim.PushBack({ 162,166 , 17,23 });
	playerUnitAnim.PushBack({ 145,166 , 17,23 });
	playerUnitAnim.PushBack({ 128,166 , 17,23 });
	playerUnitAnim.PushBack({ 112,166 , 16,22 });
	playerUnitAnim.PushBack({ 96,166 , 16,22 });
	playerUnitAnim.PushBack({ 80,166 , 16,22 });
	playerUnitAnim.PushBack({ 64,166 , 16,22 });
	playerUnitAnim.PushBack({ 48,166 , 16,22 });
	playerUnitAnim.PushBack({ 32,166 , 16,22 });
	playerUnitAnim.PushBack({ 16,166 , 16,22 });
	playerUnitAnim.PushBack({ 0,166 , 16,22 });
	playerUnitAnim.PushBack({ 224,143 , 17,23 });
	playerUnitAnim.PushBack({ 207,143 , 17,23 });
	playerUnitAnim.PushBack({ 190,143 , 17,23 });
	playerUnitAnim.PushBack({ 173,143 , 17,23 });
	playerUnitAnim.PushBack({ 156,143 , 17,23 });
	playerUnitAnim.PushBack({ 139,143 , 17,23 });
	playerUnitAnim.PushBack({ 122,143 , 17,23 });
	playerUnitAnim.PushBack({ 105,143 , 17,23 });
	playerUnitAnim.PushBack({ 84,143 , 21,21 });
	playerUnitAnim.PushBack({ 63,143 , 21,21 });
	playerUnitAnim.PushBack({ 42,143 , 21,21 });
	playerUnitAnim.PushBack({ 21,143 , 21,21 });
	playerUnitAnim.PushBack({ 0,143 , 21,21 });
	playerUnitAnim.PushBack({ 218,122 , 21,21 });
	playerUnitAnim.PushBack({ 197,122 , 21,21 });
	playerUnitAnim.PushBack({ 176,122 , 21,21 });
	playerUnitAnim.PushBack({ 154,122 , 22,17 });
	playerUnitAnim.PushBack({ 132,122 , 22,17 });
	playerUnitAnim.PushBack({ 110,122 , 22,17 });
	playerUnitAnim.PushBack({ 88,122 , 22,17 });
	playerUnitAnim.PushBack({ 66,122 , 22,17 });
	playerUnitAnim.PushBack({ 44,122 , 22,17 });
	playerUnitAnim.PushBack({ 22,122 , 22,17 });
	playerUnitAnim.PushBack({ 0,122 , 22,17 });
	playerUnitAnim.PushBack({ 220,105 , 22,16 });
	playerUnitAnim.PushBack({ 198,105 , 22,16 });
	playerUnitAnim.PushBack({ 176,105 , 22,16 });
	playerUnitAnim.PushBack({ 154,105 , 22,16 });
	playerUnitAnim.PushBack({ 132,105 , 22,16 });
	playerUnitAnim.PushBack({ 110,105 , 22,16 });
	playerUnitAnim.PushBack({ 88, 105 , 22,16 });
	playerUnitAnim.PushBack({ 66,105 , 22,16 });
	playerUnitAnim.PushBack({ 44,105 , 22,17 });
	playerUnitAnim.PushBack({ 22,105 , 22,17 });
	playerUnitAnim.PushBack({ 0,105 , 22,17 });
	playerUnitAnim.PushBack({ 214,84 , 22,17 });
	playerUnitAnim.PushBack({ 192,84 , 22,17 });
	playerUnitAnim.PushBack({ 170,84 , 22,17 });
	playerUnitAnim.PushBack({ 148,84 , 22,17 });
	playerUnitAnim.PushBack({ 126,84 , 22,17 });
	playerUnitAnim.PushBack({ 105,84 , 21,21 });
	playerUnitAnim.PushBack({ 84,84 , 21,21 });
	playerUnitAnim.PushBack({ 63,84 , 21,21 });
	playerUnitAnim.PushBack({ 42,84 , 21,21 });
	playerUnitAnim.PushBack({ 21,84 , 21,21 });
	playerUnitAnim.PushBack({ 0,84 , 21,21 });
	playerUnitAnim.PushBack({ 221,61 , 21,21 });
	playerUnitAnim.PushBack({ 200,61 , 21,21 });
	playerUnitAnim.PushBack({ 183,61 , 17,23 });
	playerUnitAnim.PushBack({ 166,61 , 17,23 });
	playerUnitAnim.PushBack({ 149,61 , 17,23 });
	playerUnitAnim.PushBack({ 132,61 , 17,23 });
	playerUnitAnim.PushBack({ 115,61 , 17,23 });
	playerUnitAnim.PushBack({ 98,61 , 17,23 });
	playerUnitAnim.PushBack({ 81,61 , 17,23 });
	playerUnitAnim.PushBack({ 64,61 , 17,23 });
	playerUnitAnim.PushBack({ 48,61 , 16,22 });
	playerUnitAnim.PushBack({ 32,61 , 16,22 });
	playerUnitAnim.PushBack({ 16,61 , 16,22 });
	playerUnitAnim.PushBack({ 0,61 , 16,22 });
	playerUnitAnim.PushBack({ 226,38 , 16,22 });
	playerUnitAnim.PushBack({ 210,38 , 16,22 });
	playerUnitAnim.PushBack({ 194,38 , 16,22 });
	playerUnitAnim.PushBack({ 178,38 , 16,22 });
	playerUnitAnim.PushBack({ 161,38 , 17,23 });
	playerUnitAnim.PushBack({ 144,38 , 17,23 });
	playerUnitAnim.PushBack({ 127,38 , 17,23 });
	playerUnitAnim.PushBack({ 110,38 , 17,23 });
	playerUnitAnim.PushBack({ 93,38 , 17,23 });
	playerUnitAnim.PushBack({ 76,38 , 17,23 });
	playerUnitAnim.PushBack({ 59,38 , 17,23 });
	playerUnitAnim.PushBack({ 42,38 , 17,23 });
	playerUnitAnim.PushBack({ 21,38 , 21,21 });
	playerUnitAnim.PushBack({ 0,38 , 21,21 });
	playerUnitAnim.PushBack({ 215,17 , 21,21 });
	playerUnitAnim.PushBack({ 194,17 , 21,21 });
	playerUnitAnim.PushBack({ 173,17 , 21,21 });
	playerUnitAnim.PushBack({ 152,17 , 21,21 });
	playerUnitAnim.PushBack({ 131,17 , 21,21 });
	playerUnitAnim.PushBack({ 110,17 , 21,21 });
	playerUnitAnim.PushBack({ 88,17 , 22,17 });
	playerUnitAnim.PushBack({ 66,17 , 22,17 });
	playerUnitAnim.PushBack({ 44,17 , 22,17 });
	playerUnitAnim.PushBack({ 22,17 , 22,17 });
	playerUnitAnim.PushBack({ 0,17 , 22,17 });
	playerUnitAnim.PushBack({ 220,0 , 22,17 });
	playerUnitAnim.PushBack({ 198,0 , 22,17 });
	playerUnitAnim.PushBack({ 176,0 , 22,17 });
	playerUnitAnim.PushBack({ 154,0 , 22,16 });
	playerUnitAnim.PushBack({ 132,0 , 22,16 });
	playerUnitAnim.PushBack({ 110,0 , 22,16 });
	playerUnitAnim.PushBack({ 88,0 , 22,16 });
	playerUnitAnim.PushBack({ 66,0 , 22,16 });
	playerUnitAnim.PushBack({ 44,0 , 22,16 });
	playerUnitAnim.PushBack({ 22,0 , 22,16 });
	playerUnitAnim.PushBack({ 0,0 , 22,16 });
	playerUnitAnim.speed = 0.5f;




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
