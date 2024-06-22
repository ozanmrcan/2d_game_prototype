#include <iostream>
#include "Game.h"

void Game::run()
{
	initializeSDLSubSystems(); // !!sdl_window and sdl_renderer initialized before this line, might cause future problems!!
	
	Uint64 lastTime = SDL_GetPerformanceCounter();
	Uint64 currentTime = 0;
	double deltaTime = 0;

	// this will change later on, i will create everything in a loadLevel() func, might dynamically allocate too
	Player player = createPlayer("res/gfx/player.png", SCREEN_WIDTH/2 - 60, SCREEN_HEIGHT/2 - 100);	
	GameObject testFloor = createObject("res/gfx/testFloor.png", 0, SCREEN_HEIGHT - 200);
	//loadLevel();

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
			update(deltaTime, player);
			render();
			break;
		}
	}

	window.cleanUp();
	quitSDLSubSystems();
}

Game::Game()
	:isRunning{ true }, window{ WINDOW_TITLE, SCREEN_WIDTH, SCREEN_HEIGHT }, player{ NULL }
{ }

void Game::handleInputs()
{
	inputHandler.update();
	if (inputHandler.isKeyDown(SDL_SCANCODE_UP))
	{
		std::cout << "pressed up!\n";
	}
}

void Game::update(double deltaTime, Player& player)
{
	player.updatePos(deltaTime);
	if (inputHandler.isKeyDown(SDL_SCANCODE_SPACE))
		player.jump();
}

void Game::render()
{
	window.clearFrame();
	window.renderAll(gameObjects);
	window.presentFrame();
}

GameObject Game::createObject(const char* spritePath, double x, double y)
{
	SDL_Texture* texture = window.loadTexture(spritePath);
	GameObject object{ texture, x, y };
	gameObjects.push_back(&object);

	return object;
}

Player Game::createPlayer(const char* spritePath, double x, double y) 
{
	SDL_Texture* texture = window.loadTexture(spritePath);
	Player player{ texture, x, y };
	gameObjects.push_back(&player);

	return player;
}

void Game::loadLevel(RenderWindow window)
{

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


