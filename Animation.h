#ifndef __ANIMATION_H__
#define __ANIMATION_H__

#include "SDL/include/SDL_rect.h"
//#define MAX_FRAMES 128
#define MAX_PTRFRAMES 128

class Animation
{
public:

	float speed = 1.0f;
	//SDL_Rect frames[MAX_FRAMES];
	SDL_Rect* frames[MAX_PTRFRAMES];// = new SDL_Rect; -----------
	bool repeat = true; //default animation is circular pattern

	~Animation()
	{
		for (int i = 0; i < MAX_PTRFRAMES; ++i)
		{
			if (frames[i] != nullptr)
			{
				delete frames[i];
				frames[i] = nullptr;
			}
		}
	}

private:
	//float current_frame;
	//int last_frame = 0;

public:

	float current_frame; //old workaround
	int last_frame = 0;
	bool finish = false; //to active last
	
	void PushBack(const SDL_Rect& rect)//, bool flip = false)
	{
		
		frames[last_frame] = new SDL_Rect; //pushback function for the dynamic frames array of rects mode
		*frames[last_frame] = rect;
		last_frame++;
		//frames[last_frame++] = rect;
		
	}

	SDL_Rect& GetCurrentFrame() //modified for avoid cycle animations of wanted linears anims
	{
		
		current_frame += speed;
		if(current_frame >= last_frame && repeat == true)
			current_frame = 0;

		if (repeat)
			return *frames[(int)current_frame];
		else if (!repeat)
		{
			if (current_frame >= last_frame)
			{
				finish = true;
				return *frames[(int)last_frame - 1];
				
			}

			else
				return *frames[(int)current_frame];
		}
			
	}
	//bool ret(return finish);

};

#endif