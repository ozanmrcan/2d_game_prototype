#pragma once
#include "Tile.h"
#include <vector>
#include <SDL.h>
#include <SDL_image.h>

class MapManager
{
public:
	void loadMap(SDL_Renderer* renderer);
	std::vector<Tile> getMap();
	int getMapLength();
private:
	std::vector<Tile> map;
	int currMapLength = 0;
};