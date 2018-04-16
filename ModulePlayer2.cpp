#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleInput.h"
#include "ModuleRender.h"
#include "ModulePlayer2.h"
#include "ModuleCollision.h"
#include "ModulePlayer2Unit.h"
#include "ModuleParticles.h"
#include "ModuleAudio.h"
#include "ModuleFadeToBlack.h"


ModulePlayer2::ModulePlayer2()
{
	position.x = 40;
	position.y = 120;

	//spawn anim
	spawnAnim.PushBack({ 0,122,111,1 }); //0,79 
	spawnAnim.PushBack({ 6,125,105,2 }); //13,80 
	spawnAnim.PushBack({ 1,127,76,4 }); //12,79 
	spawnAnim.PushBack({ 0,131,74,8 }); //12,76 
	spawnAnim.PushBack({ 2,142,62,15 }); //8,72
	spawnAnim.PushBack({ 2,171,62,15 }); //8,73
	spawnAnim.PushBack({ 13,193,51,16 }); //16,72
	spawnAnim.PushBack({ 13,219,51,16 }); //16,72
	spawnAnim.PushBack({ 64,143,64,16 }); //8,72
	spawnAnim.PushBack({ 64,164,64,25 }); //8,67
	spawnAnim.PushBack({ 71,188,57,25 }); //15,67
	spawnAnim.PushBack({ 72,214,56,25 }); //16,67
	spawnAnim.PushBack({ 156,143,36,19 }); //36,71
	spawnAnim.PushBack({ 160,171,32,15 }); //40,73        
	spawnAnim.speed = 0.143f;
	spawnAnim.repeat = false;


	//movement anim
	playerAnim.PushBack({ 0,3,32,13 }); //up2 - 0
	playerAnim.PushBack({ 32,3,32,13 }); //up1 - 1
	playerAnim.PushBack({ 64,3,32,12 }); //idle - 2
	playerAnim.PushBack({ 96,3,32,12 }); //down1 - 3
	playerAnim.PushBack({ 128,4,32,11 }); //down2 - 4


										  //Player Dying animation
	playerDyingAnim.PushBack({ 18,20,37,16 });
	playerDyingAnim.PushBack({ 14,37,41,16 });
	playerDyingAnim.PushBack({ 9,53,46,17 });
	playerDyingAnim.PushBack({ 3,70,52,17 });
	playerDyingAnim.PushBack({ 2,87,53,15 });
	playerDyingAnim.PushBack({ 0,104,55,16 });
	playerDyingAnim.PushBack({ 57,21,53,15 });
	playerDyingAnim.PushBack({ 58,36,52,16 });
	playerDyingAnim.PushBack({ 55,53,55,17 });
	playerDyingAnim.PushBack({ 56,70,54,17 });
	playerDyingAnim.PushBack({ 55,88,55,16 });
	playerDyingAnim.PushBack({ 57,104,53,17 });
	playerDyingAnim.PushBack({ 112,21,53,16 });
	playerDyingAnim.PushBack({ 114,38,51,16 });
	playerDyingAnim.PushBack({ 118,54,47,15 });
	playerDyingAnim.PushBack({ 118,70,47,16 });
	playerDyingAnim.PushBack({ 124,90,41,12 });
	playerDyingAnim.PushBack({ 128,108,37,10 });
}




ModulePlayer2::~ModulePlayer2()
{}

// Load assets
bool ModulePlayer2::Start()
{

	LOG("Loading player textures");
	bool ret = true;

	player2 = App->textures->Load("assets/Graphics/Player/player1_incomplete.png");

	//restart player positions for next time playerModule call

	position.x = 40;
	position.y = 120;

	//player collision rect
	playerCollider = App->collision->AddCollider({ position.x, position.y, 32, 12 }, COLLIDER_PLAYER, this);

	frameIncrement = 2; //initializes speed positions frame rect array incrementer at "center" -> idle

	ignitionSpeed = 0.2f; //speed when accelerate
	releaseSpeed = 0.1f; //speed when releases direction keys to return to idle

						 //load necessary fx wavs

						 // ---------------------

						 //for new gameLoops
						 //checks if the player state is normal, if is, spawn condition
	if (player_step == player_state::normal)
		player_step = player_state::spawn;

	return ret;


}

