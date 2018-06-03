#include "Application.h"
#include "EnemyColdMachine.h"
#include "ModuleCollision.h"
#include "ModuleEnemies.h"

#include "ModuleRender.h"
#include "SDL\include\SDL_timer.h"
#include "ModuleAudio.h"

EnemyColdMachine::EnemyColdMachine(int x, int y, powerUpTypes type, SDL_Texture* thisTexture) : Enemy(x, y)
{
	enemyType = COLDMACHINE;
	//links the correct spritesheet texture ----
	enemyTex = thisTexture;
	// -----------------------------------------
	powerUpType = type;
	life = 140;
	enemyScore = 100;
	// -----------------------------------------
	// Load specific boss sfx
	App->audio->LoadAudio("assets/Audio/SFX/Enemies/Boss_arm_shoot.wav", "armShoot", SFX);
	App->audio->LoadAudio("assets/Audio/SFX/Enemies/Boss_Blue_Balls.wav", "shuriken", SFX);
	App->audio->LoadAudio("assets/Audio/SFX/Enemies/Boss_knee_laser.wav", "kneeLaser", SFX);
	App->audio->LoadAudio("assets/Audio/SFX/Enemies/Boss_landing.wav", "bossLanding", SFX);
	App->audio->LoadAudio("assets/Audio/SFX/Enemies/Boss_Move.wav", "bossMove", SFX);
	App->audio->LoadAudio("assets/Audio/SFX/Enemies/Boss_rocket.wav", "bossRocket", SFX); 

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
	for (uint i = 0; i < 4; i++)
		coldMachine.chest.chestCannonAnim[NORMAL_ANIM].PushBack({ 180,466,32,32 }); // max opened 24 frames
	coldMachine.chest.chestCannonAnim[NORMAL_ANIM].PushBack({ 147,466,32,32 });
	coldMachine.chest.chestCannonAnim[NORMAL_ANIM].PushBack({ 114,466,32,32 });
	coldMachine.chest.chestCannonAnim[NORMAL_ANIM].PushBack({ 81,466,32,32 }); // max closed
	coldMachine.chest.chestCannonAnim[NORMAL_ANIM].speed = 0.125f;
	coldMachine.chest.chestCannonAnim[NORMAL_ANIM].repeat = false;

	coldMachine.chest.chestCannonAnim[DAMAGE_ANIM].PushBack({ 477,466,32,32 }); // max closed
	coldMachine.chest.chestCannonAnim[DAMAGE_ANIM].PushBack({ 510,466,32,32 });
	coldMachine.chest.chestCannonAnim[DAMAGE_ANIM].PushBack({ 543,466,32,32 });
	for (uint i = 0; i < 4; i++)
		coldMachine.chest.chestCannonAnim[DAMAGE_ANIM].PushBack({ 576,466,32,32 }); // max opened
	coldMachine.chest.chestCannonAnim[DAMAGE_ANIM].PushBack({ 543,466,32,32 });
	coldMachine.chest.chestCannonAnim[DAMAGE_ANIM].PushBack({ 510,466,32,32 });
	coldMachine.chest.chestCannonAnim[DAMAGE_ANIM].PushBack({ 477,466,32,32 }); // max closed
	coldMachine.chest.chestCannonAnim[DAMAGE_ANIM].speed = 0.125f;
	coldMachine.chest.chestCannonAnim[NORMAL_ANIM].repeat = false;
	//  chest missile launcher
	coldMachine.chest.shoulderLauncherAnim[NORMAL_ANIM].PushBack({ 114,418,32,32 }); // max closed
	coldMachine.chest.shoulderLauncherAnim[NORMAL_ANIM].PushBack({ 147,418,32,32 });

	coldMachine.chest.shoulderLauncherAnim[NORMAL_ANIM].PushBack({ 180,418,32,32 }); // max opened
	coldMachine.chest.shoulderLauncherAnim[NORMAL_ANIM].PushBack({ 180,418,32,32 }); // max opened
	coldMachine.chest.shoulderLauncherAnim[NORMAL_ANIM].PushBack({ 147,418,32,32 });
	coldMachine.chest.shoulderLauncherAnim[NORMAL_ANIM].PushBack({ 114,418,32,32 }); // max closed
	coldMachine.chest.shoulderLauncherAnim[NORMAL_ANIM].speed = 0.125f;
	coldMachine.chest.shoulderLauncherAnim[NORMAL_ANIM].repeat = false;

	coldMachine.chest.shoulderLauncherAnim[DAMAGE_ANIM].PushBack({ 510,418,32,32 }); // max closed
	coldMachine.chest.shoulderLauncherAnim[DAMAGE_ANIM].PushBack({ 543,418,32,32 });
	coldMachine.chest.shoulderLauncherAnim[DAMAGE_ANIM].PushBack({ 576,418,32,32 }); // max opened
	coldMachine.chest.shoulderLauncherAnim[DAMAGE_ANIM].PushBack({ 576,418,32,32 }); // max opened
	coldMachine.chest.shoulderLauncherAnim[DAMAGE_ANIM].PushBack({ 543,418,32,32 });
	coldMachine.chest.shoulderLauncherAnim[DAMAGE_ANIM].PushBack({ 510,418,32,32 }); // max closed
	coldMachine.chest.shoulderLauncherAnim[DAMAGE_ANIM].speed = 0.125f;
	coldMachine.chest.shoulderLauncherAnim[DAMAGE_ANIM].repeat = false;
	// dumb eye open and close cycle
	coldMachine.chest.eyeAnim[NORMAL_ANIM].PushBack({ 81,370,32,32 }); // max closed
	coldMachine.chest.eyeAnim[NORMAL_ANIM].PushBack({ 114,370,32,32 });
	coldMachine.chest.eyeAnim[NORMAL_ANIM].PushBack({ 147,370,32,32 });
	for (uint i = 0; i < 4; ++i) // 32 frames opened
	{
		coldMachine.chest.eyeAnim[NORMAL_ANIM].PushBack({ 180,370,32,32 }); // max opened
	}
	coldMachine.chest.eyeAnim[NORMAL_ANIM].PushBack({ 147,370,32,32 });
	coldMachine.chest.eyeAnim[NORMAL_ANIM].PushBack({ 114,370,32,32 });
	coldMachine.chest.eyeAnim[NORMAL_ANIM].speed = 0.125f;
	coldMachine.chest.eyeAnim[NORMAL_ANIM].repeat = false;

	coldMachine.chest.eyeAnim[DAMAGE_ANIM].PushBack({ 477,370,32,32 }); // max closed
	coldMachine.chest.eyeAnim[DAMAGE_ANIM].PushBack({ 510,370,32,32 });
	coldMachine.chest.eyeAnim[DAMAGE_ANIM].PushBack({ 543,370,32,32 });
	for (uint i = 0; i < 4; i++)
	{
		coldMachine.chest.eyeAnim[DAMAGE_ANIM].PushBack({ 576,370,32,32 }); // max opened
	}
	coldMachine.chest.eyeAnim[DAMAGE_ANIM].PushBack({ 543,370,32,32 });
	coldMachine.chest.eyeAnim[DAMAGE_ANIM].PushBack({ 510,370,32,32 });
	coldMachine.chest.eyeAnim[DAMAGE_ANIM].speed = 0.125f;
	coldMachine.chest.eyeAnim[DAMAGE_ANIM].repeat = false;
	// back shuriken launcher
	coldMachine.chest.shurikenLauncherAnim[NORMAL_ANIM].PushBack({ 303,333,48,28 }); // max closed
	coldMachine.chest.shurikenLauncherAnim[NORMAL_ANIM].PushBack({ 358,333,48,28 });
	for (uint i = 0; i < 10; i++)
		coldMachine.chest.shurikenLauncherAnim[NORMAL_ANIM].PushBack({ 410,333,48,28 }); 
	coldMachine.chest.shurikenLauncherAnim[NORMAL_ANIM].PushBack({ 462,333,48,28 });// max opened // 84 frames

	coldMachine.chest.shurikenLauncherAnim[NORMAL_ANIM].PushBack({ 358,333,48,28 });
	coldMachine.chest.shurikenLauncherAnim[NORMAL_ANIM].PushBack({ 303,333,48,28 }); // max closed
	coldMachine.chest.shurikenLauncherAnim[NORMAL_ANIM].speed = 0.125f;
	coldMachine.chest.shurikenLauncherAnim[NORMAL_ANIM].repeat = false;
	coldMachine.chest.shurikenLauncherAnim[NORMAL_ANIM].finish = true; // fake condition
	
	coldMachine.chest.shurikenLauncherAnim[DAMAGE_ANIM].PushBack({ 699,333,48,28 }); // max closed
	coldMachine.chest.shurikenLauncherAnim[DAMAGE_ANIM].PushBack({ 754,333,48,28 });
	for (uint i = 0; i < 10; i++)
		coldMachine.chest.shurikenLauncherAnim[DAMAGE_ANIM].PushBack({ 806,333,48,28 }); 
	coldMachine.chest.shurikenLauncherAnim[DAMAGE_ANIM].PushBack({ 462,333,48,28 }); // max opened // 84 frames NORMAL SPRITE,DAMAGE NOT PRESENT

	coldMachine.chest.shurikenLauncherAnim[DAMAGE_ANIM].PushBack({ 754,333,48,28 });
	coldMachine.chest.shurikenLauncherAnim[DAMAGE_ANIM].PushBack({ 699,333,48,28 }); // max closed
	coldMachine.chest.shurikenLauncherAnim[DAMAGE_ANIM].speed = 0.125f;
	coldMachine.chest.shurikenLauncherAnim[DAMAGE_ANIM].repeat = false;
	coldMachine.chest.shurikenLauncherAnim[DAMAGE_ANIM].finish = true; // fake condition

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
	coldMachine.legs.kneeAnim[NORMAL_ANIM].PushBack({ 235,160,32,32 }); //1// max opened
	coldMachine.legs.kneeAnim[NORMAL_ANIM].PushBack({ 235,160,32,32 }); //2// max opened
	coldMachine.legs.kneeAnim[NORMAL_ANIM].PushBack({ 235,160,32,32 }); //3// max opened
	coldMachine.legs.kneeAnim[NORMAL_ANIM].PushBack({ 235,160,32,32 }); //4// max opened
	coldMachine.legs.kneeAnim[NORMAL_ANIM].PushBack({ 197,160,32,32 });
	coldMachine.legs.kneeAnim[NORMAL_ANIM].PushBack({ 160,160,32,32 });
	coldMachine.legs.kneeAnim[NORMAL_ANIM].speed = 0.125f;
	coldMachine.legs.kneeAnim[NORMAL_ANIM].repeat = false;

	coldMachine.legs.kneeAnim[DAMAGE_ANIM].PushBack({ 519,160,32,32 }); // max closed
	coldMachine.legs.kneeAnim[DAMAGE_ANIM].PushBack({ 556,160,32,32 });
	coldMachine.legs.kneeAnim[DAMAGE_ANIM].PushBack({ 593,160,32,32 }); 
	coldMachine.legs.kneeAnim[DAMAGE_ANIM].PushBack({ 631,160,32,32 }); //1// max opened
	coldMachine.legs.kneeAnim[DAMAGE_ANIM].PushBack({ 631,160,32,32 });	//2// and make the max opened lasts a little more
	coldMachine.legs.kneeAnim[DAMAGE_ANIM].PushBack({ 631,160,32,32 }); //3
	coldMachine.legs.kneeAnim[DAMAGE_ANIM].PushBack({ 631,160,32,32 }); //4
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
	coldMachine.legs.armShootgunAnim[NORMAL_ANIM].PushBack({ 0,0,91,45 }); // shooting pos, lasts 24 frames
	coldMachine.legs.armShootgunAnim[NORMAL_ANIM].PushBack({ 0,0,91,45 }); // shooting pos,
	coldMachine.legs.armShootgunAnim[NORMAL_ANIM].PushBack({ 0,0,91,45 }); // shooting pos,
	coldMachine.legs.armShootgunAnim[NORMAL_ANIM].PushBack({ 0,0,91,45 }); // shooting pos,

	coldMachine.legs.armShootgunAnim[NORMAL_ANIM].PushBack({ 91,0,81,63 });
	coldMachine.legs.armShootgunAnim[NORMAL_ANIM].PushBack({ 172,0,57,99 }); // idle, pointing down, off
	coldMachine.legs.armShootgunAnim[NORMAL_ANIM].speed = 0.125f;
	coldMachine.legs.armShootgunAnim[NORMAL_ANIM].repeat = false;

	coldMachine.legs.armShootgunAnim[DAMAGE_ANIM].PushBack({ 568,0,57,99 }); // idle, bad sprite
	coldMachine.legs.armShootgunAnim[DAMAGE_ANIM].PushBack({ 487,0,81,63 });
	coldMachine.legs.armShootgunAnim[DAMAGE_ANIM].PushBack({ 396,0,91,45 }); // shooting pos
	coldMachine.legs.armShootgunAnim[DAMAGE_ANIM].PushBack({ 396,0,91,45 }); // shooting pos
	coldMachine.legs.armShootgunAnim[DAMAGE_ANIM].PushBack({ 396,0,91,45 }); // shooting pos
	coldMachine.legs.armShootgunAnim[DAMAGE_ANIM].PushBack({ 396,0,91,45 }); // shooting pos

	coldMachine.legs.armShootgunAnim[DAMAGE_ANIM].PushBack({ 487,0,81,63 });
	coldMachine.legs.armShootgunAnim[DAMAGE_ANIM].PushBack({ 568,0,57,99 }); // idle, bad sprite
	coldMachine.legs.armShootgunAnim[DAMAGE_ANIM].speed = 0.125f;
	coldMachine.legs.armShootgunAnim[DAMAGE_ANIM].repeat = false;

	// BOMBARDIER animation
	coldMachine.bombardier.anim.PushBack({ 988,0,36,24 }); // start //drop bomb
	coldMachine.bombardier.anim.PushBack({ 800,26,63,24 }); // more fire, still not really open the bombs gate
	coldMachine.bombardier.anim.PushBack({ 924,0,63,22 });
	coldMachine.bombardier.anim.PushBack({ 800,0,64,21 });
	coldMachine.bombardier.anim.PushBack({ 865,0,58,22 });
	coldMachine.bombardier.anim.PushBack({ 800,0,64,21 });
	coldMachine.bombardier.anim.PushBack({ 924,0,63,22 }); // end, then drop another bomb/restart cycle
	coldMachine.bombardier.anim.speed = 0.25f;
	coldMachine.bombardier.anim.repeat = false;
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

	// Fase 1 to fase 2 path animations
	coldMachine.f1Tof2Path.foot.PushBack({ -0.5, 1 }, 20);
	coldMachine.f1Tof2Path.lowerLeg.PushBack( {-0.5, 1}, 20);
	coldMachine.f1Tof2Path.knee.PushBack({ -0.5, 1 }, 20);
	coldMachine.f1Tof2Path.upperLeg.PushBack({ -0.5, 1 }, 20);
	coldMachine.f1Tof2Path.hip.PushBack({ -0.5, 1 }, 20);
	coldMachine.f1Tof2Path.chest.PushBack({ 0, 1 }, 20);


	
	
	//original.y = 60;
	//original.x = position.x;

	// add colliders
	int k = 0;
	collider = coldMachine.chestCollider = extraColliders[k++] = App->collision->AddCollider({ 0,0,110,130}, COLLIDER_ENEMY, (Module*)App->enemies);
	coldMachine.legCollider = extraColliders[k++] = App->collision->AddCollider({ 0,0,60,180 }, COLLIDER_ENEMY, (Module*)App->enemies);
	coldMachine.upEyeCollider = extraColliders[k++] = App->collision->AddCollider({ 0,0,20,32 }, COLLIDER_ENEMY, (Module*)App->enemies);
	coldMachine.kneeCollider = extraColliders[k++] = App->collision->AddCollider({ 0,0,39,40 }, COLLIDER_ENEMY, (Module*)App->enemies);
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
	case bossState::F1TOF2:
		F1ToF2Transition();
		position.y = fposition.y;
		break;
	case bossState::FASE2:
		fase2MovementLogic();
		fase2AttackManager();
		if (coldMachine.legs.throwMissiles && !coldMachine.leftCorner && !coldMachine.move) 
			missilesLogic(); // trick
		else
		{
			if (coldMachine.legs.throwMissiles)
			{
				coldMachine.legs.throwMissiles = false;
				coldMachine.legs.missilesWaveCount = 0;
				coldMachine.legs.missilesCount = 0;
			}
		}
		//position.y = fposition.y;
		break;
	case bossState::TOEXPLODE:
		toExplode();
		break;
	}

	position.x += 1; // GENERAL POSITION

	// update general fase timer
	coldMachine.now_cycle_time = SDL_GetTicks() - coldMachine.start_cycle_time;

	// check fase timer
	if (coldMachine.state == bossState::FASE1)
	{
		if (coldMachine.now_cycle_time > coldMachine.fase1_total_time || coldMachine.destroyedFase1)
		{
			coldMachine.state = bossState::F1TOF2;
			// update original positions for path animation
			updateOriginalPositions();
			// instantiate particles
			addBossParticles();
			// deactivate visible hip
			coldMachine.legs.destroyedHip = true;
			coldMachine.move = true;
			// resets missile function data
			coldMachine.legs.missilesWaveCount = 0;
			coldMachine.legs.missilesCount = 0;
			coldMachine.legs.shootedMissile = false;
			// shutdown missiles throwing
			coldMachine.legs.throwMissiles = false;
			// resets timers
			coldMachine.legs.start_missiles_time = SDL_GetTicks();
			coldMachine.legs.start_launch_time = SDL_GetTicks();

			// delete leg relative colliders
			if (coldMachine.legCollider != nullptr)
			{
				coldMachine.legCollider->to_delete = true;
				coldMachine.legCollider = nullptr;
			}
			if (coldMachine.kneeCollider != nullptr)
			{
				coldMachine.kneeCollider->to_delete = true;
				coldMachine.kneeCollider = nullptr;
			}
			
		}
	}

	// check fase2 timer
	if (coldMachine.state == bossState::FASE2)
	{
		if (coldMachine.now_cycle_time > coldMachine.fase2_total_time || coldMachine.destroyedFase2)
		{
			coldMachine.state = bossState::TOEXPLODE;
			// update original positions for path animation
			updateOriginalPositions();
			// instantiate particles
			addBossParticles();
			// update timer to auto destroy enemy
			coldMachine.start_exploding_time = SDL_GetTicks();

		}
	}

	// updates colliders position
	if (coldMachine.chestCollider != nullptr)
		coldMachine.chestCollider->SetPos(position.x + coldMachine.chest.chestPiece.position.x + 36, 
			position.y + coldMachine.chest.chestPiece.position.y + 20);

	if (coldMachine.legCollider != nullptr)
		coldMachine.legCollider->SetPos(position.x + coldMachine.legs.upperLegPiece.position.x + 26, 
			position.y + coldMachine.legs.upperLegPiece.position.y + 10);

	if (coldMachine.kneeCollider != nullptr)
		coldMachine.kneeCollider->SetPos(position.x + coldMachine.legs.kneePiece.position.x + 5,
			position.y + coldMachine.legs.kneePiece.position.y + 30);
	

	if (coldMachine.upEyeCollider != nullptr)
		coldMachine.upEyeCollider->SetPos(position.x + coldMachine.chest.chestPiece.position.x + 16,
			position.y + coldMachine.chest.chestPiece.position.y + 10);
	

}

