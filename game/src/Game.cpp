#include <iostream>
#include "Game.h"

void Game::run()
{
	initializeSDLSubSystems(); // !!sdl_window and sdl_renderer initialized before this line, might cause future problems!!
	
	Uint64 lastTime = SDL_GetPerformanceCounter();
	Uint64 currentTime = 0;
	double deltaTime = 0;

	loadLevel(); // more like load tiles and give them to Game
	player = createPlayer("res/gfx/player.png", 400 , LOGICAL_HEIGHT / 2 - 32);

	SDL_Event event;
	while (isRunning)
	{	
		// calculate deltaTime
		currentTime = SDL_GetPerformanceCounter();	
		deltaTime = (currentTime - lastTime) * 1000 / (double)SDL_GetPerformanceFrequency();	
		lastTime = currentTime;	

		while (SDL_PollEvent(&event)) // can do this in handleInputs() ?
		{
			if (event.type == SDL_QUIT || event.key.keysym.sym == SDLK_ESCAPE)
				isRunning = false;
		}

		switch (gameState)
		{
		case GameStates::TITLE_SCREEN:
			// logic here will be implemented with main menu implementation
			gameState = GameStates::GAMEPLAY;
			break;
		case GameStates::GAMEPLAY:
			handleInputs();
			update(deltaTime);
			render();
			break;
		}
	}

	window.cleanUp();
	quitSDLSubSystems();
}

Game::Game()
	:isRunning{ true }, 
	window{ WINDOW_TITLE, SCREEN_WIDTH, SCREEN_HEIGHT }, 
	gameState{ GameStates::TITLE_SCREEN },
	camera{ 0, 0, LOGICAL_WIDTH, LOGICAL_HEIGHT }
{ }

void Game::handleInputs()
{
	inputHandler.update();
}

void Game::update(double deltaTime)
{
	player->updatePos(tiles, deltaTime);
	updateCameraPos();
}

void Game::render()
{
	
	window.clearFrame();
	//render tiles here
	window.renderAll(gameObjects, tiles, camera);
	window.presentFrame();
}

std::shared_ptr<GameObject> Game::createObject(const char* spritePath, double x, double y)
{
	SDL_Texture* texture = window.loadTexture(spritePath);
	std::shared_ptr<GameObject> objPtr = std::make_unique<GameObject>(texture, x, y);
	gameObjects.push_back(objPtr);

	return objPtr;
}

std::shared_ptr<Player> Game::createPlayer(const char* spritePath, double x, double y) 
{
	SDL_Texture* texture = window.loadTexture(spritePath);
	std::shared_ptr<Player> playerPtr = std::make_shared<Player>(inputHandler, texture, x, y);
	gameObjects.push_back(playerPtr);

	return playerPtr;
}

void Game::updateCameraPos()
{
	//if (player->getPos().x < camera.x + camera.w / 4.0)
	//{
	//	camera.x = int(player->getPos().x + player->getWidth() / 2.0 - camera.w / 4.0);
	//}
	//else if (player->getPos().x > camera.x + 3.0 * camera.w / 4.0)
	//{
	//	camera.x = int(player->getPos().x + player->getWidth() / 2.0 - 3 * camera.w / 4.0);
	//}
	camera.x = int(player->getPos().x + player->getWidth() / 2.0 - LOGICAL_WIDTH / 2.0);
	camera.y = int(player->getPos().y + player->getHeight() / 2.0 - LOGICAL_HEIGHT / 2.0);
}

// placeholder 
void Game::loadLevel()
{
	// TERRIBLE COUPLING BUT EH
	mapManager.loadMap(window.getRenderer());
	tiles = mapManager.getMap();
}

void Game::initializeSDLSubSystems()
{
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
		std::cout << "SDL_Init failed, SDL Error: " << SDL_GetError() << std::endl;
	if (!IMG_Init(IMG_INIT_PNG))
		std::cout << "IMG_Init failed, SDL Error: " << SDL_GetError() << std::endl;
	if (TTF_Init() == -1)
		std::cout << "TTF_Init failed, SDL Error: " << SDL_GetError() << std::endl;
}

void Game::quitSDLSubSystems()
{
	SDL_Quit();
	IMG_Quit();
	TTF_Quit();
}


