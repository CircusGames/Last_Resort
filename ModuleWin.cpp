//#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleUI.h"
#include "ModuleWin.h"
#include "ModuleInput.h"
#include "ModuleFadeToBlack.h"
#include "Player.h"

ModuleWin::ModuleWin() 
{
	winInterfaceRect = { 0,0,256,256 };
	winBackgroundRect = {0,224,304,224};
}

/*ModuleUI::~ModuleWin()
{}*/

bool ModuleWin::Start()
{
	//loading textures

	winInterface = App->textures->Load("assets/Graphics/UI/Highscore.png");
	winBackground = App->textures->Load("assets/Graphics/Screens/Continue/Backgrounds.png");
	
	//changing gameState
	App->moduleUI->UI = gameplay_state::WIN;

	//restart player lives
	App->player[0]->lives = 3;
	App->player[1]->lives = 3;

	return true;
}

update_status ModuleWin::Update()
{
	App->render->Blit(winBackground, 0, 0, &winBackgroundRect, 0.0f);

	App->render->Blit(winInterface, 48, 16, &winInterfaceRect,0.0f); //

	if (App->input->keyboard[SDL_SCANCODE_RETURN] == KEY_DOWN)
	{
		App->fade->FadeToBlack(this, (Module*)App->gameTitle);
		App->player[0]->scoreReset = true;
		App->player[1]->scoreReset = true;
	}


	return UPDATE_CONTINUE;

}

bool ModuleWin::CleanUp()
{
	LOG("Unloading font textures");
	//unload font textures
	App->textures->Unload(winBackground);
	App->textures->Unload(winInterface);
	
	//changing gamePlay state
	App->moduleUI->UI = gameplay_state::NO;

	return true;
}

void ModuleWin::saveScore(int score)
{
	actualScore = score;
	
	for (int i = 0; i < 10; i++)
	{
		if (actualScore > allScores[i])
		{
				temp = allScores[i];
				allScores[i] = actualScore;
				actualScore = temp;
		}
		
	}

}

/*4000

7000
5000
3000
1000*/