void EnemyColdMachine::OnCollision(Collider* c1, Collider* c2)
{
	if (c1->type != COLLIDER_WALL)
	{
		//LOG("Collision");

		//only up eye and knee eye can receive damage, but only when its frames are more than 1 (open or opening animation state)
		if (c2 == coldMachine.kneeCollider)
		{
			if ((int)coldMachine.legs.kneeAnim[coldMachine.current_sprite_type].current_frame > 0)
			{
				LOG("Knee Collision");
				if (readyToRumble && c1->type == COLLIDER_UNIT) // collisions logic for unit orbit
				{
					coldMachine.start_damage_time = SDL_GetTicks();
					coldMachine.legs.life -= c1->damage;
					LOG("KNEE LIFE: %d", coldMachine.legs.life);
				}
				else if (c1->type != COLLIDER_UNIT)
				{
					coldMachine.start_damage_time = SDL_GetTicks();
					coldMachine.legs.life -= c1->damage;
				}
				
				if (coldMachine.legs.life <= 0)
				{
					
					coldMachine.destroyedFase1 = true;
					
				}
					
			}

		}
		if (c2 == coldMachine.upEyeCollider)
		{
			if ((int)coldMachine.chest.eyeAnim[coldMachine.current_sprite_type].current_frame > 0)
			{
				LOG("Eye Collision");
				if (readyToRumble && c1->type == COLLIDER_UNIT) // collisions logic for unit orbit
				{
					coldMachine.start_damage_time = SDL_GetTicks();
					coldMachine.chest.life -= c1->damage;
					LOG("EYE LIFE: %d", coldMachine.chest.life);
				}
				else if (c1->type != COLLIDER_UNIT)
				{
					coldMachine.start_damage_time = SDL_GetTicks();
					coldMachine.chest.life -= c1->damage;
				}

				if (coldMachine.chest.life <= 0)
				{

					coldMachine.destroyedFase1 = true;

				}
				
			}

		}

	}
		

}

