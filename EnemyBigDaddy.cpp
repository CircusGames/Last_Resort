#include "Application.h"
#include "EnemyBigDaddy.h"
#include "ModuleCollision.h"
#include "ModuleEnemies.h"

#include "ModuleRender.h"
#include "SDL\include\SDL_timer.h"

EnemyBigDaddy::EnemyBigDaddy(int x, int y, powerUpTypes type, SDL_Texture* thisTexture) : Enemy(x, y)
{
	enemyType = BIGDADDY;
	// Loads laser texture, only we have 1 big daddy on scene, loads here is ok
	laserTexture = App->textures->Load("assets/Graphics/Enemies/Level_3/laserMidBoss.png");
	// loads specific midboss sfx
	App->audio->LoadAudio("assets/Audio/SFX/Enemies/mid_boss_appear.wav", "entryScene", SFX);
	App->audio->LoadAudio("assets/Audio/SFX/Enemies/Mid_Boss_Close.wav", "close", SFX);
	App->audio->LoadAudio("assets/Audio/SFX/Enemies/Mid_Boss_OpenandLaser.wav", "openAndLaser", SFX);
	//links the correct spritesheet texture ----
	enemyTex = thisTexture;
	// -----------------------------------------
	powerUpType = type;
	life = 135;
	enemyScore = 2000;

	// animation rects --------------------------------------------------------------------------------------

	// big daddy on stage animation ------------------------------------------
	// normal anim
	bigDaddy.onStageAnim[NORMAL_ANIM].PushBack({ 0,167,64,40 }); // max closed
	bigDaddy.onStageAnim[NORMAL_ANIM].PushBack({ 65,167,64,44 });
	bigDaddy.onStageAnim[NORMAL_ANIM].PushBack({ 130,167,64,48 });
	bigDaddy.onStageAnim[NORMAL_ANIM].PushBack({ 195,167,64,52 });
	bigDaddy.onStageAnim[NORMAL_ANIM].PushBack({ 260,167,64,56 });
	
	bigDaddy.onStageAnim[NORMAL_ANIM].PushBack({ 325,167,64,60 }); // midEye center
	bigDaddy.onStageAnim[NORMAL_ANIM].PushBack({ 325,167,64,60 }); // midEye center

	for (uint i = 0; i < 8; ++i) // 8 loops rotating
	{
		bigDaddy.onStageAnim[NORMAL_ANIM].PushBack({ 325,167,64,60 }); // midEye center
		bigDaddy.onStageAnim[NORMAL_ANIM].PushBack({ 390,167,64,60 });
		bigDaddy.onStageAnim[NORMAL_ANIM].PushBack({ 455,167,64,60 });
		bigDaddy.onStageAnim[NORMAL_ANIM].PushBack({ 520,167,64,60 });
	}
	// and close again
	bigDaddy.onStageAnim[NORMAL_ANIM].PushBack({ 260,167,64,56 });
	bigDaddy.onStageAnim[NORMAL_ANIM].PushBack({ 195,167,64,52 });
	bigDaddy.onStageAnim[NORMAL_ANIM].PushBack({ 130,167,64,48 });
	bigDaddy.onStageAnim[NORMAL_ANIM].PushBack({ 65,167,64,44 });
	bigDaddy.onStageAnim[NORMAL_ANIM].PushBack({ 0,167,64,40 }); // max closed

	bigDaddy.onStageAnim[NORMAL_ANIM].speed = 0.25f;
	bigDaddy.onStageAnim[NORMAL_ANIM].repeat = false;
	// DAMAGE anim ------------
	bigDaddy.onStageAnim[DAMAGE_ANIM].PushBack({ 0,106,64,40 }); // max closed
	bigDaddy.onStageAnim[DAMAGE_ANIM].PushBack({ 65,106,64,44 });
	bigDaddy.onStageAnim[DAMAGE_ANIM].PushBack({ 130,106,64,48 });
	bigDaddy.onStageAnim[DAMAGE_ANIM].PushBack({ 195,106,64,52 });
	bigDaddy.onStageAnim[DAMAGE_ANIM].PushBack({ 260,106,64,56 });

	bigDaddy.onStageAnim[DAMAGE_ANIM].PushBack({ 325,106,64,60 }); // midEye center
	bigDaddy.onStageAnim[DAMAGE_ANIM].PushBack({ 325,167,64,60 }); // midEye center

	for (uint i = 0; i < 8; ++i)
	{
		bigDaddy.onStageAnim[DAMAGE_ANIM].PushBack({ 325,106,64,60 }); // midEye center
		bigDaddy.onStageAnim[DAMAGE_ANIM].PushBack({ 390,106,64,60 });
		bigDaddy.onStageAnim[DAMAGE_ANIM].PushBack({ 455,106,64,60 });
		bigDaddy.onStageAnim[DAMAGE_ANIM].PushBack({ 520,106,64,60 });
	}
	// and close again
	bigDaddy.onStageAnim[DAMAGE_ANIM].PushBack({ 260,106,64,56 });
	bigDaddy.onStageAnim[DAMAGE_ANIM].PushBack({ 195,106,64,52 });
	bigDaddy.onStageAnim[DAMAGE_ANIM].PushBack({ 130,106,64,48 });
	bigDaddy.onStageAnim[DAMAGE_ANIM].PushBack({ 65,106,64,44 });
	bigDaddy.onStageAnim[DAMAGE_ANIM].PushBack({ 0,106,64,40 }); // max closed
	bigDaddy.onStageAnim[DAMAGE_ANIM].speed = 0.25f;
	bigDaddy.onStageAnim[DAMAGE_ANIM].repeat = false;

	// -----------------------------------------------------------------------
	// travel path anim
	bigDaddy.travelAnim[NORMAL_ANIM].PushBack({ 0,167,64,40 }); // max closed
	// -------
	// FOREGROUND anim
	bigDaddy.foregroundAnim.PushBack({ 0,0,33,20 }); // max closed foreground
	// ENTRY animation
	bigDaddy.entryAnim.PushBack({ 35,0,34,21 });
	bigDaddy.entryAnim.PushBack({ 69,0,34,22 });
	bigDaddy.entryAnim.PushBack({ 104,0,35,22 });
	bigDaddy.entryAnim.PushBack({ 140,0,35,23 });
	bigDaddy.entryAnim.PushBack({ 176,0,36,23 });
	bigDaddy.entryAnim.PushBack({ 213,0,37,23 });
	bigDaddy.entryAnim.PushBack({ 289,0,38,23 });
	bigDaddy.entryAnim.PushBack({ 328,0,38,24 });
	bigDaddy.entryAnim.PushBack({ 367,0,39,24 });
	bigDaddy.entryAnim.PushBack({ 407,0,39,25 });
	bigDaddy.entryAnim.PushBack({ 447,0,40,25 });
	bigDaddy.entryAnim.PushBack({ 488,0,40,25 });
	bigDaddy.entryAnim.PushBack({ 529,0,41,25 });
	bigDaddy.entryAnim.PushBack({ 571,0,41,26 });
	bigDaddy.entryAnim.PushBack({ 613,0,42,26 });
	bigDaddy.entryAnim.PushBack({ 656,0,42,26 });
	bigDaddy.entryAnim.PushBack({ 699,0,43,26 });
	bigDaddy.entryAnim.PushBack({ 743,0,43,27 });
	bigDaddy.entryAnim.PushBack({ 787,0,44,27 });
	bigDaddy.entryAnim.PushBack({ 832,0,44,27 });
	bigDaddy.entryAnim.PushBack({ 877,0,45,27 });
	bigDaddy.entryAnim.PushBack({ 923,0,45,28 });
	bigDaddy.entryAnim.PushBack({ 0,29,46,28 });
	bigDaddy.entryAnim.PushBack({ 47,29,46,29 });
	bigDaddy.entryAnim.PushBack({ 94,29,47,29 });
	bigDaddy.entryAnim.PushBack({ 142,29,47,30 });
	bigDaddy.entryAnim.PushBack({ 190,29,48,30 });
	bigDaddy.entryAnim.PushBack({ 239,29,49,30 });
	bigDaddy.entryAnim.PushBack({ 289,29,49,31 });
	bigDaddy.entryAnim.PushBack({ 339,29,50,32 });
	bigDaddy.entryAnim.PushBack({ 390,29,51,32 });
	bigDaddy.entryAnim.PushBack({ 442,29,51,33 });
	bigDaddy.entryAnim.PushBack({ 494,29,52,33 });
	bigDaddy.entryAnim.PushBack({ 547,29,53,33 });
	bigDaddy.entryAnim.PushBack({ 601,29,53,33 });
	bigDaddy.entryAnim.PushBack({ 655,29,54,33 });
	bigDaddy.entryAnim.PushBack({ 710,29,54,34 });
	bigDaddy.entryAnim.PushBack({ 765,29,55,34 });
	bigDaddy.entryAnim.PushBack({ 821,29,55,35 });
	bigDaddy.entryAnim.PushBack({ 877,29,56,35 });
	bigDaddy.entryAnim.PushBack({ 934,29,56,35 });
	bigDaddy.entryAnim.PushBack({ 0,65,57,35 });
	bigDaddy.entryAnim.PushBack({ 58,65,57,36 });
	bigDaddy.entryAnim.PushBack({ 116,65,58,36 });
	bigDaddy.entryAnim.PushBack({ 175,65,58,36 });
	bigDaddy.entryAnim.PushBack({ 234,65,59,36 });
	bigDaddy.entryAnim.PushBack({ 294,65,59,37 });
	bigDaddy.entryAnim.PushBack({ 354,65,60,37 });
	bigDaddy.entryAnim.PushBack({ 415,65,61,37 });
	bigDaddy.entryAnim.PushBack({ 477,65,62,38 });
	bigDaddy.entryAnim.PushBack({ 540,65,62,39 });
	bigDaddy.entryAnim.PushBack({ 603,65,63,39 });
	bigDaddy.entryAnim.PushBack({ 667,65,63,40 });
	bigDaddy.entryAnim.speed = 0.5f;
	bigDaddy.entryAnim.repeat = false;
	// ------------------------------------------------
	// GOODBYE ANIMATION
	bigDaddy.goodByeAnim.PushBack({ 667,65,63,40 });
	bigDaddy.goodByeAnim.PushBack({ 603,65,63,39 });
	bigDaddy.goodByeAnim.PushBack({ 540,65,62,39 });
	bigDaddy.goodByeAnim.PushBack({ 477,65,62,38 });
	bigDaddy.goodByeAnim.PushBack({ 415,65,61,37 });
	bigDaddy.goodByeAnim.PushBack({ 354,65,60,37 });
	bigDaddy.goodByeAnim.PushBack({ 294,65,59,37 });
	bigDaddy.goodByeAnim.PushBack({ 234,65,59,36 });
	bigDaddy.goodByeAnim.PushBack({ 175,65,58,36 });
	bigDaddy.goodByeAnim.PushBack({ 116,65,58,36 });
	bigDaddy.goodByeAnim.PushBack({ 58,65,57,36 });
	bigDaddy.goodByeAnim.PushBack({ 0,65,57,35 });
	bigDaddy.goodByeAnim.PushBack({ 934,29,56,35 });
	bigDaddy.goodByeAnim.PushBack({ 877,29,56,35 });
	bigDaddy.goodByeAnim.PushBack({ 821,29,55,35 });
	bigDaddy.goodByeAnim.PushBack({ 765,29,55,34 });
	bigDaddy.goodByeAnim.PushBack({ 710,29,54,34 });
	bigDaddy.goodByeAnim.PushBack({ 655,29,54,33 });
	bigDaddy.goodByeAnim.PushBack({ 601,29,53,33 });
	bigDaddy.goodByeAnim.PushBack({ 547,29,53,33 });
	bigDaddy.goodByeAnim.PushBack({ 494,29,52,33 });
	bigDaddy.goodByeAnim.PushBack({ 442,29,51,33 });
	bigDaddy.goodByeAnim.PushBack({ 390,29,51,32 });
	bigDaddy.goodByeAnim.PushBack({ 339,29,50,32 });
	bigDaddy.goodByeAnim.PushBack({ 289,29,49,31 });
	bigDaddy.goodByeAnim.PushBack({ 239,29,49,30 });
	bigDaddy.goodByeAnim.PushBack({ 190,29,48,30 });
	bigDaddy.goodByeAnim.PushBack({ 142,29,47,30 });
	bigDaddy.goodByeAnim.PushBack({ 94,29,47,29 });
	bigDaddy.goodByeAnim.PushBack({ 47,29,46,29 });
	bigDaddy.goodByeAnim.PushBack({ 0,29,46,28 });
	bigDaddy.goodByeAnim.PushBack({ 923,0,45,28 });
	bigDaddy.goodByeAnim.PushBack({ 877,0,45,27 });
	bigDaddy.goodByeAnim.PushBack({ 832,0,44,27 });
	bigDaddy.goodByeAnim.PushBack({ 787,0,44,27 });
	bigDaddy.goodByeAnim.PushBack({ 743,0,43,27 });
	bigDaddy.goodByeAnim.PushBack({ 699,0,43,26 });
	bigDaddy.goodByeAnim.PushBack({ 656,0,42,26 });
	bigDaddy.goodByeAnim.PushBack({ 613,0,42,26 });
	bigDaddy.goodByeAnim.PushBack({ 571,0,41,26 });
	bigDaddy.goodByeAnim.PushBack({ 529,0,41,25 });
	bigDaddy.goodByeAnim.PushBack({ 488,0,40,25 });
	bigDaddy.goodByeAnim.PushBack({ 447,0,40,25 });
	bigDaddy.goodByeAnim.PushBack({ 407,0,39,25 });
	bigDaddy.goodByeAnim.PushBack({ 367,0,39,24 });
	bigDaddy.goodByeAnim.PushBack({ 328,0,38,24 });
	bigDaddy.goodByeAnim.PushBack({ 289,0,38,23 });
	bigDaddy.goodByeAnim.PushBack({ 213,0,37,23 });
	bigDaddy.goodByeAnim.PushBack({ 176,0,36,23 });
	bigDaddy.goodByeAnim.PushBack({ 140,0,35,23 });
	bigDaddy.goodByeAnim.PushBack({ 104,0,35,22 });
	bigDaddy.goodByeAnim.PushBack({ 69,0,34,22 });
	bigDaddy.goodByeAnim.PushBack({ 35,0,34,21 });
	bigDaddy.goodByeAnim.speed = 0.5f;
	bigDaddy.goodByeAnim.repeat = false;

	// -----------------------------------------------------------------------
	// lasers animations
	// left/right --------------------------------
	// left cap // the biggests parts lasts x2 = at the start and end of animation repeats the frame
	for (uint z = 0; z < MAX_NUM_LASERS; ++z)
	{
		laser[z].anim[0][0].PushBack({ 138,179,16,8 }); // big
		laser[z].anim[0][0].PushBack({ 90,179,15,6 }); // 
		laser[z].anim[0][0].PushBack({ 44,179,14,4 }); //
		laser[z].anim[0][0].PushBack({ 0,179,13,2 }); // 

		laser[z].anim[0][0].PushBack({ 44,179,14,4 }); //
		laser[z].anim[0][0].PushBack({ 90,179,15,6 }); // 
		laser[z].anim[0][0].PushBack({ 138,179,16,8 }); // big
		laser[z].anim[0][0].speed = 1.0f;


		// mid THREE MID PARTS TOTAL
		for (uint i = 1; i < 4; ++i)
		{
			laser[z].anim[0][i].PushBack({ 155,179,16,8 }); // big
			laser[z].anim[0][i].PushBack({ 106,179,16,6 });
			laser[z].anim[0][i].PushBack({ 59,179,16,4 });
			laser[z].anim[0][i].PushBack({ 14,179,16,2 });

			laser[z].anim[0][i].PushBack({ 59,179,16,4 });
			laser[z].anim[0][i].PushBack({ 106,179,16,6 });
			laser[z].anim[0][i].PushBack({ 155,179,16,8 }); // big
			laser[z].anim[0][i].speed = 1.0f;
		}
		// right cap
		laser[z].anim[0][4].PushBack({ 172,179,16,8 }); // big
		laser[z].anim[0][4].PushBack({ 123,179,15,6 });
		laser[z].anim[0][4].PushBack({ 76,179,14,4 });
		laser[z].anim[0][4].PushBack({ 31,179,13,2 });

		laser[z].anim[0][4].PushBack({ 76,179,14,4 });
		laser[z].anim[0][4].PushBack({ 123,179,15,6 });
		laser[z].anim[0][4].PushBack({ 172,179,16,8 }); // big
		laser[z].anim[0][4].speed = 1.0f;
		// ---------------------------------------------
		// UP & DOWN animation parts -------
		// upper cap
		laser[z].anim[1][0].PushBack({ 200,179,8,16 }); // upper cap BIG
		laser[z].anim[1][0].PushBack({ 194,179,6,15 });
		laser[z].anim[1][0].PushBack({ 190,179,4,14 });
		laser[z].anim[1][0].PushBack({ 188,179,2,13 });

		laser[z].anim[1][0].PushBack({ 190,179,4,14 });
		laser[z].anim[1][0].PushBack({ 194,179,6,15 });
		laser[z].anim[1][0].PushBack({ 200,179,8,16 }); // upper cap BIG
		laser[z].anim[1][0].speed = 1.0f;
		// MID PARTS caps
		for (uint i = 1; i < 4; ++i)
		{
			laser[z].anim[1][i].PushBack({ 200,196,8,16 }); // BIG
			laser[z].anim[1][i].PushBack({ 194,195,6,16 });
			laser[z].anim[1][i].PushBack({ 190,194,4,14 });
			laser[z].anim[1][i].PushBack({ 188,194,2,13 });

			laser[z].anim[1][i].PushBack({ 190,194,4,14 });
			laser[z].anim[1][i].PushBack({ 194,195,6,16 });
			laser[z].anim[1][i].PushBack({ 200,196,8,16 }); // BIG
			laser[z].anim[1][i].speed = 1.0f;
		}
		// down cap pointing down
		laser[z].anim[1][4].PushBack({ 200,213,8,16 }); // BIG
		laser[z].anim[1][4].PushBack({ 194,212,6,16 });
		laser[z].anim[1][4].PushBack({ 190,211,4,14 });
		laser[z].anim[1][4].PushBack({ 188,210,2,13 });

		laser[z].anim[1][4].PushBack({ 190,211,4,14 });
		laser[z].anim[1][4].PushBack({ 194,212,6,16 });
		laser[z].anim[1][4].PushBack({ 200,213,8,16 }); // BIG
		laser[z].anim[1][4].speed = 1.0f;
		// -------
		// 3pi/4 -------------------------------------------------
		// pointing "up" cap
		laser[z].anim[2][0].PushBack({ 0,129,22,16 }); // BIG
		laser[z].anim[2][0].PushBack({ 198,79,19,15 });
		laser[z].anim[2][0].PushBack({ 152,79,16,14 });
		laser[z].anim[2][0].PushBack({ 108,79,14,13 });

		laser[z].anim[2][0].PushBack({ 152,79,16,14 });
		laser[z].anim[2][0].PushBack({ 198,79,19,15 });
		laser[z].anim[2][0].PushBack({ 0,129,22,16 }); // BIG
		laser[z].anim[2][0].speed = 1.0f;
		//  mid
		for (uint i = 1; i < 4; ++i)
		{
			laser[z].anim[2][i].PushBack({ 11,146,28,16 }); // BIG
			laser[z].anim[2][i].PushBack({ 210,95,24,16 });
			laser[z].anim[2][i].PushBack({ 165,94,20,16 });
			laser[z].anim[2][i].PushBack({ 121,93,18,16 });

			laser[z].anim[2][i].PushBack({ 165,94,20,16 });
			laser[z].anim[2][i].PushBack({ 210,95,24,16 });
			laser[z].anim[2][i].PushBack({ 11,146,28,16 }); // BIG
			laser[z].anim[2][i].speed = 1.0f;
		}
		// pointing "down" cap
		laser[z].anim[2][4].PushBack({ 28,163,22,16 }); // BIG
		laser[z].anim[2][4].PushBack({ 227,112,19,15 });
		laser[z].anim[2][4].PushBack({ 182,111,16,14 });
		laser[z].anim[2][4].PushBack({ 138,110,14,13 });

		laser[z].anim[2][4].PushBack({ 182,111,16,14 });
		laser[z].anim[2][4].PushBack({ 227,112,19,15 });
		laser[z].anim[2][4].PushBack({ 28,163,22,16 }); // BIG
		laser[z].anim[2][4].speed = 1.0f;
		// -----------------------------------------------------
		// PI/4 ------------------------
		// pointing "up" cap
		laser[z].anim[3][0].PushBack({ 216,129,22,16 }); // BIG
		laser[z].anim[3][0].PushBack({ 169,129,19,15 });
		laser[z].anim[3][0].PushBack({ 124,129,16,14 });
		laser[z].anim[3][0].PushBack({ 80,129,14,13 });

		laser[z].anim[3][0].PushBack({ 124,129,16,14 });
		laser[z].anim[3][0].PushBack({ 169,129,19,15 });
		laser[z].anim[3][0].PushBack({ 216,129,22,16 }); // BIG
		laser[z].anim[3][0].speed = 1.0f;
		// mid
		for (uint i = 1; i < 4; ++i)
		{
			laser[z].anim[3][i].PushBack({ 199,146,28,16 }); // BIG
			laser[z].anim[3][i].PushBack({ 152,145,24,16 });
			laser[z].anim[3][i].PushBack({ 107,144,20,16 });
			laser[z].anim[3][i].PushBack({ 63, 143,18,16 });

			laser[z].anim[3][i].PushBack({ 107,144,20,16 });
			laser[z].anim[3][i].PushBack({ 152,145,24,16 });
			laser[z].anim[3][i].PushBack({ 199,146,28,16 }); // BIG
			laser[z].anim[3][i].speed = 1.0f;

		}
		// "down" cap
		laser[z].anim[3][4].PushBack({ 188,163,22,16 }); // BIG
		laser[z].anim[3][4].PushBack({ 140,162,19,15 });
		laser[z].anim[3][4].PushBack({ 94,161,16,14 });
		laser[z].anim[3][4].PushBack({ 50,160,14,13 });

		laser[z].anim[3][4].PushBack({ 94,161,16,14 });
		laser[z].anim[3][4].PushBack({ 140,162,19,15 });
		laser[z].anim[3][4].PushBack({ 188,163,22,16 }); // BIG
		laser[z].anim[3][4].speed = 1.0f;
		// ----------------------------------------------------
		// 22,5 degrees CAP ----
		laser[z].anim[4][0].PushBack({ 172,0,16,14 }); // BIG
		laser[z].anim[4][0].PushBack({ 123,0,15,12 });
		laser[z].anim[4][0].PushBack({ 76,0,14,10 });
		laser[z].anim[4][0].PushBack({ 31,0,13,8 });

		laser[z].anim[4][0].PushBack({ 76,0,14,10 });
		laser[z].anim[4][0].PushBack({ 123,0,15,12 });
		laser[z].anim[4][0].PushBack({ 172,0,16,14 });
		laser[z].anim[4][0].speed = 1.0f;
		// mid
		for (uint i = 1; i < 4; ++i)
		{
			laser[z].anim[4][i].PushBack({ 155,7,16,16 }); // BIG
			laser[z].anim[4][i].PushBack({ 106,7,16,14 });
			laser[z].anim[4][i].PushBack({ 59,7,16,12 });
			laser[z].anim[4][i].PushBack({ 14,7,16,10 });

			laser[z].anim[4][i].PushBack({ 59,7,16,12 });
			laser[z].anim[4][i].PushBack({ 106,7,16,14 });
			laser[z].anim[4][i].PushBack({ 155,7,16,16 }); // BIG
			laser[z].anim[4][i].speed = 1.0f;
		}
		// "down" cap
		laser[z].anim[4][4].PushBack({ 138,15,16,14 }); // BIG
		laser[z].anim[4][4].PushBack({ 90,16,15,12 });
		laser[z].anim[4][4].PushBack({ 44,16,14,10 });
		laser[z].anim[4][4].PushBack({ 0,16,13,8 });

		laser[z].anim[4][4].PushBack({ 44,16,14,10 });
		laser[z].anim[4][4].PushBack({ 90,16,15,12 });
		laser[z].anim[4][4].PushBack({ 138,15,16,14 });
		laser[z].anim[4][4].speed = 1.0f;
		// -----------------------------------------------------
		// 67'5 degrees --------
		// "up" cap
		laser[z].anim[5][0].PushBack({ 238,29,14,16 }); // BIG
		laser[z].anim[5][0].PushBack({ 210,29,12,15 });
		laser[z].anim[5][0].PushBack({ 184,29,10,14 });
		laser[z].anim[5][0].PushBack({ 160,29,8,13 });

		laser[z].anim[5][0].PushBack({ 184,29,10,14 });
		laser[z].anim[5][0].PushBack({ 210,29,12,15 });
		laser[z].anim[5][0].PushBack({ 238,29,14,16 }); // BIG
		laser[z].anim[5][0].speed = 1.0f;
		// mid
		for (uint i = 1; i < 4; ++i)
		{
			laser[z].anim[5][i].PushBack({ 229,46,16,16 }); // BIG
			laser[z].anim[5][i].PushBack({ 201,45,14,16 });
			laser[z].anim[5][i].PushBack({ 175,44,12,16 });
			laser[z].anim[5][i].PushBack({ 151,46,8,16 });

			laser[z].anim[5][i].PushBack({ 175,44,12,16 });
			laser[z].anim[5][i].PushBack({ 201,45,14,16 });
			laser[z].anim[5][i].PushBack({ 229,46,16,16 }); // BIG
			laser[z].anim[5][i].speed = 1.0f;
		}
		// "down" cap
		laser[z].anim[5][4].PushBack({ 222,63,14,16 }); // BIG
		laser[z].anim[5][4].PushBack({ 194,62,12,15 });
		laser[z].anim[5][4].PushBack({ 168,61,10,14 });
		laser[z].anim[5][4].PushBack({ 144,60,10,13 });

		laser[z].anim[5][4].PushBack({ 168,61,10,14 });
		laser[z].anim[5][4].PushBack({ 194,62,12,15 });
		laser[z].anim[5][4].PushBack({ 222,63,14,16 }); // BIG
		laser[z].anim[5][4].speed = 1.0f;
		// -----------------------------------------------------
		//112.5 degrees (pointing upLeft)
		// "up" top cap
		laser[z].anim[6][0].PushBack({ 78,79,14,16 }); // BIG
		laser[z].anim[6][0].PushBack({ 50,79,12,15 });
		laser[z].anim[6][0].PushBack({ 24,79,10,14 });
		laser[z].anim[6][0].PushBack({ 0,79,8,13 });

		laser[z].anim[6][0].PushBack({ 24,79,10,14 });
		laser[z].anim[6][0].PushBack({ 50,79,12,15 });
		laser[z].anim[6][0].PushBack({ 78,79,14,16 }); // BIG
		laser[z].anim[6][0].speed = 1.0f;
		// MID ---
		for (uint i = 1; i < 4; ++i)
		{
			laser[z].anim[6][i].PushBack({ 85,96,16,16 }); // BIG
			laser[z].anim[6][i].PushBack({ 57,95,14,16 });
			laser[z].anim[6][i].PushBack({ 31,94,12,16 });
			laser[z].anim[6][i].PushBack({ 7,93,10,16 });

			laser[z].anim[6][i].PushBack({ 31,94,12,16 });
			laser[z].anim[6][i].PushBack({ 57,95,14,16 });
			laser[z].anim[6][i].PushBack({ 85,96,16,16 }); // BIG
			laser[z].anim[6][i].speed = 1.0f;
		}
		// "down" bottom cap
		laser[z].anim[6][4].PushBack({ 94,113,14,16 }); // BIG
		laser[z].anim[6][4].PushBack({ 66,112,12,15 });
		laser[z].anim[6][4].PushBack({ 40,111,10,14 });
		laser[z].anim[6][4].PushBack({ 16,110,9,13 });

		laser[z].anim[6][4].PushBack({ 40,111,10,14 });
		laser[z].anim[6][4].PushBack({ 66,112,12,15 });
		laser[z].anim[6][4].PushBack({ 94,113,14,16 }); // BIG
		laser[z].anim[6][4].speed = 1.0f;
		// -----------------------------------------------------
		// 157.5 degrees ---------------
		// "up" top cap
		laser[z].anim[7][0].PushBack({ 94,29,16,14 }); // BIG
		laser[z].anim[7][0].PushBack({ 46,29,15,12 });
		laser[z].anim[7][0].PushBack({ 0,29,14,10 });
		laser[z].anim[7][0].PushBack({ 189,0,13,8 });

		laser[z].anim[7][0].PushBack({ 0,29,14,10 });
		laser[z].anim[7][0].PushBack({ 46,29,15,12 });
		laser[z].anim[7][0].PushBack({ 94,29,16,14 }); // BIG
		laser[z].anim[7][0].speed = 1.0f;
		// mid
		for (uint i = 1; i < 4; ++i)
		{
			laser[z].anim[7][i].PushBack({ 111,35,16,16 }); // BIG
			laser[z].anim[7][i].PushBack({ 62,36,16,14 });
			laser[z].anim[7][i].PushBack({ 15,36,16,12 });
			laser[z].anim[7][i].PushBack({ 202,7,16,10 });

			laser[z].anim[7][i].PushBack({ 15,36,16,12 });
			laser[z].anim[7][i].PushBack({ 62,36,16,14 });
			laser[z].anim[7][i].PushBack({ 111,35,16,16 }); // BIG
			laser[z].anim[7][i].speed = 1.0f;
		}
		// "down" bottom cap
		laser[z].anim[7][4].PushBack({ 128,44,16,14 }); // BIG
		laser[z].anim[7][4].PushBack({ 79,45,15,12 });
		laser[z].anim[7][4].PushBack({ 32,45,14,10 });
		laser[z].anim[7][4].PushBack({ 219,16,13,8 });

		laser[z].anim[7][4].PushBack({ 32,45,14,10 });
		laser[z].anim[7][4].PushBack({ 79,45,15,12 });
		laser[z].anim[7][4].PushBack({ 128,44,16,14 }); // BIG
		laser[z].anim[7][4].speed = 1.0f;
	}
	// -----------------------------------------------------

	// -----------------------------------------------------
	// LASER FLASH anim
	bigDaddy.laserFlashAnim.PushBack({45,229,10,10});
	bigDaddy.laserFlashAnim.PushBack({ 32,229,12,12 });
	bigDaddy.laserFlashAnim.PushBack({ 17,229,14,14 });
	bigDaddy.laserFlashAnim.PushBack({ 0,229,16,16 });
	bigDaddy.laserFlashAnim.PushBack({ 17,229,14,14 });
	bigDaddy.laserFlashAnim.PushBack({ 32,229,12,12 });
	bigDaddy.laserFlashAnim.speed = 0.25f;
	//bigDaddy.laserFlashAnim.repeat = false;

	// ---------------------------------------------------------------------------------------------


	//collider = App->collision->AddCollider({ 0, 0, 44, 48 }, COLLIDER_TYPE::COLLIDER_ENEMY, (Module*)App->enemies);


	// start timers
	bigDaddy.start_shoot_time = SDL_GetTicks();

	//offset[0][1] = { 13,0 };

	
	// -----------------------------------------------------
	// OFFSETS distances for the right/left laser, this distances measures how long can reach the first instantiated cap before the next part is activated
	// right/left offsets
	offset[0][0] = { 13,0}; // only in consideration on REVERSE order ( 4 to 0, cap right mid mid mid cap left)
	offset[0][1] = { 13,0 };
	offset[0][2] = { 16,0 };
	offset[0][3] = { 13,0 };
	offset[0][4] = { 13,0 }; // only in consideration on normal mounting order ( left to right in this case ) 0 to 4, cap left, mid mid mid cap right)
	// up down laser offsets
	offset[1][0] = { 0,13 }; // only in consideration on REVERSE order ( 4 to 0, cap right mid mid mid cap left)
	offset[1][1] = { 0,13 };
	offset[1][2] = { 0,13 };
	offset[1][3] = { 0,13 };
	offset[1][4] = { 0,13 }; // on
	// 3pi/4
	offset[2][0] = { 8,10 };
	offset[2][1] = { 10,10 };
	offset[2][2] = { 10,10 };
	offset[2][3] = { 8,10 };
	offset[2][4] = { 8,10 };
	// PI/4
	offset[3][0] = { -9,10 };
	offset[3][1] = { -8,10 };
	offset[3][2] = { -10,10 };
	offset[3][3] = { -8,10 };
	offset[3][4] = { -9,10 };
	// 22.5
	offset[4][0] = { -11,5 };
	offset[4][1] = { -14,7 };
	offset[4][2] = { -14,7 };
	offset[4][3] = { -10,4 };
	offset[4][4] = { -11,5 };
	// 67.5
	offset[5][0] = { -6,14 };
	offset[5][1] = { -4,9 };
	offset[5][2] = { -5,10 };
	offset[5][3] = { -4,9 };
	offset[5][4] = { -6,14 };
	// 112.5
	offset[6][0] = { 6,14 };
	offset[6][1] = { 4,9 };
	offset[6][2] = { 5,10 };
	offset[6][3] = { 4,9 };
	offset[6][4] = { 6,14 };
	// 157.5
	offset[7][0] = { 8,3 };
	offset[7][1] = { 13,6 };
	offset[7][2] = { 14,7 };
	offset[7][3] = { 12,6 };
	offset[7][4] = { 8,3 };


	// indicates wich axis direcion laser we have to instantiate/move/animate
	//laser.laserAxisIndex = 0; // right left situation || LINKS to the animation data
	//laser.laserAxisIndex = 7; // Up and down situation ------------------------------------------------------------------

	// spawn points boss laser corners
	/*laser.instantiationPosition[0] = { position.x + 2, position.y + 2 }; // left up corner
	laser.instantiationPosition[1] = { position.x + 64, position.y + 2}; // left down corner
	laser.instantiationPosition[2] = { position.x + 2 , position.y + 60 }; // left down corner
	laser.instantiationPosition[3] = { position.x + 64 , position.y + 60 }; // right down corner*/

	// test
	/*laser.position[0][0] = laser.instantiationPosition[0];
	laser.position[0][4] = laser.instantiationPosition[0];
	laser.position[1][4] = laser.instantiationPosition[0];
	laser.position[1][0] = laser.instantiationPosition[0];*/
	// important laser shooting logic activators ----
	/*laser.laserPartIndex[0] = 0; // direction cap selector
	laser.instantiationPoint = 0;*/
	//laser.laserPartIndex[1] = 4;
	// activate laser parts
	//laser.active[laser.laserAxisIndex][laser.laserPartIndex[0]] = true;

	// positions
	original_pos.x = x;//172;
	original_pos.y = 102;

	fposition.x = x;
	fposition.y = 102;

	//position.x = 120;
	//position.y = 20;

	// PATHS -----------------------------------------------------------------------
	// ONSTAGE path --
	// mid to right and shoot position
	bigDaddy.onStagePath.PushBack({ 1, 0},5, bigDaddy.travelAnim);
	bigDaddy.onStagePath.PushBack({ 2, -0.5f }, 50, bigDaddy.travelAnim);
	bigDaddy.onStagePath.PushBack({ 2, -0.3f }, 25, bigDaddy.travelAnim);
	bigDaddy.onStagePath.PushBack({ 1.3f, +0.3f }, 50, bigDaddy.travelAnim);
	bigDaddy.onStagePath.PushBack({ 0.7f, +0.6f }, 70, bigDaddy.travelAnim);
	bigDaddy.onStagePath.PushBack({ 1.0f, +1.0f }, 30, bigDaddy.travelAnim);

	bigDaddy.onStagePath.PushBack({ 1.0f, 0.0f }, 172, bigDaddy.onStageAnim); // shoot

	// to left
	bigDaddy.onStagePath.PushBack({ -0.2f, -0.3f }, 40, bigDaddy.travelAnim);
	bigDaddy.onStagePath.PushBack({ -0.2f, +0.3f }, 25, bigDaddy.travelAnim);
	bigDaddy.onStagePath.PushBack({ -0.3f, -0.4f }, 30, bigDaddy.travelAnim);
	bigDaddy.onStagePath.PushBack({ 0.5f, 0.3f }, 35, bigDaddy.travelAnim);
	bigDaddy.onStagePath.PushBack({ 1.0f, 0.3f }, 21, bigDaddy.travelAnim);

	bigDaddy.onStagePath.PushBack({ 1.0f, 0.0f }, 172, bigDaddy.onStageAnim); // shoot

	// to up 
	bigDaddy.onStagePath.PushBack({ -0.1f, -0.5f }, 30, bigDaddy.travelAnim);
	bigDaddy.onStagePath.PushBack({ 1.2f, -0.6f }, 40, bigDaddy.travelAnim);
	bigDaddy.onStagePath.PushBack({ 1.2f, -0.6f }, 40, bigDaddy.travelAnim);
	bigDaddy.onStagePath.PushBack({ 2.0f, -0.2f }, 40, bigDaddy.travelAnim);
	bigDaddy.onStagePath.PushBack({ 2.0f, 0.4f }, 41, bigDaddy.travelAnim);

	bigDaddy.onStagePath.PushBack({ 1.0f, 0.0f }, 172, bigDaddy.onStageAnim); // shoot

	// ---------------------------------------------------------------------------------
	// FOREGROUND path
	//bigDaddy.onForeground.PushBack({});


	//bigDaddy.onStagePath.loop = false;

	// assign the current enemy stage
	bigDaddy.current_enemy_step = currentState::FOREGROUND;
	bigDaddy.start_foreground_time = SDL_GetTicks();

	animation = &bigDaddy.foregroundAnim;

	// deactivate the first collision with unit to avoid some circunstances
	readyToRumble = false;
}

