#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleInput.h"
#include "ModuleRender.h"
#include "ModulePlayer.h"
#include "ModuleCollision.h"
#include "ModulePlayerUnit.h"
#include "ModuleParticles.h"
#include "ModuleAudio.h"
#include "ModuleFadeToBlack.h"


ModulePlayer::ModulePlayer()
{
	position.x = 40;
	position.y = 80;

	//spawn anim
	spawnAnim.PushBack({ 0,122,111,1 }); //0,79 
	spawnAnim.PushBack({ 6,125,105,2 }); //13,80 
	spawnAnim.PushBack({ 1,127,76,4 }); //12,79 
	spawnAnim.PushBack({ 0,131,74,8 }); //12,76 
	spawnAnim.PushBack({ 2,142,62,15 }); //8,72
	spawnAnim.PushBack({ 2,171,62,15 }); //8,73
	spawnAnim.PushBack({ 13,193,51,16 }); //16,72
	spawnAnim.PushBack({ 13,219,51,16 }); //16,72
	spawnAnim.PushBack({ 64,143,64,16 }); //8,72
	spawnAnim.PushBack({ 64,164,64,25 }); //8,67
	spawnAnim.PushBack({ 71,188,57,25 }); //15,67
	spawnAnim.PushBack({ 72,214,56,25 }); //16,67
	spawnAnim.PushBack({ 156,143,36,19 }); //36,71
	spawnAnim.PushBack({ 160,171,32,15 }); //40,73        
	spawnAnim.speed = 0.25f;
	spawnAnim.repeat = false;


	//movement anim
	playerAnim.PushBack({ 0,3,32,13 }); //up2 - 0
	playerAnim.PushBack({ 32,3,32,13 }); //up1 - 1
	playerAnim.PushBack({ 64,3,32,12 }); //idle - 2
	playerAnim.PushBack({ 96,3,32,12 }); //down1 - 3
	playerAnim.PushBack({ 128,4,32,11 }); //down2 - 4


	//Player Dying animation
	playerDyingAnim.PushBack({ 18,20,37,16 });
	playerDyingAnim.PushBack({ 14,37,41,16 });
	playerDyingAnim.PushBack({ 9,53,46,17 });
	playerDyingAnim.PushBack({ 3,70,52,17 });
	playerDyingAnim.PushBack({ 2,87,53,15 });
	playerDyingAnim.PushBack({ 0,104,55,16 });
	playerDyingAnim.PushBack({ 57,21,53,15 });
	playerDyingAnim.PushBack({ 58,36,52,16 });
	playerDyingAnim.PushBack({ 55,53,55,17 });
	playerDyingAnim.PushBack({ 56,70,54,17 });
	playerDyingAnim.PushBack({ 55,88,55,16 });
	playerDyingAnim.PushBack({ 57,104,53,17 });
	playerDyingAnim.PushBack({ 112,21,53,16 });
	playerDyingAnim.PushBack({ 114,38,51,16 });
	playerDyingAnim.PushBack({ 118,54,47,15 });
	playerDyingAnim.PushBack({ 118,70,47,16 });
	playerDyingAnim.PushBack({ 124,90,41,12 });
	playerDyingAnim.PushBack({ 128,108,37,10 });
	playerDyingAnim.speed = 0.3f;
	playerDyingAnim.repeat = false;

	//beam flash smoke
	beamSmoke.PushBack({ 128,126,10,9 });
	beamSmoke.PushBack({ 115,124,13,12 });
	beamSmoke.PushBack({ 0,0,0,0 });
	beamSmoke.PushBack({ 0,0,0,0 });
	beamSmoke.PushBack({ 0,0,0,0 });
	beamSmoke.PushBack({ 128,126,10,9 });
	beamSmoke.PushBack({ 115,124,13,12 });
	beamSmoke.PushBack({ 115,124,13,12 });
	beamSmoke.speed = 0.5f;
	beamSmoke.repeat = false;

	//boost animation
	boostAnim.PushBack({ 0,0,32,31 });
	boostAnim.PushBack({ 33,0,32,32});
	boostAnim.PushBack({ 64,2,32,26 });
	boostAnim.PushBack({ 96,7,32,18 });
	boostAnim.PushBack({ 0,33,32,13 });
	boostAnim.PushBack({ 33,36,32,7 }); //42,36,22,7 
	boostAnim.PushBack({ 64,36,32,7 }); //71,36,25,7 
	boostAnim.PushBack({ 96,36,32,6 }); //42,36,22,7 
	boostAnim.PushBack({ 0,53,32,6 });
	boostAnim.PushBack({ 33,52,32,6 });
	boostAnim.speed = 0.25f;
	boostAnim.repeat = false;

	// laser powerUp flash
	laserFlash.PushBack({ 1,1,13,13 });
	laserFlash.PushBack({ 16,1,15,15 });
	laserFlash.PushBack({ 33,1,27,9 });
	laserFlash.PushBack({ 32,18,31,7 });
	laserFlash.PushBack({ 1,27,31,5 });
	laserFlash.PushBack({ 1,39,32,3 });
	laserFlash.PushBack({ 1,34,32,3 });
	laserFlash.PushBack({ 1,18,30,3 });
	laserFlash.speed = 0.25f;
	laserFlash.repeat = false;

}




