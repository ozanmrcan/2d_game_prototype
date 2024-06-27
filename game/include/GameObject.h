#pragma once

#include <SDL.h>
#include <SDL_image.h>

class GameObject
{
public:
	// some of these will be virtual
	struct Coordinate { double x; double y; };
	GameObject(SDL_Texture* texture, double x, double y);
	// getters
	int getWidth() const;
	int getHeight() const;
	Coordinate getPos() const;
	SDL_Texture* getTexture() const;
	SDL_Rect getCollisionBox() const;
	// setters
	void setYcor(double y);
	void setXcor(double x);
	void updateCollisionBoxPos();

private:
	SDL_Texture* m_texture;
	Coordinate m_pos;
	int m_width, m_height;
	SDL_Rect m_collisionBox;
};