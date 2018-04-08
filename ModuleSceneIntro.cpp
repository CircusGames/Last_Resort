#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleSceneIntro.h"
#include "ModuleBackground.h"
#include "ModuleInput.h"
#include "ModuleFadeToBlack.h"

#include "SDL/include/SDL_timer.h"

#include "SDL/include/SDL_render.h"

ModuleSceneIntro::ModuleSceneIntro()
{
	//jerry_smith = { 0, 0 , 370, 452 };
	jerry_smith.x = 0;
	jerry_smith.y = 0;
	jerry_smith.w = 370;
	jerry_smith.h = 452;
	//screen = { 0, 0, SCREEN_WIDTH * SCREEN_SIZE, SCREEN_HEIGHT * SCREEN_SIZE };

	//letter L rects
	animationL.PushBack({ 468,297,13,25 });
	animationL.PushBack({ 454,297,14,37 });
	animationL.PushBack({ 439,297,15,58 });
	animationL.PushBack({ 421,297,18,66 });
	animationL.PushBack({ 401,297,20,76 });
	animationL.PushBack({ 380,297,21,79 });
	animationL.PushBack({ 359,297,21,83 });
	animationL.PushBack({ 338,297,21,81 });
	animationL.PushBack({ 317,297,21,92 });
	animationL.PushBack({ 296,297,21,101 });
	animationL.PushBack({ 273,297,23,102 });
	animationL.PushBack({ 250,297,23,107 });
	animationL.PushBack({ 227,297,23,96 });
	animationL.PushBack({ 204,297,23,112 });
	animationL.PushBack({ 181,297,23,114 });
	animationL.PushBack({ 158,297,23,116 });
	animationL.PushBack({ 135,297,23,117 });
	animationL.PushBack({ 90,297,45,121 });
	animationL.PushBack({ 45,297,45,122 });
	animationL.PushBack({ 0,297,45,122 });
	animationL.PushBack({ 426,174,45,123 });
	animationL.PushBack({ 379,174,47,118 });
	animationL.PushBack({ 332,174,47,106 });
	animationL.PushBack({ 284,174,48,94 });
	animationL.PushBack({ 236,174,48,88 });
	animationL.PushBack({ 188,174,48,84 });
	animationL.PushBack({ 141,174,47,77 });
	animationL.PushBack({ 94,174,47,69 });
	animationL.PushBack({ 47,174,47,66 });
	animationL.PushBack({ 0,174,47,63 });
	animationL.PushBack({ 460,114,46,60 });
	animationL.PushBack({ 414,114,46,57 });
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
	animationL.speed = 0.03f;
	animationL.repeat = false;

	//letter A rects
	animationA.PushBack({ 492,277, 1,1 });
	animationA.PushBack({ 482,277, 10,15 });
	animationA.PushBack({ 470,277,12,24 });
	animationA.PushBack({ 457,277,13,38 });
	animationA.PushBack({ 444,277, 13,45 });
	animationA.PushBack({ 431,277, 13,56 });
	animationA.PushBack({ 418,277, 13,63 });
	animationA.PushBack({ 405,277,13,72 });
	animationA.PushBack({ 392,277, 13,80 });
	animationA.PushBack({ 378,277, 14,87 });
	animationA.PushBack({ 359,277, 19,92 });
	animationA.PushBack({ 339,277,20,96 });
	animationA.PushBack({ 317,277,22,100 });
	animationA.PushBack({ 295,277,22,101 });
	animationA.PushBack({ 271,277,24,106 });
	animationA.PushBack({ 246,277,25,108 });
	animationA.PushBack({ 208,277,39,111 }); //x= 207
	animationA.PushBack({ 173,277, 34,115 });
	animationA.PushBack({ 135,277, 38,114 });
	animationA.PushBack({ 94,277, 41,122 });
	animationA.PushBack({ 47,277, 47,122 });
	animationA.PushBack({ 0,277 , 47,119 });
	animationA.PushBack({ 456,171 , 47,106 });
	animationA.PushBack({ 405,171 , 51,94 });
	animationA.PushBack({ 354,171, 51,84 });
	animationA.PushBack({ 303,171, 51,77 });
	animationA.PushBack({ 252,171, 51,71 });
	animationA.PushBack({ 201,171 , 51,67 });
	animationA.PushBack({ 150,171 , 51,63 });
	animationA.PushBack({ 100,171 ,50,61 });
	animationA.PushBack({ 50,171, 50,60 });
	animationA.PushBack({ 0,171 , 50,57 });
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
	animationA.speed = 0.33f;
	animationA.repeat = false;

	//Letter s1
	animationS1.PushBack({ 60, 306, 14,28 });
	animationS1.PushBack({ 46,306 ,14,57 });
	animationS1.PushBack({ 23,306,23,70 });
	animationS1.PushBack({ 0,306 ,23,73 });
	animationS1.PushBack({ 486,181,24,79 });
	animationS1.PushBack({ 461,181 , 25,77 });
	animationS1.PushBack({ 432,181 , 29,89 });
	animationS1.PushBack({ 403,181 , 29,97 });
	animationS1.PushBack({ 374,181 , 29,100 });
	animationS1.PushBack({ 343,181 , 31,103 });
	animationS1.PushBack({ 312,181, 31,107 });
	animationS1.PushBack({ 281,181 , 31,110 });
	animationS1.PushBack({ 250,181 , 31,107 });
	animationS1.PushBack({ 219,181 , 31,114 });
	animationS1.PushBack({ 188,181 , 31,115 });
	animationS1.PushBack({ 157,181 , 31,118 });
	animationS1.PushBack({ 126,181 , 31,114 });
	animationS1.PushBack({95, 181, 31,120 });
	animationS1.PushBack({64, 181, 31,120 });
	animationS1.PushBack({32,181 , 32,122 });
	animationS1.PushBack({ 0,181 , 32,125 });
	animationS1.PushBack({ 480, 58, 32,123 });
	animationS1.PushBack({ 448, 58 , 32,110 });
	animationS1.PushBack({ 416,58, 32,101 });
	animationS1.PushBack({ 384,58 , 32,91 });
	animationS1.PushBack({ 352,58 , 32,83 });
	animationS1.PushBack({ 320,58 , 32,76 });
	animationS1.PushBack({ 288,58, 32,69 });
	animationS1.PushBack({ 256,58, 32,64 });
	animationS1.PushBack({ 224,58 , 32,61 });
	animationS1.PushBack({ 192,58 , 32,59 });
	animationS1.PushBack({ 160,58 , 32,58 });
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
	animationS1.speed = 0.33f;
	animationS1.repeat = false;

	//animation letter T1
	animationT1.PushBack({ 426,430 , 46,70 });
	animationT1.PushBack({ 380,430, 46,73 });
	animationT1.PushBack({ 334,430 , 46,79 });
	animationT1.PushBack({ 288,430 , 46,84 });
	animationT1.PushBack({ 240,430 , 48,92 });
	animationT1.PushBack({ 192,430 , 48,93 });
	animationT1.PushBack({ 144,430, 48,97 });
	animationT1.PushBack({ 96,430 , 48,103 });
	animationT1.PushBack({ 48,430 , 48,103 });
	animationT1.PushBack({ 0,430, 48,109 });
	animationT1.PushBack({ 432,307, 48,97 });
	animationT1.PushBack({ 384,307 , 48,114 });
	animationT1.PushBack({ 336,307 , 48,116 });
	animationT1.PushBack({ 288,307 , 48,118 });
	animationT1.PushBack({ 240,307 , 48,119 });
	animationT1.PushBack({ 192,307 , 48,120 });
	animationT1.PushBack({ 144,307, 48,121 });
	animationT1.PushBack({ 96,307 , 48,117 });
	animationT1.PushBack({ 48,307 , 48,123 });
	animationT1.PushBack({ 0,307 , 48,123 });
	animationT1.PushBack({ 422,179 , 48,127 });
	animationT1.PushBack({ 374,179 , 48,128 });
	animationT1.PushBack({ 326,179 , 48,119 });
	animationT1.PushBack({ 278,179 , 48,108 });
	animationT1.PushBack({ 230,179 , 48,101 });
	animationT1.PushBack({ 184,179 , 46,90 });
	animationT1.PushBack({ 138,179 , 46,81 });
	animationT1.PushBack({ 92,179 , 46,73 });
	animationT1.PushBack({ 46,179 , 46,66 });
	animationT1.PushBack({ 0,179 , 46,62 });
	animationT1.PushBack({ 460,118 , 46,61 });
	animationT1.PushBack({ 414,118 , 46,59 });
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
	animationT1.speed = 0.33f;
	animationT1.repeat = false;

	//R animation
	animationR1.PushBack({ 454,401 , 31,61 });
	animationR1.PushBack({ 423,401 , 31,69 });
	animationR1.PushBack({ 385,401 , 38,76 });
	animationR1.PushBack({ 346,401 , 39,81 });
	animationR1.PushBack({ 307,401 , 39,87 });
	animationR1.PushBack({ 268,401, 39,89 });
	animationR1.PushBack({ 225,401, 43,92 });
	animationR1.PushBack({ 180,401 , 45,100 });
	animationR1.PushBack({ 135,401 , 45,103 });
	animationR1.PushBack({ 90,401 , 45,106 });
	animationR1.PushBack({ 45,401, 45,112 });
	animationR1.PushBack({ 0,401 , 45,112 });
	animationR1.PushBack({ 450,276 , 45,114 });
	animationR1.PushBack({ 405,276 , 45,118 });
	animationR1.PushBack({ 360,276, 45,118 });
	animationR1.PushBack({ 315,276 , 45,119 });
	animationR1.PushBack({ 270,276, 45,116 });
	animationR1.PushBack({ 225,276, 45,122 });
	animationR1.PushBack({ 180,276, 45,123 });
	animationR1.PushBack({ 135,276 , 45,122 });
	animationR1.PushBack({ 90,276 , 45,125 });
	animationR1.PushBack({ 45,276 , 45,123 });
	animationR1.PushBack({ 0,276 , 45,114 });
	animationR1.PushBack({ 424,174 , 45,102 });
	animationR1.PushBack({ 378,174 , 46,91 });
	animationR1.PushBack({ 332,174 , 46,83 });
	animationR1.PushBack({ 285,174, 47,75 });
	animationR1.PushBack({ 238,174 , 47,68 });
	animationR1.PushBack({ 191,174 , 47,63 });
	animationR1.PushBack({ 144,174 ,47,60 });
	animationR1.PushBack({ 96,174 ,48,59 });
	animationR1.PushBack({ 48,174 , 48,58 });

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
	animationR1.speed = 0.33f;
	animationR1.repeat = false;

	//Animation E
	animationE.PushBack({ 79,420 , 37,53 });
	animationE.PushBack({ 40,420 , 39,61 });
	animationE.PushBack({ 0,420 ,40,69 });
	animationE.PushBack({ 451,304 , 40,73 });
	animationE.PushBack({ 410,304, 41,79 });
	animationE.PushBack({ 369,304 , 41,83 });
	animationE.PushBack({ 328,304 ,41,92 });
	animationE.PushBack({ 287,304 , 41,97 });
	animationE.PushBack({ 246,304 , 41,97 });
	animationE.PushBack({ 205,304 , 41,104 });
	animationE.PushBack({ 164,304 , 41,107 });
	animationE.PushBack({ 123,304, 41,110 });
	animationE.PushBack({ 82,304 , 41,112 });
	animationE.PushBack({ 41,304 , 41,114 });
	animationE.PushBack({ 0,304 , 41,116 });
	animationE.PushBack({ 466,179 , 41,118 });
	animationE.PushBack({ 425,179 , 41,119 });
	animationE.PushBack({ 384,179 , 41,120 });
	animationE.PushBack({ 343,179 , 41,121 });
	animationE.PushBack({ 302,179 , 41,122 });
	animationE.PushBack({ 261,179 , 41,125 });
	animationE.PushBack({ 220,179 , 41,119 });
	animationE.PushBack({ 176,179, 44,112 });
	animationE.PushBack({ 132,179 , 44,99 });
	animationE.PushBack({ 88,179 , 44,88 });
	animationE.PushBack({ 44,179 , 44,78 });
	animationE.PushBack({ 0,179 , 44,70 });
	animationE.PushBack({ 467,114 , 44,65 });
	animationE.PushBack({ 423,114 , 44,61 });
	animationE.PushBack({ 379,114 , 44,60 });
	animationE.PushBack({ 336,114 , 43,59 });
	animationE.PushBack({ 294,114 , 42,57 });

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
	animationE.speed = 0.33f;
	animationE.repeat = false;

	//S2 animation rects
	animationS2.PushBack({ 109,293 ,14,28 });
	animationS2.PushBack({ 95,293 , 14,57 });
	animationS2.PushBack({ 72,293 , 23,70 });
	animationS2.PushBack({ 49,293, 23,73 });
	animationS2.PushBack({ 25,293 , 24,79 });
	animationS2.PushBack({ 0,293 , 25,77 });
	animationS2.PushBack({ 464,168 , 29,89 });
	animationS2.PushBack({ 435,168 , 29,97 });
	animationS2.PushBack({ 406,168 , 29,100 });
	animationS2.PushBack({ 375,168 , 31,103 });
	animationS2.PushBack({ 344,168 , 31,107 });
	animationS2.PushBack({ 313,168 , 31,110 });
	animationS2.PushBack({ 282,168 , 31,107 });
	animationS2.PushBack({ 251,168 , 31,114 });
	animationS2.PushBack({ 220,168 , 31,115 });
	animationS2.PushBack({ 189,168 , 31,118 });
	animationS2.PushBack({ 158,168 , 31,114 });
	animationS2.PushBack({ 127,168 , 31,120 });
	animationS2.PushBack({ 96,168 , 31,120 });
	animationS2.PushBack({ 64,168 , 32,122 });
	animationS2.PushBack({ 32,168 , 32,125 });
	animationS2.PushBack({ 0,168 , 32,123 });
	animationS2.PushBack({ 480,58 , 32,110 });
	animationS2.PushBack({ 448,58 , 32,101 });
	animationS2.PushBack({ 416,58 , 32,91 });
	animationS2.PushBack({ 384,58 , 32,83 });
	animationS2.PushBack({ 352,58 , 32,76 });
	animationS2.PushBack({ 320,58 , 32,69 });
	animationS2.PushBack({ 288,58 , 32,64 });
	animationS2.PushBack({ 256,58 , 32,61 });
	animationS2.PushBack({ 224,58 , 32,59 });
	animationS2.PushBack({ 192,58 , 32,58 });

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
	animationS2.speed = 0.33f;
	animationS2.repeat = false;

	//Animation O
	animationO.PushBack({ 432,348 , 20,58 });
	animationO.PushBack({ 412,348 , 20,66 });
	animationO.PushBack({ 384,348 , 28,76 });
	animationO.PushBack({ 355,348 , 29,79 });
	animationO.PushBack({ 321,348 , 34,84 });
	animationO.PushBack({ 287,348 , 34,89 });
	animationO.PushBack({ 252,348 , 35,96 });
	animationO.PushBack({ 215,348 , 37,99 });
	animationO.PushBack({ 177,348 , 38,104 });
	animationO.PushBack({ 133,348 , 44,106 });
	animationO.PushBack({ 89,348 , 44,109 });
	animationO.PushBack({ 45,348 , 44,111 });
	animationO.PushBack({ 0,348 , 45,114 });
	animationO.PushBack({ 430,222 , 45,118 });
	animationO.PushBack({ 384,222 , 46,120 });
	animationO.PushBack({ 338,222 , 46,121 });
	animationO.PushBack({ 292,222 , 46,120 });
	animationO.PushBack({ 244,222 , 48,123 });
	animationO.PushBack({ 196,222 , 48,122 });
	animationO.PushBack({ 148,222 , 48,122 });
	animationO.PushBack({ 100,222 , 48,126 });
	animationO.PushBack({ 50,222 , 50,122 });
	animationO.PushBack({ 0,222 , 50,116 });
	animationO.PushBack({ 439,118 , 50,104 });
	animationO.PushBack({ 389,118 , 50,92 });
	animationO.PushBack({ 339,118 , 50,82 });
	animationO.PushBack({ 290,118 , 49,74 });
	animationO.PushBack({ 241,118 , 49,68 });
	animationO.PushBack({ 192,118 , 49,63 });
	animationO.PushBack({ 144,118 , 48,61 });
	animationO.PushBack({ 96,118 , 48,60 });
	animationO.PushBack({ 48,118 , 48,59 });
	
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
	animationO.speed = 0.33f;
	animationO.repeat = false;

	//R2 animation
	animationR2.PushBack({ 186,902 , 31,61 });
	animationR2.PushBack({ 155,902 , 31,69 });
	animationR2.PushBack({ 117,902 , 38,76 });
	animationR2.PushBack({ 78,902 , 39,81 });
	animationR2.PushBack({ 39,902 , 39,87 });
	animationR2.PushBack({ 0,902 , 39,89 });
	animationR2.PushBack({ 180,790 , 43,92 });
	animationR2.PushBack({ 135,790 , 45,100 });
	animationR2.PushBack({ 90,790 , 45,103 });
	animationR2.PushBack({ 45,790 , 45,106 });
	animationR2.PushBack({ 0,790 , 45,112 });
	animationR2.PushBack({ 180,671 , 45,112 });
	animationR2.PushBack({ 135,671 , 45,114 });
	animationR2.PushBack({ 90,671 , 45,118 });
	animationR2.PushBack({ 45,671 , 45,118 });
	animationR2.PushBack({ 0,671 , 45,119 });
	animationR2.PushBack({ 180,546 , 45,116 });
	animationR2.PushBack({ 135,546 , 45,122 });
	animationR2.PushBack({ 90,546 , 45,123 });
	animationR2.PushBack({ 45,546 , 45,122 });
	animationR2.PushBack({ 0,546 , 45,125 });
	animationR2.PushBack({ 182,423 , 45,123 });
	animationR2.PushBack({ 137,423 , 45,114 });
	animationR2.PushBack({ 92,423 , 45,102 });
	animationR2.PushBack({ 46,423 , 46,91 });
	animationR2.PushBack({ 0,423 , 46,83 });
	animationR2.PushBack({ 189,348 , 47,75 });
	animationR2.PushBack({ 142,348 , 47,68 });
	animationR2.PushBack({ 95,348 , 47,63 });
	animationR2.PushBack({ 48,348 , 47,60 });
	animationR2.PushBack({ 0,348 , 48,59 });
	animationR2.PushBack({ 192,290 , 48,58 });

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
	animationR2.speed = 0.33f;
	animationR2.repeat = false;

	//T2 animation
	animationT2.PushBack({ 330,374 , 46,70 });
	animationT2.PushBack({ 284,374 , 46,73 });
	animationT2.PushBack({ 238,374 , 46,79 });
	animationT2.PushBack({ 192,374 , 46,84 });
	animationT2.PushBack({ 144,374 , 48,92 });
	animationT2.PushBack({ 96,374 , 48,93 });
	animationT2.PushBack({ 48,374 , 48,97 });
	animationT2.PushBack({ 0,374 , 48,103 });
	animationT2.PushBack({ 432,253 , 48,103 });
	animationT2.PushBack({ 384,253 , 48,109 });
	animationT2.PushBack({ 336,253 , 48,97 });
	animationT2.PushBack({ 288,253 , 48,114 });
	animationT2.PushBack({ 240,253 , 48,116 });
	animationT2.PushBack({ 192,253 , 48,118 });
	animationT2.PushBack({ 144,253 , 48,119 });
	animationT2.PushBack({ 96,253 , 48,120 });
	animationT2.PushBack({ 48,253 , 48,121 });
	animationT2.PushBack({ 0,253 , 48,117 });
	animationT2.PushBack({ 426,125 , 48,123 });
	animationT2.PushBack({ 378,125 , 48,123 });
	animationT2.PushBack({ 330,125 , 48,127 });
	animationT2.PushBack({ 282,125 , 48,128 });
	animationT2.PushBack({ 234,125 , 48,119 });
	animationT2.PushBack({ 186,125 , 48,108 });
	animationT2.PushBack({ 138,125 , 48,101 });
	animationT2.PushBack({ 92,125 , 46,90 });
	animationT2.PushBack({ 46,125 , 46,81 });
	animationT2.PushBack({ 0,125 , 46,73 });
	animationT2.PushBack({ 460,59 , 46,66 });

	animationT2.PushBack({ 414,59 , 46,62 });
	animationT2.PushBack({ 368,59 , 46,61 });
	animationT2.PushBack({ 322,59 , 46,61 });
	animationT2.PushBack({ 276,59 , 46,59 });
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
	animationT2.speed = 0.33f;
	animationT2.repeat = false;

	
	






	

}

