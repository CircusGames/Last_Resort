#ifndef __PATH_H__
#define __PATH_H__

#include "p2Point.h"
#include "ModuleAudio.h"

#define MAX_STEPS 36

class Animation;

struct Step
{
	uint frames = 1;
	fPoint speed;
	Animation* animation = nullptr;
	char* fx = nullptr;
	bool played_fx = false;
};

class Path
{
public:
	bool loop = true;
	Step steps[MAX_STEPS];
	fPoint accumulated_speed = { 0.0f, 0.0f };

private:
	uint current_frame = 0;
	uint last_step = 0;

public:

	void PushBack(fPoint speed, uint frames, Animation* animation = nullptr, char* fx = nullptr)
	{
		steps[last_step].animation = animation;
		steps[last_step].frames = frames;
		steps[last_step].fx = fx;
		steps[last_step++].speed = speed;
	}

	iPoint GetCurrentSpeed(Animation** current_animation = nullptr)
	{

		current_frame += 1;

		uint count = 0;
		uint i = 0;
		bool need_loop = true;
		bool played = false;

		for (; i < last_step; ++i)
		{
			count += steps[i].frames;
			if (current_animation != nullptr)
				*current_animation = steps[i].animation;
			if (count >= current_frame)
			{
				accumulated_speed += steps[i].speed;
				need_loop = false;
				break;
			}
		}

		if (!steps[i].played_fx && steps[i].fx != nullptr)
		{
			App->audio->ControlAudio(steps[i].fx, SFX, PLAY);
			steps[i].played_fx = true;

		}



		if (need_loop & loop)
			current_frame = 0;

		return iPoint((int)accumulated_speed.x, (int)accumulated_speed.y);
	}

	void Reset()
	{
		current_frame = 0;
	}
};

#endif // __PATH_H__