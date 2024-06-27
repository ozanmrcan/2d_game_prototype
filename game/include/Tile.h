#pragma once
#include <SDL.h>

struct Tile
{
	Tile(SDL_Texture* p_texture, int x, int y, bool isCollidable);
	bool isCollidable;
	SDL_Rect collisionBox;
	SDL_Texture* texture;
};