ModuleSceneIntro:: ~ModuleSceneIntro()
{	}


bool ModuleSceneIntro::Start()
{
	LOG("------ Starting intro Scene");

	SDL_SetRenderDrawBlendMode(App->render->renderer, SDL_BLENDMODE_BLEND);

	//initializes needed variables
	timeBetweenLetters = 2.0f; //in sec

	LTexture = App->textures->Load("assets/intro/L1.png");
	ATexture = App->textures->Load("assets/intro/A.png");
	S1Texture = App->textures->Load("assets/intro/S1.png");
	T1Texture = App->textures->Load("assets/intro/T1.png");
	R1Texture = App->textures->Load("assets/intro/R1.png");
	ETexture = App->textures->Load("assets/intro/E.png");
	S2Texture = App->textures->Load("assets/intro/S2.png");
	OTexture = App->textures->Load("assets/intro/O.png");
	R2Texture = App->textures->Load("assets/intro/R2.png");
	T2Texture = App->textures->Load("assets/intro/T2MOD.png");
	titleScreen = App->textures->Load("assets/intro/titleScreen.png");
	blackScreenTexture = App->textures->Load("assets/intro/black.png");
	logoTexture = App->textures->Load("assets/intro/logo.png");

	start_time = SDL_GetTicks(); //initializes for logo timer
	total_time = 2000.0f; //logo timer
	//now = SDL_GetTicks() - start_time;



	return true;
}

