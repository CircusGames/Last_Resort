#include "Application.h"
#include "EnemyBigDaddy.h"
#include "ModuleCollision.h"
#include "ModuleEnemies.h"

#include "ModuleRender.h"
#include "SDL\include\SDL_timer.h"

EnemyBigDaddy::EnemyBigDaddy(int x, int y, powerUpTypes type, SDL_Texture* thisTexture) : Enemy(x, y)
{
	// Loads laser texture, only we have 1 big daddy on scene, loads here is ok
	laserTexture = App->textures->Load("assets/Graphics/Enemies/Level_3/laserMidBoss.png");
	//links the correct spritesheet texture ----
	enemyTex = thisTexture;
	// -----------------------------------------
	powerUpType = type;
	life = 20;
	enemyScore = 1200;

	// animation rects --------------------------------------------------------------------------------------
	// big daddy on stage animation
	// normal anim
	bigDaddy.onStageAnim[NORMAL_ANIM].PushBack({ 325,167,64,60 }); // midEye center
	bigDaddy.onStageAnim[NORMAL_ANIM].speed = 0.25f;

	// lasers animations
	// left/right --------------------------------
	// left cap // the biggests parts lasts x2 = at the start and end of animation repeats the frame
	laser.anim[0][0].PushBack({138,179,16,8}); // big
	laser.anim[0][0].PushBack({ 90,179,15,6 }); // 
	laser.anim[0][0].PushBack({ 44,179,14,4 }); //
	laser.anim[0][0].PushBack({ 0,179,13,2 }); // 

	laser.anim[0][0].PushBack({ 44,179,14,4 }); //
	laser.anim[0][0].PushBack({ 90,179,15,6 }); // 
	laser.anim[0][0].PushBack({ 138,179,16,8 }); // big
	laser.anim[0][0].speed = 1.0f;

	// mid THREE MID PARTS TOTAL
	for (uint i = 1; i < 4; ++i)
	{
		laser.anim[0][i].PushBack({ 155,179,16,8 }); // big
		laser.anim[0][i].PushBack({ 106,179,16,6 });
		laser.anim[0][i].PushBack({ 59,179,16,4 });
		laser.anim[0][i].PushBack({ 14,179,16,2 });

		laser.anim[0][i].PushBack({ 59,179,16,4 });
		laser.anim[0][i].PushBack({ 106,179,16,6 });
		laser.anim[0][i].PushBack({ 155,179,16,8 }); // big
		laser.anim[0][i].speed = 1.0f;
	}
	// right cap
	laser.anim[0][4].PushBack({ 172,179,16,8 }); // big
	laser.anim[0][4].PushBack({ 123,179,15,6 });
	laser.anim[0][4].PushBack({ 76,179,14,4 });
	laser.anim[0][4].PushBack({ 31,179,13,2 });

	laser.anim[0][4].PushBack({ 76,179,14,4 });
	laser.anim[0][4].PushBack({ 123,179,15,6 });
	laser.anim[0][4].PushBack({ 172,179,16,8 }); // big
	laser.anim[0][4].speed = 1.0f;
	// ---------------------------------------------
	// UP & DOWN animation parts -------
	// upper cap
	laser.anim[1][0].PushBack({ 200,179,8,16 }); // upper cap BIG
	laser.anim[1][0].PushBack({ 194,179,6,15 });
	laser.anim[1][0].PushBack({ 190,179,4,14 });
	laser.anim[1][0].PushBack({ 188,179,2,13 });
	
	laser.anim[1][0].PushBack({ 190,179,4,14 });
	laser.anim[1][0].PushBack({ 194,179,6,15 });
	laser.anim[1][0].PushBack({ 200,179,8,16 }); // upper cap BIG
	laser.anim[1][0].speed = 1.0f;
	// MID PARTS caps
	for (uint i = 1; i < 4; ++i)
	{
		laser.anim[1][i].PushBack({ 200,196,8,16 }); // BIG
		laser.anim[1][i].PushBack({ 194,195,6,16 });
		laser.anim[1][i].PushBack({ 190,194,4,14 });
		laser.anim[1][i].PushBack({ 188,194,2,13 });

		laser.anim[1][i].PushBack({ 190,194,4,14 });
		laser.anim[1][i].PushBack({ 194,195,6,16 });
		laser.anim[1][i].PushBack({ 200,196,8,16 }); // BIG
		laser.anim[1][i].speed = 1.0f;
	}
	// down cap pointing down
	laser.anim[1][4].PushBack({ 200,213,8,16 }); // BIG
	laser.anim[1][4].PushBack({ 194,212,6,16 });
	laser.anim[1][4].PushBack({ 190,211,4,14 });
	laser.anim[1][4].PushBack({ 188,210,2,13 });

	laser.anim[1][4].PushBack({ 190,211,4,14 });
	laser.anim[1][4].PushBack({ 194,212,6,16 });
	laser.anim[1][4].PushBack({ 200,213,8,16 }); // BIG
	laser.anim[1][4].speed = 1.0f;
	// -------
	// 3pi/4 -------------------------------------------------
	// pointing "up" cap
	laser.anim[2][0].PushBack({ 0,129,22,16 }); // BIG
	laser.anim[2][0].PushBack({ 198,79,19,15 });
	laser.anim[2][0].PushBack({ 152,79,16,14 });
	laser.anim[2][0].PushBack({ 108,79,14,13 });

	laser.anim[2][0].PushBack({ 152,79,16,14 });
	laser.anim[2][0].PushBack({ 198,79,19,15 });
	laser.anim[2][0].PushBack({ 0,129,22,16 }); // BIG
	laser.anim[2][0].speed = 1.0f;
	//  mid
	for (uint i = 1; i < 4; ++i)
	{
		laser.anim[2][i].PushBack({ 11,146,28,16 }); // BIG
		laser.anim[2][i].PushBack({ 210,95,24,16 });
		laser.anim[2][i].PushBack({ 165,94,20,16 });
		laser.anim[2][i].PushBack({ 121,93,18,16 });

		laser.anim[2][i].PushBack({ 165,94,20,16 });
		laser.anim[2][i].PushBack({ 210,95,24,16 });
		laser.anim[2][i].PushBack({ 11,146,28,16 }); // BIG
		laser.anim[2][i].speed = 1.0f;
	}
	// pointing "down" cap
	laser.anim[2][4].PushBack({ 28,163,22,16 }); // BIG
	laser.anim[2][4].PushBack({ 227,112,19,15 });
	laser.anim[2][4].PushBack({ 182,111,16,14 });
	laser.anim[2][4].PushBack({ 138,110,14,13 });

	laser.anim[2][4].PushBack({ 182,111,16,14 });
	laser.anim[2][4].PushBack({ 227,112,19,15 });
	laser.anim[2][4].PushBack({ 28,163,22,16 }); // BIG
	laser.anim[2][4].speed = 1.0f;
	// -----------------------------------------------------
	// PI/4 ------------------------
	// pointing "up" cap
	laser.anim[3][0].PushBack({ 216,129,22,16 }); // BIG
	laser.anim[3][0].PushBack({ 169,129,19,15 }); 
	laser.anim[3][0].PushBack({ 124,129,16,14 }); 
	laser.anim[3][0].PushBack({ 80,129,14,13 });

	laser.anim[3][0].PushBack({ 124,129,16,14 });
	laser.anim[3][0].PushBack({ 169,129,19,15 });
	laser.anim[3][0].PushBack({ 216,129,22,16 }); // BIG
	laser.anim[3][0].speed = 1.0f;
	// mid
	for (uint i = 1; i < 4; ++i)
	{
		laser.anim[3][i].PushBack({ 199,146,28,16 }); // BIG
		laser.anim[3][i].PushBack({ 152,145,24,16 }); 
		laser.anim[3][i].PushBack({ 107,144,20,16 });
		laser.anim[3][i].PushBack({ 63, 143,18,16 });

		laser.anim[3][i].PushBack({ 107,144,20,16 });
		laser.anim[3][i].PushBack({ 152,145,24,16 });
		laser.anim[3][i].PushBack({ 199,146,28,16 }); // BIG
		laser.anim[3][i].speed = 1.0f;

	}
	// "down" cap
	laser.anim[3][4].PushBack({ 188,163,22,16 }); // BIG
	laser.anim[3][4].PushBack({ 140,162,19,15 });
	laser.anim[3][4].PushBack({ 94,161,16,14 });
	laser.anim[3][4].PushBack({ 50,160,14,13 });

	laser.anim[3][4].PushBack({ 94,161,16,14 });
	laser.anim[3][4].PushBack({ 140,162,19,15 });
	laser.anim[3][4].PushBack({ 188,163,22,16 }); // BIG
	laser.anim[3][4].speed = 1.0f;
	// ----------------------------------------------------


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


	collider = App->collision->AddCollider({ 0, 0, 44, 48 }, COLLIDER_TYPE::COLLIDER_ENEMY, (Module*)App->enemies);


	// start timers
	bigDaddy.start_shoot_time = SDL_GetTicks();

	//offset[0][1] = { 13,0 };

	
	// -----------------------------------------------------
	// OFFSETS distances for the right/left laser, this distances measures how long can reach the first instantiated cap before the next part is activated
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


	// indicates wich axis direcion laser we have to instantiate/move/animate
	//laser.laserAxisIndex = 0; // right left situation || LINKS to the animation data
	laser.laserAxisIndex = 0; // Up and down situation ------------------------------------------------------------------

	// spawn points boss laser corners
	laser.instantiationPosition[0] = { position.x - 50, position.y }; // left up corner
	laser.instantiationPosition[1] = { 200 , 100 }; // left down corner
	laser.instantiationPosition[2] = { 200 , 100 }; // right up corner
	laser.instantiationPosition[3] = { 200 , 100 }; // right down corner

	// test
	laser.position[0][0] = laser.instantiationPosition[0];
	laser.position[0][4] = laser.instantiationPosition[0];
	laser.position[1][4] = laser.instantiationPosition[0];
	laser.position[1][0] = laser.instantiationPosition[0];
	// important laser shooting logic activators ----
	laser.laserPartIndex[0] = 0; // direction cap selector
	//laser.laserPartIndex[1] = 4;
	// activate laser parts
	//laser.active[laser.laserAxisIndex][laser.laserPartIndex[0]] = true;
	

}

