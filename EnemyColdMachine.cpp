#include "Application.h"
#include "EnemyColdMachine.h"
#include "ModuleCollision.h"
#include "ModuleEnemies.h"

#include "ModuleRender.h"
#include "SDL\include\SDL_timer.h"

EnemyColdMachine::EnemyColdMachine(int x, int y, powerUpTypes type, SDL_Texture* thisTexture) : Enemy(x, y)
{
	//links the correct spritesheet texture ----
	enemyTex = thisTexture;
	// -----------------------------------------
	powerUpType = type;
	life = 140;
	enemyScore = 100;
	// -----------------------------------------
	
	//animation = &blabla; //links animation

	//original_y = y;
	//fposition.x = x;

	// STATIC PIECES RECTS -----------------------------------------------
	// chest statics ---
	coldMachine.chest.chestPiece.rect[NORMAL_ANIM] = { 212,361,183,168 };
	coldMachine.chest.chestPiece.rect[DAMAGE_ANIM] = { 608,361,183,168 };
	coldMachine.chest.chestPiece.position = { 0, 0};
	// -----------------
	// leg statics   ---
	coldMachine.legs.footPiece.rect[NORMAL_ANIM] = { 267,295, 134,37 };
	coldMachine.legs.footPiece.rect[DAMAGE_ANIM] = { 663,295, 134,37 };
	coldMachine.legs.footPiece.position = { 13,292 };
	// lower leg
	coldMachine.legs.lowerLegPiece.rect[NORMAL_ANIM] = { 323,199,78,90};
	coldMachine.legs.lowerLegPiece.rect[DAMAGE_ANIM] = { 719,199,78,90 };
	coldMachine.legs.lowerLegPiece.position = { 66, 208 };
	// knee
	coldMachine.legs.kneePiece.rect[NORMAL_ANIM] = { 267,124,77,75 };
	coldMachine.legs.kneePiece.rect[DAMAGE_ANIM] = { 663,124,77,75 };
	coldMachine.legs.kneePiece.position = { 19, 189 };
	// upper leg
	coldMachine.legs.upperLegPiece.rect[NORMAL_ANIM] = { 285,46,102,78 };
	coldMachine.legs.upperLegPiece.rect[DAMAGE_ANIM] = { 681,46,102,78 };
	coldMachine.legs.upperLegPiece.position = { 37,137 };
	// hip 
	coldMachine.legs.hipPiece.rect[NORMAL_ANIM] = { 403,234,136,54 };//259,0,136,46 };
	coldMachine.legs.hipPiece.rect[DAMAGE_ANIM] = { 655,0,136,46 };
	coldMachine.legs.hipPiece.position = { 11 ,129 };//,137 };
	// --------------------------------------------------------------------
	// --------------------------------------------------------------------
	// ANIMATED parts
	// chest animations ------
	// chest cannon
	coldMachine.chest.chestCannonAnim[NORMAL_ANIM].PushBack({ 81,466,32,32 }); // max closed
	coldMachine.chest.chestCannonAnim[NORMAL_ANIM].PushBack({ 114,466,32,32 });
	coldMachine.chest.chestCannonAnim[NORMAL_ANIM].PushBack({ 147,466,32,32 });
	coldMachine.chest.chestCannonAnim[NORMAL_ANIM].PushBack({ 180,466,32,32 }); // max opened
	coldMachine.chest.chestCannonAnim[NORMAL_ANIM].PushBack({ 147,466,32,32 });
	coldMachine.chest.chestCannonAnim[NORMAL_ANIM].PushBack({ 114,466,32,32 });
	coldMachine.chest.chestCannonAnim[NORMAL_ANIM].speed = 0.25f;

	coldMachine.chest.chestCannonAnim[DAMAGE_ANIM].PushBack({ 477,466,32,32 }); // max closed
	coldMachine.chest.chestCannonAnim[DAMAGE_ANIM].PushBack({ 510,466,32,32 });
	coldMachine.chest.chestCannonAnim[DAMAGE_ANIM].PushBack({ 543,466,32,32 });
	coldMachine.chest.chestCannonAnim[DAMAGE_ANIM].PushBack({ 576,466,32,32 }); // max opened
	coldMachine.chest.chestCannonAnim[DAMAGE_ANIM].PushBack({ 543,466,32,32 });
	coldMachine.chest.chestCannonAnim[DAMAGE_ANIM].PushBack({ 510,466,32,32 });
	coldMachine.chest.chestCannonAnim[DAMAGE_ANIM].speed = 0.25f;
	//  chest missile launcher
	coldMachine.chest.shoulderLauncherAnim[NORMAL_ANIM].PushBack({ 114,418,32,32 }); // max closed
	coldMachine.chest.shoulderLauncherAnim[NORMAL_ANIM].PushBack({ 147,418,32,32 });
	coldMachine.chest.shoulderLauncherAnim[NORMAL_ANIM].PushBack({ 180,418,32,32 }); // max opened
	coldMachine.chest.shoulderLauncherAnim[NORMAL_ANIM].PushBack({ 147,418,32,32 });
	coldMachine.chest.shoulderLauncherAnim[NORMAL_ANIM].speed = 0.25f;

	coldMachine.chest.shoulderLauncherAnim[DAMAGE_ANIM].PushBack({ 510,418,32,32 }); // max closed
	coldMachine.chest.shoulderLauncherAnim[DAMAGE_ANIM].PushBack({ 543,418,32,32 });
	coldMachine.chest.shoulderLauncherAnim[DAMAGE_ANIM].PushBack({ 576,418,32,32 }); // max opened
	coldMachine.chest.shoulderLauncherAnim[DAMAGE_ANIM].PushBack({ 543,418,32,32 });
	coldMachine.chest.shoulderLauncherAnim[DAMAGE_ANIM].speed = 0.25f;
	// dumb eye open and close cycle
	coldMachine.chest.eyeAnim[NORMAL_ANIM].PushBack({ 81,370,32,32 }); // max closed
	coldMachine.chest.eyeAnim[NORMAL_ANIM].PushBack({ 114,370,32,32 });
	coldMachine.chest.eyeAnim[NORMAL_ANIM].PushBack({ 147,370,32,32 });
	coldMachine.chest.eyeAnim[NORMAL_ANIM].PushBack({ 180,370,32,32 }); // max opened
	coldMachine.chest.eyeAnim[NORMAL_ANIM].PushBack({ 147,370,32,32 });
	coldMachine.chest.eyeAnim[NORMAL_ANIM].PushBack({ 114,370,32,32 });
	coldMachine.chest.eyeAnim[NORMAL_ANIM].speed = 0.25f;

	coldMachine.chest.eyeAnim[DAMAGE_ANIM].PushBack({ 477,370,32,32 }); // max closed
	coldMachine.chest.eyeAnim[DAMAGE_ANIM].PushBack({ 510,370,32,32 });
	coldMachine.chest.eyeAnim[DAMAGE_ANIM].PushBack({ 543,370,32,32 });
	coldMachine.chest.eyeAnim[DAMAGE_ANIM].PushBack({ 576,370,32,32 }); // max opened
	coldMachine.chest.eyeAnim[DAMAGE_ANIM].PushBack({ 543,370,32,32 });
	coldMachine.chest.eyeAnim[DAMAGE_ANIM].PushBack({ 510,370,32,32 });
	coldMachine.chest.eyeAnim[DAMAGE_ANIM].speed = 0.25f;
	// back shuriken launcher
	coldMachine.chest.shurikenLauncherAnim[NORMAL_ANIM].PushBack({ 303,333,48,28 }); // max closed
	coldMachine.chest.shurikenLauncherAnim[NORMAL_ANIM].PushBack({ 358,333,48,28 });
	coldMachine.chest.shurikenLauncherAnim[NORMAL_ANIM].PushBack({ 410,333,48,28 }); // max opened
	coldMachine.chest.shurikenLauncherAnim[NORMAL_ANIM].PushBack({ 358,333,48,28 });
	coldMachine.chest.shurikenLauncherAnim[NORMAL_ANIM].speed = 0.25f;
	
	coldMachine.chest.shurikenLauncherAnim[DAMAGE_ANIM].PushBack({ 699,333,48,28 }); // max closed
	coldMachine.chest.shurikenLauncherAnim[DAMAGE_ANIM].PushBack({ 754,333,48,28 });
	coldMachine.chest.shurikenLauncherAnim[DAMAGE_ANIM].PushBack({ 806,333,48,28 }); // max opened
	coldMachine.chest.shurikenLauncherAnim[DAMAGE_ANIM].PushBack({ 754,333,48,28 });
	coldMachine.chest.shurikenLauncherAnim[DAMAGE_ANIM].speed = 0.25f;

	// ------------------------------------------------------------------------------------
	// LEG animations
	// lower leg missile launcher
	coldMachine.legs.missileLauncherAnim[NORMAL_ANIM].PushBack({ 191,247,32,32 }); // max closed
	coldMachine.legs.missileLauncherAnim[NORMAL_ANIM].PushBack({ 224,247,32,32 });
	coldMachine.legs.missileLauncherAnim[NORMAL_ANIM].PushBack({ 257,247,32,32 });
	coldMachine.legs.missileLauncherAnim[NORMAL_ANIM].PushBack({ 290,247,32,32 }); // max opened
	coldMachine.legs.missileLauncherAnim[NORMAL_ANIM].PushBack({ 257,247,32,32 });
	coldMachine.legs.missileLauncherAnim[NORMAL_ANIM].PushBack({ 224,247,32,32 });
	coldMachine.legs.missileLauncherAnim[NORMAL_ANIM].speed = 0.125f;
	coldMachine.legs.missileLauncherAnim[NORMAL_ANIM].repeat = false;

	coldMachine.legs.missileLauncherAnim[DAMAGE_ANIM].PushBack({ 587,247,32,32 }); // max closed
	coldMachine.legs.missileLauncherAnim[DAMAGE_ANIM].PushBack({ 620,247,32,32 });
	coldMachine.legs.missileLauncherAnim[DAMAGE_ANIM].PushBack({ 653,247,32,32 });
	coldMachine.legs.missileLauncherAnim[DAMAGE_ANIM].PushBack({ 686,247,32,32 }); // max opened
	coldMachine.legs.missileLauncherAnim[DAMAGE_ANIM].PushBack({ 653,247,32,32 });
	coldMachine.legs.missileLauncherAnim[DAMAGE_ANIM].PushBack({ 620,247,32,32 });
	coldMachine.legs.missileLauncherAnim[DAMAGE_ANIM].speed = 0.125f;
	coldMachine.legs.missileLauncherAnim[DAMAGE_ANIM].repeat = false;
	// knee eye beam launcher
	coldMachine.legs.kneeAnim[NORMAL_ANIM].PushBack({ 123,160,32,32 }); // max closed
	coldMachine.legs.kneeAnim[NORMAL_ANIM].PushBack({ 160,160,32,32 });
	coldMachine.legs.kneeAnim[NORMAL_ANIM].PushBack({ 197,160,32,32 });
	coldMachine.legs.kneeAnim[NORMAL_ANIM].PushBack({ 235,160,32,32 }); // max opened
	coldMachine.legs.kneeAnim[NORMAL_ANIM].PushBack({ 197,160,32,32 });
	coldMachine.legs.kneeAnim[NORMAL_ANIM].PushBack({ 160,160,32,32 });
	coldMachine.legs.kneeAnim[NORMAL_ANIM].speed = 0.125f;
	coldMachine.legs.kneeAnim[NORMAL_ANIM].repeat = false;

	coldMachine.legs.kneeAnim[DAMAGE_ANIM].PushBack({ 519,160,32,32 }); // max closed
	coldMachine.legs.kneeAnim[DAMAGE_ANIM].PushBack({ 556,160,32,32 });
	coldMachine.legs.kneeAnim[DAMAGE_ANIM].PushBack({ 593,160,32,32 }); 
	coldMachine.legs.kneeAnim[DAMAGE_ANIM].PushBack({ 631,160,32,32 }); // max opened
	coldMachine.legs.kneeAnim[DAMAGE_ANIM].PushBack({ 593,160,32,32 });
	coldMachine.legs.kneeAnim[DAMAGE_ANIM].PushBack({ 556,160,32,32 });
	coldMachine.legs.kneeAnim[DAMAGE_ANIM].speed = 0.125f;
	coldMachine.legs.kneeAnim[DAMAGE_ANIM].repeat = false;
	// knee flash reflection when shoots
	coldMachine.legs.kneeFlashReflectionAnim.PushBack({ 542,569,17,32 });
	coldMachine.legs.kneeFlashReflectionAnim.PushBack({ 508,569,17,32 });
	coldMachine.legs.kneeFlashReflectionAnim.PushBack({ 479,569,17,32 });
	coldMachine.legs.kneeFlashReflectionAnim.PushBack({ 446,569,29,32 });
	coldMachine.legs.kneeFlashReflectionAnim.PushBack({ 415,569,29,32 });
	coldMachine.legs.kneeFlashReflectionAnim.PushBack({ 386,569,29,32 });
	coldMachine.legs.kneeFlashReflectionAnim.PushBack({ 357,569,29,32 });
	coldMachine.legs.kneeFlashReflectionAnim.speed = 0.125f;
	coldMachine.legs.kneeFlashReflectionAnim.repeat = false;

	// arm shootgun
	coldMachine.legs.armShootgunAnim[NORMAL_ANIM].PushBack({ 172,0,57,99 }); // idle, pointing down, off
	coldMachine.legs.armShootgunAnim[NORMAL_ANIM].PushBack({ 91,0,81,63 });
	coldMachine.legs.armShootgunAnim[NORMAL_ANIM].PushBack({ 0,0,91,45 }); // shooting pos
	coldMachine.legs.armShootgunAnim[NORMAL_ANIM].PushBack({ 91,0,81,63 });
	coldMachine.legs.armShootgunAnim[NORMAL_ANIM].speed = 0.125f;

	coldMachine.legs.armShootgunAnim[DAMAGE_ANIM].PushBack({ 568,0,57,99 }); // idle, bad sprite
	coldMachine.legs.armShootgunAnim[DAMAGE_ANIM].PushBack({ 487,0,81,63 });
	coldMachine.legs.armShootgunAnim[DAMAGE_ANIM].PushBack({ 396,0,91,45 }); // shooting pos
	coldMachine.legs.armShootgunAnim[DAMAGE_ANIM].PushBack({ 487,0,81,63 });
	coldMachine.legs.armShootgunAnim[DAMAGE_ANIM].speed = 0.125f;
	// ------------------------------------------------------------------------------------



	collider = App->collision->AddCollider({ 0, 0, 32, 16 }, COLLIDER_TYPE::COLLIDER_ENEMY, (Module*)App->enemies);

	// sets the first boss state
	coldMachine.state = bossState::LANDING;

	position.y = -329;//-137; // spawn position y
	position.x = 157; // spawn position x

	fposition.y = position.y;

	coldMachine.stopAnimations = true;

	// first contact to ground path animation
	// first step
	// lower leg path
	coldMachine.firstContact.lowerLeg.PushBack({ 0, 1.0f }, 1);
	coldMachine.firstContact.lowerLeg.PushBack({ 0, 0 }, 48);
	coldMachine.firstContact.lowerLeg.PushBack({ 0, -1.0f }, 1); // END 48 frames
	// knee path
	coldMachine.firstContact.knee.PushBack({ 0,1.0f },1);
	coldMachine.firstContact.knee.PushBack({ 0, 0}, 8);
	coldMachine.firstContact.knee.PushBack({ 0, 1.0f }, 1);
	coldMachine.firstContact.knee.PushBack({ 0,0 }, 24);
	coldMachine.firstContact.knee.PushBack({ 0, -1.0f }, 1);
	coldMachine.firstContact.knee.PushBack({ 0, 0 }, 16);
	coldMachine.firstContact.knee.PushBack({ 0, -1.0f }, 1); // END 48 frames
	// upper leg path
	coldMachine.firstContact.upperLeg.PushBack({ 0, 1},1);
	coldMachine.firstContact.upperLeg.PushBack({ 0, 0 }, 4);
	coldMachine.firstContact.upperLeg.PushBack({ 0, 1 }, 1);
	coldMachine.firstContact.upperLeg.PushBack({ 0, 0 }, 4);
	coldMachine.firstContact.upperLeg.PushBack({ 0, 1 }, 1);
	coldMachine.firstContact.upperLeg.PushBack({ 0, 0 }, 4);
	coldMachine.firstContact.upperLeg.PushBack({ 0, 1 }, 1);
	coldMachine.firstContact.upperLeg.PushBack({ 0, 0 }, 12);
	coldMachine.firstContact.upperLeg.PushBack({ 0, -1 }, 1);
	coldMachine.firstContact.upperLeg.PushBack({ 0, 0 }, 8);
	coldMachine.firstContact.upperLeg.PushBack({ 0, -1 }, 1);
	coldMachine.firstContact.upperLeg.PushBack({ 0, 0 }, 8);
	coldMachine.firstContact.upperLeg.PushBack({ 0, -1 }, 1);
	coldMachine.firstContact.upperLeg.PushBack({ 0, 0 }, 8);
	coldMachine.firstContact.upperLeg.PushBack({ 0, -1 }, 1); // END 48 frames
	// hip path, chest is the same
	coldMachine.firstContact.hip.PushBack({0, 1}, 1);
	coldMachine.firstContact.chest.PushBack({ 0, 1 }, 1);
	for (uint i = 0; i < 8; ++i)
	{
		coldMachine.firstContact.hip.PushBack({ 0, 0 }, 2);
		coldMachine.firstContact.chest.PushBack({ 0, 0 }, 2);
		coldMachine.firstContact.hip.PushBack({ 0, 1 }, 1);
		coldMachine.firstContact.chest.PushBack({ 0, 1 }, 1);
	}
	for (uint i = 0; i < 9; ++i)
	{
		coldMachine.firstContact.hip.PushBack({ 0, 0 }, 4);
		coldMachine.firstContact.chest.PushBack({ 0, 0 }, 4);
		coldMachine.firstContact.hip.PushBack({ 0, -1 }, 1);
		coldMachine.firstContact.chest.PushBack({ 0, -1 }, 1);
	}

	coldMachine.firstContact.lowerLeg.loop = false;
	coldMachine.firstContact.knee.loop = false;
	coldMachine.firstContact.upperLeg.loop = false;
	coldMachine.firstContact.hip.loop = false;
	coldMachine.firstContact.chest.loop = false;

	// ---------------------------------------------------------
	
	
	//original.y = 60;
	//original.x = position.x;

}

