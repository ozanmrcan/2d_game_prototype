#pragma once
#include "GameObject.h"

#include <SDL.h>
#include <SDL_image.h>

class Player : public GameObject
{
public:
	Player(SDL_Texture* texture, double x, double y);
	void updatePos(double deltaTime);
	void jump();
private:
	double m_gravity; // down is positive, up is negative
	double m_velY;
};