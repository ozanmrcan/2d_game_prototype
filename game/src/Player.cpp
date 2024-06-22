#include "Player.h"
#include "configs.h"

Player::Player(SDL_Texture* texture, double x, double y)
	:GameObject{ texture, x, y }, m_gravity{ PLAYER_GRAVITY }, m_velY{ 0 }
{

}

void Player::updatePos(double deltaTime)
{
	m_velY +=  m_gravity * deltaTime; // update Y velocity
	// at the moment of collision with the ground, i can do:
	// m_velY = 0; 
	// and then during the collision:
	// m_velY -= m_gravity * deltaTime;, they cancel each other so velocity stays at 0
	this->setYcor(this->getPos().y + m_velY * deltaTime / 1000.0); // update Y position
	

}

void Player::jump()
{
	m_velY -= PLAYER_JUMP_STRENGTH;
	// state change to onAir
}