void EnemyColdMachine::Move()
{
	switch (coldMachine.state)
	{
	case bossState::LANDING:
		decelerationToFloor();
		position.y = fposition.y;
		break;
	case bossState::FIRSTCONTACT:
		firstContactAnimation();
		break;
	case bossState::FASE1:
		// checks if we are throwing missiles (activated on returned rects, animation frame dependent)
		if (coldMachine.legs.throwMissiles) missilesLogic();
		if (coldMachine.legs.throwKneeBeam) kneeBeamLogic();
		break;
	}

	position.x += 1; // GENERAL POSITION
	

}

void EnemyColdMachine::kneeBeamLogic()
{

	// instantiate laser beam
	if (!coldMachine.legs.shootedLaserBeam)
	{
		App->particles->AddParticle(App->enemies->coldMachineKneeLaser, position.x + coldMachine.legs.kneePiece.position.x - 10,
			position.y + 40 + coldMachine.legs.kneePiece.position.y, COLLIDER_ENEMY_SHOT, { -1,0 }, 0);
		// update condition
		coldMachine.legs.shootedLaserBeam = true;
	}
	// instantiate laser beam reflection


}

void EnemyColdMachine::missilesLogic()
{

	// shoot the first missile of the wave
	if (!coldMachine.legs.shootedMissile)
	{
		// increment missiles count
		coldMachine.legs.missilesCount++;
		// instantiate the missile
		LOG("Missile %d instantiated", coldMachine.legs.missilesCount);
		// instantiate missile
		App->enemies->AddEnemy(HOMINGMISSILE, position.x + coldMachine.legs.lowerLegPiece.position.x + 
														   coldMachine.legs.missileCanyonsPos[coldMachine.legs.missilesCount - 1].x,	
											  position.y + coldMachine.legs.lowerLegPiece.position.y +
												           coldMachine.legs.missileCanyonsPos[coldMachine.legs.missilesCount - 1].y, NONE);
		// instantiate missile flash
		App->particles->AddParticle(App->enemies->coldMachineLegMissileFlash, position.x + coldMachine.legs.lowerLegPiece.position.x +
			coldMachine.legs.missileCanyonsPos[coldMachine.legs.missilesCount - 1].x,
			position.y - 3 + coldMachine.legs.lowerLegPiece.position.y +
			coldMachine.legs.missileCanyonsPos[coldMachine.legs.missilesCount - 1].y,
			COLLIDER_NONE, { scrollSpeed,0 }, 0);

		// update the condition
		coldMachine.legs.shootedMissile = true;
		// update timer
		coldMachine.legs.start_launch_time = SDL_GetTicks();

		// check if we finish the wave and activate timer
		if (coldMachine.legs.missilesCount == 4) // max 4 missiles per wave
		{
			coldMachine.legs.start_missiles_wave = SDL_GetTicks();
			coldMachine.legs.missilesWaveCount++; // update finished wave count
			LOG("Finished missiles wave %d", coldMachine.legs.missilesWaveCount);
		}
	}

	if (coldMachine.legs.missilesCount < 4) // max missiles per wave
	{
		// update timer for next missile shoot
		coldMachine.legs.current_missile_time = SDL_GetTicks() - coldMachine.legs.start_launch_time;
		if (coldMachine.legs.current_missile_time > coldMachine.legs.time_between_missiles)
		{
			coldMachine.legs.shootedMissile = false; // launch next missile
		}
	}
	else // wait for wave 2 of 2
	{
		coldMachine.legs.now_missile_wave_time = SDL_GetTicks() - coldMachine.legs.start_missiles_wave;
		if (coldMachine.legs.now_missile_wave_time > coldMachine.legs.time_between_waves)
		{

			// reset missileCount for activate next wave
			coldMachine.legs.missilesCount = 0;
			// update missile start launch timer
			coldMachine.legs.start_launch_time = SDL_GetTicks();
		}

	}

}

