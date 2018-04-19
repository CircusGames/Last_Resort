#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleUI.h"
#include "ModulePlayer.h"

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

	font_score = App->moduleUI->Load("assets/Graphics/UI/blue_chars.png", "0123456789[]abcdefghijklmnopqrstuvwxyz _.,&#", 1);
	redNumbers = App->moduleUI->Load("assets/Graphics/UI/red_numbers.png", "0123456789 ", 1);
	return true;
}

bool ModuleUI::CleanUp()
{
	LOG("Unloading font textures");
	//unload font textures
	UnLoad(font_score);

	return true;
}

update_status ModuleUI::Update()
{
	score = App->player->playerScore;
	// Draw UI (score) --------------------------------------
	sprintf_s(score_text, 10, "%7d", score);
	sprintf_s(redNumbers_text, 10, "%7d", score2);

	//Blit the text of the score in the screen
	
	//BlitText(150, 200, font_score, "hello world 0123");//score_text);

	//BlitText(150, 200, font_score, score_text);//"hello world 0123");//score_text);
	//BlitText(150, 210, redNumbers, "01234 56789");//score_text);

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
				
				App->render->Blit(font->graphic, x, y, &rect, 0.0f, false);
				x += rect.w;
				break;
			}
		}

	}
}