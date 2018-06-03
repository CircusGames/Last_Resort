#ifndef __MODULEUI_H__
#define __MODULEUI_H__

#include "Module.h"
#include "SDL\include\SDL_pixels.h"
#include <iostream>

#define MAX_FONTS 10
#define MAX_FONT_CHARS 256

enum gameplay_state
{
	NO,
	LOGO,
	GAMETITTLE,
	SCENE,
	WIN
};

struct SDL_Texture;

struct Font
{
	char table[MAX_FONT_CHARS];
	SDL_Texture* graphic = nullptr;
	uint rows, len,len2,len3, char_w, char_h, row_chars;
};

class ModuleUI : public Module
{
public:

	ModuleUI();
	~ModuleUI();

	bool Start();
	//update_status Update();
	update_status PostUpdate();
	bool CleanUp();
	// Load Font
	int Load(const char* texture_path, const char* characters, uint rows = 1);
	void UnLoad(int font_id);

	// Create a surface from text
	void BlitText(int x, int y, int bmp_font_id, const char* text) const;

private:

	Font	 fonts[MAX_FONTS];

public:
	int lastResortBlueFont = -1;
	int redNumbers = -1;

	int unit1Pow = 0;
	int unit2Pow = 0;
	int pressToStart = 0;

	char score_text[10];
	char redNumbers_text[10];

	SDL_Texture* uiTexture = nullptr;

	SDL_Rect p1Rect = { 1,0,22,8 };
	SDL_Rect p1ShipRect = { 0,8,24,8 };

	SDL_Rect powRect = { 0,16,96,8 };
	SDL_Rect powBarRect;
	SDL_Rect powBar2Rect;//player2

	SDL_Rect p2Rect = { 161,16,23,8 };
	SDL_Rect p2ShipRect = { 160,24,24,8 };

	SDL_Rect pressRect = { 159,0,96,16 };

	Uint32 score = 0;
	Uint32 score2 = 0; //provisonal name to redNumbers call
	uint lives1 = 0;
	uint lives2 = 0;

	uint zero = 0; //fast fix
	
	int scores[10] = { 74000,63500,58200,43700,47000,43000,32900,21100,0,0 };
	//Uint32 lastScore
	//int scorePosY[10] = { 48,68,88,108,128,148,168,188,208,228 };

	SDL_Rect coinsRect;

	int coins = 0;

	struct Players
	{
		char* name = nullptr;
		char* topName = nullptr;
		int score = 0;
	};

	Players ships[10];

	char* names[10] = { "momar","elmascapo","ice","fire","albanian","mako","pete","john","player 1","player 2" };
	char* topNames[10] = { "[momar]","[elmascapo]","[ice]","[fire]","[albanian]","[mako]","[pete]","[john]","[player 1]","[player 2]" };

	char* topPlayer = nullptr;
	Players aux;

	bool computed = false;
	gameplay_state UI;

};


#endif // __MODULEUI_H__