void EnemyColdMachine::firstContactAnimation()
{
	// update path animations

	coldMachine.legs.lowerLegPiece.position = original.lowerLeg + coldMachine.firstContact.lowerLeg.GetCurrentSpeed();
	coldMachine.legs.kneePiece.position = original.knee + coldMachine.firstContact.knee.GetCurrentSpeed();
	coldMachine.legs.upperLegPiece.position = original.upperLeg + coldMachine.firstContact.upperLeg.GetCurrentSpeed();
	coldMachine.legs.hipPiece.position = original.hip + coldMachine.firstContact.hip.GetCurrentSpeed();
	coldMachine.chest.chestPiece.position = original.chest + coldMachine.firstContact.chest.GetCurrentSpeed();

	// check countdown timer to switch to fase1
	coldMachine.now_cycle_time = SDL_GetTicks() - coldMachine.start_cycle_time;
	if (coldMachine.now_cycle_time > coldMachine.total_firstContact_time)
	{
		// switch enemy state
		coldMachine.state = bossState::FASE1;
		// start attack timers
		coldMachine.legs.start_missiles_time = SDL_GetTicks();
		coldMachine.legs.start_kneeBeam_time = SDL_GetTicks();
		coldMachine.legs.start_armShooting_time = SDL_GetTicks();
	}
	
}