void EnemyBigDaddy::Move()
{
	// updates laser instantiation position to follow enemy position || instatiation point position
	laser.instantiationPosition[0] = { position.x - 50 , position.y }; // left up corner
	
	//fposition.x -= 1.35;
	//position.x = fposition.x;
	position.x += 1; // ENEMY position

	// this array stores the first shooted part of one of the total 4 instantiation enemy corner points 
	// for do correct for loops checks(inverse/reverse order), or this is the intention
	// in really only stores the last or the first 0/4 (order for activate the correct parts dependent of direction)
	//laser.laserPartIndex[0] = 4;
	// activate laser parts
	//laser.active[0][laser.laserPartIndex[0]] = true;

	// UPDATES POSITIONS OF ALL PARTS of the LASERS -----------------------------------------------
	// check if the instantiated laser need to be mounted in inverse/reverse
	// if is to the right to left 4 to 0... and the next part of the chain isnt yet instantiated, associate each parts positions and updates it
	
	for (uint i = 0; i < 5; ++i)
	{
		if (laser.active[laser.laserAxisIndex][i])
		{
			//laser.position[laser.laserAxisIndex][i].x += 2; //5 to right
			//laser.position[laser.laserAxisIndex][i].y += 1;
		}
	}



	// -----------------------------------------------------------------------------------

	// set colliders pos
	collider->SetPos(position.x + 10, position.y + 8);

	
	//laser.position[1][0].x += 2;
	//laser.position[0][0].y = 100;

}