void EnemyBigDaddy::Move()
{
	//position.x = fposition.x;
	//position.y = fposition.y;
	//fposition.x = position.x;
	//fposition.y = position.y;
	// updates laser instantiation position to follow enemy position || instatiation point position
	/*bigDaddy.instantiationPosition[0] = { position.x + 2, position.y + 2 }; // left up corner
	bigDaddy.instantiationPosition[1] = { position.x + 64, position.y + 2 }; // right up corner
	bigDaddy.instantiationPosition[2] = { position.x + 2 , position.y + 60 }; // left down corner
	bigDaddy.instantiationPosition[3] = { position.x + 64 , position.y + 60 }; // right down corner*/

	// faked instantiation positions to nicolas with faked printed method to do correct open/close animation of the enemy...
	bigDaddy.instantiationPosition[0] = { position.x + 2, position.y - 26 }; // left up corner
	bigDaddy.instantiationPosition[1] = { position.x + 64, position.y - 26 }; // right up corner
	bigDaddy.instantiationPosition[2] = { position.x + 2 , position.y + 26  }; // left down corner
	bigDaddy.instantiationPosition[3] = { position.x + 64 , position.y + 26  }; // right down corner
	// ---------------------------------------------------------------------------------------------------------------------
	//fposition.x -= 1.35;
	//position.x = fposition.x;
	//position.x += 1; // ENEMY position
	if (bigDaddy.current_enemy_step == FOREGROUND)
	{
		if (bigDaddy.going_up)
		{
			if (bigDaddy.wave > 1.0f)
				bigDaddy.going_up = false;
			else
				bigDaddy.wave += 0.08f;
		}
		else
		{
			if (bigDaddy.wave < -1.0f)
				bigDaddy.going_up = true;
			else
				bigDaddy.wave -= 0.08f;
		}

		position.y = 102 + int(7.0f * sinf(bigDaddy.wave));
		fposition.x += 1.3f;
		position.x = fposition.x;

		// timer
		bigDaddy.now_foreground_time = SDL_GetTicks() - bigDaddy.start_foreground_time;

		if (bigDaddy.now_foreground_time > bigDaddy.total_foreground_time)
		{
			bigDaddy.current_enemy_step = ENTRYANIM;
			//original_pos = position;
			//position.y = fposition.y;
			//fposition.x = position.x;
			//fposition.y = position.y;
		}
	}
	if (bigDaddy.current_enemy_step == ENTRYANIM)
	{
		animation = &bigDaddy.entryAnim;
		if (bigDaddy.entryAnim.finish)
		{
			bigDaddy.current_enemy_step = ONSTAGE;
			original_pos = position;
			// PLAY SFX
			App->audio->ControlAudio("entryScene",SFX,PLAY);
		}
		position.x += 1;
	}

	if (bigDaddy.current_enemy_step == ONSTAGE)
	{
		// ADDS COLLIDER
		if (collider== nullptr)
			collider = App->collision->AddCollider({ 0, 0, 44, 48 }, COLLIDER_TYPE::COLLIDER_ENEMY, (Module*)App->enemies);

		position = original_pos + bigDaddy.onStagePath.GetCurrentSpeed(&animation);
	}

	// checks the num of attacks, then goodbye
	if (numAttacks == 7)
	{
		bigDaddy.current_enemy_step = GOODBYEANIM;
		fposition.x = position.x;
	}
	if (bigDaddy.current_enemy_step == GOODBYEANIM)
	{
		// DESTROY COLLIDER
		if (collider != nullptr)
		{
			collider->to_delete = true;
			collider = nullptr;
		}

		animation = &bigDaddy.goodByeAnim;

		// assigns speed to last goodBye
		fposition.x -= 0.07f;
		position.x = fposition.x;
	}
	//else
		//position.x += 1;

	//fposition.x = position.x;
	//fposition.y = position.y;

	// check player angle and decide what laser axis to spawn and the cap wich are pointing to

	//youDecide();

	// this array stores the first shooted part of one of the total 4 instantiation enemy corner points 
	// for do correct for loops checks(inverse/reverse order), or this is the intention
	// in really only stores the last or the first 0/4 (order for activate the correct parts dependent of direction)
	//laser[0].laserPartIndex[0] = 4;
	// activate laser parts
	//laser[0].active[0][laser[0].laserPartIndex[0]] = true;

	// UPDATES POSITIONS OF ALL PARTS of the LASERS -----------------------------------------------
	// check if the instantiated laser need to be mounted in inverse/reverse
	// if is to the right to left 4 to 0... and the next part of the chain isnt yet instantiated, associate each parts positions and updates it

	for (uint z = 0; z < numActiveLasers; ++z)
	{
		for (uint i = 0; i < 5; ++i)
		{
			if (laser[z].active[laser[z].laserAxisIndex][i])
			{
				laser[z].fposition[laser[z].laserAxisIndex][i].x += laser[z].xSpeed + 1;
				//laser.fposition[laser.laserAxisIndex][i].x += 1;
				laser[z].fposition[laser[z].laserAxisIndex][i].y += laser[z].ySpeed;
				laser[z].position[laser[z].laserAxisIndex][i].x = laser[z].fposition[laser[z].laserAxisIndex][i].x; //2; //5 to right
				laser[z].position[laser[z].laserAxisIndex][i].y = laser[z].fposition[laser[z].laserAxisIndex][i].y;

				// updates laser colliders positions
				if(laser[z].laserCollider != nullptr)
					laser[z].laserCollider->SetPos(laser[z].position[laser[z].laserAxisIndex][laser[z].laserPartIndex[0]].x, laser[z].position[laser[z].laserAxisIndex][laser[z].laserPartIndex[0]].y);
			}
		}
	}



	// -----------------------------------------------------------------------------------

	// set colliders pos
	if(collider != nullptr)
		collider->SetPos(position.x + 10, position.y - 20);

	
	//laser.position[1][0].x += 2;
	//laser.position[0][0].y = 100;

}