void EnemyColdMachine::decelerationToFloor()
{

	if (position.y < -138)
	{
		if (coldMachine.ySpeed < 2.5f)
			coldMachine.ySpeed += 0.07f;

		fposition.y += coldMachine.ySpeed;
	}
	else
	{
		coldMachine.state = bossState::FIRSTCONTACT;
		// and assign actual positions for path entry animation
		original.lowerLeg = coldMachine.legs.lowerLegPiece.position;
		original.knee = coldMachine.legs.kneePiece.position;
		original.upperLeg = coldMachine.legs.upperLegPiece.position;
		original.hip = coldMachine.legs.hipPiece.position;
		original.chest = coldMachine.chest.chestPiece.position;
		// instantiate particles
		addBossParticles();
		// start countdown timer
		coldMachine.start_cycle_time = SDL_GetTicks();
	}

}

void EnemyColdMachine::Draw()
{

	// update all cycle attack timers
	coldMachine.legs.now_missiles_time = SDL_GetTicks() - coldMachine.legs.start_missiles_time;
	coldMachine.legs.now_kneeBeam_time = SDL_GetTicks() - coldMachine.legs.start_kneeBeam_time;
	coldMachine.legs.now_armShooting_time = SDL_GetTicks() - coldMachine.legs.start_armShooting_time;

	// assign if we receive damage the desireds damage sprites
	coldMachine.current_sprite_type = swapAnimType::NORMAL_ANIM; //DAMAGE_ANIM;

	// DRAW full chest static pieces --------
	// static upper part chest
	App->render->Blit(enemyTex, position.x + coldMachine.chest.chestPiece.position.x, 
		position.y + coldMachine.chest.chestPiece.position.y, &coldMachine.chest.chestPiece.rect[coldMachine.current_sprite_type]);
	// static hip
	App->render->Blit(enemyTex, position.x + coldMachine.legs.hipPiece.position.x, 
		position.y + coldMachine.legs.hipPiece.position.y, &coldMachine.legs.hipPiece.rect[coldMachine.current_sprite_type]);
	// static upper leg piece 
	App->render->Blit(enemyTex, position.x + coldMachine.legs.upperLegPiece.position.x,
		position.y + coldMachine.legs.upperLegPiece.position.y, &coldMachine.legs.upperLegPiece.rect[coldMachine.current_sprite_type]);
	// static upper leg
	App->render->Blit(enemyTex, position.x + coldMachine.legs.lowerLegPiece.position.x,
		position.y + coldMachine.legs.lowerLegPiece.position.y, &coldMachine.legs.lowerLegPiece.rect[coldMachine.current_sprite_type]);
	// static knee
	App->render->Blit(enemyTex, position.x + coldMachine.legs.kneePiece.position.x,
		position.y + coldMachine.legs.kneePiece.position.y, &coldMachine.legs.kneePiece.rect[coldMachine.current_sprite_type]);
	// static foot
	App->render->Blit(enemyTex, position.x + coldMachine.legs.footPiece.position.x,
		position.y + coldMachine.legs.footPiece.position.y, &coldMachine.legs.footPiece.rect[coldMachine.current_sprite_type]);
	
	// DRAW ALL animations
	// on landing fase, all animations are stopped
	// lower leg missile launcher ---
	
	App->render->Blit(enemyTex, position.x + coldMachine.legs.lowerLegPiece.position.x - 23,
		position.y + coldMachine.legs.lowerLegPiece.position.y + 49, &returnRect(coldMachine.legs.missileLauncherAnim));

	// knee open eye for beam --------------------------------------------------------------------------------------------

	App->render->Blit(enemyTex, position.x + coldMachine.legs.kneePiece.position.x  ,
		position.y + coldMachine.legs.kneePiece.position.y + 36, &returnRect(coldMachine.legs.kneeAnim));

	// checks if we needs to play reflection
	// play reflection animation
	if (coldMachine.legs.playReflection)
	{
		App->render->Blit(enemyTex, position.x + coldMachine.legs.kneePiece.position.x,
			position.y + coldMachine.legs.kneePiece.position.y + 36,
			&coldMachine.legs.kneeFlashReflectionAnim.GetCurrentFrame());

		if (coldMachine.legs.kneeFlashReflectionAnim.finish)
			coldMachine.legs.playReflection = false;
	}
	// --------------------------------------------------------------------------------------------------------------------

	// arm shooting //coldMachine.legs.armShootgunAnim[coldMachine.current_sprite_type].frames[0];//
	coldMachine.legs.armShotgunRect = returnRect(coldMachine.legs.armShootgunAnim);
	
	App->render->Blit(enemyTex, position.x + coldMachine.legs.hipPiece.position.x + 
		coldMachine.legs.shotGunPivots[(int)coldMachine.legs.armShootgunAnim->current_frame].x - coldMachine.legs.armShotgunRect.w,
		position.y + coldMachine.legs.hipPiece.position.y + coldMachine.legs.shotGunPivots[(int)coldMachine.legs.armShootgunAnim->current_frame].y, 
		&coldMachine.legs.armShotgunRect);

}