ModulePlayer::~ModulePlayer()
{}

// Load assets
bool ModulePlayer::Start()
{
	
	LOG("Loading player textures");
	bool ret = true;

	player = App->textures->Load("assets/Graphics/Player/player1_incomplete.png");
	powerUpTextures = App->textures->Load("assets/Graphics/Player/PowerUps.png");
	laserFlashTexture = App->textures->Load("assets/Graphics/Player/laserFlash.png");
	//restart player positions for next time playerModule call
	
	position.x = 40;
	position.y = 80;
	
	//player collision rect
	//playerCollider = App->collision->AddCollider({ position.x, position.y, 32, 12 }, COLLIDER_PLAYER,this);

	frameIncrement = 2; //initializes speed positions frame rect array incrementer at "center" -> idle

	ignitionSpeed = 0.2f; //speed when accelerate
	releaseSpeed = 0.1f; //speed when releases direction keys to return to idle

	//resets player score on every start
	playerScore = 0;

	destroyed = false;

	//load necessary fx wavs
	App->audio->LoadAudio("assets/Audio/SFX/Player/speedUpgrade.wav", "speedUP", SFX);
	App->audio->LoadAudio("assets/Audio/SFX/Player/speedDowngrade.wav", "speedDN", SFX);
	App->audio->LoadAudio("assets/Audio/SFX/Player/spawn.wav", "spawn", SFX);
	App->audio->LoadAudio("assets/Audio/SFX/Player/death.wav", "death", SFX);
	
	// ---------------------

	//for new gameLoops
	//checks if the player state is normal, if is, spawn condition
	if (player_step == player_state::normal || player_step == player_state::died)
		player_step = player_state::spawn;
		
	//and play FX, for the moment, right here is good
	App->audio->ControlAudio("spawn", SFX, PLAY);
	

	//defines times for buffs
	powerUpTime = 5000; //in ms

	return ret;


}

