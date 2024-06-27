#include "Tile.h"
#include "configs.h"


Tile::Tile(SDL_Texture* p_texture, int x, int y, bool collidable)
	:collisionBox{ x, y, TILE_SIZE, TILE_SIZE },
	isCollidable{ collidable },
	texture{ p_texture }
{ }
