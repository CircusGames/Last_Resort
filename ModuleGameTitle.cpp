#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleGameTitle.h"
#include "ModuleSceneLvl1.h"
#include "ModuleInput.h"
#include "ModuleFadeToBlack.h"
#include "ModuleAudio.h"

#include "SDL/include/SDL_timer.h"

#include "SDL/include/SDL_render.h"

ModuleGameTitle::ModuleGameTitle()
{

	//rect for title screen after swap animated letters to fixed background
	titleScreenRect.x = 0;
	titleScreenRect.y = 0;
	titleScreenRect.w = 276;
	titleScreenRect.h = 139;

	//snk rect
	snk.x = 0;
	snk.y = 0;
	snk.w = 72;
	snk.h = 19;
	
	//snkCorp rect
	snkCorp.x = 0;
	snkCorp.y = 0;
	snkCorp.w = 168;
	snkCorp.h = 8;


	//animation pushStart Button
	/*pushStart.PushBack({ 276,110,138,11 });
	pushStart.PushBack({ 138,110,138,11 });
	pushStart.PushBack({ 0,110,138,11 });
	pushStart.PushBack({ 276,99,138,11 });
	pushStart.PushBack({ 138,99,138,11 });*/

	pushStart.PushBack({ 0,99,138,11 });
	pushStart.PushBack({ 276,88,138,11 });
	pushStart.PushBack({ 138,88,138,11 });
	pushStart.PushBack({ 0,88,138,11 });
	pushStart.PushBack({ 276,77,138,11 });
	pushStart.PushBack({ 138,77,138,11 });
	pushStart.PushBack({ 0,77,138,11 });
	pushStart.PushBack({ 276,66,138,11 });
	pushStart.PushBack({ 138,66 ,138,11 });
	pushStart.PushBack({ 0,66,138,11 });
	pushStart.PushBack({ 276,55, 138,11 });
	pushStart.PushBack({ 138,55, 138,11 });
	pushStart.PushBack({ 0,55, 138,11 });
	pushStart.PushBack({ 276,44, 138,11 });
	pushStart.PushBack({ 138,44, 138,11 });
	pushStart.PushBack({ 0,44, 138,11 });
	pushStart.PushBack({ 276,33, 138,11 });
	pushStart.PushBack({ 138, 33, 138,11 });
	pushStart.PushBack({ 0,33, 138,11 });
	pushStart.PushBack({ 276,22, 138,11 });
	pushStart.PushBack({ 138,22, 138,11 });
	pushStart.PushBack({ 0 ,22, 138,11 });
	pushStart.PushBack({ 276,11, 138,11 });
	pushStart.PushBack({ 138,11, 138,11 });
	pushStart.PushBack({ 0,11, 138,11 });
	pushStart.PushBack({ 276,0, 138,11 });
	pushStart.PushBack({ 138,0,138,11 });
	//full light -------------------------
	pushStart.PushBack({ 0,0, 138,11 });
	pushStart.PushBack({ 0,0, 138,11 });
	pushStart.PushBack({ 0,0, 138,11 });
	pushStart.PushBack({ 0,0, 138,11 });
	pushStart.PushBack({ 0,0, 138,11 });
	pushStart.PushBack({ 0,0, 138,11 });
	pushStart.PushBack({ 0,0, 138,11 });
	pushStart.PushBack({ 0,0, 138,11 });
	pushStart.PushBack({ 0,0, 138,11 });
	pushStart.PushBack({ 0,0, 138,11 });
	pushStart.PushBack({ 0,0, 138,11 });
	// -----------------------------------
	//pushStart.PushBack({ 0,0, 138,11 });
	pushStart.PushBack({ 138,0,138,11 });
	pushStart.PushBack({ 276,0, 138,11 });
	pushStart.PushBack({ 0,11, 138,11 });
	pushStart.PushBack({ 138,11, 138,11 });
	pushStart.PushBack({ 276,11, 138,11 });
	pushStart.PushBack({ 0 ,22, 138,11 });
	pushStart.PushBack({ 138,22, 138,11 });
	pushStart.PushBack({ 276,22, 138,11 });
	pushStart.PushBack({ 0,33, 138,11 });
	pushStart.PushBack({ 138, 33, 138,11 });
	pushStart.PushBack({ 276,33, 138,11 });
	pushStart.PushBack({ 0,44, 138,11 });
	pushStart.PushBack({ 138,44, 138,11 });
	pushStart.PushBack({ 276,44, 138,11 });
	pushStart.PushBack({ 0,55, 138,11 });
	pushStart.PushBack({ 138,55, 138,11 });
	pushStart.PushBack({ 276,55, 138,11 });
	pushStart.PushBack({ 0,66,138,11 });
	pushStart.PushBack({ 138,66 ,138,11 });
	pushStart.PushBack({ 276,66,138,11 });
	pushStart.PushBack({ 0,77,138,11 });
	pushStart.PushBack({ 138,77,138,11 });
	pushStart.PushBack({ 276,77,138,11 });
	pushStart.PushBack({ 0,88,138,11 });
	pushStart.PushBack({ 138,88,138,11 });
	pushStart.PushBack({ 276,88,138,11 });
	pushStart.PushBack({ 0,99,138,11 });
	pushStart.PushBack({ 138,99,138,11 });
	pushStart.PushBack({ 276,99,138,11 });
	pushStart.PushBack({ 0,110,138,11 });
	pushStart.PushBack({ 138,110,138,11 });
	//light off ---------------------------
	pushStart.PushBack({ 276,110,138,11 });
	pushStart.PushBack({ 276,110,138,11 });
	pushStart.PushBack({ 276,110,138,11 });
	pushStart.PushBack({ 276,110,138,11 });
	pushStart.PushBack({ 276,110,138,11 });
	pushStart.PushBack({ 276,110,138,11 });
	pushStart.PushBack({ 276,110,138,11 });
	pushStart.PushBack({ 276,110,138,11 });
	pushStart.PushBack({ 276,110,138,11 });

	pushStart.PushBack({ 276,110,138,11 });
	pushStart.PushBack({ 138,110,138,11 });
	pushStart.PushBack({ 0,110,138,11 });
	pushStart.PushBack({ 276,99,138,11 });
	pushStart.PushBack({ 138,99,138,11 });

	pushStart.speed = 0.5f;

	//letter L rects ----------------------------------------------------
	letters[0].PushBack({ 468,297,13,25 });
	letters[0].PushBack({ 454,297,14,37 });
	letters[0].PushBack({ 439,297,15,58 });
	letters[0].PushBack({ 421,297,18,66 });
	letters[0].PushBack({ 401,297,20,76 });
	letters[0].PushBack({ 380,297,21,79 });
	letters[0].PushBack({ 359,297,21,83 });
	letters[0].PushBack({ 338,297,21,81 });
	letters[0].PushBack({ 317,297,21,92 });
	letters[0].PushBack({ 296,297,21,101 });
	letters[0].PushBack({ 273,297,23,102 });
	letters[0].PushBack({ 250,297,23,107 });
	letters[0].PushBack({ 227,297,23,96 });
	letters[0].PushBack({ 204,297,23,112 });
	letters[0].PushBack({ 181,297,23,114 });
	letters[0].PushBack({ 158,297,23,116 });
	letters[0].PushBack({ 135,297,23,117 });
	letters[0].PushBack({ 90,297,45,121 });
	letters[0].PushBack({ 45,297,45,122 });
	letters[0].PushBack({ 0,297,45,122 });
	letters[0].PushBack({ 426,174,45,123 });
	letters[0].PushBack({ 379,174,47,118 });
	letters[0].PushBack({ 332,174,47,106 });
	letters[0].PushBack({ 284,174,48,94 });
	letters[0].PushBack({ 236,174,48,88 });
	letters[0].PushBack({ 188,174,48,84 });
	letters[0].PushBack({ 141,174,47,77 });
	letters[0].PushBack({ 94,174,47,69 });
	letters[0].PushBack({ 47,174,47,66 });
	letters[0].PushBack({ 0,174,47,63 });
	letters[0].PushBack({ 460,114,46,60 });
	letters[0].PushBack({ 414,114,46,57 });
	/*animationL.PushBack({ 368,114,46,57 });
	animationL.PushBack({ 322,114,46,57 });
	animationL.PushBack({ 276,114,46,57 });
	animationL.PushBack({ 230,114,46,57 });
	animationL.PushBack({ 184,114,46,57 });
	animationL.PushBack({ 138,114,46,57 });
	animationL.PushBack({ 92,114,46,57 });
	animationL.PushBack({ 46,114,46,57 });
	animationL.PushBack({ 0,114,46,57 });
	animationL.PushBack({ 460,57,46,57 });
	animationL.PushBack({ 414,57,46,57 });
	animationL.PushBack({ 368,57,46,57 });
	animationL.PushBack({ 322,57,46,57 });
	animationL.PushBack({ 276,57,46,57 });
	animationL.PushBack({ 230,57,46,57 });
	animationL.PushBack({ 184,57,46,57 });
	animationL.PushBack({ 138,57,46,57 });
	animationL.PushBack({ 92,57,46,57 });
	animationL.PushBack({ 46,57,46,57 });
	animationL.PushBack({ 0,57,46,57 });
	animationL.PushBack({ 460,0,46,57 });
	animationL.PushBack({ 414,0,46,57 });
	animationL.PushBack({ 368,0,46,57 });
	animationL.PushBack({ 322,0,46,57 });
	animationL.PushBack({ 276,0,46,57 });
	animationL.PushBack({ 230,0,46,57 });
	animationL.PushBack({ 184,0,46,57 });
	animationL.PushBack({ 138,0,46,57 });
	animationL.PushBack({ 92,0,46,57 });
	animationL.PushBack({ 46,0,46,57 });
	animationL.PushBack({ 0,0,46,57 });*/
	

	//letter A rects
	letters[1].PushBack({ 492,277, 1,1 });
	letters[1].PushBack({ 482,277, 10,15 });
	letters[1].PushBack({ 470,277,12,24 });
	letters[1].PushBack({ 457,277,13,38 });
	letters[1].PushBack({ 444,277, 13,45 });
	letters[1].PushBack({ 431,277, 13,56 });
	letters[1].PushBack({ 418,277, 13,63 });
	letters[1].PushBack({ 405,277,13,72 });
	letters[1].PushBack({ 392,277, 13,80 });
	letters[1].PushBack({ 378,277, 14,87 });
	letters[1].PushBack({ 359,277, 19,92 });
	letters[1].PushBack({ 339,277,20,96 });
	letters[1].PushBack({ 317,277,22,100 });
	letters[1].PushBack({ 295,277,22,101 });
	letters[1].PushBack({ 271,277,24,106 });
	letters[1].PushBack({ 246,277,25,108 });
	letters[1].PushBack({ 208,277,39,111 }); //x= 207
	letters[1].PushBack({ 173,277, 34,115 });
	letters[1].PushBack({ 135,277, 38,114 });
	letters[1].PushBack({ 94,277, 41,122 });
	letters[1].PushBack({ 47,277, 47,122 });
	letters[1].PushBack({ 0,277 , 47,119 });
	letters[1].PushBack({ 456,171 , 47,106 });
	letters[1].PushBack({ 405,171 , 51,94 });
	letters[1].PushBack({ 354,171, 51,84 });
	letters[1].PushBack({ 303,171, 51,77 });
	letters[1].PushBack({ 252,171, 51,71 });
	letters[1].PushBack({ 201,171 , 51,67 });
	letters[1].PushBack({ 150,171 , 51,63 });
	letters[1].PushBack({ 100,171 ,50,61 });
	letters[1].PushBack({ 50,171, 50,60 });
	letters[1].PushBack({ 0,171 , 50,57 });
	/*animationA.PushBack({ 450,114, 50,57 });
	animationA.PushBack({ 400,114 , 50,57 });
	animationA.PushBack({ 350,114 , 50,57 });
	animationA.PushBack({ 300,114 , 50,57 });
	animationA.PushBack({ 250,114 , 50,57 });
	animationA.PushBack({ 200,114 , 50,57 });
	animationA.PushBack({ 150,114 ,50,57 });
	animationA.PushBack({ 100,114 , 50,57 });
	animationA.PushBack({ 50,114 , 50,57 });
	animationA.PushBack({ 0,114 , 50,57 });
	animationA.PushBack({ 450,57 , 50,57 });
	animationA.PushBack({ 400,57 , 50,57 });
	animationA.PushBack({ 350,57 , 50,57 });
	animationA.PushBack({ 300,57 , 50,57 });
	animationA.PushBack({ 250,57 , 50,57 });
	animationA.PushBack({ 200,57, 50,57 });
	animationA.PushBack({ 150,57 , 50,57 });
	animationA.PushBack({ 100, 57 , 50,57 });
	animationA.PushBack({ 50,57 , 50,57 });
	animationA.PushBack({ 0,57 , 50,57 });
	animationA.PushBack({ 450,0 , 50,57 });
	animationA.PushBack({ 400,0 , 50,57 });
	animationA.PushBack({ 350,0 , 50,57 });
	animationA.PushBack({ 300,0 , 50,57 });
	animationA.PushBack({ 250,0, 50,57 });
	animationA.PushBack({ 200,0 , 50,57 });
	animationA.PushBack({ 150,0 , 50,57 });
	animationA.PushBack({ 100,0 , 50,57 });
	animationA.PushBack({ 50,0 ,50,57 });
	animationA.PushBack({ 0,0 , 50,57 });*/
	
	//Letter s1
	letters[2].PushBack({ 60, 306, 14,28 });
	letters[2].PushBack({ 46,306 ,14,57 });
	letters[2].PushBack({ 23,306,23,70 });
	letters[2].PushBack({ 0,306 ,23,73 });
	letters[2].PushBack({ 486,181,24,79 });
	letters[2].PushBack({ 461,181 , 25,77 });
	letters[2].PushBack({ 432,181 , 29,89 });
	letters[2].PushBack({ 403,181 , 29,97 });
	letters[2].PushBack({ 374,181 , 29,100 });
	letters[2].PushBack({ 343,181 , 31,103 });
	letters[2].PushBack({ 312,181, 31,107 });
	letters[2].PushBack({ 281,181 , 31,110 });
	letters[2].PushBack({ 250,181 , 31,107 });
	letters[2].PushBack({ 219,181 , 31,114 });
	letters[2].PushBack({ 188,181 , 31,115 });
	letters[2].PushBack({ 157,181 , 31,118 });
	letters[2].PushBack({ 126,181 , 31,114 });
	letters[2].PushBack({95, 181, 31,120 });
	letters[2].PushBack({64, 181, 31,120 });
	letters[2].PushBack({32,181 , 32,122 });
	letters[2].PushBack({ 0,181 , 32,125 });
	letters[2].PushBack({ 480, 58, 32,123 });
	letters[2].PushBack({ 448, 58 , 32,110 });
	letters[2].PushBack({ 416,58, 32,101 });
	letters[2].PushBack({ 384,58 , 32,91 });
	letters[2].PushBack({ 352,58 , 32,83 });
	letters[2].PushBack({ 320,58 , 32,76 });
	letters[2].PushBack({ 288,58, 32,69 });
	letters[2].PushBack({ 256,58, 32,64 });
	letters[2].PushBack({ 224,58 , 32,61 });
	letters[2].PushBack({ 192,58 , 32,59 });
	letters[2].PushBack({ 160,58 , 32,58 });
	/*animationS1.PushBack({ 128,58 , 32,58 });
	animationS1.PushBack({ 96,58 , 32,58 });
	animationS1.PushBack({ 64,58, 32,58 });
	animationS1.PushBack({ 32,58 , 32,58 });
	animationS1.PushBack({ 0,58 , 32,58 });
	animationS1.PushBack({ 480,0 , 32,58 });
	animationS1.PushBack({ 448,0 , 32,58 });
	animationS1.PushBack({ 416,0 , 32,58 });
	animationS1.PushBack({ 384,0 , 32,58 });
	animationS1.PushBack({ 352,0 , 32,58 });
	animationS1.PushBack({ 320,0, 32,58 });
	animationS1.PushBack({ 288,0 , 32,58 });
	animationS1.PushBack({ 256,0 , 32,58 });
	animationS1.PushBack({ 224,0 , 32,58 });
	animationS1.PushBack({ 192,0 , 32,58 });
	animationS1.PushBack({ 160,0 , 32,58 });
	animationS1.PushBack({ 128,0 , 32,58 });
	animationS1.PushBack({ 96,0 , 32,58 });
	animationS1.PushBack({ 64,0 , 32,58 });
	animationS1.PushBack({ 32,0, 32,58 });
	animationS1.PushBack({ 0,0 , 32,58 });*/
	

	//animation letter T1
	letters[3].PushBack({ 426,430 , 46,70 });
	letters[3].PushBack({ 380,430, 46,73 });
	letters[3].PushBack({ 334,430 , 46,79 });
	letters[3].PushBack({ 288,430 , 46,84 });
	letters[3].PushBack({ 240,430 , 48,92 });
	letters[3].PushBack({ 192,430 , 48,93 });
	letters[3].PushBack({ 144,430, 48,97 });
	letters[3].PushBack({ 96,430 , 48,103 });
	letters[3].PushBack({ 48,430 , 48,103 });
	letters[3].PushBack({ 0,430, 48,109 });
	letters[3].PushBack({ 432,307, 48,97 });
	letters[3].PushBack({ 384,307 , 48,114 });
	letters[3].PushBack({ 336,307 , 48,116 });
	letters[3].PushBack({ 288,307 , 48,118 });
	letters[3].PushBack({ 240,307 , 48,119 });
	letters[3].PushBack({ 192,307 , 48,120 });
	letters[3].PushBack({ 144,307, 48,121 });
	letters[3].PushBack({ 96,307 , 48,117 });
	letters[3].PushBack({ 48,307 , 48,123 });
	letters[3].PushBack({ 0,307 , 48,123 });
	letters[3].PushBack({ 422,179 , 48,127 });
	letters[3].PushBack({ 374,179 , 48,128 });
	letters[3].PushBack({ 326,179 , 48,119 });
	letters[3].PushBack({ 278,179 , 48,108 });
	letters[3].PushBack({ 230,179 , 48,101 });
	letters[3].PushBack({ 184,179 , 46,90 });
	letters[3].PushBack({ 138,179 , 46,81 });
	letters[3].PushBack({ 92,179 , 46,73 });
	letters[3].PushBack({ 46,179 , 46,66 });
	letters[3].PushBack({ 0,179 , 46,62 });
	letters[3].PushBack({ 460,118 , 46,61 });
	letters[3].PushBack({ 414,118 , 46,59 });
	//fade color to white
	/*animationT1.PushBack({ 368,118 , 46,59 });
	animationT1.PushBack({ 322,118 , 46,59 });
	animationT1.PushBack({ 276,118, 46,59 });
	animationT1.PushBack({ 230,118, 46,59 });
	animationT1.PushBack({ 184,118 , 46,59 });
	animationT1.PushBack({ 138,118 , 46,59 });
	animationT1.PushBack({ 92,118 , 46,59 });
	animationT1.PushBack({ 46,118 , 46,59 });
	animationT1.PushBack({ 0,118, 46,59 });
	animationT1.PushBack({ 460,59 , 46,59 });
	animationT1.PushBack({ 414,59 , 46,59 });
	animationT1.PushBack({ 368,59 , 46,59 });
	animationT1.PushBack({ 322,59 , 46,59 });
	animationT1.PushBack({ 276,59 , 46,59 });
	animationT1.PushBack({ 230,59 , 46,59 });
	animationT1.PushBack({ 184,59 , 46,59 });
	animationT1.PushBack({ 138,59 , 46,59 });
	animationT1.PushBack({ 92,59 , 46,59 });
	animationT1.PushBack({ 46,59 , 46,59 });
	animationT1.PushBack({ 0,59 , 46,59 });
	animationT1.PushBack({ 460,0 , 46,59 });
	animationT1.PushBack({ 414,0 , 46,59 });
	animationT1.PushBack({ 368,0 , 46,59 });
	animationT1.PushBack({ 322,0 , 46,59 });
	animationT1.PushBack({ 276,0 , 46,59 });
	animationT1.PushBack({ 230,0 , 46,59 });
	animationT1.PushBack({ 184,0 , 46,59 });
	animationT1.PushBack({ 138,0 , 46,59 });
	animationT1.PushBack({ 92,0 , 46,59 });
	animationT1.PushBack({ 46,0 , 46,59 });
	animationT1.PushBack({ 0,0 , 46,59 });*/
	

	//R animation
	letters[4].PushBack({ 454,401 , 31,61 });
	letters[4].PushBack({ 423,401 , 31,69 });
	letters[4].PushBack({ 385,401 , 38,76 });
	letters[4].PushBack({ 346,401 , 39,81 });
	letters[4].PushBack({ 307,401 , 39,87 });
	letters[4].PushBack({ 268,401, 39,89 });
	letters[4].PushBack({ 225,401, 43,92 });
	letters[4].PushBack({ 180,401 , 45,100 });
	letters[4].PushBack({ 135,401 , 45,103 });
	letters[4].PushBack({ 90,401 , 45,106 });
	letters[4].PushBack({ 45,401, 45,112 });
	letters[4].PushBack({ 0,401 , 45,112 });
	letters[4].PushBack({ 450,276 , 45,114 });
	letters[4].PushBack({ 405,276 , 45,118 });
	letters[4].PushBack({ 360,276, 45,118 });
	letters[4].PushBack({ 315,276 , 45,119 });
	letters[4].PushBack({ 270,276, 45,116 });
	letters[4].PushBack({ 225,276, 45,122 });
	letters[4].PushBack({ 180,276, 45,123 });
	letters[4].PushBack({ 135,276 , 45,122 });
	letters[4].PushBack({ 90,276 , 45,125 });
	letters[4].PushBack({ 45,276 , 45,123 });
	letters[4].PushBack({ 0,276 , 45,114 });
	letters[4].PushBack({ 424,174 , 45,102 });
	letters[4].PushBack({ 378,174 , 46,91 });
	letters[4].PushBack({ 332,174 , 46,83 });
	letters[4].PushBack({ 285,174, 47,75 });
	letters[4].PushBack({ 238,174 , 47,68 });
	letters[4].PushBack({ 191,174 , 47,63 });
	letters[4].PushBack({ 144,174 ,47,60 });
	letters[4].PushBack({ 96,174 ,48,59 });
	letters[4].PushBack({ 48,174 , 48,58 });

	/*animationR1.PushBack({ 0,174 , 48,58 });
	animationR1.PushBack({ 432,116, 48,58 });
	animationR1.PushBack({ 384,116 , 48,58 });
	animationR1.PushBack({ 336,116 , 48,58 });
	animationR1.PushBack({ 288,116 , 48,58 });
	animationR1.PushBack({ 240,116 , 48,58 });
	animationR1.PushBack({ 192,116 , 48,58 });
	animationR1.PushBack({ 144,116 , 48,58 });
	animationR1.PushBack({ 96,116 , 48,58 });
	animationR1.PushBack({ 48,116 , 48,58 });
	animationR1.PushBack({ 0,116 ,48,58 });
	animationR1.PushBack({ 432,58 , 48,58 });
	animationR1.PushBack({ 384,58 , 48,58 });
	animationR1.PushBack({ 336,58 , 48,58 });
	animationR1.PushBack({ 288,58 , 48,58 });
	animationR1.PushBack({ 240,58, 48,58 });
	animationR1.PushBack({ 192,58, 48,58 });
	animationR1.PushBack({ 144,58 , 48,58 });
	animationR1.PushBack({ 96,58 , 48,58 });
	animationR1.PushBack({ 48,58 ,48,58 });
	animationR1.PushBack({ 0,58 , 48,58 });
	animationR1.PushBack({ 432,0 , 48,58 });
	animationR1.PushBack({ 384,0 , 48,58 });
	animationR1.PushBack({ 336,0 , 48,58 });
	animationR1.PushBack({ 288,0, 48,58 });
	animationR1.PushBack({ 240,0 , 48,58 });
	animationR1.PushBack({ 192,0 , 48,58 });
	animationR1.PushBack({ 144,0, 48,58 });
	animationR1.PushBack({ 96,0 , 48,58 });
	animationR1.PushBack({ 48,0 , 48,58 });
	animationR1.PushBack({ 0,0 , 48,58 });*/
	

	//Animation E
	letters[5].PushBack({ 79,420 , 37,53 });
	letters[5].PushBack({ 40,420 , 39,61 });
	letters[5].PushBack({ 0,420 ,40,69 });
	letters[5].PushBack({ 451,304 , 40,73 });
	letters[5].PushBack({ 410,304, 41,79 });
	letters[5].PushBack({ 369,304 , 41,83 });
	letters[5].PushBack({ 328,304 ,41,92 });
	letters[5].PushBack({ 287,304 , 41,97 });
	letters[5].PushBack({ 246,304 , 41,97 });
	letters[5].PushBack({ 205,304 , 41,104 });
	letters[5].PushBack({ 164,304 , 41,107 });
	letters[5].PushBack({ 123,304, 41,110 });
	letters[5].PushBack({ 82,304 , 41,112 });
	letters[5].PushBack({ 41,304 , 41,114 });
	letters[5].PushBack({ 0,304 , 41,116 });
	letters[5].PushBack({ 466,179 , 41,118 });
	letters[5].PushBack({ 425,179 , 41,119 });
	letters[5].PushBack({ 384,179 , 41,120 });
	letters[5].PushBack({ 343,179 , 41,121 });
	letters[5].PushBack({ 302,179 , 41,122 });
	letters[5].PushBack({ 261,179 , 41,125 });
	letters[5].PushBack({ 220,179 , 41,119 });
	letters[5].PushBack({ 176,179, 44,112 });
	letters[5].PushBack({ 132,179 , 44,99 });
	letters[5].PushBack({ 88,179 , 44,88 });
	letters[5].PushBack({ 44,179 , 44,78 });
	letters[5].PushBack({ 0,179 , 44,70 });
	letters[5].PushBack({ 467,114 , 44,65 });
	letters[5].PushBack({ 423,114 , 44,61 });
	letters[5].PushBack({ 379,114 , 44,60 });
	letters[5].PushBack({ 336,114 , 43,59 });
	letters[5].PushBack({ 294,114 , 42,57 });

	/*animationE.PushBack({ 252,114 , 42,57 });
	animationE.PushBack({ 210,114 , 42,57 });
	animationE.PushBack({ 168,114 , 42,57 });
	animationE.PushBack({ 126,114 , 42,57 });
	animationE.PushBack({ 84,114 , 42,57 });
	animationE.PushBack({ 42,114 , 42,57 });
	animationE.PushBack({ 0,114 , 42,57 });
	animationE.PushBack({ 462,57 , 42,57 });
	animationE.PushBack({ 420,57 , 42,57 });
	animationE.PushBack({ 378,57 , 42,57 });
	animationE.PushBack({ 336,57 , 42,57 });
	animationE.PushBack({ 294,57 , 42,57 });
	animationE.PushBack({ 252,57 , 42,57 });
	animationE.PushBack({ 210,57 , 42,57 });
	animationE.PushBack({ 168,57 , 42,57 });
	animationE.PushBack({ 126,57 , 42,57 });
	animationE.PushBack({ 84,57 , 42,57 });
	animationE.PushBack({ 42,57 , 42,57 });
	animationE.PushBack({ 0,57 , 42,57 });
	animationE.PushBack({ 462,0 , 42,57 });
	animationE.PushBack({ 420,0 , 42,57 });
	animationE.PushBack({ 378,0 , 42,57 });
	animationE.PushBack({ 336,0 , 42,57 });
	animationE.PushBack({ 294,0 , 42,57 });
	animationE.PushBack({ 252,0 , 42,57 });
	animationE.PushBack({ 210,0 , 42,57 });
	animationE.PushBack({ 168,0 , 42,57 });
	animationE.PushBack({ 126,0 , 42,57 });
	animationE.PushBack({ 84,0 , 42,57 });
	animationE.PushBack({ 42,0 , 42,57 });
	animationE.PushBack({ 0,0 , 42,57 });*/
	

	//S2 animation rects
	letters[6].PushBack({ 109,293 ,14,28 });
	letters[6].PushBack({ 95,293 , 14,57 });
	letters[6].PushBack({ 72,293 , 23,70 });
	letters[6].PushBack({ 49,293, 23,73 });
	letters[6].PushBack({ 25,293 , 24,79 });
	letters[6].PushBack({ 0,293 , 25,77 });
	letters[6].PushBack({ 464,168 , 29,89 });
	letters[6].PushBack({ 435,168 , 29,97 });
	letters[6].PushBack({ 406,168 , 29,100 });
	letters[6].PushBack({ 375,168 , 31,103 });
	letters[6].PushBack({ 344,168 , 31,107 });
	letters[6].PushBack({ 313,168 , 31,110 });
	letters[6].PushBack({ 282,168 , 31,107 });
	letters[6].PushBack({ 251,168 , 31,114 });
	letters[6].PushBack({ 220,168 , 31,115 });
	letters[6].PushBack({ 189,168 , 31,118 });
	letters[6].PushBack({ 158,168 , 31,114 });
	letters[6].PushBack({ 127,168 , 31,120 });
	letters[6].PushBack({ 96,168 , 31,120 });
	letters[6].PushBack({ 64,168 , 32,122 });
	letters[6].PushBack({ 32,168 , 32,125 });
	letters[6].PushBack({ 0,168 , 32,123 });
	letters[6].PushBack({ 480,58 , 32,110 });
	letters[6].PushBack({ 448,58 , 32,101 });
	letters[6].PushBack({ 416,58 , 32,91 });
	letters[6].PushBack({ 384,58 , 32,83 });
	letters[6].PushBack({ 352,58 , 32,76 });
	letters[6].PushBack({ 320,58 , 32,69 });
	letters[6].PushBack({ 288,58 , 32,64 });
	letters[6].PushBack({ 256,58 , 32,61 });
	letters[6].PushBack({ 224,58 , 32,59 });
	letters[6].PushBack({ 192,58 , 32,58 });

	/*animationS2.PushBack({ 160,58 , 32,58 });
	animationS2.PushBack({ 128,58 , 32,58 });
	animationS2.PushBack({ 96,58 , 32,58 });
	animationS2.PushBack({ 64,58 , 32,58 });
	animationS2.PushBack({ 32,58 , 32,58 });
	animationS2.PushBack({ 0,58 , 32,58 });
	animationS2.PushBack({ 480,0 , 32,58 });
	animationS2.PushBack({ 448,0 , 32,58 });
	animationS2.PushBack({ 416,0 , 32,58 });
	animationS2.PushBack({ 384,0 , 32,58 });
	animationS2.PushBack({ 352,0 , 32,58 });
	animationS2.PushBack({ 320,0 , 32,58 });
	animationS2.PushBack({ 288,0 , 32,58 });
	animationS2.PushBack({ 256,0 , 32,58 });
	animationS2.PushBack({ 224,0 , 32,58 });
	animationS2.PushBack({ 192,0 , 32,58 });
	animationS2.PushBack({ 160,0 , 32,58 });
	animationS2.PushBack({ 128,0 , 32,58 });
	animationS2.PushBack({ 96,0 , 32,58 });
	animationS2.PushBack({ 64,0 , 32,58 });
	animationS2.PushBack({ 32,0 , 32,58 });
	animationS2.PushBack({ 0,0 , 32,58 });*/


	//Animation O
	letters[7].PushBack({ 432,348 , 20,58 });
	letters[7].PushBack({ 412,348 , 20,66 });
	letters[7].PushBack({ 384,348 , 28,76 });
	letters[7].PushBack({ 355,348 , 29,79 });
	letters[7].PushBack({ 321,348 , 34,84 });
	letters[7].PushBack({ 287,348 , 34,89 });
	letters[7].PushBack({ 252,348 , 35,96 });
	letters[7].PushBack({ 215,348 , 37,99 });
	letters[7].PushBack({ 177,348 , 38,104 });
	letters[7].PushBack({ 133,348 , 44,106 });
	letters[7].PushBack({ 89,348 , 44,109 });
	letters[7].PushBack({ 45,348 , 44,111 });
	letters[7].PushBack({ 0,348 , 45,114 });
	letters[7].PushBack({ 430,222 , 45,118 });
	letters[7].PushBack({ 384,222 , 46,120 });
	letters[7].PushBack({ 338,222 , 46,121 });
	letters[7].PushBack({ 292,222 , 46,120 });
	letters[7].PushBack({ 244,222 , 48,123 });
	letters[7].PushBack({ 196,222 , 48,122 });
	letters[7].PushBack({ 148,222 , 48,122 });
	letters[7].PushBack({ 100,222 , 48,126 });
	letters[7].PushBack({ 50,222 , 50,122 });
	letters[7].PushBack({ 0,222 , 50,116 });
	letters[7].PushBack({ 439,118 , 50,104 });
	letters[7].PushBack({ 389,118 , 50,92 });
	letters[7].PushBack({ 339,118 , 50,82 });
	letters[7].PushBack({ 290,118 , 49,74 });
	letters[7].PushBack({ 241,118 , 49,68 });
	letters[7].PushBack({ 192,118 , 49,63 });
	letters[7].PushBack({ 144,118 , 48,61 });
	letters[7].PushBack({ 96,118 , 48,60 });
	letters[7].PushBack({ 48,118 , 48,59 });
	
	/*animationO.PushBack({ 0,118 , 48,59 });
	animationO.PushBack({ 432,59 , 48,59 });
	animationO.PushBack({ 384,59 , 48,59 });
	animationO.PushBack({ 336,59 , 48,59 });
	animationO.PushBack({ 288,59 , 48,59 });
	animationO.PushBack({ 240,59 , 48,59 });
	animationO.PushBack({ 192,59 , 48,59 });
	animationO.PushBack({ 144,59 , 48,59 });
	animationO.PushBack({ 96,59 , 48,59 });
	animationO.PushBack({ 48,59 , 48,59 });
	animationO.PushBack({ 0,59 , 48,59 });
	animationO.PushBack({ 432,0 , 48,59 });
	animationO.PushBack({ 384,0 , 48,59 });
	animationO.PushBack({ 336,0 , 48,59 });
	animationO.PushBack({ 288,0 , 48,59 });
	animationO.PushBack({ 240,0 , 48,59 });
	animationO.PushBack({ 192,0 , 48,59 });
	animationO.PushBack({ 144,0 , 48,59 });
	animationO.PushBack({ 96,0 , 48,59 });
	animationO.PushBack({ 48,0 , 48,59 });
	animationO.PushBack({ 0,0 , 48,59 });*/


	//R2 animation
	letters[8].PushBack({ 186,902 , 31,61 });
	letters[8].PushBack({ 155,902 , 31,69 });
	letters[8].PushBack({ 117,902 , 38,76 });
	letters[8].PushBack({ 78,902 , 39,81 });
	letters[8].PushBack({ 39,902 , 39,87 });
	letters[8].PushBack({ 0,902 , 39,89 });
	letters[8].PushBack({ 180,790 , 43,92 });
	letters[8].PushBack({ 135,790 , 45,100 });
	letters[8].PushBack({ 90,790 , 45,103 });
	letters[8].PushBack({ 45,790 , 45,106 });
	letters[8].PushBack({ 0,790 , 45,112 });
	letters[8].PushBack({ 180,671 , 45,112 });
	letters[8].PushBack({ 135,671 , 45,114 });
	letters[8].PushBack({ 90,671 , 45,118 });
	letters[8].PushBack({ 45,671 , 45,118 });
	letters[8].PushBack({ 0,671 , 45,119 });
	letters[8].PushBack({ 180,546 , 45,116 });
	letters[8].PushBack({ 135,546 , 45,122 });
	letters[8].PushBack({ 90,546 , 45,123 });
	letters[8].PushBack({ 45,546 , 45,122 });
	letters[8].PushBack({ 0,546 , 45,125 });
	letters[8].PushBack({ 182,423 , 45,123 });
	letters[8].PushBack({ 137,423 , 45,114 });
	letters[8].PushBack({ 92,423 , 45,102 });
	letters[8].PushBack({ 46,423 , 46,91 });
	letters[8].PushBack({ 0,423 , 46,83 });
	letters[8].PushBack({ 189,348 , 47,75 });
	letters[8].PushBack({ 142,348 , 47,68 });
	letters[8].PushBack({ 95,348 , 47,63 });
	letters[8].PushBack({ 48,348 , 47,60 });
	letters[8].PushBack({ 0,348 , 48,59 });
	letters[8].PushBack({ 192,290 , 48,58 });

	/*animationR2.PushBack({ 144,290 , 48,58 });
	animationR2.PushBack({ 96,290 , 48,58 });
	animationR2.PushBack({ 48,290 , 48,58 });
	animationR2.PushBack({ 0,290 , 48,58 });
	animationR2.PushBack({ 192,232 , 48,58 });
	animationR2.PushBack({ 144,232 , 48,58 });
	animationR2.PushBack({ 96,232 , 48,58 });
	animationR2.PushBack({ 48,232 , 48,58 });
	animationR2.PushBack({ 0,232 , 48,58 });
	animationR2.PushBack({ 192,174 , 48,58 });
	animationR2.PushBack({ 144,174 , 48,58 });
	animationR2.PushBack({ 96,174 , 48,58 });
	animationR2.PushBack({ 48,174 , 48,58 });
	animationR2.PushBack({ 0,174 , 48,58 });
	animationR2.PushBack({ 192,116 , 48,58 });
	animationR2.PushBack({ 144,116 , 48,58 });
	animationR2.PushBack({ 96,116 , 48,58 });
	animationR2.PushBack({ 48,116 , 48,58 });
	animationR2.PushBack({ 0,116 , 48,58 });
	animationR2.PushBack({ 192,58 , 48,58 });
	animationR2.PushBack({ 144,58 , 48,58 });
	animationR2.PushBack({ 96,58 , 48,58 });
	animationR2.PushBack({ 48,58 , 48,58 });
	animationR2.PushBack({ 0,58 , 48,58 });
	animationR2.PushBack({ 192,0 , 48,58 });
	animationR2.PushBack({ 144,0 , 48,58 });
	animationR2.PushBack({ 96,0 , 48,58 });
	animationR2.PushBack({ 48,0 , 48,58 });
	animationR2.PushBack({ 0,0 , 48,58 });*/

	//T2 animation
	letters[9].PushBack({ 330,374 , 46,70 });
	letters[9].PushBack({ 284,374 , 46,73 });
	letters[9].PushBack({ 238,374 , 46,79 });

	letters[9].PushBack({ 192,374 , 46,84 });
	letters[9].PushBack({ 144,374 , 48,92 });
	letters[9].PushBack({ 96,374 , 48,93 });
	letters[9].PushBack({ 48,374 , 48,97 });
	letters[9].PushBack({ 0,374 , 48,103 });
	letters[9].PushBack({ 432,253 , 48,103 });
	letters[9].PushBack({ 384,253 , 48,109 });
	letters[9].PushBack({ 336,253 , 48,97 });
	letters[9].PushBack({ 288,253 , 48,114 });
	letters[9].PushBack({ 240,253 , 48,116 });

	letters[9].PushBack({ 192,253 , 48,118 });
	letters[9].PushBack({ 144,253 , 48,119 });
	letters[9].PushBack({ 96,253 , 48,120 });
	letters[9].PushBack({ 48,253 , 48,121 });
	letters[9].PushBack({ 0,253 , 48,117 });
	letters[9].PushBack({ 426,125 , 48,123 });
	letters[9].PushBack({ 378,125 , 48,123 });
	letters[9].PushBack({ 330,125 , 48,127 });
	letters[9].PushBack({ 282,125 , 48,128 });
	letters[9].PushBack({ 234,125 , 48,119 });

	letters[9].PushBack({ 186,125 , 48,108 });
	letters[9].PushBack({ 138,125 , 48,101 });
	letters[9].PushBack({ 92,125 , 46,90 });
	letters[9].PushBack({ 46,125 , 46,81 });
	letters[9].PushBack({ 0,125 , 46,73 });
	letters[9].PushBack({ 460,59 , 46,66 });
	letters[9].PushBack({ 414,59 , 46,62 });
	letters[9].PushBack({ 368,59 , 46,61 });
	letters[9].PushBack({ 322,59 , 46,61 });
	letters[9].PushBack({ 276,59 , 46,59 });
	
	/*animationT2.PushBack({ 230,59 , 46,59 });
	animationT2.PushBack({ 184,59 , 46,59 });
	animationT2.PushBack({ 138,59 , 46,59 });
	animationT2.PushBack({ 92,59 , 46,59 });
	animationT2.PushBack({ 46,59 , 46,59 });
	animationT2.PushBack({ 0,59 , 46,59 });
	animationT2.PushBack({ 460,0 , 46,59 });
	animationT2.PushBack({ 414,0 , 46,59 });
	animationT2.PushBack({ 368,0 , 46,59 });
	animationT2.PushBack({ 322,0 , 46,59 });
	animationT2.PushBack({ 276,0 , 46,59 });
	animationT2.PushBack({ 230,0 , 46,59 });
	animationT2.PushBack({ 184,0 , 46,59 });
	animationT2.PushBack({ 138,0 , 46,59 });
	animationT2.PushBack({ 92,0 , 46,59 });
	animationT2.PushBack({ 46,0 , 46,59 });
	animationT2.PushBack({ 0,0 , 46,59 });*/

	for (int i = 0; i < 10; ++i)
	{
		letters[i].speed = 0.325f;
		letters[i].repeat = false;
	}

}

