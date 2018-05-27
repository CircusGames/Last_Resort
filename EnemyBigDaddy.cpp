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

	// animations ------------------------------
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
	// mid 1
	laser.anim[0][1].PushBack({ 155,179,16,8 }); // big
	laser.anim[0][1].PushBack({ 106,179,16,6 });
	laser.anim[0][1].PushBack({ 59,179,16,4 });
	laser.anim[0][1].PushBack({ 14,179,16,2 });

	laser.anim[0][1].PushBack({ 59,179,16,4 });
	laser.anim[0][1].PushBack({ 106,179,16,6 });
	laser.anim[0][1].PushBack({ 155,179,16,8 }); // big
	laser.anim[0][1].speed = 1.0f;
	// mid 2
	laser.anim[0][2].PushBack({ 155,179,16,8 }); // big
	laser.anim[0][2].PushBack({ 106,179,16,6 });
	laser.anim[0][2].PushBack({ 59,179,16,4 });
	laser.anim[0][2].PushBack({ 14,179,16,2 });

	laser.anim[0][2].PushBack({ 59,179,16,4 });
	laser.anim[0][2].PushBack({ 106,179,16,6 });
	laser.anim[0][2].PushBack({ 155,179,16,8 }); // big
	laser.anim[0][2].speed = 1.0f;
	// mid 3
	laser.anim[0][3].PushBack({ 155,179,16,8 }); // big
	laser.anim[0][3].PushBack({ 106,179,16,6 });
	laser.anim[0][3].PushBack({ 59,179,16,4 });
	laser.anim[0][3].PushBack({ 14,179,16,2 });

	laser.anim[0][3].PushBack({ 59,179,16,4 });
	laser.anim[0][3].PushBack({ 106,179,16,6 });
	laser.anim[0][3].PushBack({ 155,179,16,8 }); // big
	laser.anim[0][3].speed = 1.0f;
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

	
	collider = App->collision->AddCollider({ 0, 0, 44, 48 }, COLLIDER_TYPE::COLLIDER_ENEMY, (Module*)App->enemies);


	// start timers
	bigDaddy.start_shoot_time = SDL_GetTicks();

	offset[0][1] = { 13,0 };
	offset[0][2] = { 16,0 };
	offset[0][3] = { 16,0 };
	offset[0][4] = { 16,0 };

	// spawn points boss laser corners
	laser.instantiationPosition[0] = { position.x , position.y }; // left up corner
	laser.instantiationPosition[1] = { 200 , 100 }; // left down corner
	laser.instantiationPosition[2] = { 200 , 100 }; // right up corner
	laser.instantiationPosition[3] = { 200 , 100 }; // right down corner

	laser.position[0][0] = laser.instantiationPosition[0];


}

void EnemyBigDaddy::Move()
{
	// updates laser instantiation position to follow enemy position
	laser.instantiationPosition[0] = { position.x , position.y }; // left up corner

	//fposition.x -= 1.35;
	//position.x = fposition.x;
	position.x += 1;

	// laser test positions
	laser.position[0][0].x -= 1;
	//laser.position[0][0].y -= 1;
	laser.position[0][1] = laser.position[0][0] + offset[0][1];
	laser.position[0][2] = laser.position[0][1] + offset[0][2];
	laser.position[0][3] = laser.position[0][2] + offset[0][3];
	laser.position[0][4] = laser.position[0][3] + offset[0][4];

	// set colliders pos
	collider->SetPos(position.x + 10, position.y + 8);

	// activate laser parts
	laser.active[0][0] = true;
	//laser.active[0][1] = true;


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
	if (bigDaddy.attack)
	{

	}

	// check distance of the instantiated laser to grow up the lenght with more parts (active ones)

	for (uint i = 0; i < 5; ++i)
	{
		if (laser.position[0][i].x < laser.instantiationPosition[0].x - offset[0][i+1].x && !laser.active[0][i+1])//- offset[0][1].x)
		{
			laser.active[0][i+1] = true;
			laser.anim[0][i+1].current_frame = laser.anim[0][0].current_frame;
		}
	}
	/*for (uint i = 4; i > 0; --i)
	{
		if (laser.position[0][i].x > laser.instantiationPosition[0].x + offset[0][i - 1].x && !laser.active[0][i - 1])//- offset[0][1].x)
		{
			laser.active[0][i - 1] = true;
			laser.anim[0][i - 1].current_frame = laser.anim[0][4].current_frame;
		}
	}*/
	/*if (laser.position[0][0].x < laser.instantiationPosition[0].x - offset[0][1].x && !laser.active[0][1])//- offset[0][1].x)
	{
		laser.active[0][1] = true;
		laser.anim[0][1].current_frame = laser.anim[0][0].current_frame;
	}*/

	// and draw the actives
	for (uint i = 0; i < 5; ++i)
	//for (uint i = 4; i > 0; --i)
	{

		if (laser.active[0][i])
		{
			laser.rect = laser.anim[0][i].GetCurrentFrame();

			App->render->Blit(laserTexture, laser.position[0][i].x, laser.position[0][i].y - laser.rect.h / 2, &laser.rect);
		}
	}

	/*App->render->Blit(laserTexture, laser.position[0][1].x , laser.position[0][1].y, &laser.anim[0][1].GetCurrentFrame());

	App->render->Blit(laserTexture, laser.position[0][2].x , laser.position[0][2].y, &laser.anim[0][2].GetCurrentFrame());

	App->render->Blit(laserTexture, laser.position[0][3].x, laser.position[0][3].y, &laser.anim[0][3].GetCurrentFrame());

	App->render->Blit(laserTexture, laser.position[0][4].x, laser.position[0][4].y, &laser.anim[0][4].GetCurrentFrame());*/
}

EnemyBigDaddy::~EnemyBigDaddy()
{
	// unloads laser texture
	App->textures->Unload(laserTexture);
	

}