const Collider* EnemyColdMachine::GetCollider() const
{
	return extraColliders[collisionColliderIndex];
}

void EnemyColdMachine::fase2AttackManager()
{

	// shurikens attack logic

	// checks shuriken timer, !SHURIKEN CONDITION HAPPENS when ColdEnemy its ONLY on left corner!
	if (coldMachine.leftCorner) //&& coldMachine.moveToLeft) //while on left corner
	{
		coldMachine.chest.now_shuriken_time = SDL_GetTicks() - coldMachine.chest.start_shuriken_time;
		if (coldMachine.chest.now_shuriken_time > coldMachine.chest.shuriken_waves_time && !coldMachine.chest.throwShuriken)
		{
			LOG("Left corner reached and countdown is over: WAVE of shuriken");
			// start shuriken timer and activate shuriken mode
			coldMachine.chest.start_shuriken_time = SDL_GetTicks();
			coldMachine.chest.throwShuriken = true;
			// resets animation data
			coldMachine.chest.shurikenLauncherAnim[coldMachine.current_sprite_type].current_frame = 0;
			coldMachine.chest.shurikenLauncherAnim[coldMachine.current_sprite_type].finish = false;
		}
		// check shuriken delay between shurikens
		if (coldMachine.chest.throwShuriken)
		{
			if (coldMachine.chest.now_shuriken_time > coldMachine.chest.shuriken_cadenece_time)
			{
				// resets timer
				coldMachine.chest.start_shuriken_time = SDL_GetTicks();
				// instantiate next shuriken
				coldMachine.chest.numShurikens++;
				LOG("SHURIKEN %d", coldMachine.chest.numShurikens);
				App->enemies->AddEnemy(SHURIKEN, position.x + coldMachine.chest.chestPiece.position.x + 100, 
					position.y + coldMachine.chest.chestPiece.position.y - 6, NONE);

				//PLAY SFX
				App->audio->ControlAudio("shuriken", SFX, PLAY);

				if (coldMachine.chest.numShurikens > 2) // max 3 shurikens per wave
				{
					coldMachine.chest.start_shuriken_time = SDL_GetTicks();
					coldMachine.chest.throwShuriken = false;
					coldMachine.chest.numShurikens = 0;
				}
			}
		}

	}

	if (!coldMachine.leftCorner && !coldMachine.move)
	{
		if (!coldMachine.chest.throwGlassCannon)
		{
			// update start time for glass cannon
			coldMachine.chest.start_glass_cannon_time = SDL_GetTicks();
			// update condition
			coldMachine.chest.throwGlassCannon = true;

		}
		else
		{
			coldMachine.chest.now_glass_cannon_time = SDL_GetTicks() - coldMachine.chest.start_glass_cannon_time;
			if (coldMachine.chest.now_glass_cannon_time > coldMachine.chest.time_waiting_for_glass && !coldMachine.chest.shootedGlass)
			{
				LOG("Opening GLASS CANNON gate");
				coldMachine.chest.shootedGlass = true;
				//PLAY SFX
				App->audio->ControlAudio("glassLaser", SFX, PLAY);
			}
			// checks animation data to instantiate the shoot on correct frame
			if ((int)coldMachine.chest.chestCannonAnim[coldMachine.current_sprite_type].current_frame == 3 && 
				!coldMachine.chest.instantiatedGlass)
			{
				LOG("INSTANTIATING GLASS");
				coldMachine.chest.instantiatedGlass = true;
				// instantiate particles
				// glass shot particle
				App->particles->AddParticle(App->enemies->glassShoot, position.x + coldMachine.chest.chestPiece.position.x,
					                                                  position.y + coldMachine.chest.chestPiece.position.y + 120,
					COLLIDER_ENEMY_SHOT, {-2,0});
				// glass shot effect
				App->particles->AddParticle(App->enemies->glassShootEffect, position.x + coldMachine.chest.chestPiece.position.x - 25,
					position.y + coldMachine.chest.chestPiece.position.y + 114,
					COLLIDER_NONE, { scrollSpeed,0 });
				// glass rotary trails upwards static
				App->particles->AddParticle(App->enemies->glassRotary, position.x + coldMachine.chest.chestPiece.position.x - 10,
					position.y + coldMachine.chest.chestPiece.position.y + 120,
					COLLIDER_NONE, { scrollSpeed,0 }, 50);
				App->particles->AddParticle(App->enemies->glassRotary, position.x + coldMachine.chest.chestPiece.position.x - 45,
					position.y + coldMachine.chest.chestPiece.position.y + 120,
					COLLIDER_NONE, { scrollSpeed,0 }, 250);
				App->particles->AddParticle(App->enemies->glassRotary, position.x + coldMachine.chest.chestPiece.position.x - 80,
					position.y + coldMachine.chest.chestPiece.position.y + 120,
					COLLIDER_NONE, { scrollSpeed,0 }, 450);
				App->particles->AddParticle(App->enemies->glassRotary, position.x + coldMachine.chest.chestPiece.position.x - 115,
					position.y + coldMachine.chest.chestPiece.position.y + 120,
					COLLIDER_NONE, { scrollSpeed,0 }, 850);
				App->particles->AddParticle(App->enemies->glassRotary, position.x + coldMachine.chest.chestPiece.position.x - 150,
					position.y + coldMachine.chest.chestPiece.position.y + 120,
					COLLIDER_NONE, { scrollSpeed,0 }, 1050);


			}
		}
	}
	else
	{
		// resets condition
		if (coldMachine.chest.instantiatedGlass)
		{
			coldMachine.chest.throwGlassCannon = false;
			coldMachine.chest.shootedGlass = false;
			coldMachine.chest.instantiatedGlass = false;
			// resets animation data
			coldMachine.chest.chestCannonAnim[coldMachine.current_sprite_type].current_frame = 0;
			coldMachine.chest.chestCannonAnim[coldMachine.current_sprite_type].finish = false;
		}
	}

	



}