ModuleGameTitle::~ModuleGameTitle()
{	}

bool ModuleGameTitle::Init()
{

	return true;
}


bool ModuleGameTitle::Start()
{
	LOG("------ Starting intro Scene");

	SDL_SetRenderDrawBlendMode(App->render->renderer, SDL_BLENDMODE_BLEND);

	//initializes needed variables
	timeBetweenLetters = 160; //in ms

	titleScreen = App->textures->Load("assets/Graphics/Screens/Intro/titleScreen.png");
	blackScreenTexture = App->textures->Load("assets/Graphics/Screens/Intro/black.png");
	pushStartTexture = App->textures->Load("assets/Graphics/Screens/Intro/pushStart.png");
	snkTexture = App->textures->Load("assets/Graphics/Screens/Intro/snk.png");
	snkCorpTexture = App->textures->Load("assets/Graphics/Screens/Intro/snkCorp.png");

	lettersTexture[0] = App->textures->Load("assets/Graphics/Screens/Intro/L1.png");
	lettersTexture[1] = App->textures->Load("assets/Graphics/Screens/Intro/A.png");
	lettersTexture[2] = App->textures->Load("assets/Graphics/Screens/Intro/S1.png");
	lettersTexture[3] = App->textures->Load("assets/Graphics/Screens/Intro/T1.png");
	lettersTexture[4] = App->textures->Load("assets/Graphics/Screens/Intro/R1.png");
	lettersTexture[5] = App->textures->Load("assets/Graphics/Screens/Intro/E.png");
	lettersTexture[6] = App->textures->Load("assets/Graphics/Screens/Intro/S2.png");
	lettersTexture[7] = App->textures->Load("assets/Graphics/Screens/Intro/O.png");
	lettersTexture[8] = App->textures->Load("assets/Graphics/Screens/Intro/R2.png");
	lettersTexture[9] = App->textures->Load("assets/Graphics/Screens/Intro/T2MOD.png");

	//loading appropiate music
	App->audio->LoadAudio("assets/Audio/Music/titleScreenSong.ogg", "titleSong", MUSIC);
	App->audio->ControlAudio("titleSong", MUSIC, FADEIN, 0, 1000.0f); //type, mode, loops, fadeIn, fadeout
	// -----------------------

	start_time = SDL_GetTicks(); //next letter counter
	showMeNext = 1; //start with the first letter

	return true;
}

