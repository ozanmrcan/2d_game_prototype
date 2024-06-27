#include "MapManager.h"
#include "configs.h"

#include <fstream>
#include <string>
#include <sstream>
#include <iostream>

void MapManager::loadMap(SDL_Renderer* renderer)
{
	SDL_Texture* blueTexture = IMG_LoadTexture(renderer, "res/gfx/blueTile.png");
	SDL_Texture* brownTexture = IMG_LoadTexture(renderer, "res/gfx/brownTile.png");
	// get data from txt
	// parse it depending on int values, collidable and non collidable ones are seperate
	// i'll give game a container of all tiles. game can use it itself and give it to renderWindow
	std::ifstream file("res/data/map.txt");
	std::string line = "";
	int rowCount = 0;
	// row count
	while (getline(file, line))
	{
		rowCount++;
	}
	// return to first row
	file.clear();
	file.seekg(0);

	// column count (of the first row)
	getline(file, line);
	std::stringstream colCtr(line);
	int colCount = 0;
	while (getline(colCtr, line, ' '))
	{
		colCount++;
	}
	// return to first row
	file.clear();
	file.seekg(0);

	// row by row
	int currRow = 0;
	while (getline(file, line))
	{
		std::string tileData;
		int tileInt = 0;
		std::stringstream ss{ line };
		// through a row 
		int currCol = 0;
		while (getline(ss, tileData, ' '))
		{
			tileInt = std::stoi(tileData);
			switch (tileInt)
			{
			case 1: // blue - not collidable
				map.emplace_back(blueTexture, currCol * TILE_SIZE, currRow * TILE_SIZE, false);
				break;
			case 2: // brown - collidable
				map.emplace_back(brownTexture, currCol * TILE_SIZE, currRow * TILE_SIZE, true);
				break;
			case 3: // brown - not collidable
				map.emplace_back(brownTexture, currCol * TILE_SIZE, currRow * TILE_SIZE, false);
				break;
			}
			currCol++;
		}
		currCol = 0;
		currRow++;
	}

	currMapLength = colCount;
}

std::vector<Tile> MapManager::getMap()
{
	return map;
}

int MapManager::getMapLength()
{
	return currMapLength;
}
