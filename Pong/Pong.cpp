#pragma once

#include "Bat.h"
#include "Ball.h"
#include <sstream>
#include <cstdlib>
#include <SFML/Graphics.hpp>

int main()
{
	sf::VideoMode vm(1920, 1080);
	sf::RenderWindow window(vm, "Pong", sf::Style::Default);

	int score = 0;
	int lives = 3;

	// GameObjects
	Bat bat(1920 / 2, 1080 - 20);
	Ball ball(1920 / 2, 0);
	
	// HUD
	sf::Text hud;
	sf::Font font;
	font.loadFromFile("fonts/DS-DIGIT.ttf");
	hud.setFont(font);

	hud.setCharacterSize(75);
	hud.setFillColor(sf::Color::White);
	hud.setPosition(20, 20);

	// Game Clock
	sf::Clock clock;

	while (window.isOpen())
	{
		// Player input
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				window.close(); // Quit game when window closed
			}
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
		{
			window.close(); // Quit game when player presses escape
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		{
			bat.moveLeft();
		}
		else
		{
			bat.stopLeft();
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		{
			bat.moveRight();
		}
		else
		{
			bat.stopRight();
		}

		// Update game state

		// Updating deltaTime
		sf::Time deltaTime = clock.restart();
		bat.update(deltaTime);
		ball.update(deltaTime);
		std::stringstream ss;
		ss << "Score: " << score << "\n" << "Lives: " << lives; // Update the HUD text (not sure why we do this every frame - may be more efficient to make HUD class that does this when it changes)
		hud.setString(ss.str());

		// Check if top of ball off bottom of screen (may cause issues if you want the ball to rotate)
		if (ball.getPosition().top > window.getSize().y)
		{
			ball.reboundBottom();
			lives--;

			// Reset game if run out of lives (could add fail and menu screen here)
			if (lives < 1) {
				score = 0;
				lives = 3;
			}
		}

		// Check if ball hits top wall and reward player
		if (ball.getPosition().top < 0)
		{
			ball.reboundBatOrTop();
			score++;
		}

		if (ball.getPosition().left<0 || ball.getPosition().left + ball.getPosition().width>window.getSize().x)
		{
			ball.reboundSides(); // Bounce the ball off the sides if the left/right of the ball is off the left/right of the screen respectively
		}

		if (ball.getPosition().intersects(bat.getPosition()))
		{
			ball.reboundBatOrTop();
		}

		// Issue with collision - if ball collides with the side of the paddle, it gets briefly stuck in the paddle and then falls through it
		// Second issue with collision - score is added to as if the player collided with the top when the ball is reset

		// Draw new frame
		window.clear();
		window.draw(hud);
		window.draw(bat.getShape());
		window.draw(ball.getShape());
		window.display();

	}
	return 0;
}
