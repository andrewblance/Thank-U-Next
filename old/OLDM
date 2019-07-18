CC = g++ 
CFLAGS = -g -m64 

default: play SDL2 SDL2_IM SDL2__IM ZZ JPEG WEB MIX MIX_

LDFLAGS = -L$(PWD)/lib
LDFLAGS_L = -L$(PWD)/lib_linux
LIBS = -lz -lSDL2 -lSDL2_image -lSDL2_mixer 
SDL2 : 
	$(shell install_name_tool -change /usr/local/opt/sdl2/lib/libSDL2-2.0.0.dylib lib/libSDL2-2.0.0.dylib play)
SDL2_IM :
	 $(shell install_name_tool -change /usr/local/opt/sdl2_image/lib/libSDL2_image-2.0.0.dylib lib/libSDL2_image-2.0.0.dylib play)
SDL2__IM :
	$(shell install_name_tool -change /usr/local/opt/sdl2/lib/libSDL2-2.0.0.dylib lib/libSDL2-2.0.0.dylib lib/libSDL2_image-2.0.0.dylib)
ZZ :
	$(shell install_name_tool -change /usr/local/lib/libz.1.dylib lib/libz.1.dylib play)
JPEG: 
	$(shell install_name_tool -change /usr/local/opt/jpeg/lib/libjpeg.9.dylib lib/libjpeg.9.dylib lib/libSDL2_image-2.0.0.dylib)
WEB: 
	$(shell install_name_tool -change /usr/local/opt/webp/lib/libwebp.7.dylib lib/libwebp.7.dylib lib/libSDL2_image-2.0.0.dylib) 
MIX : 
	$(shell install_name_tool -change /usr/local/lib/libSDL2_mixer-2.0.0.dylib lib/libSDL2_mixer-2.0.0.dylib play)
MIX_ :
	$(shell install_name_tool -change /usr/local/lib/libSDL2-2.0.0.dylib lib/libSDL2-2.0.0.dylib lib/libSDL2_mixer-2.0.0.dylib)
play: main.o Game.o TextureManager.o Player.o SDLGameObject.o InputHandler.o MainMenuState.o PlayState.o \
	GameStateMachine.o MenuButton.o PauseState.o GameOverState.o AnimatedGraphic.o GameObjectFactory.o StateParser.o \
	 Level.o TileLayer.o LevelParser.o base64.o ObjectLayer.o SoundManager.o \
	 ScrollingBackground.o BetweenLevelState.o CollisionManager.o
	$(CC) $(CFLAGS) -o play -I include include/tinyxml/tinyxml.cpp include/tinyxml/tinystr.cpp include/tinyxml/tinyxmlparser.cpp include/tinyxml/tinyxmlerror.cpp Game.o main.o TextureManager.o  Player.o SDLGameObject.o InputHandler.o MainMenuState.o PlayState.o GameStateMachine.o MenuButton.o PauseState.o GameOverState.o AnimatedGraphic.o GameObjectFactory.o StateParser.o Level.o TileLayer.o LevelParser.o base64.o ObjectLayer.o  SoundManager.o ScrollingBackground.o BetweenLevelState.o CollisionManager.o $(LDFLAGS) $(LIBS)

play_linux: main.o Game.o TextureManager.o Player.o SDLGameObject.o InputHandler.o MainMenuState.o PlayState.o GameStateMachine.o MenuButton.o PauseState.o GameOverState.o AnimatedGraphic.o GameObjectFactory.o StateParser.o Level.o TileLayer.o LevelParser.o base64.o ObjectLayer.o SoundManager.o ScrollingBackground.o BetweenLevelState.o CollisionManager.o
	$(CC) $(CFLAGS) -o play -I include include/tinyxml/tinyxml.cpp include/tinyxml/tinystr.cpp include/tinyxml/tinyxmlparser.cpp include/tinyxml/tinyxmlerror.cpp Game.o main.o TextureManager.o  Player.o SDLGameObject.o InputHandler.o MainMenuState.o PlayState.o GameStateMachine.o MenuButton.o PauseState.o GameOverState.o AnimatedGraphic.o GameObjectFactory.o StateParser.o Level.o TileLayer.o LevelParser.o base64.o ObjectLayer.o SoundManager.o ScrollingBackground.o BetweenLevelState.o CollisionManager.o $(LDFLAGS_L) $(LIBS) -Wl,-rpath,$(PWD)/lib_linux
	
	
