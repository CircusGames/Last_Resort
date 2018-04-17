#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleInput.h"
#include "ModuleRender.h"
#include "ModulePlayer.h"
#include "ModulePlayerUnit.h"
#include "ModuleParticles.h"

#define UNITANIMSPEED 0.25f

ModulePlayerUnit::ModulePlayerUnit()
{
	//needed rects for animations

	//animation 8 extra axis
	playerUnitAnim[15].PushBack({ 88,212,22,17 });
	playerUnitAnim[15].PushBack({ 66,212 , 22,17 });
	playerUnitAnim[15].PushBack({ 44,212 , 22,17 });
	playerUnitAnim[15].PushBack({ 22,212 , 22,17 });
	playerUnitAnim[15].PushBack({ 0,212 , 22,17 });
	playerUnitAnim[15].PushBack({ 229,189 , 22,17 });
	playerUnitAnim[15].PushBack({ 207,189 , 22,17 });
	playerUnitAnim[15].PushBack({ 185,189 , 22,17 });
	playerUnitAnim[15].speed = UNITANIMSPEED; //original framerate update
	//animation 8 basic axis
	playerUnitAnim[14].PushBack({ 164,189 , 21,21 });
	playerUnitAnim[14].PushBack({ 143,189 , 21,21 });
	playerUnitAnim[14].PushBack({ 122,189 , 21,21 });
	playerUnitAnim[14].PushBack({ 101,189 , 21,21 });
	playerUnitAnim[14].PushBack({ 80,189 , 21,21 });
	playerUnitAnim[14].PushBack({ 59,189 , 21,21 });
	playerUnitAnim[14].PushBack({ 38,189 , 21,21 });
	playerUnitAnim[14].PushBack({ 17,189 , 21,21 });
	playerUnitAnim[14].speed = UNITANIMSPEED;
	//animation 7 extra axis
	playerUnitAnim[13].PushBack({ 0,189 , 17,23 });
	playerUnitAnim[13].PushBack({ 230,166 , 17,23 });
	playerUnitAnim[13].PushBack({ 213,166 , 17,23 });
	playerUnitAnim[13].PushBack({ 196,166 , 17,23 });
	playerUnitAnim[13].PushBack({ 179,166 , 17,23 });
	playerUnitAnim[13].PushBack({ 162,166 , 17,23 });
	playerUnitAnim[13].PushBack({ 145,166 , 17,23 });
	playerUnitAnim[13].PushBack({ 128,166 , 17,23 });
	playerUnitAnim[13].speed = UNITANIMSPEED;
	//animation 7 basic axis
	playerUnitAnim[12].PushBack({ 112,166 , 16,22 });
	playerUnitAnim[12].PushBack({ 96,166 , 16,22 });
	playerUnitAnim[12].PushBack({ 80,166 , 16,22 });
	playerUnitAnim[12].PushBack({ 64,166 , 16,22 });
	playerUnitAnim[12].PushBack({ 48,166 , 16,22 });
	playerUnitAnim[12].PushBack({ 32,166 , 16,22 });
	playerUnitAnim[12].PushBack({ 16,166 , 16,22 });
	playerUnitAnim[12].PushBack({ 0,166 , 16,22 });
	playerUnitAnim[12].speed = UNITANIMSPEED;
	//animation 6 extra axis
	playerUnitAnim[11].PushBack({ 224,143 , 17,23 });
	playerUnitAnim[11].PushBack({ 207,143 , 17,23 });
	playerUnitAnim[11].PushBack({ 190,143 , 17,23 });
	playerUnitAnim[11].PushBack({ 173,143 , 17,23 });
	playerUnitAnim[11].PushBack({ 156,143 , 17,23 });
	playerUnitAnim[11].PushBack({ 139,143 , 17,23 });
	playerUnitAnim[11].PushBack({ 122,143 , 17,23 });
	playerUnitAnim[11].PushBack({ 105,143 , 17,23 });
	playerUnitAnim[11].speed = UNITANIMSPEED;
	//animation 6 basic axis
	playerUnitAnim[10].PushBack({ 84,143 , 21,21 });
	playerUnitAnim[10].PushBack({ 63,143 , 21,21 });
	playerUnitAnim[10].PushBack({ 42,143 , 21,21 });
	playerUnitAnim[10].PushBack({ 21,143 , 21,21 });
	playerUnitAnim[10].PushBack({ 0,143 , 21,21 });
	playerUnitAnim[10].PushBack({ 218,122 , 21,21 });
	playerUnitAnim[10].PushBack({ 197,122 , 21,21 });
	playerUnitAnim[10].PushBack({ 176,122 , 21,21 });
	playerUnitAnim[10].speed = UNITANIMSPEED;
	//animation 5 extra axis
	playerUnitAnim[9].PushBack({ 154,122 , 22,17 });
	playerUnitAnim[9].PushBack({ 132,122 , 22,17 });
	playerUnitAnim[9].PushBack({ 110,122 , 22,17 });
	playerUnitAnim[9].PushBack({ 88,122 , 22,17 });
	playerUnitAnim[9].PushBack({ 66,122 , 22,17 });
	playerUnitAnim[9].PushBack({ 44,122 , 22,17 });
	playerUnitAnim[9].PushBack({ 22,122 , 22,17 });
	playerUnitAnim[9].PushBack({ 0,122 , 22,17 });
	playerUnitAnim[9].speed = UNITANIMSPEED;
	//animation 5 basic axis
	playerUnitAnim[8].PushBack({ 220,105 , 22,16 });
	playerUnitAnim[8].PushBack({ 198,105 , 22,16 });
	playerUnitAnim[8].PushBack({ 176,105 , 22,16 });
	playerUnitAnim[8].PushBack({ 154,105 , 22,16 });
	playerUnitAnim[8].PushBack({ 132,105 , 22,16 });
	playerUnitAnim[8].PushBack({ 110,105 , 22,16 });
	playerUnitAnim[8].PushBack({ 88, 105 , 22,16 });
	playerUnitAnim[8].PushBack({ 66,105 , 22,16 });
	playerUnitAnim[8].speed = UNITANIMSPEED;
	//animation 4 extra axis
	playerUnitAnim[7].PushBack({ 44,105 , 22,17 });
	playerUnitAnim[7].PushBack({ 22,105 , 22,17 });
	playerUnitAnim[7].PushBack({ 0,105 , 22,17 });
	playerUnitAnim[7].PushBack({ 214,84 , 22,17 });
	playerUnitAnim[7].PushBack({ 192,84 , 22,17 });
	playerUnitAnim[7].PushBack({ 170,84 , 22,17 });
	playerUnitAnim[7].PushBack({ 148,84 , 22,17 });
	playerUnitAnim[7].PushBack({ 126,84 , 22,17 });
	playerUnitAnim[7].speed = UNITANIMSPEED;
	//animation 4 basic axis
	playerUnitAnim[6].PushBack({ 105,84 , 21,21 });
	playerUnitAnim[6].PushBack({ 84,84 , 21,21 });
	playerUnitAnim[6].PushBack({ 63,84 , 21,21 });
	playerUnitAnim[6].PushBack({ 42,84 , 21,21 });
	playerUnitAnim[6].PushBack({ 21,84 , 21,21 });
	playerUnitAnim[6].PushBack({ 0,84 , 21,21 });
	playerUnitAnim[6].PushBack({ 221,61 , 21,21 });
	playerUnitAnim[6].PushBack({ 200,61 , 21,21 });
	playerUnitAnim[6].speed = UNITANIMSPEED;
	//animation 3 extra axis
	playerUnitAnim[5].PushBack({ 183,61 , 17,23 });
	playerUnitAnim[5].PushBack({ 166,61 , 17,23 });
	playerUnitAnim[5].PushBack({ 149,61 , 17,23 });
	playerUnitAnim[5].PushBack({ 132,61 , 17,23 });
	playerUnitAnim[5].PushBack({ 115,61 , 17,23 });
	playerUnitAnim[5].PushBack({ 98,61 , 17,23 });
	playerUnitAnim[5].PushBack({ 81,61 , 17,23 });
	playerUnitAnim[5].PushBack({ 64,61 , 17,23 });
	playerUnitAnim[5].speed = UNITANIMSPEED;
	//animation 3 basic axis (pointing UP)
	playerUnitAnim[4].PushBack({ 48,61 , 16,22 });
	playerUnitAnim[4].PushBack({ 32,61 , 16,22 });
	playerUnitAnim[4].PushBack({ 16,61 , 16,22 });
	playerUnitAnim[4].PushBack({ 0,61 , 16,22 });
	playerUnitAnim[4].PushBack({ 226,38 , 16,22 });
	playerUnitAnim[4].PushBack({ 210,38 , 16,22 });
	playerUnitAnim[4].PushBack({ 194,38 , 16,22 });
	playerUnitAnim[4].PushBack({ 178,38 , 16,22 });
	playerUnitAnim[4].speed = UNITANIMSPEED;
	//animation 2 extra axis
	playerUnitAnim[3].PushBack({ 161,38 , 17,23 });
	playerUnitAnim[3].PushBack({ 144,38 , 17,23 });
	playerUnitAnim[3].PushBack({ 127,38 , 17,23 });
	playerUnitAnim[3].PushBack({ 110,38 , 17,23 });
	playerUnitAnim[3].PushBack({ 93,38 , 17,23 });
	playerUnitAnim[3].PushBack({ 76,38 , 17,23 });
	playerUnitAnim[3].PushBack({ 59,38 , 17,23 });
	playerUnitAnim[3].PushBack({ 42,38 , 17,23 });
	playerUnitAnim[3].speed = UNITANIMSPEED;
	//animation 2 basic axis
	playerUnitAnim[2].PushBack({ 21,38 , 21,21 });
	playerUnitAnim[2].PushBack({ 0,38 , 21,21 });
	playerUnitAnim[2].PushBack({ 215,17 , 21,21 });
	playerUnitAnim[2].PushBack({ 194,17 , 21,21 });
	playerUnitAnim[2].PushBack({ 173,17 , 21,21 });
	playerUnitAnim[2].PushBack({ 152,17 , 21,21 });
	playerUnitAnim[2].PushBack({ 131,17 , 21,21 });
	playerUnitAnim[2].PushBack({ 110,17 , 21,21 });
	playerUnitAnim[2].speed = UNITANIMSPEED;
	//animation 1 extra axis
	playerUnitAnim[1].PushBack({ 88,17 , 22,17 });
	playerUnitAnim[1].PushBack({ 66,17 , 22,17 });
	playerUnitAnim[1].PushBack({ 44,17 , 22,17 });
	playerUnitAnim[1].PushBack({ 22,17 , 22,17 });
	playerUnitAnim[1].PushBack({ 0,17 , 22,17 });
	playerUnitAnim[1].PushBack({ 220,0 , 22,17 });
	playerUnitAnim[1].PushBack({ 198,0 , 22,17 });
	playerUnitAnim[1].PushBack({ 176,0 , 22,17 });
	playerUnitAnim[1].speed = UNITANIMSPEED;
	//Animation 1 basic axis (pointing right (animation 1 (spawn animation cycle))
	playerUnitAnim[0].PushBack({ 154,0 , 22,16 });
	playerUnitAnim[0].PushBack({ 132,0 , 22,16 });
	playerUnitAnim[0].PushBack({ 110,0 , 22,16 });
	playerUnitAnim[0].PushBack({ 88,0 , 22,16 });
	playerUnitAnim[0].PushBack({ 66,0 , 22,16 });
	playerUnitAnim[0].PushBack({ 44,0 , 22,16 });
	playerUnitAnim[0].PushBack({ 22,0 , 22,16 });
	playerUnitAnim[0].PushBack({ 0,0 , 22,16 });
	playerUnitAnim[0].speed = UNITANIMSPEED;

}

