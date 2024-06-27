#pragma once
#include "GameObject.h"
#include "InputHandler.h"
#include "Tile.h"

#include <SDL.h>
#include <SDL_image.h>
#include <vector>
#include <memory>

enum class PlayerStates 
{
	Standing, // involves running too for now
	Running,
	Jumping,
	Falling
};

enum class Direction { NONE = 0, TOP, BOTTOM, LEFT, RIGHT};

class Player : public GameObject
{
public:
	Player(InputHandler& inputHandler, SDL_Texture* texture, double x, double y);
	void updatePos(const std::vector<Tile>& tiles, double deltaTime);
	void jump();
private:
	bool onGround(const std::vector<Tile>& tiles) const;
	bool checkCollisionWith(Tile& tile) const;
	Direction determineCollisionSide(Tile& tile) const;
	void moveRightIfPossible(const std::vector<Tile>& tiles, double deltaTime);
	void moveLeftIfPossible(const std::vector<Tile>& tiles, double deltaTime);
	InputHandler m_inputHandler;
	PlayerStates m_playerState;
	double m_gravity; // down is positive, up is negative
	double m_velY;
	double m_velX;
};