void EnemyBigDaddy::Draw()
{


	// check shooting cadence time
	bigDaddy.now_shoot_time = SDL_GetTicks() - bigDaddy.start_shoot_time;
	if (bigDaddy.now_shoot_time > bigDaddy.cadence_shoot_time && !bigDaddy.attack)
	{
		bigDaddy.attack = true;
	}

	// full body onStage animation
	App->render->Blit(enemyTex,position.x, position.y, &bigDaddy.onStageAnim->GetCurrentFrame());

	// instantiate laser beams
	if (bigDaddy.attack && !laser.active[laser.laserAxisIndex][laser.laserPartIndex[0]])
	{
		laser.active[laser.laserAxisIndex][laser.laserPartIndex[0]] = true;
		laser.position[laser.laserAxisIndex][laser.laserPartIndex[0]] = laser.instantiationPosition[0];
	}

	// check distances ---

	if (!laser.laserPartIndex[0] > 0)
	{
		if (laser.active[laser.laserAxisIndex][0])
		{
			for (uint i = 1; i < 5; ++i)
			{
				distanceManhattan = laser.position[laser.laserAxisIndex][0].DistanceManhattan(laser.instantiationPosition[0]);

				if (distanceManhattan > maxDistances[i - 1] && !laser.active[laser.laserAxisIndex][i])
				{
					laser.active[laser.laserAxisIndex][i] = true;
					laser.position[laser.laserAxisIndex][i] = laser.position[laser.laserAxisIndex][i - 1] + offset[laser.laserAxisIndex][i];
					laser.anim[laser.laserAxisIndex][i].current_frame = laser.anim[laser.laserAxisIndex][i - 1].current_frame;
				}
			}
		}
	}
	else
	{
		if (laser.active[laser.laserAxisIndex][4])
		{
			for (int i = 4; i >= 0; --i)
			{
				distanceManhattan = laser.position[laser.laserAxisIndex][4].DistanceManhattan(laser.instantiationPosition[0]);

				if (distanceManhattan > maxDistances[3 - i] && !laser.active[laser.laserAxisIndex][i])
				{
					laser.active[laser.laserAxisIndex][i] = true;
					laser.position[laser.laserAxisIndex][i] = laser.position[laser.laserAxisIndex][i + 1] - offset[laser.laserAxisIndex][i];
					laser.anim[laser.laserAxisIndex][i].current_frame = laser.anim[laser.laserAxisIndex][i + 1].current_frame;
				}
			}
		}
	}


	

	// DRAW lasers actives 
	for (uint i = 0; i < 5; ++i)
	{

		if (laser.active[laser.laserAxisIndex][i])
		{
			laser.rect = laser.anim[laser.laserAxisIndex][i].GetCurrentFrame();

			App->render->Blit(laserTexture, laser.position[laser.laserAxisIndex][i].x - laser.rect.w / 2, laser.position[laser.laserAxisIndex][i].y - laser.rect.h / 2, &laser.rect);
		}
	}

	/*App->render->Blit(laserTexture, laser.position[0][1].x , laser.position[0][1].y, &laser.anim[0][1].GetCurrentFrame());

	App->render->Blit(laserTexture, laser.position[0][2].x , laser.position[0][2].y, &laser.anim[0][2].GetCurrentFrame());

	App->render->Blit(laserTexture, laser.position[0][3].x, laser.position[0][3].y, &laser.anim[0][3].GetCurrentFrame());

	App->render->Blit(laserTexture, laser.position[0][4].x, laser.position[0][4].y, &laser.anim[0][4].GetCurrentFrame());*/

	// DRAW FIRE animation
	//flashAnimRect = bigDaddy.laserFlashAnim.GetCurrentFrame();

	App->render->Blit(laserTexture, laser.instantiationPosition[0].x - 5 + pivotFlashAnim[(int)bigDaddy.laserFlashAnim.current_frame].x,
		laser.instantiationPosition[0].y + pivotFlashAnim[(int)bigDaddy.laserFlashAnim.current_frame].y - 5, &bigDaddy.laserFlashAnim.GetCurrentFrame());
}

EnemyBigDaddy::~EnemyBigDaddy()
{
	// unloads laser texture
	App->textures->Unload(laserTexture);
	

}