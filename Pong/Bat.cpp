#include "Bat.h"

Bat::Bat(float startX, float startY)
{
	m_Position.x = startX;
	m_Position.y = startY;
	m_Shape.setSize(sf::Vector2f(50, 5));
	m_Shape.setPosition(m_Position);

	// Page 169/170
}

sf::FloatRect Bat::getPosition()
{
	return m_Shape.getGlobalBounds(); // Get the position of the (top,bottom,left,right of the) rectangle that is the bat
}

sf::RectangleShape Bat::getShape()
{
	return m_Shape; // Get the actual shape the bat is made of
}

void Bat::moveLeft()
{
	m_MovingLeft = true; 
}

void Bat::moveRight()
{
	m_MovingRight = true; 
}

void Bat::stopLeft()
{
	m_MovingLeft = false;
}

void Bat::stopRight()
{
	m_MovingRight = false;
}

void Bat::update(sf::Time deltaTime) // The bat is responsible for updating itself
{
	if (m_MovingLeft) {
		m_Position.x -= m_Speed * deltaTime.asSeconds(); // Move bat horizontally left if bat moving left
	}
	if (m_MovingRight) {
		m_Position.x += m_Speed * deltaTime.asSeconds(); // Move bat horizontally right if bat moving right
	}
	m_Shape.setPosition(m_Position); // Move the visible sprite for the bat
}