void EnemyColdMachine::toExplode()
{
	if (going_up)
	{
		if (wave > 1.0f)
			going_up = false;
		else
			wave += 0.07f;
	}
	else
	{
		if (wave < -1.0f)
			going_up = true;
		else
			wave -= 0.07f;
	}

	coldMachine.chest.chestPiece.position.y = original.chest.y + int(8.0f * sinf(wave));

	coldMachine.now_exploding_time = SDL_GetTicks() - coldMachine.start_exploding_time;
	if (coldMachine.now_exploding_time > coldMachine.time_exploding)
	{
		killMe = true;
	}

}

void EnemyColdMachine::fase2MovementLogic()
{
	if (going_up)
	{
		if (wave > 1.0f)
			going_up = false;
		else
			wave += 0.07f;
	}
	else
	{
		if (wave < -1.0f)
			going_up = true;
		else
			wave -= 0.07f;
	}

	coldMachine.chest.chestPiece.position.y =  original.chest.y + int(8.0f * sinf(wave));
	
	if (coldMachine.move)
	{
		if (coldMachine.moveToLeft)
		{
			if (coldMachine.chest.chestPiece.position.x > -208)
			{
				coldMachine.fposition.x -= 0.5f;
				coldMachine.chest.chestPiece.position.x = coldMachine.fposition.x;
			}
			else
			{
				// stop mov
				coldMachine.move = false;
				// arrives at corner functionality
				coldMachine.leftCorner = true;
			}
		}
		else
		{
			if (coldMachine.chest.chestPiece.position.x <= 0)
			{
				coldMachine.fposition.x += 0.5f;
				coldMachine.chest.chestPiece.position.x = coldMachine.fposition.x;
			}
			else
			{
				coldMachine.move = false;
				coldMachine.leftCorner = false;
			}
		}

		//PLAY SFX
		App->audio->ControlAudio("bossMove", SFX, PLAY);
	
		
	}
	else
	{
		if (coldMachine.moveToLeft && coldMachine.leftCorner)
		{
			// next move will be to right
			coldMachine.moveToLeft = false;
			// arrives at left corner attack logic
			coldMachine.leftCorner = true;
			// start left corner timer
			coldMachine.start_corner_time = SDL_GetTicks();
		}
		if (!coldMachine.moveToLeft && !coldMachine.leftCorner)
		{
			// next move will be to right
			coldMachine.moveToLeft = true;
			// arrives at left corner attack logic
			coldMachine.leftCorner = false;
			// start left corner timer
			coldMachine.start_corner_time = SDL_GetTicks();
		}
		
		// update current left corner time
		coldMachine.now_corner_time = SDL_GetTicks() - coldMachine.start_corner_time;
		if (coldMachine.now_corner_time > coldMachine.total_corner_time)
		{
			if (!coldMachine.move)
				coldMachine.move = true;

			if (coldMachine.leftCorner) coldMachine.leftCorner = false; // only shurikens fase
			
		}
	}
	
}

void EnemyColdMachine::updateOriginalPositions()
{

	original.foot = coldMachine.legs.footPiece.position;
	original.lowerLeg = coldMachine.legs.lowerLegPiece.position;
	original.knee = coldMachine.legs.kneePiece.position;
	original.upperLeg = coldMachine.legs.upperLegPiece.position;
	original.hip = coldMachine.legs.hipPiece.position;
	original.chest = coldMachine.chest.chestPiece.position;
	
}