void EnemyBigDaddy::youDecide()
{


	if (numActivePlayers == 2) numActiveLasers = 4;
	else
		numActiveLasers = 2;

	fPoint sourcePos;

	float pointDistances[4];

	//for (uint z = 0; z < numActiveLasers; z++)
	//{
		for (uint i = 0; i < 4; ++i) // store all the distances nearest to the nearest active player
		{
			sourcePos.x = bigDaddy.instantiationPosition[i].x;
			sourcePos.y = bigDaddy.instantiationPosition[i].y;

			pointDistances[i] = GetNearestPlayerSqrtDistance(sourcePos);
		}

		float tempValue = 500; // fake distance (player never can be than far away)
		float tempValue2 = 500; // fake distance

		int secondPoint = 0;

		int assignedP[4] = {-1,-1,-1,-1}; // not assigned yet

		// checks the nearest point
		for (uint i = 0; i < 4; ++i)
		{
			if (pointDistances[i] < tempValue)
			{
				tempValue = pointDistances[i];
				laser[0].instantiationPoint = i;
				//instantiationIndex = i;
				assignedP[0] = i;
			}
		}
		// second check to decide the next second point nearest to player
		for (uint i = 0; i < 4; ++i)
		{
			// if index is the same checked before continue
			if (pointDistances[i] == tempValue) continue;

			if (pointDistances[i] < tempValue2)
			{
				tempValue2 = pointDistances[i];
				secondPoint = i;
				laser[1].instantiationPoint = i; // second laser instantiation point
				assignedP[1] = i;
				//instantiationIndex = i;
			}
		}

		// assign the rest of points 
		// checks the no assigned instantiation points
		if (numActiveLasers > 2)
		{
			for (uint i = 0; i < 4; i++)
			{
				if (assignedP[i] == -1) // if is not assigned
				{
					for (uint z = 0; z < 4; z++)
					{
						if (z == laser[i].instantiationPoint) 
							continue;

						if (z != laser[z].instantiationPoint)
						{
							laser[z].instantiationPoint = z;
							//break;
						}

					}
				}
			}
		}

		
		for (uint z = 0; z < numActiveLasers; z++)
		{
			sourcePos.x = bigDaddy.instantiationPosition[laser[z].instantiationPoint].x;
			sourcePos.y = bigDaddy.instantiationPosition[laser[z].instantiationPoint].y;

			laser[z].distance = GetNearestPlayerSqrtDistance(sourcePos);

			//if (nearestTarget == nearestPlayer::P1 && !laser[z].active[laser[z].laserAxisIndex][laser[z].laserPartIndex[0]])
			if (!laser[z].active[laser[z].laserAxisIndex][laser[z].laserPartIndex[0]])
			{
				float tx;
				float ty;

				if (nearestTarget == P1)
				{
					tx = App->player[0]->position.x - sourcePos.x;
					ty = App->player[0]->position.y - sourcePos.y;
				}
				else
				{
					tx = App->player[1]->position.x - sourcePos.x;
					ty = App->player[1]->position.y - sourcePos.y;
				}

				laser[z].playerAngle = atan2f(ty, tx);

				laser[z].xSpeed = 4 * cos(laser[z].playerAngle);
				laser[z].ySpeed = 4 * sin(laser[z].playerAngle);

				bigDaddy.now_shoot_time = SDL_GetTicks() - bigDaddy.start_shoot_time;

				//if (bigDaddy.now_shoot_time >= bigDaddy.cadence_shoot_time)
					//bigDaddy.attack = true;

				// assigns correct cap and axis to "instantiated" laser
				assignAxis(z);
				//if (laser.playerAngle)
			}
		}

		//LOG("playerAngle: %f", laser.playerAngle);
	//}
		//}
}