ModulePlayerUnit::~ModulePlayerUnit() {}

/*bool ModulePlayerUnit::Init()
{

	return true;
}*/

bool ModulePlayerUnit::Start()
{
	LOG("Starting playerUnit Module");

	
	playerUnitBlue = App->textures->Load("assets/Graphics/Player/blueUnit.png");

	//delta calculations
	orbitSpeed = 1.0f;
	last_tick = 0;

	//links the animation to 0 index at every module Start
	angle = 0;
	currentUnitAnim = &playerUnitAnim[0];
	frameIncrement = 0; //starts at 0 index pos (spawn direction animation)

	unitLocked = false; //locks or unlocks circular movement

	return true;
}

update_status ModulePlayerUnit::PreUpdate()
{
	//locks and unlocks unit movement control
	if (App->input->keyboard[SDL_SCANCODE_LSHIFT] == KEY_STATE::KEY_DOWN)
	{
		if (unitLocked) unitLocked = false;
		else unitLocked = true;
	}

	//PlayerUnit movement logic and input -----------------------------------------------------------------

		//angle += orbit_speed * delta_time;
		//x = center_x + radius * cos(angle);
		//y = center_y + radius * sin(angle);

		Uint32 tick_now = SDL_GetTicks();
		if (tick_now > last_tick)
		{
			delta_time = tick_now - last_tick;
			last_tick = tick_now;
		}

		//y height ball distante to player pos up and down = 18
		//x width unit right and left = 8

	//if the unit is not locked, permits movement calculations
	if(!unitLocked)
	{ 

		orbitSpeed = 6.5f;

		//linear moves ----------------------------------------------------------------------------------------

		if (App->input->keyboard[SDL_SCANCODE_A] == KEY_STATE::KEY_REPEAT &&
			App->input->keyboard[SDL_SCANCODE_S] == KEY_STATE::KEY_IDLE &&
			App->input->keyboard[SDL_SCANCODE_W] == KEY_STATE::KEY_IDLE) //constrains upper left diagonal case
		{
			if (angle >= 3.14f)
			{
				angle += (int)orbitSpeed * (delta_time / 1000);
			}
			if (angle < 3.14f && angle >= 0) //returns upwards
			{
				angle -= (int)orbitSpeed * (delta_time / 1000);
			}
		}

		if (App->input->keyboard[SDL_SCANCODE_D] == KEY_STATE::KEY_REPEAT && //if right
			App->input->keyboard[SDL_SCANCODE_A] == KEY_STATE::KEY_IDLE &&   //and not left (original opposite direction priority)
			App->input->keyboard[SDL_SCANCODE_W] == KEY_STATE::KEY_IDLE &&   //and not up (diagonal case)
			App->input->keyboard[SDL_SCANCODE_S] == KEY_STATE::KEY_IDLE)     //and not down right
		{
			if (angle > 3.14f && angle < 6.28f)
			{
				angle -= (int)orbitSpeed * (delta_time / 1000);
			}
			if (angle < 3.14f)
			{
				angle += (int)orbitSpeed * (delta_time / 1000);
			}

		}

		if (angle >= 6.28f) angle = 0;
		else if (angle < 0) angle = 6.28f; //if we go under 0, full circle

		if (App->input->keyboard[SDL_SCANCODE_W] == KEY_STATE::KEY_REPEAT &&
			App->input->keyboard[SDL_SCANCODE_S] == KEY_STATE::KEY_IDLE   && //constrains original opposite up and down case
			App->input->keyboard[SDL_SCANCODE_D] == KEY_STATE::KEY_IDLE   &&
			App->input->keyboard[SDL_SCANCODE_A] == KEY_STATE::KEY_IDLE)    //constrains upper left diagonal case
		{

			if (angle < 1.57f && angle >= 0) //|| angle > 4.71f) //separated to avoid clack
			{
				angle -= (int)orbitSpeed * (delta_time / 1000);
			}
			//force the check to avoid mini Nicolas
			if (angle < 0) angle = 6.28f; //if we go under 0, full circle

			if (angle > 4.71f) //separate check to workaround mini Nicolas
			{
				angle -= (int)orbitSpeed * (delta_time / 1000);
			}

			if (angle >= 1.57f && angle <= 4.71)
			{
				angle += (int)orbitSpeed * (delta_time / 1000);
			}
		}

		if (App->input->keyboard[SDL_SCANCODE_S] == KEY_STATE::KEY_REPEAT &&
			App->input->keyboard[SDL_SCANCODE_A] == KEY_STATE::KEY_IDLE && //constrains diagonal down and left
			App->input->keyboard[SDL_SCANCODE_D] == KEY_STATE::KEY_IDLE) //constrains diagonal down and right
		{
			if (angle > 1.57f && angle < 4.71f)
			{
				angle -= (int)orbitSpeed * (delta_time / 1000);
			}

			if (angle < 1.57f && angle >= 0 || angle >= 4.71f)
			{
				angle += (int)orbitSpeed * (delta_time / 1000);
			}
		}
		// ------------------------------------------------------------------------------------------------

		//diagonal moves ----------------------------------------------------------------------------------

		//down and left case
		if (App->input->keyboard[SDL_SCANCODE_S] == KEY_STATE::KEY_REPEAT &&
			App->input->keyboard[SDL_SCANCODE_A] == KEY_STATE::KEY_REPEAT)
		{
			if (angle > (1.25f * 3.14f) && angle > 0)//4.71f && angle > 0)
			{
				angle += (int)orbitSpeed * (delta_time / 1000);
			}
			if (angle < 1.57f && angle >= 0 && angle < 1.57f / 2)
			{
				angle += (int)orbitSpeed * (delta_time / 1000);
			}
			if (angle < (1.25f * 3.14f) && angle > 1.57f / 2)
			{
				angle -= (int)orbitSpeed * (delta_time / 1000);
			}
		}

		//down and right case
		if (App->input->keyboard[SDL_SCANCODE_S] == KEY_STATE::KEY_REPEAT &&
			App->input->keyboard[SDL_SCANCODE_D] == KEY_STATE::KEY_REPEAT)
		{
			if (angle > (1.75f * 3.14f) && angle > 0)
			{
				angle += (int)orbitSpeed * (delta_time / 1000);
			}
			if (angle < 0.75f * 3.14f) //(3/4*pi) quadrant
			{
				angle += (int)orbitSpeed * (delta_time / 1000);
			}
			if (angle < (1.75f * 3.14f) && angle >(0.75f * 3.14f))
			{
				angle -= (int)orbitSpeed * (delta_time / 1000);
			}
		}

		//up and left case
		if (App->input->keyboard[SDL_SCANCODE_W] == KEY_STATE::KEY_REPEAT &&
			App->input->keyboard[SDL_SCANCODE_A] == KEY_STATE::KEY_REPEAT)
		{
			if (angle < (0.75f * 3.14f) && angle > 0)
			{
				angle -= (int)orbitSpeed * (delta_time / 1000);
			}

			if (angle >= 6.28f) angle = 0; //force check to avoid Nicolas
			else if (angle < 0) angle = 6.28f; //if we go under 0, full circle

			if (angle <= 0 || angle >(1.75f * 3.14f)) // 7/4*pi quadrant
			{
				angle -= (int)orbitSpeed * (delta_time / 1000);
			}
			if (angle > (0.75f* 3.14f) && angle < (1.75f * 3.14f))
			{
				angle += (int)orbitSpeed * (delta_time / 1000);
			}
		}

		//up and right case
		if (App->input->keyboard[SDL_SCANCODE_W] == KEY_STATE::KEY_REPEAT &&
			App->input->keyboard[SDL_SCANCODE_D] == KEY_STATE::KEY_REPEAT)
		{
			if (angle > (1.75f / 2) && angle < 1.25f * 3.14f)
			{
				angle += (int)orbitSpeed * (delta_time / 1000);
			}
			if (angle <= (1.75f / 2) && angle > 0)
			{
				angle -= (int)orbitSpeed * (delta_time / 1000);
			}
			if (angle < 0) angle = 6.28f; //if we go under 0, full circle
										  //if (angle >= 6.28f) angle = 0; //force check to avoid Nicolas
			if (angle <= 6.28f && angle >(1.25f * 3.14f))
			{
				angle -= (int)orbitSpeed * (delta_time / 1000);
			}

		}
	}

	// -------------------------------------------------------------------------------------------------

	return UPDATE_CONTINUE;
}