update_status ModulePlayer::PreUpdate()
{
	//FUNCTIONALITY POWERUPS, assigns speeds, animations etc
	if (player_step == player_state::normal)
	{
		now = SDL_GetTicks() - start_time; //time events/states general counter
		//BOOST LOGIC ---------------------------------------------------------
		if (powerUpActive == powerUpTypes::BOOST)
		{
			start_time = SDL_GetTicks(); //start time of the boost buff
			speed = boostPlayerSpeed;
			activebuff.boost = true; //actives bool condition
			activebuff.boostAnim = true;
			activebuff.brake = false;
			powerUpActive = powerUpTypes::NONE; //resets the enumerator to free the way for another
			//play FX
			App->audio->ControlAudio("speedUP", SFX, PLAY);
		}
		//float speed = 1.4f; //player position speed
		if (!activebuff.boost && !activebuff.brake) //if the time for boost go out... and the boost brake is not active, normal speed
		{

			playerSpeed = speed = normalPlayerSpeed; //resets the temporal incrementer to always Nicolas at the desired incrementer count
													 //new change direction starts incrementer at speed correct value (always same distances)
		}
		else if (activebuff.brake)
			speed = brakePlayerSpeed;

		if (powerUpActive == powerUpTypes::BRAKE)
		{
			//activebuff.boost = false; //its finish automatic when its animation finish
			activebuff.brake = true;
			powerUpActive = powerUpTypes::NONE;
		}

		if (powerUpActive == powerUpTypes::LASER)
		{
			activebuff.laser = true;
			powerUpActive = powerUpTypes::NONE;
		}
		// --------------------------------------------------------------------
		
	}


	return UPDATE_CONTINUE;
}
// Update: draw background
update_status ModulePlayer::Update()
{
	current_animation = &playerAnim;
	SDL_Rect r;

	if (player_step == player_state::spawn)
	{
		current_animation = &spawnAnim;
		r = current_animation->GetCurrentFrame();
		if (current_animation->finish)
		{
			player_step = player_state::normal;
			current_animation->finish = false; //and resets condition
			current_animation->current_frame = 0;
			//activate collider
			playerCollider = App->collision->AddCollider({ position.x, position.y, 32, 12 }, COLLIDER_PLAYER, this);
		}
	}

	else if (player_step == player_state::normal)
	{
		//for now activates playerUnit for testing here
		if (!App->playerUnit->IsEnabled())
		{
			//App->playerUnit->Enable();
		}
		
		/*if (powerUpActive == powerUpTypes::BOOST)
		{
			speed = boostPlayerSpeed;
			now = SDL_GetTicks() - start_time;

			if (now >= poweUpTime)
			{
				start_time = SDL_GetTicks();
				powerUpActive = powerUpTypes::NONE;

			}
		}
		//float speed = 1.4f; //player position speed
		else
		playerSpeed = speed = normalPlayerSpeed; //resets the temporal incrementer to always Nicolas at the desired incrementer count
							  //new change direction starts incrementer at speed correct value (always same distances)*/

		//App->render->Blit(player,300, 50, &spawnAnim.GetCurrentFrame());

		//Animation* current_animation = &playerAnim;

		//animation logic ---------------------------------------------------------------

		if (App->input->keyboard[SDL_SCANCODE_S] == KEY_STATE::KEY_REPEAT) //while press down
		{
			frameIncrement += ignitionSpeed;
			if (frameIncrement >= 5)
				frameIncrement = 4.99f;
		}

		//for quickly directions change, release  to turn idle speed incrementer doesn't affect
		//yet, and go to top up animation (or wherever we are) at ignition speed (normal/fast direction change)
		//and only if the two keys are released, return at release speed to idle position
		//we check on separate for fast direction change (no key release = to estabilization spaceship)

		//----ship estabilization check (return to idle when release up or down) ---

		if (App->input->keyboard[SDL_SCANCODE_S] == KEY_STATE::KEY_IDLE && (int)frameIncrement != 2)
		{
			if ((int)frameIncrement >= 2)
				frameIncrement -= releaseSpeed;

		}

		if (App->input->keyboard[SDL_SCANCODE_W] == KEY_STATE::KEY_IDLE && (int)frameIncrement != 2)
		{
			if (frameIncrement < 2)
				frameIncrement += releaseSpeed;
		}

		//---------------------------------------------------------------------------
		//already, double check to imitate original animation behaviour (emulator)
		if (App->input->keyboard[SDL_SCANCODE_W] == KEY_STATE::KEY_REPEAT &&
			App->input->keyboard[SDL_SCANCODE_S] == KEY_STATE::KEY_IDLE) //while press up
		{
			frameIncrement -= ignitionSpeed;
			if (frameIncrement <= 0)
				frameIncrement = 0;
		}

		//--------------------------------------------------------------------------------

		 r = current_animation->frames[(int)frameIncrement]; //idle

		//--------------------------------------------------------------------------------

		//move player position (this section must be code optimized ----------------------
		//down move position
		if (App->input->keyboard[SDL_SCANCODE_S] == KEY_STATE::KEY_REPEAT)
		{
			playerSpeed += speed;
			position.y += (int)playerSpeed;
			if (playerSpeed >= speed + 1) //returns correct value to cast incrementer
				playerSpeed = speed;

			if (position.y + (int)playerSpeed >= SCREEN_HEIGHT - 8) // 8 = player height/2 + required offset
				position.y = 216; //target max down player position (original game pixel)
		}

		//up move position, checks if not down to imitate original game (emulator) behaviour
		if (App->input->keyboard[SDL_SCANCODE_W] == KEY_STATE::KEY_REPEAT &&
			App->input->keyboard[SDL_SCANCODE_S] == KEY_STATE::KEY_IDLE)
		{

			playerSpeed += speed;
			position.y -= (int)playerSpeed;
			if (playerSpeed >= speed + 1) //checks and assign correct value to int cast float incrementer
				playerSpeed = speed;	  //and next cycle

			if (position.y + (int)playerSpeed <= 0 + 8) //0 = min y coordinate, 8 = texture height/2 + offset
				position.y = 8; //target min y player position

		}

		//---------------------------------------------------------------------------------

		//right move, doble check for imitate original (emulator) behaviour
		if (App->input->keyboard[SDL_SCANCODE_D] == KEY_STATE::KEY_REPEAT &&
			App->input->keyboard[SDL_SCANCODE_A] == KEY_STATE::KEY_IDLE)
		{
			playerSpeed += speed;
			position.x += (int)playerSpeed;
			if (playerSpeed >= speed + 1) //checks and assign correct value to int cast float incrementer
				playerSpeed = speed;		//and next cycle

			//playerSpeed at if is for assure the limits independent of speed value
			//if (position.x + (int)playerSpeed >= 256) //0 = min y coordinate, 9=texture height/2 + offset
				//position.x = 256; //target min y player position

			if (position.x > (abs(App->render->camera.x) / SCREEN_SIZE) + SCREEN_WIDTH - (32+16)) //player text width + offset
			{
				position.x = (abs(App->render->camera.x) / SCREEN_SIZE) + SCREEN_WIDTH - (32+16);// 16 = 1/2 player width + 16 offset original game
			}
		}

		//left move
		if (App->input->keyboard[SDL_SCANCODE_A] == KEY_STATE::KEY_REPEAT)
		{
			playerSpeed += speed;
			position.x -= (int)playerSpeed;
			if (playerSpeed >= speed + 1) //checks and assign correct value to int cast float incrementer
				playerSpeed = speed;		//and next cycle

			/*if (position.x + (int)playerSpeed <= 0 + 16) //0 = min y coordinate, 9=texture height/2 + offset
				position.x = 16; //target min y player position*/
			if (position.x < abs(App->render->camera.x) / SCREEN_SIZE + 16)
			{
				position.x = abs(App->render->camera.x) / SCREEN_SIZE + 16;// 16 = 1/2 player width + 16 offset original game
			}
		}

		cameraPosition = abs(App->render->camera.x / 3);
		//--------------------------------------------------------------------------------

		//if player press keys of particles emitters

		if (App->input->keyboard[SDL_SCANCODE_SPACE] == KEY_STATE::KEY_DOWN)
		{
			LOG("Beam!");
			if (activebuff.laser)
			{
				shootingLaser = true;
				App->particles->AddParticle(App->particles->laser, position.x + 32, position.y - 2, COLLIDER_PLAYER_SHOT); //"shot");
			}

			shooting = true;
			App->particles->AddParticle(App->particles->beam, position.x + 32, position.y - 4, COLLIDER_PLAYER_SHOT); //, "shot");
		
		}
		//checks animation cycle
		if (shooting)
		{
			if (beamSmoke.current_frame == beamSmoke.last_frame) //resets animation cycle
			{
				beamSmoke.current_frame = 0;
				beamSmoke.finish = false;
				shooting = false;
			}
			App->render->Blit(player, position.x + 32, position.y - 6, &beamSmoke.GetCurrentFrame());
		}

		if (shootingLaser)
		{
			Animation* currentLaserFlash = &laserFlash;
			SDL_Rect currentLaserFlashRect = currentLaserFlash->GetCurrentFrame();

			if (App->input->keyboard[SDL_SCANCODE_SPACE] == KEY_DOWN) //force restart animation for new shot
				currentLaserFlash->current_frame = 0;

			if (currentLaserFlash->current_frame >= currentLaserFlash->last_frame) //resets animation cycle
			{
				laserFlash.current_frame = 0;
				laserFlash.finish = false;
				shootingLaser = false;
			}
			App->render->Blit(laserFlashTexture, position.x + 32, position.y - 1 - (currentLaserFlashRect.h / 2), &currentLaserFlashRect);
		}
		// -------------------------------------------------------------------------------------------------------------------------


		//CHECK POWERUP ANIMATIONS etc ---------------------------------------------------------------------------------------------
		if (activebuff.boost)
		{
			now = SDL_GetTicks() - start_time;
			if (now >= powerUpTime) //checks the timer counter and deactivate the boost time
			{
				activebuff.boost = false;
				//PLAY SFX
				App->audio->ControlAudio("speedDN", SFX, PLAY);
			}

			if (activebuff.boostAnim)
			{
				current_animation = &boostAnim;
				SDL_Rect boostAnimRect = current_animation->GetCurrentFrame();
				if (current_animation->finish) 
				{ 
					activebuff.boostAnim = false;
					current_animation->current_frame = 0; //and resets its values for next boost
					current_animation->finish = false;
				}
				else
					App->render->Blit(powerUpTextures, position.x - 32, position.y - (boostAnimRect.h / 2), &boostAnimRect);
			}
		}
		
		// --------------------------------------------------------------------------------------------------------------------------

		//update player collider to its position -----------------------------------------
		
			playerCollider->SetPos(position.x, position.y - 6);
		
		//DEBUG FUNCTIONALITIES -------------------------------------------------------------------------------------------------

		//DEBUG: GODMODE F2 ---------------------------------
		if (App->input->keyboard[SDL_SCANCODE_F2] == KEY_DOWN)
		{
			if (playerCollider != nullptr && !godMode)
			{
				this->playerCollider->to_delete = true;
				playerCollider = nullptr;
				playerCollider = App->collision->AddCollider({ position.x, position.y - 6, 32, 12 }, COLLIDER_PLAYER_GOD, this);
				godMode = true;
			}
			else
			{
				this->playerCollider->to_delete = true;
				playerCollider = nullptr;
				playerCollider = App->collision->AddCollider({ position.x, position.y - 6, 32, 12 }, COLLIDER_PLAYER, this);
				godMode = false;
			}
		}
		//DEBUG: ACTIVATE/DEACTIVATE UNIT, cycle: blue/orange/off
		if (App->input->keyboard[SDL_SCANCODE_F3] == KEY_DOWN)
		{
			if (!App->playerUnit->IsEnabled())
			{
				App->playerUnit->swapColor(powerUpColor::BLUE);
				App->playerUnit->Enable();
			}
			else if (App->playerUnit->actualUnitColor == powerUpColor::ORANGE)
			{
				App->playerUnit->Disable();
			}
			else if (App->playerUnit->actualUnitColor == powerUpColor::BLUE)
			{
				App->playerUnit->swapColor(powerUpColor::ORANGE);
			}
			
		}
		//DEBUG: SPAWN POWERUPS ------------------------------------------------------------------------------
		if (App->input->keyboard[SDL_SCANCODE_F4] == KEY_DOWN)
		{
			App->modulePowerUp->SpawnPowerUp({ position.x + (32 + 100),position.y - 8}, powerUpTypes::BOOST);
		}
		if (App->input->keyboard[SDL_SCANCODE_F5] == KEY_DOWN)
		{
			App->modulePowerUp->SpawnPowerUp({ position.x + (32 + 100),position.y - 8 }, powerUpTypes::BOMBS);
		}
		if (App->input->keyboard[SDL_SCANCODE_F6] == KEY_DOWN)
		{
			App->modulePowerUp->SpawnPowerUp({ position.x + (32 + 100),position.y - 8}, powerUpTypes::BRAKE);
		}
		if (App->input->keyboard[SDL_SCANCODE_F7] == KEY_DOWN)
		{
			App->modulePowerUp->SpawnPowerUp({ position.x + (32 + 100),position.y - 8}, powerUpTypes::LASER);
		}
		if (App->input->keyboard[SDL_SCANCODE_F8] == KEY_DOWN)
		{
			App->modulePowerUp->SpawnPowerUp({ position.x + (32 + 100),position.y - 8 }, powerUpTypes::MISSILES);
		}

		//DEBUG: PAUSE/UNPAUSE MUSIC on modulePlayer for now --- debugging SFX etc
		if (App->input->keyboard[SDL_SCANCODE_F10] == KEY_DOWN)
		{
			if (Mix_PausedMusic())
			{
				Mix_ResumeMusic();
				
			}
			else
				Mix_PauseMusic();
		}

	}	// ----------------------------------------------------------------------------------------------------------------------

	//DRAW PLAYER ---------------------------------------------------------------------------
	//draw SPAWN ANIMATION --------
	if (player_step == player_state::spawn)
	App->render->Blit(player, position.x - pivotsSpawnX[(int)current_animation->current_frame], position.y - (r.h / 2), &r, 1.0f);
	else if (player_step == player_state::normal)
	//draw player NORMAL STATE --------------------------------------------------------------
	App->render->Blit(player, position.x, position.y - (r.h / 2), &r, 1.0f);
	// --------------------------------------------------------------------------------------

	else if (player_step == player_state::died && destroyed)
	{
		current_animation = &playerDyingAnim;
		r = current_animation->GetCurrentFrame();
		App->render->Blit(player, position.x, position.y - (r.h / 2), &r);
		if (current_animation->finish)
		{
			current_animation->current_frame = 0;
			current_animation->finish = false;
			destroyed = false;
			if (lives <= 1)
			{
				//resets lives counter for next gameLoop
				lives = 3;
				App->fade->FadeToBlack((Module*)App->scene_lvl1, (Module*)App->gameOverScreen);
			}
			else
			{
				App->fade->FadeToBlack((Module*)App->scene_lvl1, (Module*)App->continueScreen, 1.0f);   //<-------------------SHOULD GO TO READY SCREEN
				--lives;
			}
		}

	}
	
	return UPDATE_CONTINUE;

}

void ModulePlayer::OnCollision(Collider* collider1, Collider* collider2)
{
		//deactivate player active powerUps
	if(App->playerUnit->IsEnabled())
		App->playerUnit->Disable();

		player_step = player_state::died;
		destroyed = true;
		//PLAY FX
		App->audio->ControlAudio("death", SFX, PLAY);

	if (playerCollider != nullptr)
			this->playerCollider->to_delete = true;
}

bool ModulePlayer::CleanUp()
{
	//freeing textures
	if(player != nullptr)
		App->textures->Unload(player);
	if(powerUpTextures != nullptr)
		App->textures->Unload(powerUpTextures);

	if (playerCollider != nullptr)
	{
		playerCollider->to_delete = true;
	}

	//if we are on super sayan GOD
	godMode = false;

	//unloading SFX
	App->audio->UnloadAudio("speedDN", SFX);
	App->audio->UnloadAudio("speedUP", SFX);
	App->audio->UnloadAudio("spawn", SFX);
	App->audio->UnloadAudio("death", SFX);

	//deactivate all possible active buffs
	activebuff.bombs = false;
	activebuff.boost = false;
	activebuff.brake = false;
	activebuff.laser = false;
	
	return true;
}