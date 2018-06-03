# Circus Games

# LAST RESORT 

<p align="center">
  <b>Tribute From Circus Games</b><br>
</p>

<p align="center">
<img src="https://upload.wikimedia.org/wikipedia/en/thumb/1/14/Last_Resort_Neo_Geo_cover.jpg/250px-Last_Resort_Neo_Geo_cover.jpg" width="400">
</p>

Last Resort is one of the greatest arcade shoot 'em up videogames because of his great technical quality for the times of his release and it's very well-known for his challenging and brutally difficulty. The original version of the game was released in 1992 for NeoGeo Arcade Systems by SNK. Later was released for NeoGeo CD. Since then, was remastered in SNK Arcade Classics Vol.1 for the PS2, PSP and Wii in 2007 and later on, in 2017, for PS4, Xbox One and Nintendo Switch. This game is an spiritual sequel of R-Type, because of the similarity of their mechanics. Also, his art was very inspired on the manga Akira.

<p align="center">
<img src="http://www.mobygames.com/images/shots/l/101879-last-resort-neo-geo-screenshot-boss.gif" width="480">
</p>

***

## Responsabilities


| Name	        | Main Function  | Github account|
| ------------- |:-------------:|:-------------:|
| Kevin      | Management |[DustHandler](https://github.com/dusthandler)|
| Jos� Antonio      | Code      |[PeterMcP](https://github.com/peterMcP)|
| Rafa | Art/Design      |[RafaKanex](https://github.com/RafaKanex)|
| V�ctor | QA      |[VictorSegura99](https://github.com/VictorSegura99)|


## Team photo

<p align="center">
<img src="https://github.com/dusthandler/CITM_Proyecto_1/blob/master/docs/Team_Photo.jpg" width="480">
</p>

***

## Gameplay video of the original title

[![Watch the video](https://www.youtube.com/watch?v=y1xUT7QJ-mA)](https://www.youtube.com/watch?v=y1xUT7QJ-mA)

<iframe width="854" height="480" src="https://

## Gameplay of our version

[![Watch the video](https://www.youtube.com/watch?v=ROs_Zj6Vj4U&feature=youtu.be)](https://www.youtube.com/watch?v=ROs_Zj6Vj4U&feature=youtu.be)

<iframe width="854" height="480" src="https://

***

***


## Wiki

[Landing Page](https://github.com/CircusGames/Last_Resort/wiki)

[General analysis](https://github.com/CircusGames/Last_Resort/wiki/Analysis)

[Design](https://github.com/CircusGames/Last_Resort/wiki/Design)

[User interface](https://github.com/CircusGames/Last_Resort/wiki/UI)

[Audio](https://github.com/CircusGames/Last_Resort/wiki/Audio)

[Art](https://github.com/CircusGames/Last_Resort/wiki/Art)

[How to extract sprites](https://github.com/CircusGames/Last_Resortwiki/HowTo)


***

## Changelogs

### changelog v1.0

    * Added Enemy Submarine
    * Added Enemy MiniTank
        * Added All Enemies spawned by Submarine
    * Added MidBoss Enemy
    * Added Boss Enemy
        * Added All Enemies spawned by the Boss
    * Added Enemy Lamella
    * UI polished
    * More Power Ups Added and Fixed
    * Win Module Fixed
        * Win/Lose Points Recorded
    * Player 2 Full Funcionality
    * Coins System Added

***

### changelog v0.7.5

    * Enemies now are capable to follow the nearest valid player.
    * Unit is now completed
         * you can maintain pressed shot button to charge.
         * blue functionality, bouncing.
         * orange functionality, follow colliders in correct direction.
         * when the unit is throwed you can damage the enemies the respected charged amount.
              * if the amount is minor to enemy actual life, returns unit, if not, continue.

***

### changelog v0.6.5

    * Added full backgrounds/animations and logic of Level 3 scene
    * Added gamePad functionality for two players (with hot plug)
    * Added fullScreen mode
    * Added Protator enemy
    * Added metal red bird enemy
    * Added bee dropper
    * Updated metal bee to scene 3
    * Several fixes

***

### changelog v0.5

    * Added player 2, still WIP
    * Added multiple enemies
    * Added god mode
    * Added a lot of debuging tools
    * Added laser and speed powerups
    * Added continue, gameover and socoreboard screens

***

### changelog v0.4
	
   * Added moduleCollisions.
   * Fixed player Camera limits.
   * Updated moduleParticles to consider collisions.
   * Particles now can be locked to follow player position.
   * Removed animations dynamic memory workaround till we get more reliable method.
   * Recoded ModuleAudio to just have 3 functions, load unload and control independent of its format.

***

### changelog v0.3

   * Added moduleParticles:
      * modified to accept, speed, life, and sourceAnimation.
	  * SourceAnimation is used to link pointer of structure particles to animation.
	  * SourceAnimation is created to coexist with animations dynamic memory destructor.
   * Splitted ModuleScene into two separated modules, gameTitle and teamLogo:
      * gameTitle now have full animations and logic.
   * Added Player Unit Module:
      * Contains the logic and animations of the basic weapon of the game, the Unit.
	  * Full linear and diagonals moves respect the player position.
	  * Links correctly the flow of the Unit animation itself.
	  * NOT CONTEMPLED YET: diagonals of the Unit animation itself (where it's pointing with diagonal press).
   * Adapted ModuleAudio to accept the load, severals options to play music,FX, and unload FX.

***

### changelog v0.2.1
	
   * Code updated to sdl5_handout (ModuleFadeToBlack and some new adaptations).
   * Added circular scene switching (teamLogo and TitleScreen(WIP) -> lvl1 -> game over -> TitleScreen and so on).
   * Modified, but WIP moduleAudio with functions to load, unload and control music.
   * Every current scene loads their needed music song audio and unloads them.
   * Now we can close the game with mouse :).
   
***
   
### changelog v0.2

   * Changed ModuleParallax for ModuleBackground.
   * ModuleBackground contains:
	  * Functionality to scroll backgrounds with parameter camera speed simulating parallax profundity effect.
	  * Added ALL background logic and animations.
   * Modified ModuleRender with funcionality:
      * To flip textures.
      *	Optional parameter of parallax speed y.
   * Modified class animation: 
      * To accept parameter repeat, wich optional prevent cycling animations.
	  * Adapted the method pushback to reserve new rects with dynamic memory.
   * Added ModulePlayer with all the player movement logic and appropiate animations.

***   
 
### Changelog v0.1

   * Added provisional moduleParallax for scroll differents backgrounds at various speeds.
   * Added provisional moduleAudio wich loads one specific sound.
      * Functionality to playMusic with fadeIn, and on quit, fadeOut.
	  