void EnemyBigDaddy::assignAxis(uint index)
{
	// check lasers angles
	// 2.35 = 135 degrees

	float AlphaCentaury = laser[index].playerAngle;

	// mid down situations
	if (AlphaCentaury > 2.94f)// 0 || AlphaCentaury < 0.39f)
	{
		laser[index].laserAxisIndex = 0;
		laser[index].laserPartIndex[0] = 0;
	}
	if (AlphaCentaury > 2.67f && AlphaCentaury < 2.94f)
	{
		laser[index].laserAxisIndex = 4;
		laser[index].laserPartIndex[0] = 4;
	}
	if (AlphaCentaury > 2.17f && AlphaCentaury < 2.67f)
	{
		laser[index].laserAxisIndex = 3;
		laser[index].laserPartIndex[0] = 4;
	}
	if (AlphaCentaury > 1.77f && AlphaCentaury < 2.17f)
	{
		laser[index].laserAxisIndex = 5;
		laser[index].laserPartIndex[0] = 4;
	}
	if (AlphaCentaury > 1.37f && AlphaCentaury < 1.77f) // mid bottom 1.57 offset 0.2
	{
		laser[index].laserAxisIndex = 1;
		laser[index].laserPartIndex[0] = 4;
	}
	if (AlphaCentaury > 0.97f && AlphaCentaury < 1.37f)
	{
		laser[index].laserAxisIndex = 6;
		laser[index].laserPartIndex[0] = 4;
	}
	if (AlphaCentaury > 0.47f && AlphaCentaury < 0.97f)
	{
		laser[index].laserAxisIndex = 2;
		laser[index].laserPartIndex[0] = 4;
	}
	if (AlphaCentaury > 0.17f && AlphaCentaury < 0.47f)
	{
		laser[index].laserAxisIndex = 7;
		laser[index].laserPartIndex[0] = 4;
	}
	if (AlphaCentaury > 0 && AlphaCentaury < 0.17f)
	{
		laser[index].laserAxisIndex = 0;
		laser[index].laserPartIndex[0] = 4;
	}
	// mid up situations
	if (AlphaCentaury < 0 && AlphaCentaury > -0.17f)
	{
		laser[index].laserAxisIndex = 0;
		laser[index].laserPartIndex[0] = 4;
	}
	if (AlphaCentaury < -0.17 && AlphaCentaury > -0.47f)
	{
		laser[index].laserAxisIndex = 4;
		laser[index].laserPartIndex[0] = 0;
	}
	if (AlphaCentaury < -0.47 && AlphaCentaury > -0.97f)
	{
		laser[index].laserAxisIndex = 3;
		laser[index].laserPartIndex[0] = 0;
	}
	if (AlphaCentaury < -0.97 && AlphaCentaury > -1.37f)
	{
		laser[index].laserAxisIndex = 5;
		laser[index].laserPartIndex[0] = 0;
	}
	if (AlphaCentaury < -1.37 && AlphaCentaury > -1.77f)
	{
		laser[index].laserAxisIndex = 1;
		laser[index].laserPartIndex[0] = 0;
	}
	if (AlphaCentaury < -1.77 && AlphaCentaury > -2.17f)
	{
		laser[index].laserAxisIndex = 6;
		laser[index].laserPartIndex[0] = 0;
	}
	if (AlphaCentaury < -2.17 && AlphaCentaury > -2.67f)
	{
		laser[index].laserAxisIndex = 2;
		laser[index].laserPartIndex[0] = 0;
	}
	if (AlphaCentaury < -2.67 && AlphaCentaury > -2.94f)
	{
		laser[index].laserAxisIndex = 7;
		laser[index].laserPartIndex[0] = 0;
	}
	if (AlphaCentaury < -2.94)
	{
		laser[index].laserAxisIndex = 0;
		laser[index].laserPartIndex[0] = 0;
	}

}

