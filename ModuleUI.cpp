

//still much work to do in this module , 00001 alpha -------------------------------------

#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleUI.h"
#include "ModulePlayer.h"
#include "ModuleWin.h"
// ---------------------
#include "ModuleInput.h"
#include "ModuleFadeToBlack.h"

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

	

	return true;


}

bool ModuleUI::CleanUp()
{
	LOG("Unloading font textures");
	//unload font textures
	UnLoad(lastResortBlueFont);
	UnLoad(redNumbers);
	return true;
}

update_status ModuleUI::Update()
{

	
	//compute the score //provisional...
	App->winScreen->saveScore(score);
	score = App->player->playerScore;

	for (int i = 0; i < 10; ++i)
	{
		scores[i] = App->winScreen->allScores[i];
	}

	//prints scene UI
	if (UI == gameplay_state::SCENE)
	{
		//draw lives
		lives1 = App->player->lives;
		sprintf_s(score_text, 10, "%7d", lives1);
		BlitText(32, 24, lastResortBlueFont, "x"); // 136
		BlitText(0, 24, lastResortBlueFont, score_text); //original pos x 72,y 16

		// Draw UI (score) -------------------------------------- //padding of 7 spaces !!!! 24? 40?
		sprintf_s(score_text, 10, "%7d", score);
		BlitText( 16 , 16, lastResortBlueFont, "1p"); //32
		BlitText(112 , 16, lastResortBlueFont, "top"); // 136
		BlitText(32,16, lastResortBlueFont, score_text); //original pos x 72,y 16
		

	}
	//prints WIN UI
	if (UI == gameplay_state::WIN)
	{
		//score = App->player->playerScore;
		//try to save player actual score
		

		if (!computed)
		{
			App->winScreen->saveScore(score);

			for (int i = 0; i < 10; ++i)
				scores[i] = App->winScreen->allScores[i];
				
			computed = true;
		}

		for (int i = 0; i < 10; ++i)
		{
			// Draw UI (score) --------------------------------------
			sprintf_s(score_text, 10, "%7d", scores[i]);
			BlitText(118, 48 + 16 * i, redNumbers, score_text); //original pos x 72,y 16 //118,48
		}

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