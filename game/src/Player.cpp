#include "Player.h"
#include "configs.h"
#include <iostream>

Player::Player(InputHandler& inputHandler, SDL_Texture* texture, double x, double y)
	:GameObject{ texture, x, y },
	m_gravity{ PLAYER_GRAVITY }, 
	m_velY{ 0 },
	m_velX{ MOVEMENT_SPEED },
	m_playerState{PlayerStates::Falling},
	m_inputHandler{inputHandler}
{ }

void Player::updatePos(const std::vector<Tile>& tiles, double deltaTime)
{
	// update collision box before handling horizontal collision
	this->updateCollisionBoxPos();

	// HORIZONTAL MOVEMENT (no acceleration logic here, immediate horizontal controls like hollow knight
	if (m_inputHandler.isKeyDown(SDL_SCANCODE_D))
		this->moveRightIfPossible(tiles, deltaTime);
	if (m_inputHandler.isKeyDown(SDL_SCANCODE_A))
		this->moveLeftIfPossible(tiles, deltaTime);

	// update collision box before handling vertical collision
	this->updateCollisionBoxPos();
	if (m_playerState == PlayerStates::Standing)
	{
		if (m_inputHandler.isKeyDown(SDL_SCANCODE_SPACE))
		{
			jump();
			m_playerState = PlayerStates::Jumping;
			std::cout << "Standing --> Jumping\n";
		}
		if (!onGround(tiles))
		{
			m_playerState = PlayerStates::Falling;	
			std::cout << "Standing --> Falling\n";
		}
	}
	else if (m_playerState == PlayerStates::Jumping)
	{
		this->setYcor(this->getPos().y + m_velY * deltaTime / 1000.0);
		m_velY += m_gravity * deltaTime;
		if (m_velY >= 0)
		{
			m_playerState = PlayerStates::Falling;
			std::cout << "Jumping --> Falling\n";
		}
	}
	else if (m_playerState == PlayerStates::Falling)
	{
		this->setYcor(this->getPos().y + m_velY * deltaTime / 1000.0);
		m_velY += m_gravity * deltaTime * FALLING_GRAVITY_CONSTANT; // faster when descending compared to ascending

		// spaghetti code ama yapcak bi þey yok yoksa bütün aþaðýdaki 
		// fonksiyonlarý baþtan obj deðil rect ile yazmam baya bi þeyi deðiþtirmem lazým
		for (Tile t : tiles)	
		{
				if (checkCollisionWith(t) && determineCollisionSide(t) == Direction::TOP
					&& t.isCollidable)
				{
					this->setYcor(t.collisionBox.y - this->getCollisionBox().h +1);
					m_velY = 0;
					m_playerState = PlayerStates::Standing;
					std::cout << "Falling --> Standing\n";
				}					
		}	
	}
}

void Player::jump()
{
	m_velY -= JUMP_STRENGTH;
}

bool Player::onGround(const std::vector<Tile>& tiles) const
{
	for (Tile t : tiles)
	{
			if (checkCollisionWith(t) && determineCollisionSide(t) == Direction::TOP
				&& t.isCollidable)
			{
				return true;
			}
	}
	return false;
}

bool Player::checkCollisionWith(Tile& tile) const
{
	SDL_Rect playerBox = this->getCollisionBox();
	SDL_Rect objectBox = tile.collisionBox;

	int pLeft = playerBox.x;
	int pRight = playerBox.x + playerBox.w;
	int pTop = playerBox.y;
	int pBottom = playerBox.y + playerBox.h;

	int objLeft = objectBox.x;
	int objRight = objectBox.x + objectBox.w;
	int objTop = objectBox.y;
	int objBottom = objectBox.y + objectBox.h;

	if (pRight <= objLeft)
		return false;
	if (pLeft >= objRight)
		return false;
	if (pBottom <= objTop)
		return false;
	if (pTop >= objBottom)
		return false;
	return true;
}

Direction Player::determineCollisionSide(Tile& tile) const
{
	SDL_Rect playerBox = this->getCollisionBox();	
	SDL_Rect objectBox = tile.collisionBox;

	int pLeft = playerBox.x;
	int pRight = playerBox.x + playerBox.w;
	int pTop = playerBox.y;
	int pBottom = playerBox.y + playerBox.h;

	int objLeft = objectBox.x;
	int objRight = objectBox.x + objectBox.w;
	int objTop = objectBox.y;
	int objBottom = objectBox.y + objectBox.h;

	int topDepth = abs(pBottom - objTop);
	int bottomDepth = abs(pTop - objBottom);
	int leftDepth = abs(pRight - objLeft);
	int rightDepth = abs(pLeft - objRight);

	int minDepth = std::min({ topDepth, bottomDepth, leftDepth, rightDepth });

	if (minDepth == topDepth)
		return Direction::TOP;
	if (minDepth == bottomDepth)
		return Direction::BOTTOM;	
	if (minDepth == leftDepth)
		return Direction::LEFT;	
	if (minDepth == rightDepth)
		return Direction::RIGHT;
	else
		return Direction::NONE;	
}

void Player::moveRightIfPossible(const std::vector<Tile>& tiles, double deltaTime)
{
	this->setXcor(this->getPos().x + m_velX * deltaTime);
	for (Tile t : tiles)
	{
			if (checkCollisionWith(t) && determineCollisionSide(t) == Direction::LEFT
				&& t.isCollidable)
			{
				this->setXcor(this->getPos().x - m_velX * deltaTime); // substract what you added so x doesnt change
			}
	}
}

void Player::moveLeftIfPossible(const std::vector<Tile>& tiles, double deltaTime)
{
	this->setXcor(this->getPos().x - m_velX * deltaTime);
	for (Tile t : tiles)
	{
			if (checkCollisionWith(t) && determineCollisionSide(t) == Direction::RIGHT
				&& t.isCollidable)
			{
				this->setXcor(this->getPos().x + m_velX * deltaTime); // substract what you added so x doesnt change
			}
	}
}