void EnemyBigDaddy::Draw()
{

	LOG("NUM ATTACKS: %d", numAttacks);
	// check shooting cadence time
	/*bigDaddy.now_shoot_time = SDL_GetTicks() - bigDaddy.start_shoot_time;
	if (bigDaddy.now_shoot_time > bigDaddy.cadence_shoot_time && !bigDaddy.attack)
	{
		bigDaddy.attack = true;
	}*/

	// full body onStage animation
	//App->render->Blit(enemyTex,position.x, position.y, &bigDaddy.onStageAnim->GetCurrentFrame());
	//if (receiveDamage) animation = &animation[DAMAGE_ANIM];

	// check if we are taken damage and swaps -------------------------------------------------------
	if (receiveDamage)
	{
		nowDamagetime = SDL_GetTicks() - start_damage_time;
		if (nowDamagetime > damageAnimTime) receiveDamage = false;

		animation = &animation[DAMAGE_ANIM];
		animation->current_frame = bigDaddy.current_frame;
	}
	else
	{
		animation = &animation[NORMAL_ANIM];
		animation->current_frame = bigDaddy.current_frame;
	}

	bigDaddy.rect = animation->GetCurrentFrame();


	App->render->Blit(enemyTex, position.x, position.y - bigDaddy.rect.h / 2, &bigDaddy.rect);

	bigDaddy.current_frame = animation->current_frame;
	
	// ----------------------------------------------------------------------------------------------

	//if (bigDaddy.onStageAnim->finish && !bigDaddy.attack)
	if ((int)bigDaddy.onStageAnim->current_frame == 6 && readyForNextShot)//&& bigDaddy.onStageAnim->current_frame < 7 && !bigDaddy.attack)
	{
		youDecide();
		bigDaddy.attack = true;
		readyForNextShot = false;
		// PLAY SFX
		App->audio->ControlAudio("openAndLaser", SFX, PLAY);
	}
	// checks if we can receive damage
	if (animation == bigDaddy.onStageAnim)
	{
		canReceiveDamage = true;

	}
	else
		canReceiveDamage = false;

	if (animation != bigDaddy.onStageAnim && !readyForNextShot)
	{
		bigDaddy.onStageAnim->finish = false;
		bigDaddy.onStageAnim->current_frame = 0;
		readyForNextShot = true;
		numAttacks++;
		// PLAY SFX
		App->audio->ControlAudio("close", SFX,PLAY);
	}

	// instantiate laser beams
	for (uint z = 0; z < numActiveLasers; z++)
	{
		if (bigDaddy.attack && !laser[z].active[laser[z].laserAxisIndex][laser[z].laserPartIndex[0]])
		{
			laser[z].active[laser[z].laserAxisIndex][laser[z].laserPartIndex[0]] = true;
			laser[z].position[laser[z].laserAxisIndex][laser[z].laserPartIndex[0]] = bigDaddy.instantiationPosition[laser[z].instantiationPoint]; //+ offset[laser.laserAxisIndex][laser.laserPartIndex[0]];

			// assign fpositions
			laser[z].fposition[laser[z].laserAxisIndex][laser[z].laserPartIndex[0]].x = laser[z].position[laser[z].laserAxisIndex][laser[z].laserPartIndex[0]].x;
			laser[z].fposition[laser[z].laserAxisIndex][laser[z].laserPartIndex[0]].y = laser[z].position[laser[z].laserAxisIndex][laser[z].laserPartIndex[0]].y;

			// ADD colliders to cap
			if(laser[z].laserCollider == nullptr)
				laser[z].laserCollider = App->collision->AddCollider({0,0,10,10}, COLLIDER_ENEMY_SHOT, (Module*)App->enemies);
			

			if (z == numActiveLasers -1)
			{
				bigDaddy.attack = false;
				bigDaddy.start_shoot_time = SDL_GetTicks();
				// general timer
				//start_all_shoots_time = SDL_GetTicks();
				//bigDaddy.showFlashAnim = false;
			}
			start_all_shoots_time = SDL_GetTicks();
			bigDaddy.showFlashAnim = true;
			bigDaddy.start_flash_time = SDL_GetTicks();
		}
	}

	// check distances ---
	for (uint z = 0; z < numActiveLasers; z++)
	{
		if (!laser[z].laserPartIndex[0] > 0)
		{
			if (laser[z].active[laser[z].laserAxisIndex][0]) // "top cap part"
			{
				for (uint i = 1; i < 5; ++i)
				{
					distanceManhattan = laser[z].position[laser[z].laserAxisIndex][0].DistanceManhattan(bigDaddy.instantiationPosition[laser[z].instantiationPoint]);

					if (distanceManhattan > maxDistances[i - 1] && !laser[z].active[laser[z].laserAxisIndex][i])
					{
						laser[z].active[laser[z].laserAxisIndex][i] = true;
						laser[z].position[laser[z].laserAxisIndex][i] = laser[z].position[laser[z].laserAxisIndex][i - 1] + offset[laser[z].laserAxisIndex][i];
						laser[z].anim[laser[z].laserAxisIndex][i].current_frame = laser[z].anim[laser[z].laserAxisIndex][i - 1].current_frame;

						// assign fpositions
						laser[z].fposition[laser[z].laserAxisIndex][i].x = laser[z].position[laser[z].laserAxisIndex][i].x;
						laser[z].fposition[laser[z].laserAxisIndex][i].y = laser[z].position[laser[z].laserAxisIndex][i].y;
					}
					// deactivates laser to prepare next shoot
					/*if (distanceManhattan > 400) // distance with the latest checked part
					{
						for (uint i = 0; i < 5; ++i)
							laser[z].active[laser[z].laserAxisIndex][i] = false;
					}*/

				}
			}
		}
		else
		{
			if (laser[z].active[laser[z].laserAxisIndex][4]) // "bottom cap part"
			{
				for (int i = 4; i >= 0; --i)
				{
					distanceManhattan = laser[z].position[laser[z].laserAxisIndex][4].DistanceManhattan(bigDaddy.instantiationPosition[laser[z].instantiationPoint]);

					if (distanceManhattan > maxDistances[3 - i] && !laser[z].active[laser[z].laserAxisIndex][i])
					{
						laser[z].active[laser[z].laserAxisIndex][i] = true;
						laser[z].position[laser[z].laserAxisIndex][i] = laser[z].position[laser[z].laserAxisIndex][i + 1] - offset[laser[z].laserAxisIndex][i];
						laser[z].anim[laser[z].laserAxisIndex][i].current_frame = laser[z].anim[laser[z].laserAxisIndex][i + 1].current_frame;

						// assign fpositions
						laser[z].fposition[laser[z].laserAxisIndex][i].x = laser[z].position[laser[z].laserAxisIndex][i].x;
						laser[z].fposition[laser[z].laserAxisIndex][i].y = laser[z].position[laser[z].laserAxisIndex][i].y;
					}

					// deactivates laser to prepare next shoot
					/*if (distanceManhattan > 400) // distance with the latest checked part
					{
						for (uint i = 0; i < 5; ++i)
							laser[z].active[laser[z].laserAxisIndex][i] = false;
					}*/
				}
			}
		}
	}

	// timer for destroy all lasers independent of its distance
	now_all_shoots_time = SDL_GetTicks() - start_all_shoots_time;
	if (now_all_shoots_time > time_to_destroy)
	{
		for (uint i = 0; i < numActiveLasers; ++i)
		{
			for (uint z = 0; z < 5; z++) // deactivate all parts
			{
				if (laser[i].active[laser[i].laserAxisIndex][z])
				{
					laser[i].active[laser[i].laserAxisIndex][z] = false;
				}
			}
			// remove laser collider
			if (laser[i].laserCollider != nullptr)
			{
				laser[i].laserCollider->to_delete = true;
				laser[i].laserCollider = nullptr;
			}
		}
	}


	

	// DRAW active lasers
	for (uint z = 0; z < numActiveLasers; z++)
	{
		for (uint i = 0; i < 5; ++i) // all parts, all active lasers
		{

			if (laser[z].active[laser[z].laserAxisIndex][i])
			{
				laser[z].rect = laser[z].anim[laser[z].laserAxisIndex][i].GetCurrentFrame();

				App->render->Blit(laserTexture, laser[z].position[laser[z].laserAxisIndex][i].x - laser[z].rect.w / 2, laser[z].position[laser[z].laserAxisIndex][i].y - laser[z].rect.h / 2, &laser[z].rect);
			}
		}
	}

	// DRAW LASER FLASH animation
	if (bigDaddy.showFlashAnim)
	{
		bigDaddy.now_flash_time = SDL_GetTicks() - bigDaddy.start_flash_time;
		if (bigDaddy.now_flash_time > bigDaddy.total_flash_time)
		{
			bigDaddy.showFlashAnim = false;
			bigDaddy.laserFlashAnim.current_frame = 0;
		}

		bigDaddy.flashRect = bigDaddy.laserFlashAnim.GetCurrentFrame();

		for (uint i = 0; i < numActiveLasers; ++i)
		{

			App->render->Blit(laserTexture, bigDaddy.instantiationPosition[laser[i].instantiationPoint].x - 5 + pivotFlashAnim[(int)bigDaddy.laserFlashAnim.current_frame].x,
				bigDaddy.instantiationPosition[laser[i].instantiationPoint].y + pivotFlashAnim[(int)bigDaddy.laserFlashAnim.current_frame].y - 5, &bigDaddy.flashRect);
		}
	}
}

