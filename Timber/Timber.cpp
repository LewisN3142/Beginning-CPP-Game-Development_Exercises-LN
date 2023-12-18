// Timber.cpp 

#include <iostream>
#include <../../SFML/Graphics.hpp>

// John Horton recommends using namespace. I personally take Cherno's perspective and avoid namespace where I can. It is useful to know exactly where functions I call are coming from. If one uses namespace sf, then one may remove sf:: where :: is the scope resolution operator, from the script.
// using namespace sf; 

// Main function from which execution starts
int main()
{
	// Create object vm of class VideoMode with size 1920 by 1080 
	sf::VideoMode vm(1920, 1080);

	// Create and open game window using VideoMode vm
	sf::RenderWindow window(vm, "Timber!!!", sf::Style::Fullscreen);

	return 0;
}

