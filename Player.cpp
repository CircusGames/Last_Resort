#include "Application.h"
//#include "Globals.h"
#include "Player.h"
#include "ModuleInput.h"
//#include "ModuleRender.h"
#include "ModuleTextures.h"


bool Player::Init()
{
	// PLAYER 1
	if (this == App->player[0])
	{
		playerIndex = 0;

		//movement animation
		playerAnim.PushBack({ 0,3,32,13 }); //up2 - 0
		playerAnim.PushBack({ 32,3,32,13 }); //up1 - 1
		playerAnim.PushBack({ 64,3,32,12 }); //idle - 2
		playerAnim.PushBack({ 96,3,32,12 }); //down1 - 3
		playerAnim.PushBack({ 128,4,32,11 }); //down2 - 4

		//spawn anim rects
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
		spawnAnim.speed = 0.25f;
		spawnAnim.repeat = false;

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
		playerDyingAnim.speed = 0.3f;
		playerDyingAnim.repeat = false;


	}
	else // player2 rects
	{

		playerIndex = 1;

		// player 2 animation

		playerAnim.PushBack({ 103,15,32,11 }); //up2 - 0
		playerAnim.PushBack({ 63,17,32,11 }); //up1 - 1
		playerAnim.PushBack({ 24,27,32,11 }); //idle - 2
		playerAnim.PushBack({ 64,36,32,12 }); //down1 - 3
		playerAnim.PushBack({ 104,35,32,12 }); //down2 - 4

		//spawn anim rects
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
		spawnAnim.speed = 0.25f;
		spawnAnim.repeat = false;

		// player 2 death anim
		playerDyingAnim.PushBack({ 22,74,32,11 });
		playerDyingAnim.PushBack({ 62,74,32,12 });
		playerDyingAnim.PushBack({ 101,71,35,15 });
		playerDyingAnim.PushBack({ 143,68,40,18 });
		playerDyingAnim.PushBack({ 192,67,45,19 });
		playerDyingAnim.PushBack({ 14,90,51,20 });
		playerDyingAnim.PushBack({ 69,89,59,21 });
		playerDyingAnim.PushBack({ 131,88,62,22 });
		playerDyingAnim.PushBack({ 199,86,63,24 });
		playerDyingAnim.PushBack({ 15,112,63,23 });
		playerDyingAnim.PushBack({ 85,112,63,23 });
		playerDyingAnim.PushBack({ 160,113,60,24 });
		playerDyingAnim.PushBack({ 21,144,58,25 });
		playerDyingAnim.PushBack({ 90,144,54,26 });
		playerDyingAnim.PushBack({ 159,142,58,27 });
		playerDyingAnim.PushBack({ 21,182,60,28 });
		playerDyingAnim.PushBack({ 93,181,55,28 });
		playerDyingAnim.PushBack({ 163,179,54,28 });
		playerDyingAnim.PushBack({ 22,220,51,27 });
		playerDyingAnim.PushBack({ 88,221,50,21 });
		playerDyingAnim.speed = 0.3f;
		playerDyingAnim.repeat = false;

	}

	return true;
}


void Player::checkInput()
{
	//check player index
	if (this == App->player[0])
	{
		playerInput.moveRight = App->input->keyboard[SDL_SCANCODE_D] == KEY_REPEAT;
		playerInput.moveLeft = App->input->keyboard[SDL_SCANCODE_A] == KEY_REPEAT;
		playerInput.moveUp = App->input->keyboard[SDL_SCANCODE_W] == KEY_REPEAT;
		playerInput.moveDown = App->input->keyboard[SDL_SCANCODE_S] == KEY_REPEAT;
		playerInput.lockUnit = App->input->keyboard[SDL_SCANCODE_LSHIFT] == KEY_DOWN;
		playerInput.shot = App->input->keyboard[SDL_SCANCODE_SPACE] == KEY_DOWN;
		playerInput.chargedShot = App->input->keyboard[SDL_SCANCODE_SPACE] == KEY_REPEAT;
	}
	if (this == App->player[1])
	{
		playerInput.moveRight = App->input->keyboard[SDL_SCANCODE_RIGHT] == KEY_REPEAT;
		playerInput.moveLeft = App->input->keyboard[SDL_SCANCODE_LEFT] == KEY_REPEAT;
		playerInput.moveUp = App->input->keyboard[SDL_SCANCODE_UP] == KEY_REPEAT;
		playerInput.moveDown = App->input->keyboard[SDL_SCANCODE_DOWN] == KEY_REPEAT;
		playerInput.lockUnit = App->input->keyboard[SDL_SCANCODE_RSHIFT] == KEY_DOWN;
		playerInput.shot = App->input->keyboard[SDL_SCANCODE_RALT] == KEY_DOWN;
		playerInput.chargedShot = App->input->keyboard[SDL_SCANCODE_RALT] == KEY_REPEAT;
	}
}