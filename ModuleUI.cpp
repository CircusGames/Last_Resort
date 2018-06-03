

//still much work to do in this module , 00001 alpha -------------------------------------

#define _CRT_SECURE_NO_WARNINGS

#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleUI.h"
//#include "ModulePlayer.h"

#include "Player.h"

#include "ModuleWin.h"
// ---------------------
#include "ModuleInput.h"
#include "ModuleFadeToBlack.h"
#include "ModulePlayerUnit.h"

//needed standard headers for strings functions
#include<string.h>
#include<stdio.h>

// Constructor
ModuleUI::ModuleUI() : Module()
{}

// Destructor
ModuleUI::~ModuleUI()
{}

bool ModuleUI::Start()
{
	//loading fonts typo's
	lastResortBlueFont = App->moduleUI->Load("assets/Graphics/UI/blue_chars.png", "0123456789[]abcdefghijklmnopqrstuvwxyz _.,&#", 1);
	redNumbers = App->moduleUI->Load("assets/Graphics/UI/red_numbers.png", "0123456789 ", 1);
	uiTexture = App->textures->Load("assets/Graphics/UI/UI.png");

	App->audio->LoadAudio("assets/Audio/SFX/Screens/001. Coin inserted.wav", "inserted", SFX);

	return true;
}

bool ModuleUI::CleanUp()
{
	LOG("Unloading font textures");
	//unload font textures
	UnLoad(lastResortBlueFont);
	UnLoad(redNumbers);

	App->textures->Unload(uiTexture);

	return true;
}

update_status ModuleUI::PostUpdate()//Update()
{
	unit1Pow = 7 * App->playerUnit[0]->charge; //CHARGER
	unit2Pow = 7 * App->playerUnit[1]->charge; //CHARGER 2

	if(unit1Pow>64)
		powBarRect = { 96,16,64, 3 };
	else
		powBarRect = { 96,16,unit1Pow, 3 };

	if (unit2Pow>64)
		powBar2Rect = { 96,16,64, 3 };
	else
		powBar2Rect = { 96,16,unit2Pow, 3 };
	
	
	//compute the score //provisional...
	App->winScreen->saveScore(score);

	lives1 = App->player[0]->lives;
	score = App->player[0]->playerScore;

	lives2 = App->player[1]->lives;
	score2 = App->player[1]->playerScore;

	//prints scene UI
	if (UI == gameplay_state::SCENE)
	{
		if (App->player[0]->IsEnabled())
		{
			//draw lives
			sprintf_s(score_text, 10, "%6i%d", zero, lives1);
			BlitText(0, 24, lastResortBlueFont, score_text); //original pos x 72,y 16

			// Draw UI (score) -------------------------------------- //padding of 7 spaces !!!! 24? 40?
			sprintf_s(score_text, 10, "%7d", score);
			App->render->Blit(uiTexture, 17, 16, &p1Rect, 0);
			App->render->Blit(uiTexture, 16, 24, &p1ShipRect, 0);

			App->render->Blit(uiTexture, 24, 208, &powRect, 0); //24,208 POWER 
			App->render->Blit(uiTexture, 48, 210, &powBarRect, 0); //48,210 POWER BAR
			
			BlitText(32, 16, lastResortBlueFont, score_text); //original pos x 72,y 16

			if (App->player[0]->godMode)
			{
				if (godModeBlink[0] < 4000)
				{
					godModeBlink[0] = godModeBlink[0] + 100;
					BlitText(16, 33, lastResortBlueFont, "[god mode]");
				}

				else if (godModeBlink[0] >= 4000)
				{
					if (godModeBlink[0]<8000)
						godModeBlink[0] = godModeBlink[0] + 100;
					else
						godModeBlink[0] = 0;
				}
			}				
			
		}

		if (App->player[1]->IsEnabled())
		{
			bothPlayers = true;
			//draw lives
			sprintf_s(score_text, 10, "%6i%d", zero, lives2);
			BlitText(216, 24, lastResortBlueFont, score_text); 

			// Draw UI (score) -------------------------------------- //padding of 7 spaces !!!! 24? 40?
			App->render->Blit(uiTexture, 273, 16, &p2Rect, 0);
			App->render->Blit(uiTexture, 272, 24, &p2ShipRect, 0);

			App->render->Blit(uiTexture, 184, 208, &powRect, 0); //184,208 POWER  2 //48+40
			App->render->Blit(uiTexture, 208, 210, &powBar2Rect, 0); //208,210 POWER BAR  2

			sprintf_s(score_text, 10, "%7d", score2);
			BlitText(32+160, 16, lastResortBlueFont, score_text); //original pos x 72,y 16


			if (App->player[1]->godMode)
			{
				if (godModeBlink[1] < 4000)
				{
					godModeBlink[1] = godModeBlink[1] + 100;
					BlitText(218, 33, lastResortBlueFont, "[god mode]");
				}

				else if (godModeBlink[1] >= 4000)
				{
					if (godModeBlink[1]<8000)
						godModeBlink[1] = godModeBlink[1] + 100;
					else
						godModeBlink[1] = 0;
				}
			}
		}

		else
		{
			if (pressToStart < 5000)
			{
				pressToStart = pressToStart + 100;
				App->render->Blit(uiTexture, 192, 16, &pressRect, 0);
			}

			else if (pressToStart >= 5000)
			{
				if (pressToStart<10000)
					pressToStart = pressToStart + 100;
				else
					pressToStart = 0;
			}
		}

		

		if (!computed)
		{
			for (int i = 0; i < 10; i++)
			{
				ships[i].name = names[i];
				ships[i].score = scores[i];
				ships[i].topName = topNames[i];
			}
			computed = true;
		}

		for (int i = 0; i < 10; i++)
		{
			if (ships[i].name == "player 1")
				ships[i].score = score;
			if (App->player[1]->IsEnabled())
			{
				if (ships[i].name == "player 2")
					ships[i].score = score2;
			}
		}

		for (int j = 0; j < 9; j++)
		{
			for (int i = 0; i < 9-j; i++)
			{
				if (ships[i].score < ships[i + 1].score)
				{
					aux = ships[i];
					ships[i] = ships[i + 1];
					ships[i + 1] = aux;
				}
			}
		}

		sprintf_s(score_text, 10, "%6d",ships[0].score);
		BlitText(144, 16, lastResortBlueFont, score_text); 

		BlitText(112, 16, lastResortBlueFont, "top");
		BlitText(112, 24, lastResortBlueFont,ships[0].topName); // 133
	}
	//prints WIN UI
	if (UI == gameplay_state::WIN)
	{
		for (int i = 0; i < 10; ++i)
		{
			// Draw UI (score) --------------------------------------
			sprintf_s(score_text, 10, "%7d", ships[i].score);
			BlitText(118, 48 + 16 * i, redNumbers, score_text); //original pos x 72,y 16 //118,48

			BlitText(200, 48 + 16 * i, lastResortBlueFont, ships[i].name);
		}
	}

	if (UI != gameplay_state::LOGO)
	{
		BlitText(208, 216, lastResortBlueFont, "credit");
		
		if(coins>=10)
			sprintf_s(score_text, 10, "%d",coins);

		else
			sprintf_s(score_text, 10, "%i%d", zero, coins);
		
		BlitText(272, 216, lastResortBlueFont, score_text);

		if (UI == gameplay_state::GAMETITTLE && coins < 99)
			if (App->input->keyboard[SDL_SCANCODE_SPACE] == KEY_UP)
			{
				coins = coins + 2;
				if (coins > 99)coins = 99;
				App->audio->ControlAudio("inserted", SFX, PLAY);
			}
	}

	if (UI == gameplay_state::PAUSE)
	{
		BlitText(136, 112, lastResortBlueFont, "pause");
		SDL_Rect rect;
		rect = { 0,0, SCREEN_WIDTH * SCREEN_SIZE, SCREEN_HEIGHT * SCREEN_SIZE };
		//App->render->DrawQuad(rect, 255, 0, 255, 50);

		SDL_SetRenderDrawBlendMode(App->render->renderer, SDL_BLENDMODE_BLEND);
		SDL_SetRenderDrawColor(App->render->renderer, 255, 0, 255, 1);
		SDL_RenderFillRect(App->render->renderer, NULL);
	}

	return UPDATE_CONTINUE;
}