update_status ModuleSceneIntro::Update()
{

	Animation* current_animation;
	SDL_Rect r;

	if (current_step == intro_step::teamLogo || current_step == intro_step::fade_to_white )
	{
		now = SDL_GetTicks() - start_time;
		App->render->Blit(blackScreenTexture, 0, 0, NULL);
		App->render->Blit(logoTexture, 0, 0, &jerry_smith);

		if (now >= total_time && current_step == intro_step::teamLogo)
		//if (App->input->keyboard[SDL_SCANCODE_SPACE] == 1)
		{
			current_step = intro_step::fade_to_white;
			start_time = SDL_GetTicks();
			total_time = 1000.0f;
		}

	}

		if (current_step == intro_step::firstSecuence || 
			current_step == intro_step::fade_to_white && logoDone == true)// ||
			//current_step == intro_step::fade_from_white)
		{
			App->render->Blit(blackScreenTexture, 0, 0, NULL);

			current_animation = &animationL;
			r = current_animation->GetCurrentFrame();

			App->render->Blit(LTexture, 20, 30, &r);

			current_animation = &animationA;
			r = current_animation->GetCurrentFrame();

			App->render->Blit(ATexture, 70 - pivotArrayA[(int)current_animation->current_frame],30, &r);

			App->render->Blit(S1Texture, 120, 30, &animationS1.GetCurrentFrame());

			App->render->Blit(T1Texture, 170, 30, &animationT1.GetCurrentFrame());

			App->render->Blit(R1Texture, 10, 100, &animationR1.GetCurrentFrame());

			App->render->Blit(ETexture, 60, 100, &animationE.GetCurrentFrame());

			App->render->Blit(S2Texture, 110, 100, &animationS2.GetCurrentFrame());

			App->render->Blit(OTexture, 160, 100, &animationO.GetCurrentFrame());

			App->render->Blit(R2Texture, 210, 100, &animationR2.GetCurrentFrame());

			current_animation = &animationT2;
			r = current_animation->GetCurrentFrame();

			App->render->Blit(T2Texture, 260, 100, &r);

			//SDL_SetRenderDrawColor(App->render->renderer, 0, 0, 0 , 0);
			//SDL_RenderFillRect(App->render->renderer, NULL);

			if (App->input->keyboard[SDL_SCANCODE_RETURN] == 1) //skip letters animation scene
				App->fade->FadeToBlack(App->introScreen, App->background);

			/*if ((int)current_animation->current_frame == (int)current_animation->last_frame)
			{

				current_step = intro_step::fade_to_white;
				start_time = SDL_GetTicks();
				total_time = 500.0f;
				lastFadeFromWhiteTime = 3000.0f;
			}*/

		}
	

	if (current_step == intro_step::fade_to_white || 
		current_step == intro_step::fade_from_white)
	{
		//App->render->Blit(titleScreen, 0, 0, NULL);
		now = SDL_GetTicks() - start_time;
		float normalized;
		
		if(logoDone && current_step == intro_step::fade_from_white)
			normalized = MIN(1.0f, (float)now / (float)lastFadeFromWhiteTime);
		else
			normalized = MIN(1.0f, (float)now / (float)total_time);

		if (current_step == intro_step::fade_to_white)
		{
			if (now >= total_time)
			{
				if (logoDone)
				{
					App->render->Blit(blackScreenTexture, 0, 0, NULL);
					App->render->Blit(titleScreen, 0, 0, NULL);
					
				}
				else
				{
					App->render->Blit(blackScreenTexture, 0, 0, NULL);
					App->render->Blit(logoTexture, 0, 0, NULL);
					
					current_step = intro_step::firstSecuence;
				}

				SDL_SetRenderDrawColor(App->render->renderer, 255, 255, 255, (Uint8)(normalized * 255.0f));
				SDL_RenderFillRect(App->render->renderer, NULL);
				// ---
				total_time += total_time;
				start_time = SDL_GetTicks();
				if (logoDone == false)
				{
					logoDone = true;
					current_step = intro_step::firstSecuence;
				}
				else

				current_step = intro_step::fade_from_white;
				
			}
		}

		else if (current_step == intro_step::fade_from_white)
		{
			
			App->render->Blit(blackScreenTexture, 0, 0, NULL);
			App->render->Blit(titleScreen, 0, 0, NULL);
			normalized = 1.0f - normalized;
			//current_step = intro_step::press_start_screen;
			
			if (now >= lastFadeFromWhiteTime)//total_time)
				current_step = intro_step::press_start_screen;
		}

		SDL_SetRenderDrawColor(App->render->renderer, 255, 255, 255, (Uint8)(normalized * 255.0f));
		SDL_RenderFillRect(App->render->renderer, NULL);
	}

	if(current_step == intro_step::press_start_screen)
	{
		App->render->Blit(blackScreenTexture, 0, 0, NULL);
		App->render->Blit(titleScreen, 0, 0, NULL);

		if (App->input->keyboard[SDL_SCANCODE_RETURN] == 1)
			App->fade->FadeToBlack(App->introScreen, App->background);
	}




	/*if (current_step == intro_step::press_start_screen)
	{
		if (App->input->keyboard[SDL_SCANCODE_RETURN] == 1)
			App->fade->FadeToBlack(App->introScreen, App->background);
	}*/

	return UPDATE_CONTINUE;
}