SDL_Rect& EnemyColdMachine::returnRect(Animation* anim)
{
	// general stop animations
	if (coldMachine.state != bossState::FASE1 && coldMachine.state != bossState::FASE2)
	{
		if (coldMachine.stopAnimations)
			return anim[coldMachine.current_sprite_type].frames[0];
		else
			return anim[coldMachine.current_sprite_type].GetCurrentFrame();
	}

	// weapons cycle return fase1, legs
	// missiles
	if (coldMachine.state == bossState::FASE1 && anim == coldMachine.legs.missileLauncherAnim)
	{
		// missiles animation and activator logic -----------------------------------------------

		if (coldMachine.legs.now_missiles_time > coldMachine.legs.missiles_cadence_time) //&& anim == coldMachine.legs.missileLauncherAnim)
		{
			if (anim[coldMachine.current_sprite_type].current_frame >= 3 && coldMachine.legs.missilesWaveCount < 2)
			{
				if (!coldMachine.legs.throwMissiles) // activate the launch and assigns timer
				{
					coldMachine.legs.start_missiles_wave = SDL_GetTicks();
					coldMachine.legs.throwMissiles = true;
				}
				// return opened missile launcher gate
				return anim[coldMachine.current_sprite_type].frames[3];
			}
			else
			{

				if (anim[coldMachine.current_sprite_type].finish)
				{
					// resets missiles waves counter and prepare next missile launch
					coldMachine.legs.missilesWaveCount = 0;
					coldMachine.legs.missilesCount = 0;
					coldMachine.legs.shootedMissile = false;
					// shutdown missiles throwing
					coldMachine.legs.throwMissiles = false;
					// resets timers
					coldMachine.legs.start_missiles_time = SDL_GetTicks();
					coldMachine.legs.start_launch_time = SDL_GetTicks();
					// resets and return correct frame animation
					anim->current_frame = 0;
					anim->finish = false;
					//returns correct frame
					return anim[coldMachine.current_sprite_type].frames[0];
				}
				else
					return anim[coldMachine.current_sprite_type].GetCurrentFrame();

			}
		}
		else
			return anim[coldMachine.current_sprite_type].frames[0];

	}
		// -------------------------------------------------------------------------------------

	// KNEE BEAM fase 1
	if (coldMachine.state == bossState::FASE1 && anim == coldMachine.legs.kneeAnim)
	{
		if (coldMachine.legs.now_kneeBeam_time > coldMachine.legs.kneeBeam_cadence_time)
		{
			if (anim[coldMachine.current_sprite_type].current_frame >= 3 && !coldMachine.legs.kneeFlashReflectionAnim.finish)
			{
				coldMachine.legs.throwKneeBeam = true;
				if(!coldMachine.legs.playReflection)
					coldMachine.legs.playReflection = true;
				// checks if reflection finish and finish max open situation to return to close and wait for next shot



				return anim[coldMachine.current_sprite_type].frames[3];
			}
			else
			{

				if (anim[coldMachine.current_sprite_type].finish)
				{
					// reset timer
					coldMachine.legs.start_kneeBeam_time = SDL_GetTicks();
					// reset animation data
					anim[coldMachine.current_sprite_type].finish = false;
					anim[coldMachine.current_sprite_type].current_frame = 0;
					// reset reflection animation data
					coldMachine.legs.kneeFlashReflectionAnim.finish = false;
					coldMachine.legs.kneeFlashReflectionAnim.current_frame = 0;
					// resets needed laser shoot relatives
					coldMachine.legs.throwKneeBeam = false;
					coldMachine.legs.shootedLaserBeam = false;
					// return last correct frame
					return  anim[coldMachine.current_sprite_type].frames[0];
				}

				return anim[coldMachine.current_sprite_type].GetCurrentFrame();
			}
				
		}
		else
			return anim[coldMachine.current_sprite_type].frames[0];
	}
	


}

