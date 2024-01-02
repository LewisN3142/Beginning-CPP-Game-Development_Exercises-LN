#pragma once

#include <SFML/Graphics.hpp>

class Bat {
private: 
	sf::Vector2f m_Position;
	sf::RectangleShape m_Shape; // The visible bat
	float m_Speed = 1000.0f;
	bool m_MovingRight = false;
	bool m_MovingLeft = false;

public:
	Bat(float startX, float startY); // Initialise object with initial position (constructors do not return)
	sf::FloatRect getPosition(); // Access vector position
	sf::RectangleShape getShape(); 
	void moveLeft(); 
	void moveRight();
	void stopLeft();
	void stopRight();
	void update(sf::Time deltaTime);

	// I see no declaration of the default constructor or destructor
};