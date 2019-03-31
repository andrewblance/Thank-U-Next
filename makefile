CC = g++ -std=c++14 
CFLAGS = -g -m64 

default: play
LIBS = -lz -lSDL2 -lSDL2_image -lSDL2_mixer

play: main.o Game.o TextureManager.o Player.o SDLGameObject.o InputHandler.o MainMenuState.o PlayState.o \
	GameStateMachine.o MenuButton.o PauseState.o GameOverState.o AnimatedGraphic.o GameObjectFactory.o StateParser.o \
	 Level.o TileLayer.o LevelParser.o base64.o ObjectLayer.o SoundManager.o \
	 ScrollingBackground.o BetweenLevelState.o CollisionManager.o
	$(CC) $(CFLAGS) -o play -I include include/tinyxml/tinyxml.cpp include/tinyxml/tinystr.cpp include/tinyxml/tinyxmlparser.cpp include/tinyxml/tinyxmlerror.cpp Game.o main.o TextureManager.o  Player.o SDLGameObject.o InputHandler.o MainMenuState.o PlayState.o GameStateMachine.o MenuButton.o PauseState.o GameOverState.o AnimatedGraphic.o GameObjectFactory.o StateParser.o Level.o TileLayer.o LevelParser.o base64.o ObjectLayer.o  SoundManager.o ScrollingBackground.o BetweenLevelState.o CollisionManager.o $(LIBS)

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
