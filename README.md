# Thank-U-Next

## Introduction
This repo contains the begins of code to make a side scrolling shooter/ platformer game. At the current moment it will not compile on a machine unless you can supply libraries for SDL2, SDL2_mixer and SDL2_image. On top of this the music and graphics of the game are also not included. The makefile included is pretty specific for my machine, so good luck.

The code is based on the book SDL Game Development by Shaun Mitchell.

## Improvements 
The code requires a few major improvements, and a few more minor ones. These include:
* make is so when you scroll of the screen you die
    * this will require testing of the death, respawning and lives parts on the Player::update function. This may not be a small task.
* Add collision with "dangerous" tiles
* Add collision with enemies
* Add bullets and enable collisions with them
* Regain the ability to compile properly on other mac and linux machines

These are all potentially very time consuming tasks. However, at this point the game arguably would be "finished". Smaller improvements may consist of:
* allow the buttons to be added in Tiled, rather than in the test.xml file
* currently music is .wav, would be better to be .ogg
* when the screen is scrolling and players collide with the enviroment the subsequent player scrolling is not smooth
* Level select screen/ way to select level from command line to allow for easier debugging.
* when pressing a menu button the sound plays to late, meaning you hear the noise on the next screen
* Investigate how to change screen size
* Generally cleaning up the code, many files include old functions that are no longer used.

More improvements to the game may include:
* Add more enemies
* Score/ Timer/ ???
* Touching a flag to end the level, like mario


