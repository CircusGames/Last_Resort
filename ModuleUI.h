#ifndef __MODULEUI_H__
#define __MODULEUI_H__

#include "Module.h"
#include "SDL\include\SDL_pixels.h"

#define MAX_FONTS 10
#define MAX_FONT_CHARS 256

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
	int font_score = -1;
	int redNumbers = -1;
	char score_text[10];
	char redNumbers_text[10];
	uint score = 0;
	uint score2 = 0; //provisonal name to redNumbers call
};


#endif // __MODULEUI_H__