update_status ModuleGameTitle::Update()
{

	Animation* current_animation;
	SDL_Rect r;


	if (current_step == intro_step::firstSecuence ||
		current_step == intro_step::fade_to_white)
	{
		App->render->Blit(blackScreenTexture, 0, 0, NULL);
			
		//activate next letter
		now = SDL_GetTicks() - start_time;
		if (now >= timeBetweenLetters && showMeNext < 10)
		{
			showMeNext++;
			start_time = SDL_GetTicks();
		}

		for (int i = 0; i < showMeNext; ++i)
		{ 
			int substractX = 0, substractY=0;
			current_animation = &letters[i];
			r = current_animation->GetCurrentFrame();
			if (!current_animation->finish)
			{
				substractX = pivotMegaDimensionalX[i][(int)current_animation->current_frame];
				substractY = pivotMegaDimensionalY[i][(int)current_animation->current_frame];
			}
			//moves the y coordinate
			float speedY = 1.9f;
			if (letterTransitionPositions[i] >= positionsLettersY[i])
			{
				letterTransitionPositions[i] -= speedY;
			}

				App->render->Blit(lettersTexture[i], positionsLettersX[i] - substractX, 
													 letterTransitionPositions[i] - substractY, &r);
		}

		if (current_step == intro_step::firstSecuence)
		{
			if (letters[9].current_frame >= letters[9].last_frame - 4) //advance fade to white 4 frames before 
			{														   //last letter accomplish finish condition
				current_step = intro_step::fade_to_white;
				start_time = SDL_GetTicks();
				total_time = 500.0f;
				lastFadeFromWhiteTime = 3000.0f;
			}
		}
			//original game it does not allow us to skip letters sequence
			//if (App->input->keyboard[SDL_SCANCODE_RETURN] == 1) //skip letters animation scene
				//App->fade->FadeToBlack(App->gameTitle, App->background);
	}
	

	if (current_step == intro_step::fade_to_white || 
		current_step == intro_step::fade_from_white||
		current_step == intro_step::time_in_white)
	{
		now = SDL_GetTicks() - start_time;
		float normalized;
		if (current_step == intro_step::fade_from_white) normalized = MIN(1.0f, (float)now / (float)lastFadeFromWhiteTime);
		else normalized = MIN(1.0f, (float)now / (float)total_time);

		if (current_step == intro_step::fade_to_white)
		{
			if (now >= total_time)
			{
			
				App->render->Blit(blackScreenTexture, 0, 0, NULL);
				App->render->Blit(titleScreen, 12, 9, NULL);
	
				SDL_SetRenderDrawColor(App->render->renderer, 255, 255, 255, (Uint8)(normalized * 255.0f));
				SDL_RenderFillRect(App->render->renderer, NULL);
				// ---
				total_time += total_time;
				start_time = SDL_GetTicks();
				current_step = intro_step::time_in_white;
				
			}
		}
		else if (current_step == intro_step::time_in_white)
		{
			timeInWhite = 500;
			if (now >= timeInWhite)
			{
				current_step = intro_step::fade_from_white;
				normalized = 1.0f;
				start_time = SDL_GetTicks();
			}
		}

		else if (current_step == intro_step::fade_from_white)
		{
			
			App->render->Blit(blackScreenTexture, 0, 0, NULL);
			App->render->Blit(titleScreen, 12, 9, &titleScreenRect);
			normalized = 1.0f - normalized;
		
			if (now >= lastFadeFromWhiteTime)
				current_step = intro_step::press_start_screen;
		}

		SDL_SetRenderDrawColor(App->render->renderer, 255, 255, 255, (Uint8)(normalized * 255.0f));
		SDL_RenderFillRect(App->render->renderer, NULL);
	}

	if(current_step == intro_step::press_start_screen)
	{
		App->render->Blit(blackScreenTexture, 0, 0, NULL);
		App->render->Blit(titleScreen, 12, 9, &titleScreenRect);

		//pushStart anim
		App->render->Blit(pushStartTexture, 104, 175, &pushStart.GetCurrentFrame());
		
		//snk trademark
		App->render->Blit(snkTexture, 12, 170, &snk);
		App->render->Blit(snkCorpTexture, 64, 200, &snkCorp);

		if (App->input->keyboard[SDL_SCANCODE_RETURN] == 1)
			App->fade->FadeToBlack(App->gameTitle, App->scene_lvl1, 1.0f);
	}


	return UPDATE_CONTINUE;
}

bool ModuleGameTitle::CleanUp()
{
	//unload textures
	App->textures->Unload(snkCorpTexture);
	App->textures->Unload(snkTexture);
	App->textures->Unload(pushStartTexture);
	App->textures->Unload(blackScreenTexture);
	App->textures->Unload(titleScreen);
	for (int i = 0; i < 10; ++i)
	App->textures->Unload(lettersTexture[i]);

	//reposition enum state to correct next game loop
	current_step = intro_step::firstSecuence;


	//unlock last frame animations for non repeated method cycles
	for (int i = 0; i < 10; ++i)
	{
		letters[i].finish = false;
		letters[i].current_frame = 0;
		letterTransitionPositions[i] = lettersTransitions0pos[i]; //restart y positions
	}

	pushStart.current_frame = 0;

	//unloading music
	Mix_FadeOutMusic(500);
	App->audio->UnloadAudio("titleSong", MUSIC);
	
	return true;
}