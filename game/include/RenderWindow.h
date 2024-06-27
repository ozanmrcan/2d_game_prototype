#pragma once

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <vector>
#include <memory>

#include "GameObject.h"
#include "MapManager.h"

class RenderWindow
{
public:
	RenderWindow(const char* title, int width, int height);
	SDL_Renderer* getRenderer();
	void cleanUp();
	SDL_Texture* loadTexture(const char* path);
	void clearFrame();
	void renderObject(const std::shared_ptr<GameObject> obj, SDL_Rect camera);
	void renderTile(const Tile& tile, SDL_Rect camera);
	void renderAll(
		const std::vector<std::shared_ptr<GameObject>>& gameObjects, 
		const std::vector<Tile>& tiles, 
		SDL_Rect camera);
	void presentFrame();
private:
	SDL_Window* m_window;
	SDL_Renderer* m_renderer;
	std::vector<SDL_Texture*> m_textures;
};