# Thank U, Next (a side scrolling shooter game)

## Introduction
This repo contains the begins of code to make a side scrolling shooter/ platformer game. At the current moment it will not compile on a machine unless you can supply libraries for SDL2, SDL2_mixer and SDL2_image. Also, the makefile included is pretty specific for my machine, so good luck.

Eventually, i will add the libraries and assets required to compile this properly.

## Improvements 
The code requires a few major improvements, and a few more minor ones. These include:
* make it so when you scroll of the screen you die - for now just respawn at the top-left of screen (DONE)
* need to have seperate end-game and you-died screens, as the restart button should do different things in either context
* Add collision with "dangerous" tiles (DONE - could be fine tuned a lil though)
* add lives/ death animation/ invulnerability after respawn (DONE)
* add health bar/ lives bar/ etc (DONE)
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
* the ability to parse in text would be great
* right now theres no map up or down, only to your left or right. Changing this would mean improve level variety


The end goal would be that the files could be downloaded on any mac or linux system, and without any installing any sdl2 libraries beforehand, be able to run the makefile and successfully compile the game.

## Assets
The code is based on Shaun Mitchell's book SDL Game Development.

I have created the assets in this game from the following sources:
* The tileset (Caves of Gallet) - Adam Saltsman
* Health bar (pixel health bar asset pack 2) and buttons (button asset pack) - adwitr
* Flying Eye Creature/ The Summoner/ Wizard Sprite - Warren Clark
* Tiny Button Push : available at soundbible.com

The game is also meant to play a 8-bit version of Thank U, Next by Ariana Grande, but I dont think i can distribute that, so you will just have to imagine it.

## Patch Notes
* 0.25
    * collisions with enemies now kill you. 
* 0.20
    * colliding with water and lava kills you
* 0.16
    * health bar "fixed". collidable ground now seperated from other collidable objects
* 0.15
    * began adding a health bar, will need to make a nicer one before its totally right
* 0.1
    * if you are pushed off screen you now die
    * resurect function works
    * you have a max num of lives now, when you run out you go to game over
    * theres a specific function now that decides if you completed the level by going far enough right
