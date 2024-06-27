#include <iostream>
#include "RenderWindow.h"
#include "configs.h"


RenderWindow::RenderWindow(const char* title, int width, int height)
	:m_window{NULL}, m_renderer{NULL}
{
	m_window = SDL_CreateWindow(title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_SHOWN);
	if (m_window == NULL)
		std::cout << "SDL_CreateWindow failed, SDL Error: " << SDL_GetError() << std::endl;

	m_renderer = SDL_CreateRenderer(m_window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (m_renderer == NULL)
		std::cout << "SDL_CreateRenderer failed, SDL Error: " << SDL_GetError() << std::endl;

	if (SDL_RenderSetLogicalSize(m_renderer, LOGICAL_WIDTH , LOGICAL_HEIGHT) < 0)
		std::cout << "SDL_RenderSetLogicalSize failed, SDL Error: " << SDL_GetError() << std::endl;

	SDL_ShowCursor(SDL_DISABLE);
	SDL_SetRenderDrawColor(m_renderer, 30, 28, 28, 255);
}

SDL_Renderer* RenderWindow::getRenderer()
{
	return m_renderer;
}

void RenderWindow::cleanUp()
{
	SDL_DestroyWindow(m_window);
	SDL_DestroyRenderer(m_renderer);
}

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

void RenderWindow::renderObject(const std::shared_ptr<GameObject> obj, SDL_Rect camera)
{
	SDL_Rect src = { 0, 0, obj->getWidth(), obj->getHeight() };
	// explicit conversion required, otherwise it acts normal in 1280x720 but completely off when its 1920x1080, idk why
	SDL_Rect dst = { int(obj->getPos().x - camera.x), int(obj->getPos().y - camera.y), obj->getWidth(), obj->getHeight() };

	SDL_RenderCopy(m_renderer, obj->getTexture(), &src, &dst);
}

void RenderWindow::renderTile(const Tile& tile, SDL_Rect camera)
{
	SDL_Rect src = { 0, 0, tile.collisionBox.w, tile.collisionBox.h };
	// explicit conversion required, otherwise it acts normal in 1280x720 but completely off when its 1920x1080, idk why
	SDL_Rect dst = { tile.collisionBox.x - camera.x, tile.collisionBox.y - camera.y, tile.collisionBox.w, tile.collisionBox.h };

	SDL_RenderCopy(m_renderer, tile.texture, &src, &dst);
}

void RenderWindow::renderAll(const std::vector<std::shared_ptr<GameObject>>& gameObjects, const std::vector<Tile>& map, SDL_Rect camera)
{
	for (const Tile& t : map)
	{
		renderTile(t, camera);
	}
	for (const std::shared_ptr<GameObject>& obj : gameObjects)
	{
		renderObject(obj, camera);
	}
}


void RenderWindow::presentFrame()
{
	SDL_RenderPresent(m_renderer);
}

