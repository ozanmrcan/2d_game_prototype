#include "GameObject.h"

GameObject::GameObject(SDL_Texture* texture, double x, double y)
	:m_texture{texture}, m_pos{ x, y }
{
	SDL_QueryTexture(m_texture, NULL, NULL, &m_width, &m_height);
	m_collisionBox = { int(m_pos.x), int(m_pos.y), m_width, m_height };
}

int GameObject::getWidth() const
{
	return m_width;
}

int GameObject::getHeight() const
{
	return m_height;
}

GameObject::Coordinate GameObject::getPos() const
{
	return m_pos;
}

SDL_Texture* GameObject::getTexture() const
{
	return m_texture;
}

void GameObject::setYcor(double y)
{
	this->m_pos.y = y;
}
