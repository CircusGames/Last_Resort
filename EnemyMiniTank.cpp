#include "Application.h"
#include "EnemyMiniTank.h"
#include "ModuleCollision.h"
#include "Globals.h"
#include "ModuleEnemies.h"
#include "SDL\include\SDL_timer.h"
#include "Path.h"
#include "ModuleRender.h"

Enemy_MiniTank::Enemy_MiniTank(int x, int y, powerUpTypes type, SDL_Texture* thisTexture) : Enemy(x, y)
{

	//Missiles Animation
	/*missilelaunch.PushBack({ 0,110,21,16 });
	missilelaunch.PushBack({ 22,110,21,24 });
	missilelaunch.PushBack({ 44,110,27,29 });
	missilelaunch.PushBack({ 72,110,28,31 });
	missilelaunch.PushBack({ 103,110,30,32 });
	missilelaunch.PushBack({ 134,110,31,32 });
	missilelaunch.PushBack({ 166,110,32,32 });
	missilelaunch.PushBack({ 199,110,32,31 });
	missilelaunch.PushBack({ 232,110,31,30 });
	missilelaunch.PushBack({ 264,110,30,16 });
	missilelaunch.PushBack({ 0,143,19,12 });
	missilelaunch.PushBack({ 25,143,23,15 });

	missileexplode.PushBack({ 0,171,23,19 });
	missileexplode.PushBack({ 24,163,25,17 });
	missileexplode.PushBack({ 50,160,30,30 });
	missileexplode.PushBack({ 114,161,25,29 });
	missileexplode.PushBack({ 140,159,28,31 });
	missileexplode.PushBack({ 170,159,30,31 });
	missileexplode.PushBack({ 201,159,32,31 });
	missileexplode.PushBack({ 233,161,30,29 });
	missileexplode.PushBack({ 264,163,29,27 });*/

	/*missile.PushBack({ 184,11,10,14 });//0º Mira hacia arriba
	missile.PushBack({ 195,11,11,13 });//22'5º
	missile.PushBack({ 207,11,13,13 });//45º
	missile.PushBack({ 221,11,13,11 });//67'5º
	missile.PushBack({ 235,13,14,10 });//90º
	missile.PushBack({ 250,11,13,11 });//112'5º
	missile.PushBack({ 264,11,13,13 });//135º
	missile.PushBack({ 278,11,11,13 });//157'5º
	missile.PushBack({ 290,11,10,14 });//180º
	missile.PushBack({ 278,26,11,13 });//202'5º
	missile.PushBack({ 264,26,13,13 });//225º
	missile.PushBack({ 250,26,13,11 });//247'5º
	missile.PushBack({ 235,26,14,10 });//270º
	missile.PushBack({ 221,26,13,11 });//292'5º
	missile.PushBack({ 207,26,13,13 });//315º
	missile.PushBack({ 195,26,10,14 });//337'5º*/

	/*fire.PushBack({ 221,84,16,16 });
	fire.PushBack({ 238,84,12,12 });
	fire.PushBack({ 251,84,8,8 });
	fire.PushBack({ 260,84,6,6 });
	fire.speed = 0.5f;*/

	/*missilesmoke.PushBack({ 314,164,13,14 });
	missilesmoke.PushBack({ 339,164,15,14 });
	missilesmoke.PushBack({ 366,164,16,16 });
	missilesmoke.PushBack({ 394,164,14,16 });
	missilesmoke.PushBack({ 420,164,15,14 });
	missilesmoke.PushBack({ 447,164,15,14 });*/

	// -----------------------------------------------------------------
	enemyTex = thisTexture; // links enemy to correct texture

	powerUpType = type; // assigns receveid powerup

	//original_pos.x = x;
	//original_pos.y = y;

	life = 17;

	// animations ------------------------------------------------------
	// 
	// normal anim up 8 frames, 4 and 4
	cartePillar.moveAnim[NORMAL_ANIM].PushBack({61,11,61,48}); // wheels 1 || 4 frames
	cartePillar.moveAnim[NORMAL_ANIM].PushBack({ 122,11,61,48 }); // wheels 2 || 4 frames
	cartePillar.moveAnim[NORMAL_ANIM].PushBack({ 0,11,61,48 }); // wheels down || 4 frames
	cartePillar.moveAnim[NORMAL_ANIM].speed = 0.25f;
	// shooting animation
	cartePillar.shootAnim[NORMAL_ANIM].PushBack({301,333,61,48});


	collider = App->collision->AddCollider({ 0, 0, 61, 48 }, COLLIDER_TYPE::COLLIDER_ENEMY, (Module*)App->enemies);

	position.x = x;
	position.y = y;

}

void Enemy_MiniTank::Move()
{
	
	// update collider position
	collider->SetPos(position.x,position.y);


}


void Enemy_MiniTank::Draw()
{

	App->render->Blit(enemyTex, position.x, position.y, &cartePillar.moveAnim->GetCurrentFrame());
	
}

void Enemy_MiniTank::OnCollision(Collider* collider, Collider* collider2)
{





}