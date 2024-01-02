#pragma once

#include <SFML/Graphics.hpp>

class Ball
{
private:
	sf::Vector2f m_Position;
	sf::RectangleShape m_Shape;
	float m_Speed = 700.0f; // Would be nice to add some randomness to the ball's initial direction and some system that changes the speed (difficulty?)
	float m_DirectionX = .2f; // Could easily make this a vector m_Direction...
	float m_DirectionY = .2f;

public:
	Ball(float startX, float startY); // Non-default constructor initialising position
	
	sf::FloatRect getPosition();
	sf::RectangleShape getShape();

	float getXVelocity();
	void reboundSides();
	void reboundBottom();
	void reboundBatOrTop();

	void update(sf::Time deltaTime);
};