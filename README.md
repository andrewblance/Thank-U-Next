# Thank U, Next (a side scrolling shooter game)

## Introduction
This repo contains the begins of code to make a side scrolling shooter/ platformer game. At the current moment it will not compile on a machine unless you can supply libraries for SDL2, SDL2_mixer and SDL2_image. On top of this the music and graphics of the game are also not included. Also, the makefile included is pretty specific for my machine, so good luck.

The code is based on the book SDL Game Development by Shaun Mitchell.

Eventually, i will add the libraries and assets required to compile this properly.

## Improvements 
The code requires a few major improvements, and a few more minor ones. These include:
* make it so when you scroll of the screen you die - for now just respawn at the top-left of screen (DONE)
* need to have seperate end-game and you-died screens, as the restart button should do different things in either context
* Add collision with "dangerous" tiles
* add lives/ death animation/ invulnerability after respawn
* add health bar/ lives bar/ etc
* Add collision with enemies
* Add bullets and enable collisions with them
* Regain the ability to compile properly on other mac and linux machines without the need to have any SDL libraries pre-installed

These are all potentially very time consuming tasks. However, at this point the game arguably would be "finished". Smaller improvements may consist of:
* allow the buttons to be added in Tiled, rather than in the test.xml file
* currently music is .wav, would be better to be .ogg
* when the screen is scrolling and players collide with the enviroment the subsequent player scrolling is not smooth
* Level select screen/ way to select level from command line to allow for easier debugging.
* when pressing a menu button the sound plays to late, meaning you hear the noise on the next screen
* Investigate how to change screen size
* look into cleaning up scrolling collision - might help to use other version on character .png, where background isnt transparent.
* Generally cleaning up the code, many files include old functions that are no longer used.

More improvements to the game may include:
* Add more enemies
* Score/ Timer/ ???
* Touching a flag to end the level, like mario


The end goal would be that the files could be downloaded on any mac or linux system, and without any installing any sdl2 libraries beforehand, be able to run the makefile and successfully compile the game.


## Patch Notes
* 0.1
    * if you are pushed off screen you now die
    * resurect function works
    * you have a max num of lives now, when you run out you go to game over
    * theres a specific function now that decides if you completed the level by going far enough right