main.o: main.cpp Game.h TextureManager.h GameObject.h 
	$(CC) $(CFLAGS) -c main.cpp 
TextureManager.o: TextureManager.cpp TextureManager.h
	$(CC) $(CFLAGS) -c TextureManager.cpp  
Game.o: Game.cpp Game.h Player.h Enemy.h GameObject.h 
	$(CC) $(CFLAGS) -c Game.cpp 
Player.o: Player.cpp Player.h SDLGameObject.h
	$(CC) $(CFLAGS) -c Player.cpp 
SDLGameObject.o: SDLGameObject.cpp SDLGameObject.h GameObject.h
	$(CC) $(CFLAGS) -c SDLGameObject.cpp 
InputHandler.o: InputHandler.cpp InputHandler.h
	$(CC) $(CFLAGS) -c InputHandler.cpp
MainMenuState.o: MainMenuState.cpp MainMenuState.h
	$(CC) $(CFLAGS) -c MainMenuState.cpp 
PlayState.o: PlayState.cpp PlayState.h
	$(CC) $(CFLAGS) -c PlayState.cpp 
GameStateMachine.o: GameStateMachine.cpp GameStateMachine.h
	$(CC) $(CFLAGS) -c GameStateMachine.cpp 
MenuButton.o: MenuButton.cpp MenuButton.h
	$(CC) $(CFLAGS) -c MenuButton.cpp 
PauseState.o: PauseState.cpp PauseState.h
	$(CC) $(CFLAGS) -c PauseState.cpp
GameOverState.o: GameOverState.cpp GameOverState.h
	$(CC) $(CFLAGS) -c GameOverState.cpp 
AnimatedGraphic.o: AnimatedGraphic.cpp AnimatedGraphic.h
	$(CC) $(CFLAGS) -c AnimatedGraphic.cpp 
GameObjectFactory.o: GameObjectFactory.cpp GameObjectFactory.h
	$(CC) $(CFLAGS) -c GameObjectFactory.cpp 
StateParser.o: StateParser.cpp StateParser.h
	$(CC) $(CFLAGS) -c StateParser.cpp 
Level.o: Level.cpp Level.h
	$(CC) $(CFLAGS) -c Level.cpp 
TileLayer.o: TileLayer.cpp TileLayer.h
	$(CC) $(CFLAGS) -c TileLayer.cpp 
LevelParser.o: LevelParser.cpp LevelParser.h
	$(CC) $(CFLAGS) -c LevelParser.cpp 
base64.o: base64.cpp base64.h
	$(CC) $(CFLAGS) -c base64.cpp 
ObjectLayer.o: ObjectLayer.cpp ObjectLayer.h
	$(CC) $(CFLAGS) -c ObjectLayer.cpp
SoundManager.o: SoundManager.cpp SoundManager.h
	$(CC) $(CFLAGS) -c SoundManager.cpp
ScrollingBackground.o: ScrollingBackground.cpp ScrollingBackground.h
	$(CC) $(CFLAGS) -c ScrollingBackground.cpp
BetweenLevelState.o: BetweenLevelState.cpp BetweenLevelState.h
	$(CC) $(CFLAGS) -c BetweenLevelState.cpp
CollisionManager.o: CollisionManager.cpp CollisionManager.h
	$(CC) $(CFLAGS) -c CollisionManager.cpp
clean:
	$(RM) count *.o *~ play