void EnemyBigDaddy::OnCollision(Collider* collider, Collider* collider2)
{

	if (collider->type == COLLIDER_PLAYER_SHOT && canReceiveDamage)
	{
		receiveDamage = true;
		start_damage_time = SDL_GetTicks();
		life -= collider->damage;
	}

}

void EnemyBigDaddy::OnCollisionUnit(Collider* c2, Collider* c1)
{
	if (readyToRumble == true) 
	{ 
		readyToRumble = false; 
		receiveDamage = true; 
	}
	
	else
	{
		now_unit_damage_time = SDL_GetTicks() - start_unit_damage_time;

		if (now_unit_damage_time >= cadence_unit_damage_time && canReceiveDamage)
			readyToRumble = true;
	}
}


EnemyBigDaddy::~EnemyBigDaddy()
{
	// unloads laser texture
	App->textures->Unload(laserTexture);
	
	// removes all colliders
	for (uint i = 0; i < numActiveLasers; ++i)
	{
		if (laser[i].laserCollider != nullptr)
		{
			laser[i].laserCollider->to_delete = true;
			laser[i].laserCollider = nullptr;
		}
	}

	// unloads SFX
	App->audio->UnloadAudio("entryScene",SFX);
	App->audio->UnloadAudio("close", SFX);
	App->audio->UnloadAudio("openAndLaser", SFX);

}