// Load new texture from file path
int ModuleUI::Load(const char* texture_path, const char* characters, uint rows)
{
	int id = -1;

	if (texture_path == nullptr || characters == nullptr || rows == 0)
	{
		LOG("Could not load font");
		return id;
	}

	SDL_Texture* tex = App->textures->Load(texture_path);

	if (tex == nullptr || strlen(characters) >= MAX_FONT_CHARS)
	{
		LOG("Could not load font at %s with characters '%s'", texture_path, characters);
		return id;
	}

	id = 0;
	for (; id < MAX_FONTS; ++id)
		if (fonts[id].graphic == nullptr)
			break;

	if (id == MAX_FONTS)
	{
		LOG("Cannot load font %s. Array is full (max %d).", texture_path, MAX_FONTS);
		return id;
	}

	fonts[id].graphic = tex; // graphic: pointer to the texture
	fonts[id].rows = rows; // rows: rows of characters in the texture
	fonts[id].len = 0; // len: length of the table

	strcpy_s(fonts[id].table, characters);
	fonts[id].len = strlen(fonts[id].table);
	fonts[id].row_chars = fonts[id].len / rows;
	App->textures->GetSize(tex, fonts[id].char_w, fonts[id].char_h);
	fonts[id].char_w = fonts[id].char_w / fonts[id].row_chars;
	fonts[id].char_h = fonts[id].char_h / fonts[id].rows;
	
	// table: array of chars to have the list of characters
	// row_chars: amount of chars per row of the texture
	// char_w: width of each character
	// char_h: height of each character

	LOG("Successfully loaded BMP font from %s", texture_path);

	return id;
}

void ModuleUI::UnLoad(int font_id)
{
	if (font_id >= 0 && font_id < MAX_FONTS && fonts[font_id].graphic != nullptr)
	{
		App->textures->Unload(fonts[font_id].graphic);
		fonts[font_id].graphic = nullptr;
		LOG("Successfully Unloaded BMP font_id %d", font_id);
	}
}

// Render text using a bitmap font
void ModuleUI::BlitText(int x, int y, int font_id, const char* text) const
{
	if (text == nullptr || font_id < 0 || font_id >= MAX_FONTS || fonts[font_id].graphic == nullptr)
	{
		LOG("Unable to render text with bmp font id %d", font_id);
		return;
	}

	const Font* font = &fonts[font_id];
	SDL_Rect rect;
	uint len = strlen(text);

	rect.w = font->char_w;
	rect.h = font->char_h;

	for (uint i = 0; i < len; ++i)
	{
		for (int j = 0; j < font->len; ++j)
		{
			if (font->table[j] == text[i])
			{
				//the magic happens here, not today my friend :)
				rect = { rect.w * (j % (int)font->row_chars) , rect.h * (j / (int)font->row_chars) , rect.w, rect.h };
				App->render->Blit(font->graphic, x, y, &rect, 0.0f);
				x += rect.w;
				break;
			}
		}

	}
}