#pragma once

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <vector>
#include <memory>

#include "configs.h"
#include "GameObject.h"
#include "RenderWindow.h"
#include "InputHandler.h"
#include "Player.h"

enum class GameStates { TITLE_SCREEN, GAMEPLAY, END_SCREEN };

class Game
{
public:
	Game();
	void run();	
private:
	GameStates gameState;
	std::vector<std::shared_ptr<GameObject>> gameObjects; 
	std::vector<Tile> tiles;
	std::shared_ptr<Player> player;
	RenderWindow window;
	InputHandler inputHandler;
	MapManager mapManager;
	bool isRunning;
	SDL_Rect camera;

	void handleInputs();
	void update(double deltaTime);
	void render();
	void updateCameraPos();
	std::shared_ptr<GameObject> createObject(const char* spritePath, double x, double y);
	std::shared_ptr<Player> createPlayer(const char* spritePath, double x, double y);
	void loadLevel();
	void initializeSDLSubSystems();
	void quitSDLSubSystems();
};