void EnemyColdMachine::F1ToF2Transition()
{

	// update path animations
	coldMachine.legs.footPiece.position = original.foot + coldMachine.f1Tof2Path.foot.GetCurrentSpeed();
	coldMachine.legs.lowerLegPiece.position = original.lowerLeg + coldMachine.f1Tof2Path.lowerLeg.GetCurrentSpeed();
	coldMachine.legs.kneePiece.position = original.knee + coldMachine.f1Tof2Path.knee.GetCurrentSpeed();
	coldMachine.legs.upperLegPiece.position = original.upperLeg + coldMachine.f1Tof2Path.upperLeg.GetCurrentSpeed();
	coldMachine.legs.hipPiece.position = original.hip + coldMachine.f1Tof2Path.hip.GetCurrentSpeed();
	coldMachine.chest.chestPiece.position = original.chest + coldMachine.f1Tof2Path.chest.GetCurrentSpeed();

	// updates general positions

	// check chest position to switch to fase2
	if (coldMachine.chest.chestPiece.position.y > 180)
	{
		coldMachine.state = bossState::FASE2;
		// "destroy" bottom part
		coldMachine.legs.destroyed = true;
		// start new fase timer
		coldMachine.start_cycle_time = SDL_GetTicks();
		// start eye blink timer
		coldMachine.chest.start_eye_time = SDL_GetTicks();

		// store chest position y to sinusoidal fixed y
		//position.y = coldMachine.chest.chestPiece.position.y - 237;
		original.chest.y = coldMachine.chest.chestPiece.position.y - 7;// + 20;//position.y;//coldMachine.chest.chestPiece.position.y;
		//original.chest.x = position.x + coldMachine.chest.chestPiece.position.x;

		coldMachine.fposition.x = original.chest.x;
		coldMachine.fposition.y = original.chest.y;

		//position.y = original.chest.y;

	}

		/*// start attack timers
		coldMachine.legs.start_missiles_time = SDL_GetTicks();
		coldMachine.legs.start_kneeBeam_time = SDL_GetTicks();
		coldMachine.legs.start_armShooting_time = SDL_GetTicks();
		// start countdown timer Fase1
		coldMachine.start_cycle_time = SDL_GetTicks();*/

}

void EnemyColdMachine::kneeBeamLogic()
{
	// instantiate laser beam
	if (!coldMachine.legs.shootedLaserBeam)
	{
		// instantiate laser beam
		App->particles->AddParticle(App->enemies->coldMachineKneeLaser, position.x + coldMachine.legs.kneePiece.position.x - 10,
			position.y + 40 + coldMachine.legs.kneePiece.position.y, COLLIDER_ENEMY_SHOT, { -1,0 }, 0);
		// instantiate shoot explosion effect
		App->particles->AddParticle(App->enemies->coldMachineKneeLaserShotEffect, position.x + coldMachine.legs.kneePiece.position.x + 4,
			position.y + 45 + coldMachine.legs.kneePiece.position.y, COLLIDER_NONE, { scrollSpeed,0 }, 0);

		// update condition
		coldMachine.legs.shootedLaserBeam = true;

		//PLAY SFX
		App->audio->ControlAudio("kneeLaser", SFX, PLAY);
	}

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
		//PLAY SFX
		App->audio->ControlAudio("bossRocket", SFX, PLAY);
		// instantiate missile
		// FASE 1 logic
		if (coldMachine.state == bossState::FASE1)
		{
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
		}
		else
		{
			App->enemies->AddEnemy(HOMINGMISSILE, position.x + coldMachine.chest.chestPiece.position.x +
				coldMachine.chest.missileCanyonsPos[coldMachine.legs.missilesCount - 1].x,
				position.y + coldMachine.chest.chestPiece.position.y +
				coldMachine.chest.missileCanyonsPos[coldMachine.legs.missilesCount - 1].y, NONE);
			// instantiate missile flash
			App->particles->AddParticle(App->enemies->coldMachineLegMissileFlash, position.x + coldMachine.chest.chestPiece.position.x +
				coldMachine.chest.missileCanyonsPos[coldMachine.legs.missilesCount - 1].x,
				position.y - 3 + coldMachine.chest.chestPiece.position.y +
				coldMachine.chest.missileCanyonsPos[coldMachine.legs.missilesCount - 1].y,
				COLLIDER_NONE, { scrollSpeed,0 }, 0);
		}


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
		// start countdown timer Fase1
		coldMachine.start_cycle_time = SDL_GetTicks();

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
		updateOriginalPositions();
		// instantiate particles
		addBossParticles();
		// start countdown timer
		coldMachine.start_cycle_time = SDL_GetTicks();

		//PLAY SFX
		App->audio->ControlAudio("bossLanding", SFX, PLAY);
	}

}