void EnemyColdMachine::addBossParticles()
{
	// foot fire explosion 8 frames --------
	App->particles->AddParticle(App->enemies->coldMachineFootFire, position.x + coldMachine.legs.footPiece.position.x + 22,
		position.y + 19 + coldMachine.legs.footPiece.position.y, COLLIDER_NONE, { scrollSpeed,0 }, 0);
	App->particles->AddParticle(App->enemies->coldMachineFootFire, position.x + coldMachine.legs.footPiece.position.x + 30,
		position.y + 19 + coldMachine.legs.footPiece.position.y, COLLIDER_NONE, { scrollSpeed,0 }, 0);
	App->particles->AddParticle(App->enemies->coldMachineFootFire, position.x + coldMachine.legs.footPiece.position.x + 62,
		position.y + 19 + coldMachine.legs.footPiece.position.y, COLLIDER_NONE, { scrollSpeed,0 }, 0);
	App->particles->AddParticle(App->enemies->coldMachineFootFire, position.x + coldMachine.legs.footPiece.position.x + 94,
		position.y + 19 + coldMachine.legs.footPiece.position.y, COLLIDER_NONE, { scrollSpeed,0 }, 0);
	// foot smoke -----
	App->particles->AddParticle(App->enemies->coldMachineFootSmoke, position.x + coldMachine.legs.footPiece.position.x + 22,
		position.y + 5 + coldMachine.legs.footPiece.position.y, COLLIDER_NONE, { scrollSpeed,0 }, 200);
	App->particles->AddParticle(App->enemies->coldMachineFootSmoke, position.x + coldMachine.legs.footPiece.position.x + 31,
		position.y + 5 + coldMachine.legs.footPiece.position.y, COLLIDER_NONE, { scrollSpeed,0 }, 200);
	App->particles->AddParticle(App->enemies->coldMachineFootSmoke, position.x + coldMachine.legs.footPiece.position.x + 63,
		position.y + 5 + coldMachine.legs.footPiece.position.y, COLLIDER_NONE, { scrollSpeed,0 }, 200);
	App->particles->AddParticle(App->enemies->coldMachineFootSmoke, position.x + coldMachine.legs.footPiece.position.x + 95,
		position.y + 5 + coldMachine.legs.footPiece.position.y, COLLIDER_NONE, { scrollSpeed,0 }, 200);
	// between moving pieces smoke
	App->particles->AddParticle(App->enemies->coldMachinePiecesSmoke, position.x + coldMachine.legs.hipPiece.position.x + 19,
		position.y + 31 + coldMachine.legs.hipPiece.position.y, COLLIDER_NONE, { scrollSpeed,0 }, 0);
	App->particles->AddParticle(App->enemies->coldMachinePiecesSmoke, position.x + coldMachine.legs.hipPiece.position.x + 75,
		position.y + 47 + coldMachine.legs.hipPiece.position.y, COLLIDER_NONE, { scrollSpeed,0 }, 0);
	App->particles->AddParticle(App->enemies->coldMachinePiecesSmoke, position.x + coldMachine.legs.hipPiece.position.x + 67,
		position.y + 79 + coldMachine.legs.hipPiece.position.y, COLLIDER_NONE, { scrollSpeed,0 }, 0);
	App->particles->AddParticle(App->enemies->coldMachinePiecesSmoke, position.x + coldMachine.legs.hipPiece.position.x + 107,
		position.y + 47 + coldMachine.legs.hipPiece.position.y, COLLIDER_NONE, { scrollSpeed,0 }, 0);
	App->particles->AddParticle(App->enemies->coldMachinePiecesSmoke, position.x + coldMachine.legs.hipPiece.position.x + 69,
		position.y - 7 + coldMachine.legs.hipPiece.position.y, COLLIDER_NONE, { scrollSpeed,0 }, 0);

}