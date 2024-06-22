#include <iostream>
#include "RenderWindow.h"

RenderWindow::RenderWindow(const char* title, int width, int height)
	:m_window{NULL}, m_renderer{NULL}
{
	m_window = SDL_CreateWindow(title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_SHOWN);
	if (m_window == NULL)
		std::cout << "SDL_CreateWindow failed, SDL Error: " << SDL_GetError() << std::endl;

	m_renderer = SDL_CreateRenderer(m_window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (m_renderer == NULL)
		std::cout << "SDL_CreateRenderer failed, SDL Error: " << SDL_GetError() << std::endl;

	//if (SDL_RenderSetLogicalSize(m_renderer, 1280, 720) < 0)
	//	std::cout << "SDL_RenderSetLogicalSize failed, SDL Error: " << SDL_GetError() << std::endl;

	SDL_SetRenderDrawColor(m_renderer, 0, 0, 0, 255);
}

void RenderWindow::cleanUp()
{
	SDL_DestroyWindow(m_window);
	SDL_DestroyRenderer(m_renderer);
}

// Loads texture and adds it to textures container
SDL_Texture* RenderWindow::loadTexture(const char* path)
{
	SDL_Texture* texture = NULL;
	texture = IMG_LoadTexture(m_renderer, path);
	if (texture == NULL)
		std::cout << "IMG_LoadTexture failed, SDL Error: " << SDL_GetError() << std::endl;

	return texture;
}

void RenderWindow::clearFrame()
{
	SDL_RenderClear(m_renderer);
}

void RenderWindow::renderObject(GameObject* obj)
{
	SDL_Rect src = { 0, 0, obj->getWidth(), obj->getHeight() };
	// explicit conversion required, otherwise it acts normal in 1280x720 but completely off when its 1920x1080, idk why
	SDL_Rect dst = { int(obj->getPos().x), int(obj->getPos().y), obj->getWidth(), obj->getHeight() };

	SDL_RenderCopy(m_renderer, obj->getTexture(), &src, &dst);
}

void RenderWindow::renderAll(const std::vector<GameObject*>& gameObjects)
{
	for (GameObject* obj : gameObjects)
	{
		renderObject(obj);
	}
}

void RenderWindow::presentFrame()
{
	SDL_RenderPresent(m_renderer);
}