void EnemyColdMachine::Draw()
{

	// update all cycle attack timers
	coldMachine.legs.now_missiles_time = SDL_GetTicks() - coldMachine.legs.start_missiles_time;
	coldMachine.legs.now_kneeBeam_time = SDL_GetTicks() - coldMachine.legs.start_kneeBeam_time;
	coldMachine.legs.now_armShooting_time = SDL_GetTicks() - coldMachine.legs.start_armShooting_time;

	// damage timer
	coldMachine.now_damage_time = SDL_GetTicks() - coldMachine.start_damage_time;
	if (coldMachine.now_damage_time > coldMachine.total_damage_time)
	{
		receiveDamage = false;
		coldMachine.current_sprite_type = swapAnimType::NORMAL_ANIM;
	}
	else
	{
		coldMachine.current_sprite_type = swapAnimType::DAMAGE_ANIM;
	}

	// fase 2 timers
	coldMachine.chest.now_eye_time = SDL_GetTicks() - coldMachine.chest.start_eye_time;

	// assign if we receive damage the desireds damage sprites
	//coldMachine.current_sprite_type = swapAnimType::NORMAL_ANIM; //DAMAGE_ANIM;

	// DRAW full chest static pieces --------
	// static upper part chest
	App->render->Blit(enemyTex, position.x + coldMachine.chest.chestPiece.position.x, 
		position.y + coldMachine.chest.chestPiece.position.y, &coldMachine.chest.chestPiece.rect[coldMachine.current_sprite_type]);

	// parts down here pertain only to fase 1 legs -----------------------------------------------------------------------------------------
	if (!coldMachine.legs.destroyed)
	{
		// static hip - destroys before the rest
		if (!coldMachine.legs.destroyedHip)
		{
			App->render->Blit(enemyTex, position.x + coldMachine.legs.hipPiece.position.x,
				position.y + coldMachine.legs.hipPiece.position.y, &coldMachine.legs.hipPiece.rect[coldMachine.current_sprite_type]);
		}
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

		App->render->Blit(enemyTex, position.x + coldMachine.legs.kneePiece.position.x,
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

		if (coldMachine.bombardier.throwBombs)
		{
			// instantiate morter BOMB
			App->particles->AddParticle(App->enemies->bombardierBomb, coldMachine.bombardier.position.x,
				coldMachine.bombardier.position.y + 14, COLLIDER_ENEMY_SHOT, { 0,2 }, 0);
			

			coldMachine.bombardier.throwBombs = false;
		}

		if (coldMachine.bombardier.instantiate)
		{

			App->render->Blit(enemyTex, coldMachine.bombardier.position.x, coldMachine.bombardier.position.y,
				&coldMachine.bombardier.anim.GetCurrentFrame());
			// updates position
			coldMachine.bombardier.position.x -= 1;

			if (coldMachine.bombardier.anim.finish)
			{
				// restart animation data
				// throw next bomb
				coldMachine.bombardier.throwBombs = true;
				// resets animation data
				coldMachine.bombardier.anim.finish = false;
				coldMachine.bombardier.anim.current_frame = 0;
			}

		}

		coldMachine.legs.armShotgunRect = returnRect(coldMachine.legs.armShootgunAnim);

		App->render->Blit(enemyTex, position.x + coldMachine.legs.hipPiece.position.x +
			coldMachine.legs.shotGunPivots[(int)coldMachine.legs.armShootgunAnim->current_frame].x - coldMachine.legs.armShotgunRect.w,
			position.y + coldMachine.legs.hipPiece.position.y + coldMachine.legs.shotGunPivots[(int)coldMachine.legs.armShootgunAnim->current_frame].y,
			&coldMachine.legs.armShotgunRect);

	// ----------------------------------------------------------------------------------------------------------------------------------------
	}
	// UPPER FASE ANIMATIONS, chest
	// chest cannon
	App->render->Blit(enemyTex, position.x + coldMachine.chest.chestPiece.position.x - 5,
		position.y + coldMachine.chest.chestPiece.position.y + 105 , &returnRect(coldMachine.chest.chestCannonAnim));
	
	// dumb eye
	App->render->Blit(enemyTex, position.x + coldMachine.chest.chestPiece.position.x + 11,
		position.y + coldMachine.chest.chestPiece.position.y + 9, &returnRect(coldMachine.chest.eyeAnim));

	// shurikens launcher
	App->render->Blit(enemyTex, position.x + coldMachine.chest.chestPiece.position.x + 91,
		position.y + coldMachine.chest.chestPiece.position.y - 3, &returnRect(coldMachine.chest.shurikenLauncherAnim));

	// chest missile launcher
	App->render->Blit(enemyTex, position.x + coldMachine.chest.chestPiece.position.x + 43,
		position.y + coldMachine.chest.chestPiece.position.y + 57, &returnRect(coldMachine.chest.shoulderLauncherAnim));


}

SDL_Rect& EnemyColdMachine::returnRect(Animation* anim)
{

	// update current frame
	anim[coldMachine.current_sprite_type].current_frame = anim->current_frame;

	// general stop animations
	if (coldMachine.state != bossState::FASE1 && coldMachine.state != bossState::FASE2)
	{

		if (coldMachine.stopAnimations)
		{
			// set current frame to 0, protection
			if((int)anim[coldMachine.current_sprite_type].current_frame > 0)
				anim[coldMachine.current_sprite_type].current_frame = 0;
			return anim[coldMachine.current_sprite_type].frames[0];
		}
		else
			return anim[coldMachine.current_sprite_type].GetCurrentFrame();
	}

	// weapons cycle return fase1, legs
	// missiles
	if (coldMachine.state == bossState::FASE1 && anim == coldMachine.legs.missileLauncherAnim || 
		coldMachine.state == bossState::FASE2 && anim == coldMachine.chest.shoulderLauncherAnim)
	{
		// missiles animation and activator logic -----------------------------------------------

		if (coldMachine.legs.now_missiles_time > coldMachine.legs.missiles_cadence_time && !coldMachine.move && !coldMachine.leftCorner) //&& anim == coldMachine.legs.missileLauncherAnim)
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
		{
			return anim[coldMachine.current_sprite_type].frames[0];
		}

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
		{
			if (anim[coldMachine.current_sprite_type].current_frame != 0) anim[coldMachine.current_sprite_type].current_frame = 0;
			return anim[coldMachine.current_sprite_type].frames[0];
		}
	}

	// ARM SHOOTING, fase1
	if (coldMachine.state == bossState::FASE1 && anim == coldMachine.legs.armShootgunAnim)
	{
		if (coldMachine.legs.now_armShooting_time > coldMachine.legs.armShooting_cadence_time)
		{
			if (anim[coldMachine.current_sprite_type].finish)
			{
				// resets timer
				coldMachine.legs.start_armShooting_time = SDL_GetTicks();
				// resets animation data
				anim[coldMachine.current_sprite_type].finish = false;
				anim[coldMachine.current_sprite_type].current_frame = 0;
				// prepares next bombardier instantiation
				coldMachine.legs.throwArmShoot = false;
				// returns correct frame
				return anim[coldMachine.current_sprite_type].frames[0];
			}
			else
			{
				if (anim[coldMachine.current_sprite_type].current_frame > 2 && !coldMachine.legs.throwArmShoot)
				{
					/*// throw bombardier
					App->enemies->AddEnemy(COLDMACHINEBOMBARDIER, position.x + coldMachine.legs.hipPiece.position.x - 10, 
						position.y + coldMachine.legs.hipPiece.position.y + 10, NONE);*/

					// instantiate smoke shoot particle
					App->particles->AddParticle(App->enemies->coldMachineArmShootSmoke, position.x + coldMachine.legs.hipPiece.position.x - 33,
						position.y + coldMachine.legs.hipPiece.position.y + 14, COLLIDER_NONE, {scrollSpeed,0},0);

					// updates condition
					coldMachine.legs.throwArmShoot = true;
					coldMachine.bombardier.throwBombs = true;
					coldMachine.bombardier.instantiate = true;
					// assigns correct internal position to bombardier position
					coldMachine.bombardier.position.x = position.x + coldMachine.legs.hipPiece.position.x - 10;
					coldMachine.bombardier.position.y = position.y + coldMachine.legs.hipPiece.position.y + 18;
					// resets bombardier animation data
					coldMachine.bombardier.anim.finish = false;
					coldMachine.bombardier.anim.current_frame = 0;
					//PLAY SFX
					App->audio->ControlAudio("armShoot", SFX, PLAY);
				}

				return anim[coldMachine.current_sprite_type].GetCurrentFrame();
			}
		}
		else
			return anim[coldMachine.current_sprite_type].frames[0];
	}

	// fase 2 return animation logic
	
		// chest cannon
		if (coldMachine.state == bossState::FASE2 && anim == coldMachine.chest.chestCannonAnim)
		{
			if (coldMachine.chest.shootedGlass)
			{
				return anim[coldMachine.current_sprite_type].GetCurrentFrame();
			}
			else
			{
				return anim[coldMachine.current_sprite_type].frames[0];
			}
		}

		// eye anim

		if (coldMachine.state == bossState::FASE2 && anim == coldMachine.chest.eyeAnim)
		{
			if (coldMachine.chest.now_eye_time > coldMachine.chest.time_between_eye)
			{
				if (anim == coldMachine.chest.eyeAnim)
				{

					if (anim[coldMachine.current_sprite_type].finish)
					{
						// resets animation data
						anim[coldMachine.current_sprite_type].current_frame = 0;
						anim[coldMachine.current_sprite_type].finish = false;
						// start timer for next animation loop
						coldMachine.chest.start_eye_time = SDL_GetTicks();

						return anim[coldMachine.current_sprite_type].frames[0];
					}
					return anim[coldMachine.current_sprite_type].GetCurrentFrame();
				}
			}
			else
			{
				if (anim[coldMachine.current_sprite_type].current_frame != 0) anim[coldMachine.current_sprite_type].current_frame = 0;
				return anim[coldMachine.current_sprite_type].frames[0];
			}
		}

		// blue shurikens

		if (coldMachine.state == bossState::FASE2 && anim == coldMachine.chest.shurikenLauncherAnim)
		{
			if (coldMachine.chest.throwShuriken) //|| coldMachine.leftCorner)
			{
				return anim[coldMachine.current_sprite_type].GetCurrentFrame();
			}
			else
			{
				if (!anim[coldMachine.current_sprite_type].finish) // if the animation still not finish, finish it
					return anim[coldMachine.current_sprite_type].GetCurrentFrame();
				else
					return anim[coldMachine.current_sprite_type].frames[0];
			}
		}

		// shoulder missile launcher

		/*if (coldMachine.state == bossState::FASE2 && anim == coldMachine.chest.shoulderLauncherAnim)
		{
			return anim[coldMachine.current_sprite_type].GetCurrentFrame();
		}*/




}

void EnemyColdMachine::addBossParticles()
{
	if (coldMachine.state == bossState::FIRSTCONTACT)
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

	if (coldMachine.state == bossState::F1TOF2) // explosion festival
	{
		//int i = 0;
		// first wave
		for (uint i = 0; i < 6; ++i)
		{
			App->particles->AddParticle(App->particles->explosion, position.x + coldMachine.chest.chestPiece.position.x +
				coldMachine.f1Tof1ParticlePoints[i].x,//50,
				position.y + coldMachine.chest.chestPiece.position.y + coldMachine.f1Tof1ParticlePoints[i].y,
				COLLIDER_NONE, { scrollSpeed ,0 }, coldMachine.f1Tof1ParticlesDelay[i]);
		}
		
		for (uint i = 0; i < 6; ++i)
		{
			App->particles->AddParticle(App->particles->explosion, position.x + coldMachine.chest.chestPiece.position.x +
				coldMachine.f1Tof1ParticlePoints[i].x + 50,
				position.y + 110 + coldMachine.chest.chestPiece.position.y + coldMachine.f1Tof1ParticlePoints[i].y,
				COLLIDER_NONE, { scrollSpeed ,0 }, coldMachine.f1Tof1ParticlesDelay[i]);
		}
		
		// second wave
		for (uint i = 0; i < 6; ++i)
		{
			App->particles->AddParticle(App->particles->explosion, position.x + coldMachine.chest.chestPiece.position.x +
				coldMachine.f1Tof1ParticlePoints[i].x + 10,
				position.y - 40 + coldMachine.chest.chestPiece.position.y + coldMachine.f1Tof1ParticlePoints[i].y,
				COLLIDER_NONE, { scrollSpeed ,0 }, coldMachine.f1Tof1ParticlesDelay[i] + 400);
		}
		for (uint i = 0; i < 6; ++i)
		{
			App->particles->AddParticle(App->particles->explosion, position.x + coldMachine.chest.chestPiece.position.x +
				coldMachine.f1Tof1ParticlePoints[i].x + 60,
				position.y + 80 + coldMachine.chest.chestPiece.position.y + coldMachine.f1Tof1ParticlePoints[i].y,
				COLLIDER_NONE, { scrollSpeed ,0 }, coldMachine.f1Tof1ParticlesDelay[i] + 400);
		}

		// third wave
		for (uint i = 0; i < 6; ++i)
		{
			App->particles->AddParticle(App->particles->explosion, position.x + coldMachine.chest.chestPiece.position.x +
				coldMachine.f1Tof1ParticlePoints[i].x + 30,
				position.y - 30 + coldMachine.chest.chestPiece.position.y + coldMachine.f1Tof1ParticlePoints[i].y,
				COLLIDER_NONE, { scrollSpeed ,0 }, coldMachine.f1Tof1ParticlesDelay[i] + 600);
		}
		for (uint i = 0; i < 6; ++i)
		{
			App->particles->AddParticle(App->particles->explosion, position.x + coldMachine.chest.chestPiece.position.x +
				coldMachine.f1Tof1ParticlePoints[i].x + 46,
				position.y + 70 + coldMachine.chest.chestPiece.position.y + coldMachine.f1Tof1ParticlePoints[i].y,
				COLLIDER_NONE, { scrollSpeed ,0 }, coldMachine.f1Tof1ParticlesDelay[i] + 800);
		}
	
		// fourth
		for (uint i = 0; i < 6; ++i)
		{
			App->particles->AddParticle(App->particles->explosion, position.x + coldMachine.chest.chestPiece.position.x +
				coldMachine.f1Tof1ParticlePoints[i].x + 30,
				position.y - 30 + coldMachine.chest.chestPiece.position.y + coldMachine.f1Tof1ParticlePoints[i].y,
				COLLIDER_NONE, { scrollSpeed ,0 }, coldMachine.f1Tof1ParticlesDelay[i] + 900);
		}
		for (uint i = 0; i < 6; ++i)
		{
			App->particles->AddParticle(App->particles->explosion, position.x + coldMachine.chest.chestPiece.position.x +
				coldMachine.f1Tof1ParticlePoints[i].x,
				position.y + 130 + coldMachine.chest.chestPiece.position.y + coldMachine.f1Tof1ParticlePoints[i].y,
				COLLIDER_NONE, { scrollSpeed ,0 }, coldMachine.f1Tof1ParticlesDelay[i] + 1000);
		}
		for (uint i = 0; i < 6; ++i)
		{
			App->particles->AddParticle(App->particles->explosion, position.x + coldMachine.chest.chestPiece.position.x +
				coldMachine.f1Tof1ParticlePoints[i].x + 70,
				position.y + 160 + coldMachine.chest.chestPiece.position.y + coldMachine.f1Tof1ParticlePoints[i].y,
				COLLIDER_NONE, { scrollSpeed ,0 }, coldMachine.f1Tof1ParticlesDelay[i] + 1000);
		}

		// fifth
		for (uint i = 0; i < 6; ++i)
		{
			App->particles->AddParticle(App->particles->explosion, position.x + coldMachine.chest.chestPiece.position.x +
				coldMachine.f1Tof1ParticlePoints[i].x + 10,
				position.y + 50 + coldMachine.chest.chestPiece.position.y + coldMachine.f1Tof1ParticlePoints[i].y,
				COLLIDER_NONE, { scrollSpeed ,0 }, coldMachine.f1Tof1ParticlesDelay[i] + 1200);
		}
		for (uint i = 0; i < 6; ++i)
		{
			App->particles->AddParticle(App->particles->explosion, position.x + coldMachine.chest.chestPiece.position.x +
				coldMachine.f1Tof1ParticlePoints[i].x+ 36,
				position.y + 20 + coldMachine.chest.chestPiece.position.y + coldMachine.f1Tof1ParticlePoints[i].y,
				COLLIDER_NONE, { scrollSpeed ,0 }, coldMachine.f1Tof1ParticlesDelay[i] + 1200);
		}
		// sixth
		for (uint i = 0; i < 6; ++i)
		{
			App->particles->AddParticle(App->particles->explosion, position.x + coldMachine.chest.chestPiece.position.x +
				coldMachine.f1Tof1ParticlePoints[i].x + 30,
				position.y + 63 + coldMachine.chest.chestPiece.position.y + coldMachine.f1Tof1ParticlePoints[i].y,
				COLLIDER_NONE, { scrollSpeed ,0 }, coldMachine.f1Tof1ParticlesDelay[i] + 1550);
		}
		for (uint i = 0; i < 6; ++i)
		{
			App->particles->AddParticle(App->particles->explosion, position.x + coldMachine.chest.chestPiece.position.x +
				coldMachine.f1Tof1ParticlePoints[i].x + 10,
				position.y + 90 + coldMachine.chest.chestPiece.position.y + coldMachine.f1Tof1ParticlePoints[i].y,
				COLLIDER_NONE, { scrollSpeed ,0 }, coldMachine.f1Tof1ParticlesDelay[i] + 1650);
		}
		for (uint i = 0; i < 6; ++i)
		{
			App->particles->AddParticle(App->particles->explosion, position.x + coldMachine.chest.chestPiece.position.x +
				coldMachine.f1Tof1ParticlePoints[i].x  + 60,
				position.y + 75 + coldMachine.chest.chestPiece.position.y + coldMachine.f1Tof1ParticlePoints[i].y,
				COLLIDER_NONE, { scrollSpeed ,0 }, coldMachine.f1Tof1ParticlesDelay[i] + 1750);
		}
		for (uint i = 0; i < 6; ++i)
		{
			App->particles->AddParticle(App->particles->explosion, position.x + coldMachine.chest.chestPiece.position.x +
				coldMachine.f1Tof1ParticlePoints[i].x + 32,
				position.y + 90 + coldMachine.chest.chestPiece.position.y + coldMachine.f1Tof1ParticlePoints[i].y,
				COLLIDER_NONE, { scrollSpeed ,0 }, coldMachine.f1Tof1ParticlesDelay[i] + 1950);
		}
		for (uint i = 0; i < 6; ++i)
		{
			App->particles->AddParticle(App->particles->explosion, position.x + coldMachine.chest.chestPiece.position.x +
				coldMachine.f1Tof1ParticlePoints[i].x + 16,
				position.y + 75 + coldMachine.chest.chestPiece.position.y + coldMachine.f1Tof1ParticlePoints[i].y,
				COLLIDER_NONE, { scrollSpeed ,0 }, coldMachine.f1Tof1ParticlesDelay[i] + 2150);
		}


	}
	// TO explode particles
	if (coldMachine.state == bossState::TOEXPLODE) // festival of destruction
	{
		// first wave
		for (uint i = 0; i < 6; ++i)
		{
			App->particles->AddParticle(App->particles->explosion, position.x + coldMachine.chest.chestPiece.position.x +
				coldMachine.f1Tof1ParticlePoints[i].x + 16 ,//50,
				position.y + coldMachine.chest.chestPiece.position.y + coldMachine.f1Tof1ParticlePoints[i].y - 160,
				COLLIDER_NONE, { scrollSpeed ,0 }, coldMachine.f1Tof1ParticlesDelay[i]);
		}
		for (uint i = 0; i < 6; ++i)
		{
			App->particles->AddParticle(App->particles->explosion, position.x + coldMachine.chest.chestPiece.position.x +
				coldMachine.f1Tof1ParticlePoints[i].x + 50,
				position.y + coldMachine.chest.chestPiece.position.y + coldMachine.f1Tof1ParticlePoints[i].y - 140,
				COLLIDER_NONE, { scrollSpeed ,0 }, coldMachine.f1Tof1ParticlesDelay[i]);
		}
		for (uint i = 0; i < 6; ++i)
		{
			App->particles->AddParticle(App->particles->explosion, position.x + coldMachine.chest.chestPiece.position.x +
				coldMachine.f1Tof1ParticlePoints[i].x, //+ 16,//50,
				position.y + coldMachine.chest.chestPiece.position.y + coldMachine.f1Tof1ParticlePoints[i].y - 110,
				COLLIDER_NONE, { scrollSpeed ,0 }, coldMachine.f1Tof1ParticlesDelay[i]);
		}
		for (uint i = 0; i < 6; ++i)
		{
			App->particles->AddParticle(App->particles->explosion, position.x + coldMachine.chest.chestPiece.position.x +
				coldMachine.f1Tof1ParticlePoints[i].x + 36,
				position.y + coldMachine.chest.chestPiece.position.y + coldMachine.f1Tof1ParticlePoints[i].y - 70,
				COLLIDER_NONE, { scrollSpeed ,0 }, coldMachine.f1Tof1ParticlesDelay[i]);
		}
		// second wave
		for (uint i = 0; i < 6; ++i)
		{
			App->particles->AddParticle(App->particles->explosion, position.x + coldMachine.chest.chestPiece.position.x +
				coldMachine.f1Tof1ParticlePoints[i].x + 71,//50,
				position.y + coldMachine.chest.chestPiece.position.y + coldMachine.f1Tof1ParticlePoints[i].y - 120,
				COLLIDER_NONE, { scrollSpeed ,0 }, coldMachine.f1Tof1ParticlesDelay[i] + 200);
		}
		for (uint i = 0; i < 6; ++i)
		{
			App->particles->AddParticle(App->particles->explosion, position.x + coldMachine.chest.chestPiece.position.x +
				coldMachine.f1Tof1ParticlePoints[i].x + 50,
				position.y + coldMachine.chest.chestPiece.position.y + coldMachine.f1Tof1ParticlePoints[i].y - 140,
				COLLIDER_NONE, { scrollSpeed ,0 }, coldMachine.f1Tof1ParticlesDelay[i] + 280);
		}
		for (uint i = 0; i < 6; ++i)
		{
			App->particles->AddParticle(App->particles->explosion, position.x + coldMachine.chest.chestPiece.position.x +
				coldMachine.f1Tof1ParticlePoints[i].x - 10, //+ 16,//50,
				position.y + coldMachine.chest.chestPiece.position.y + coldMachine.f1Tof1ParticlePoints[i].y - 40,
				COLLIDER_NONE, { scrollSpeed ,0 }, coldMachine.f1Tof1ParticlesDelay[i] + 340);
		}
		for (uint i = 0; i < 6; ++i)
		{
			App->particles->AddParticle(App->particles->explosion, position.x + coldMachine.chest.chestPiece.position.x +
				coldMachine.f1Tof1ParticlePoints[i].x + 36,
				position.y + coldMachine.chest.chestPiece.position.y + coldMachine.f1Tof1ParticlePoints[i].y - 20,
				COLLIDER_NONE, { scrollSpeed ,0 }, coldMachine.f1Tof1ParticlesDelay[i] + 480);
		}
		// third and last wave
		// second wave
		for (uint i = 0; i < 6; ++i)
		{
			App->particles->AddParticle(App->particles->explosion, position.x + coldMachine.chest.chestPiece.position.x +
				coldMachine.f1Tof1ParticlePoints[i].x + 20,//50,
				position.y + coldMachine.chest.chestPiece.position.y + coldMachine.f1Tof1ParticlePoints[i].y - 50,
				COLLIDER_NONE, { scrollSpeed ,0 }, coldMachine.f1Tof1ParticlesDelay[i] + 600);
		}
		for (uint i = 0; i < 6; ++i)
		{
			App->particles->AddParticle(App->particles->explosion, position.x + coldMachine.chest.chestPiece.position.x +
				coldMachine.f1Tof1ParticlePoints[i].x + 80,
				position.y + coldMachine.chest.chestPiece.position.y + coldMachine.f1Tof1ParticlePoints[i].y - 70,
				COLLIDER_NONE, { scrollSpeed ,0 }, coldMachine.f1Tof1ParticlesDelay[i] + 700);
		}
		for (uint i = 0; i < 6; ++i)
		{
			App->particles->AddParticle(App->particles->explosion, position.x + coldMachine.chest.chestPiece.position.x +
				coldMachine.f1Tof1ParticlePoints[i].x - 3, //+ 16,//50,
				position.y + coldMachine.chest.chestPiece.position.y + coldMachine.f1Tof1ParticlePoints[i].y - 120,
				COLLIDER_NONE, { scrollSpeed ,0 }, coldMachine.f1Tof1ParticlesDelay[i] + 900);
		}
		for (uint i = 0; i < 6; ++i)
		{
			App->particles->AddParticle(App->particles->explosion, position.x + coldMachine.chest.chestPiece.position.x +
				coldMachine.f1Tof1ParticlePoints[i].x + 53,
				position.y + coldMachine.chest.chestPiece.position.y + coldMachine.f1Tof1ParticlePoints[i].y - 90,
				COLLIDER_NONE, { scrollSpeed ,0 }, coldMachine.f1Tof1ParticlesDelay[i] + 1000);
		}



	}


}

EnemyColdMachine::~EnemyColdMachine()
{
	// unload sfx 8 in total
	App->audio->UnloadAudio("armShoot", SFX);
	App->audio->UnloadAudio("shuriken", SFX);
	
	
	App->audio->UnloadAudio("kneeLaser", SFX);
	App->audio->UnloadAudio("bossLanding", SFX);
	App->audio->UnloadAudio("bossMove", SFX);
	App->audio->UnloadAudio("bossRocket", SFX);

}