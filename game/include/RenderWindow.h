#pragma once

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <vector>
#include "GameObject.h"

class RenderWindow
{
public:
	RenderWindow(const char* title, int width, int height);
	void cleanUp();
	SDL_Texture* loadTexture(const char* path);
	void clearFrame();
	void renderObject(GameObject* obj);
	void renderAll(const std::vector<GameObject*>& gameObjects);
	void presentFrame();
private:
	SDL_Window* m_window;
	SDL_Renderer* m_renderer;
	std::vector<SDL_Texture*> m_textures;
};