update_status ModulePlayerUnit::Update()
{

	//animation logic ----------------------------------------------------------------------------------
	//the ball moves independent of the position of the angle, only consider direction of
	//pulsations direction (and remember on a temporal value the last pulsation to stuck the animation
	//to its desired animation position (at module start links to position of spawn (animation index 0)
	
	SDL_Rect unitRect;
	unitRect = currentUnitAnim->GetCurrentFrame();

	float animationRotationSpeed = 0.9f;
	
	//if we press up
	if (App->input->keyboard[SDL_SCANCODE_S] == KEY_STATE::KEY_REPEAT)
	{	
		//index 4 is the unit pointing up and 12 unit pointing down, the two directions to consider on this axis
		if (frameIncrement > 4 && frameIncrement < 12) //if we are on a superior animation, we go on the short way
		{											   //original game behaviour
			frameIncrement -= animationRotationSpeed; 
		}
		else
		{	//the short way in some cases MUST consider 0 pos...
			frameIncrement += animationRotationSpeed;
			if ((int)frameIncrement >= MAX_ANIMS - 1) frameIncrement = 0;
		}
		if ((int)frameIncrement == 4) frameIncrement = 4; //stuck on the correct MAX frame
	}
	//if we press down
	if (App->input->keyboard[SDL_SCANCODE_W] == KEY_STATE::KEY_REPEAT &&
		App->input->keyboard[SDL_SCANCODE_S] == KEY_STATE::KEY_IDLE) //original game behaviour priority
	{
		if (frameIncrement > 12 || frameIncrement < 4) 
		{					   
			frameIncrement -= animationRotationSpeed;
			if ((int)frameIncrement <= 0) frameIncrement = MAX_ANIMS - 1; //when we reach max anims index
		}
		else if(frameIncrement >= 4) //opposite direction
		{
			frameIncrement += animationRotationSpeed;
		}
		if ((int)frameIncrement == 12) frameIncrement = 12; //stuck on the correct MAX frame
	}
	//if we press right
	if (App->input->keyboard[SDL_SCANCODE_D] == KEY_STATE::KEY_REPEAT &&
		App->input->keyboard[SDL_SCANCODE_A] == KEY_STATE::KEY_IDLE) //double check for original game priority
	{
		//index 8 pointing left , index 0 pointing right
		if (frameIncrement > 8) frameIncrement -= animationRotationSpeed;
		else frameIncrement += animationRotationSpeed;
		if ((int)frameIncrement == 8) frameIncrement = 8;
	}
	//if we press left
	if (App->input->keyboard[SDL_SCANCODE_A] == KEY_STATE::KEY_REPEAT)
	{
		if (frameIncrement < 8 && frameIncrement > 0) frameIncrement -= animationRotationSpeed;
		else frameIncrement += animationRotationSpeed;
		if ((int)frameIncrement >= MAX_ANIMS - 1) frameIncrement = 0;
	}
	// ------------------------------------------------------------------------------------------------

	// Basic shooting ---------------------------------------------------------------------------------

	if (App->input->keyboard[SDL_SCANCODE_SPACE] == KEY_DOWN)
	{
		if ((int)frameIncrement == 0)
		{
			shotVectorSpeed = { 2,0 }; //speed on X and Y coordinates
			//App->particles->AddParticle{};
		}
			
	}


	//draw the unit -----------------------------------------------------------------------------------

	currentUnitAnim = &playerUnitAnim[(int)frameIncrement]; //prepares the correct draw 
	
	currentUnitAnim->current_frame = lastFrame; //recovery last animation frame and continues the flow
	unitRect = currentUnitAnim->GetCurrentFrame();
	lastFrame = currentUnitAnim->current_frame; //and stores the new "last frame"

	playerPos.x = (App->player->position.x + 9) + cos(angle) * 31.5f;//orginal distance // 9
	playerPos.y = (App->player->position.y - 7) - sin(angle) * 32;//24; // 7
	
	App->render->Blit(playerUnitBlue,
		playerPos.x - pivotArrayPositionsX[(int)frameIncrement],
		playerPos.y - pivotArrayPositionsY[(int)frameIncrement],
		&unitRect);

	// ------------------------------------------------------------------------------------------------
	return UPDATE_CONTINUE;
}

bool ModulePlayerUnit::CleanUp()
{
	//unload textures
	App->textures->Unload(playerUnitBlue);

	return true;
}
