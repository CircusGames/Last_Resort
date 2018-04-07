#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleInput.h"
#include "ModuleRender.h"
#include "ModulePlayer.h"


ModulePlayer::ModulePlayer()
{
	position.x = 40;
	position.y = 80;
	
	playerAnim.PushBack({ 0,3,32,13 }); //up2 - 0
	playerAnim.PushBack({ 32,3,32,13 }); //up1 - 1
	playerAnim.PushBack({ 64,3,32,12 }); //idle - 2
	playerAnim.PushBack({ 96,3,32,12 }); //down1 - 3
	playerAnim.PushBack({ 128,4,32,11 }); //down2 - 4

}

ModulePlayer::~ModulePlayer()
{}

// Load assets
bool ModulePlayer::Start()
{
	
	LOG("Loading player textures");
	bool ret = true;
	
	player = App->textures->Load("assets/player1_incomplete.png");

	frameIncrement = 2; //initializes speed positions frame rect array incrementer at "center" -> idle

	ignitionSpeed = 0.2f; //speed when accelerate
	releaseSpeed = 0.1f; //speed when releases direction keys to return to idle

	return ret;


}

// Update: draw background
update_status ModulePlayer::Update()
{
	float speed = 1.4f; //player position speed
	playerSpeed = speed; //resets the temporal incrementer to always Nicolas at the desired incrementer count
						  //new change direction starts incrementer at speed correct value (always same distances)

	Animation* current_animation = &playerAnim;
	
	//animation logic ---------------------------------------------------------------

	if (App->input->keyboard[SDL_SCANCODE_S] == 1) //while press down
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

	if (App->input->keyboard[SDL_SCANCODE_S] == 0 && (int)frameIncrement != 2)
	{
		if ((int)frameIncrement >= 2)
			frameIncrement -= releaseSpeed;
		
	}

	if (App->input->keyboard[SDL_SCANCODE_W] == 0 && (int)frameIncrement != 2)
	{
		if (frameIncrement < 2)
			frameIncrement += releaseSpeed;
	}

	//---------------------------------------------------------------------------
	//already, double check to imitate original animation behaviour (emulator)
	if (App->input->keyboard[SDL_SCANCODE_W] == 1 && App->input->keyboard[SDL_SCANCODE_S] == 0) //while press up
	{
		frameIncrement -= ignitionSpeed;
		if (frameIncrement <= 0)
			frameIncrement = 0;
	}

	//--------------------------------------------------------------------------------
	
	SDL_Rect r = *current_animation->frames[(int)frameIncrement]; //idle

	//--------------------------------------------------------------------------------

	//move player position (this section must be code optimized ----------------------
	//down move position
	if (App->input->keyboard[SDL_SCANCODE_S] == 1)
	{
			playerSpeed += speed;
			position.y += (int)playerSpeed;
			if (playerSpeed >= speed + 1) //returns correct value to cast incrementer
				playerSpeed = speed;

			if (position.y + (int)playerSpeed >= SCREEN_HEIGHT - 8) // 8 = player height/2 + required offset
				position.y = 216; //target max down player position (original game pixel)
	}

	//up move position, checks if not down to imitate original game (emulator) behaviour
	if (App->input->keyboard[SDL_SCANCODE_W] == 1 && App->input->keyboard[SDL_SCANCODE_S] == 0)
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
	if (App->input->keyboard[SDL_SCANCODE_D] == 1 && App->input->keyboard[SDL_SCANCODE_A] == 0)
	{
		playerSpeed += speed;
		position.x += (int)playerSpeed;
		if (playerSpeed >= speed + 1) //checks and assign correct value to int cast float incrementer
			playerSpeed = speed;		//and next cycle

		//playerSpeed at if is for assure the limits independent of speed value
		if (position.x + (int)playerSpeed >= 256) //0 = min y coordinate, 9=texture height/2 + offset
			position.x = 256; //target min y player position
	}

	//left move
	if (App->input->keyboard[SDL_SCANCODE_A] == 1)
	{
		playerSpeed += speed;
		position.x -= (int)playerSpeed;
		if (playerSpeed >= speed + 1) //checks and assign correct value to int cast float incrementer
			playerSpeed = speed;		//and next cycle

		if (position.x + (int)playerSpeed <= 0 + 16) //0 = min y coordinate, 9=texture height/2 + offset
			position.x = 16; //target min y player position
	}

	
	//--------------------------------------------------------------------------------


	//draw player --------------------------------------------------------------------

	App->render->Blit(player, position.x, position.y - (r.h / 2), &r, 0.0f);

	
	return UPDATE_CONTINUE;

}

/*bool ModulePlayer::CleanUp()
{
	jumpDown.cleanUp();
	jumpUpwards.cleanUp();
	kick.cleanUp();
	punch.cleanUp();
	backward.cleanUp();
	forward.cleanUp();
	idle.cleanUp();

	return true;
}*/