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
	playerUnitAnim.speed = 0.143f;




}

ModulePlayerUnit::~ModulePlayerUnit() {}

bool ModulePlayerUnit::Init()
{

	return true;
}

bool ModulePlayerUnit::Start()
{
	LOG("Starting playerUnit Module");

	
	playerUnitBlue = App->textures->Load("assets/player/blueUnit.png");

	//delta calculations
	orbitSpeed = 1.0f;
	last_tick = 0;

	return true;
}

update_status ModulePlayerUnit::Update()
{
	Animation* current_animation;
	SDL_Rect unitRect;
	current_animation = &playerUnitAnim;
	unitRect = current_animation->GetCurrentFrame();

	//angle += orbit_speed * delta_time;
	//x = center_x + radius * cos(angle);
	//y = center_y + radius * sin(angle);
	
	//int angle = 0;
	Uint32 tick_now = SDL_GetTicks();
	if (tick_now > last_tick)
	{
		delta_time = tick_now - last_tick;
		last_tick = tick_now;
	}

	//y height ball distante to player pos up and down = 18
	//x width unit right and left = 8

	orbitSpeed = 3.0f;

	if (App->input->keyboard[SDL_SCANCODE_A] == 1)
	{
		if(angle > 3.14)
		angle += (int)orbitSpeed * (delta_time / 1000);
	}
	if (App->input->keyboard[SDL_SCANCODE_D] == 1)
	{
		if (angle < 3.14)
			angle += (int)orbitSpeed * (delta_time / 1000);
	}
	if (angle > 6.28) angle = 0;


	Animation* currentPlayerFrameAnim;
	currentPlayerFrameAnim = &App->player->playerAnim;
	SDL_Rect* playerPosX = &currentPlayerFrameAnim->GetCurrentFrame();

	float  x = (App->player->position.x + 10) + cos(angle) * 32;//23.5;
	float y = (App->player->position.y - 7) - sin(angle) * 32;//24;
	//App->render->Blit(playerUnitBlue, 40 - unitRect.w/2 ,40 - unitRect.h/2, &unitRect, 0.0f);

	App->render->Blit(playerUnitBlue,  x - pivotArrayPositionsX[(int)current_animation->current_frame],  y - pivotArrayPositionsY[(int)current_animation->current_frame], &unitRect, 0.0f);

	return UPDATE_CONTINUE;
}

bool ModulePlayerUnit::CleanUp()
{

	return true;
}
