#ifndef __MODULEUI_H__
#define __MODULEUI_H__

#include "Module.h"
#include "SDL\include\SDL_pixels.h"

#define MAX_FONTS 10
#define MAX_FONT_CHARS 256

enum gameplay_state
{
	NO,
	SCENE,
	WIN
};

struct SDL_Texture;

struct Font
{
	char table[MAX_FONT_CHARS];
	SDL_Texture* graphic = nullptr;
	uint rows, len, char_w, char_h, row_chars;
};

class ModuleUI : public Module
{
public:

	ModuleUI();
	~ModuleUI();

	bool Start();
	update_status Update();
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
	char score_text[10];
	char redNumbers_text[10];
	Uint32 score = 0;
	Uint32 score2 = 0; //provisonal name to redNumbers call
	uint lives1 = 0;
	uint lives2 = 0;
	
	int scores[10] = { 0,0,0,0,0,0,0,0,0,0 };
	Uint32 lastScore;
	int scorePosY[10] = { 48,68,88,108,128,148,168,188,208,228 };

	bool computed = false;
	gameplay_state UI;

};


#endif // __MODULEUI_H__