// Update: draw background
update_status ModulePlayer2::Update()
{
	Animation* current_animation = &playerAnim;
	SDL_Rect r;

	if (player_step == player_state::spawn)
	{
		current_animation = &spawnAnim;
		r = current_animation->GetCurrentFrame();
		if (current_animation->finish)
		{
			player_step = player_state::normal;
			current_animation->finish = false; //and resets condition
			current_animation->current_frame = 0;
		}
	}

	else
	{
		//for now activates playerUnit for testing here
		if (!App->player2Unit->IsEnabled())
		{
			App->player2Unit->Enable();
		}

		float speed = 1.4f; //player position speed
		playerSpeed = speed; //resets the temporal incrementer to always Nicolas at the desired incrementer count
							 //new change direction starts incrementer at speed correct value (always same distances)

							 //App->render->Blit(player,300, 50, &spawnAnim.GetCurrentFrame());

							 //Animation* current_animation = &playerAnim;

							 //animation logic ---------------------------------------------------------------

		if (App->input->keyboard[SDL_SCANCODE_DOWN] == KEY_STATE::KEY_REPEAT) //while press down
		{
			frameIncrement += ignitionSpeed;
			if (frameIncrement >= 5)
				frameIncrement = 4.99f;
		}

		//for quickly directions change, release  to turn idle speed incrementer doesn't affect
		//yet, and go to top up animation (or wherever we are) at ignition speed (normal/fast direction change)
		//and only if the two keys are released, return at release speed to idle position
		//we check on separate for fast direction change (no key release = to estabilization spaceship)

		//----ship estabilization check (return to idle when release up or down) ---

		if (App->input->keyboard[SDL_SCANCODE_DOWN] == KEY_STATE::KEY_IDLE && (int)frameIncrement != 2)
		{
			if ((int)frameIncrement >= 2)
				frameIncrement -= releaseSpeed;

		}

		if (App->input->keyboard[SDL_SCANCODE_UP] == KEY_STATE::KEY_IDLE && (int)frameIncrement != 2)
		{
			if (frameIncrement < 2)
				frameIncrement += releaseSpeed;
		}

		//---------------------------------------------------------------------------
		//already, double check to imitate original animation behaviour (emulator)
		if (App->input->keyboard[SDL_SCANCODE_UP] == KEY_STATE::KEY_REPEAT &&
			App->input->keyboard[SDL_SCANCODE_DOWN] == KEY_STATE::KEY_IDLE) //while press up
		{
			frameIncrement -= ignitionSpeed;
			if (frameIncrement <= 0)
				frameIncrement = 0;
		}

		//--------------------------------------------------------------------------------

		r = current_animation->frames[(int)frameIncrement]; //idle

															//--------------------------------------------------------------------------------

															//move player position (this section must be code optimized ----------------------
															//down move position
		if (App->input->keyboard[SDL_SCANCODE_DOWN] == KEY_STATE::KEY_REPEAT)
		{
			playerSpeed += speed;
			position.y += (int)playerSpeed;
			if (playerSpeed >= speed + 1) //returns correct value to cast incrementer
				playerSpeed = speed;

			if (position.y + (int)playerSpeed >= SCREEN_HEIGHT - 8) // 8 = player height/2 + required offset
				position.y = 216; //target max down player position (original game pixel)
		}

		//up move position, checks if not down to imitate original game (emulator) behaviour
		if (App->input->keyboard[SDL_SCANCODE_UP] == KEY_STATE::KEY_REPEAT &&
			App->input->keyboard[SDL_SCANCODE_DOWN] == KEY_STATE::KEY_IDLE)
		{

			playerSpeed += speed;
			position.y -= (int)playerSpeed;
			if (playerSpeed >= speed + 1) //checks and assign correct value to int cast float incrementer
				playerSpeed = speed;	  //and next cycle

			if (position.y + (int)playerSpeed <= 0 + 8) //0 = min y coordinate, 8 = texture height/2 + offset
				position.y = 8; //target min y player position

		}

		//---------------------------------------------------------------------------------

		//right move, doble check for imitate original (emulator) behaviour
		if (App->input->keyboard[SDL_SCANCODE_RIGHT] == KEY_STATE::KEY_REPEAT &&
			App->input->keyboard[SDL_SCANCODE_LEFT] == KEY_STATE::KEY_IDLE)
		{
			playerSpeed += speed;
			position.x += (int)playerSpeed;
			if (playerSpeed >= speed + 1) //checks and assign correct value to int cast float incrementer
				playerSpeed = speed;		//and next cycle

											//playerSpeed at if is for assure the limits independent of speed value
											//if (position.x + (int)playerSpeed >= 256) //0 = min y coordinate, 9=texture height/2 + offset
											//position.x = 256; //target min y player position

			if (position.x > (abs(App->render->camera.x) / SCREEN_SIZE) + SCREEN_WIDTH - 30)
			{
				position.x = (abs(App->render->camera.x) / SCREEN_SIZE) + SCREEN_WIDTH - 30;// 16 = 1/2 player width + 16 offset original game
			}
		}

		//left move
		if (App->input->keyboard[SDL_SCANCODE_LEFT] == KEY_STATE::KEY_REPEAT)
		{
			playerSpeed += speed;
			position.x -= (int)playerSpeed;
			if (playerSpeed >= speed + 1) //checks and assign correct value to int cast float incrementer
				playerSpeed = speed;		//and next cycle

											/*if (position.x + (int)playerSpeed <= 0 + 16) //0 = min y coordinate, 9=texture height/2 + offset
											position.x = 16; //target min y player position*/
			if (position.x < abs(App->render->camera.x) / SCREEN_SIZE + 30)
			{
				position.x = abs(App->render->camera.x) / SCREEN_SIZE + 30;// 16 = 1/2 player width + 16 offset original game
			}
		}

		cameraPosition = abs(App->render->camera.x / 3);
		//--------------------------------------------------------------------------------

		//if player press keys of particles emitters

		if (App->input->keyboard[SDL_SCANCODE_SPACE] == KEY_STATE::KEY_DOWN)
		{
			LOG("Beam!");
			App->particles->AddParticle(App->particles->beamSmoke, position.x + 16, position.y - 6, COLLIDER_NONE);

			App->particles->AddParticle(App->particles->beam, position.x + 14, position.y - 4, COLLIDER_PLAYER_SHOT); //, "shot");

		}
	}

	//update player collider to its position -----------------------------------------

	playerCollider->SetPos(position.x - 16, position.y - 6);

	//draw player --------------------------------------------------------------------

	App->render->Blit(player2, position.x - (r.w / 2), position.y - (r.h / 2), &r, 1.0f);

	//if (App->playerUnit->IsEnabled()) App->playerUnit->playerPos.x = position.x;


	return UPDATE_CONTINUE;

}

void ModulePlayer2::OnCollision(Collider* collider1, Collider* collider2)
{
	//if (!Collided)
	//{
	this->Disable();
	App->player2Unit->Disable();

	if (playerCollider != nullptr)
		this->playerCollider->to_delete = true;

	//Destroyed();

	//Collided = true;
	//}
	App->fade->FadeToBlack((Module*)App->scene_lvl1, (Module*)App->gameOverScreen);
}

bool ModulePlayer2::CleanUp()
{
	App->textures->Unload(player2);

	return true;
}