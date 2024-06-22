#pragma once

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

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
	GameStates gameState = GameStates::TITLE_SCREEN; // change to 0 to start from main menu after implementing it
	std::vector<GameObject*> gameObjects; 
	Player* player;
	RenderWindow window;
	InputHandler inputHandler;
	bool isRunning;

	void handleInputs();
	void update(double deltaTime, Player& player);
	void render();
	GameObject createObject(const char* spritePath, double x, double y);
	Player createPlayer(const char* spritePath, double x, double y);
	void loadLevel(RenderWindow window);
	void initializeSDLSubSystems();
	void quitSDLSubSystems();
};