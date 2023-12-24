// Note to self -- change from dynamic to static implementation of sfml when application complete.

#include <sstream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

// John Horton recommends using namespace. I personally take Cherno's perspective and avoid namespace where I can. It is useful to know exactly where functions I call are coming from. If one uses namespace sf, then one may remove sf:: where :: is the scope resolution operator, from the script.
// using namespace sf; 

// Function declaration for...
void updateBranches(int seed);

const int NUM_BRANCHES = 6; // There will be 6 levels of branches
sf::Sprite branches[NUM_BRANCHES]; // A C-style array of 6 branch sprites
enum class side {LEFT, RIGHT, NONE}; // An enum class of type side containing possible locations for each branch (left/right of tree and not present) or the player
// NONE is first as default state for tree.
side branchPositions[NUM_BRANCHES]; // An array of side objects, one for each branch


// Main function from which execution starts
int main()
{
	// Create object vm of class VideoMode with size 1920 by 1080 
	sf::VideoMode vm(1920, 1080);

	// Create and open game window using VideoMode vm with title Timber!!!
	// At this stage, John Horton uses a third argument sf::Style::Fullscreen, however, to avoid issues with higher resolution screens, I omit this here. Alternatives include Resize and Default (see docs)
	sf::RenderWindow window(vm, "Timber",sf::Style::Default);

	// Set Up Background
	sf::Texture textureBackground; // No contructor includes loading file
	textureBackground.loadFromFile("graphics/background.png");
	sf::Sprite spriteBackground(textureBackground); // Could also use the setTexture method/member function of Sprite
	spriteBackground.setPosition(0, 0); // No constructor in SFML includes position... why?

	// Set Up Tree
	sf::Texture textureTree;
	textureTree.loadFromFile("graphics/tree.png");
	sf::Sprite spriteTree(textureTree);
	spriteTree.setPosition(810,0);

	// Set Up Tree
	sf::Texture textureBee;
	textureBee.loadFromFile("graphics/bee.png");
	sf::Sprite spriteBee(textureBee);
	spriteBee.setPosition(0, 800);

	bool isBeeMoving = false; // Use 'is' as identifier for boolean variables
	float beeSpeed = 0.0f; // Speed in pixels per second (need to modify physics by deltatime to get pixel per frame speed for use in loop)

	// Set Up Clouds - I really would prefer using a class for this and making instances. Could have a constructor fix cloud height and speed to be different
	// Could even store the constructed clouds in an array of some kind and draw from the array clouds of different heights
	sf::Texture textureCloud;
	textureCloud.loadFromFile("graphics/cloud.png");

	sf::Sprite spriteCloud1(textureCloud);
	sf::Sprite spriteCloud2(textureCloud);
	sf::Sprite spriteCloud3(textureCloud);

	spriteCloud1.setPosition(0, 0);
	spriteCloud2.setPosition(0, 250);
	spriteCloud3.setPosition(0, 500);

	bool isCloud1Moving = false;
	bool isCloud2Moving = false;
	bool isCloud3Moving = false;

	float cloud1Speed = 0.0f;
	float cloud2Speed = 0.0f;
	float cloud3Speed = 0.0f;

	sf::Clock engineClock; // SFML clock object to measure framerate

	// Time Bar Set Up
	// Make a red rectangle of height 80 and initial width/length 400 and position its horizontal centre at the centre of the screen
	sf::RectangleShape timeBar;
	float timeBarStartWidth = 400;
	float timeBarHeight = 80;
	timeBar.setSize(sf::Vector2f(timeBarStartWidth, timeBarHeight));
	timeBar.setFillColor(sf::Color::Red);
	timeBar.setPosition((1920 / 2) - timeBarStartWidth / 2, 980);

	// Make a new time object
	sf::Time gameTimeTotal; // What is this for?

	// The player begins with 6 seconds on the clock - we divide the bar into sixths accordingly
	float timeRemaining = 6.0f;
	float timeBarWidthPerSecond = timeBarStartWidth / timeRemaining;

	bool isGamePaused = true;

	// Draw HUD text
	// Text variables
	int score = 0;
	sf::Text messageText;
	sf::Text scoreText;
	sf::Font font;

	// Set Up Font
	font.loadFromFile("fonts/KOMIKAP_.ttf");
	messageText.setFont(font);
	scoreText.setFont(font);

	// Set Up Text
	messageText.setString("Press Enter to start!");
	scoreText.setString("Score = 0");
	messageText.setCharacterSize(75);
	scoreText.setCharacterSize(75);
	messageText.setFillColor(sf::Color::White);
	scoreText.setFillColor(sf::Color::White);

	// Position Text
	sf::FloatRect textRect = messageText.getLocalBounds(); // Construct a bounding the same size as the messagge text

	messageText.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f); 
	// Set new origin for the message text at the centre of the message box (top is original vertical 0, left is original horizontal 0) using bounds from textRect

	messageText.setPosition(1920 / 2.0f, 1080 / 2.0f); // Place centre of messageText at centre of screen
	scoreText.setPosition(20, 20);

	// Set Up Branches
	sf::Texture textureBranch;
	textureBranch.loadFromFile("graphics/branch.png");
	
	for (int i = 0; i < NUM_BRANCHES; i++)
	{
		branches[i].setTexture(textureBranch);
		branches[i].setPosition(-500, -500);
		branches[i].setOrigin(220, 20); // Branch origin is centre of branch
	}

	// Set Up Player
	sf::Texture texturePlayer;
	texturePlayer.loadFromFile("graphics/player.png");
	sf::Sprite spritePlayer(texturePlayer);
	spritePlayer.setPosition(580, 720);
	side playerSide = side::LEFT; 

	// Set Up Gravestone
	sf::Texture textureRip;
	textureRip.loadFromFile("graphics/rip.png");
	sf::Sprite spriteRip(textureRip);
	spriteRip.setPosition(600, 860);

	// Set Up Axe
	sf::Texture textureAxe;
	textureAxe.loadFromFile("graphics/axe.png");
	sf::Sprite spriteAxe(textureAxe);
	spriteAxe.setPosition(700, 830);

	// Line up horizontal position of axe with tree
	const float AXE_POSITION_LEFT = 700;
	const float AXE_POSITION_RIGHT = 1075;

	// Set Up Log
	sf::Texture textureLog;
	textureLog.loadFromFile("graphics/log.png");
	sf::Sprite spriteLog(textureLog);
	spriteLog.setPosition(810, 720);

	// Variables for log
	bool isLogMoving = false;
	float logSpeedX = 0;
	float logSpeedY = -500;

	// Check whether the player is currently pressing a key
	bool isGameAcceptingInput = false;

	// Load sounds into memory
	sf::SoundBuffer chopBuffer;
	chopBuffer.loadFromFile("sound/chop.wav");
	sf::Sound chop(chopBuffer); // Short for Sound chop; chop.setBuffer(chopBuffer);

	sf::SoundBuffer deathBuffer;
	deathBuffer.loadFromFile("sound/death.wav");
	sf::Sound death(deathBuffer);

	sf::SoundBuffer ootBuffer;
	ootBuffer.loadFromFile("sound/out_of_time.wav");
	sf::Sound outOfTime(ootBuffer);

	/*
	**********************************
	Game Loop
	**********************************
	*/
	while (window.isOpen())
	{
		/* 
		*******************************************
		Input Handler 
		*******************************************
		*/

		// Check whether or not a key has been released
		sf::Event event;

		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::KeyReleased && !isGamePaused) // Probably worth checking what key was released? Else the player could alternate?
			{
				isGameAcceptingInput = true;
				spriteAxe.setPosition(2000, spriteAxe.getPosition().y); // Hide axe and allow new player input
			}
		}

		// Close the window when the escape key is pressed
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
		{
			window.close();
		}
		// Unpause game if the game is paused and enter is pressed.
		if (isGamePaused && sf::Keyboard::isKeyPressed(sf::Keyboard::Return))
		{
			isGamePaused = false;

			// Reset game timers and score
			score = 0;
			timeRemaining = 6;
			engineClock.restart(); // As cloud and bee movement tied to engine clock, need to reset to prevent teleporting when game restarts (due to frame time)

			// Reset all but top branch to not present
			for (int i = 1; i < NUM_BRANCHES; i++)
			{
				branchPositions[i] = side::NONE;
			}

			// Hide Gravestone
			spriteRip.setPosition(675, 1500);

			// Reset log
			spriteLog.setPosition(810, 720);

			// Put player on left side of tree
			spritePlayer.setPosition(580, 720);

			// Hide axe
			spriteAxe.setPosition(2000, spriteAxe.getPosition().y);

			// Will want to flip the sprite using below but need to set origin to centre of sprite first
			// spritePlayer.scale(-1.0f, 1.0f);

			isGameAcceptingInput = true;
		}

		if (isGameAcceptingInput)
		{
			// Could make the content of these if blocks a function taking side as an argument?
			// Move player to right side of tree and chop (may need to edit to flip sprite etc)
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
			{
				playerSide = side::RIGHT;
				score++; 
				timeRemaining += (2 / score) + 0.15; // Add extra time based on score (increased difficulty near end)
				spriteAxe.setPosition(AXE_POSITION_RIGHT,spriteAxe.getPosition().y);
				spritePlayer.setPosition(1200, 720);

				updateBranches(score); // Use score to seed the next branch

				spriteLog.setPosition(810, 720); // Put log at base of tree
				logSpeedX = -4000;
				isLogMoving = true;

				isGameAcceptingInput = false;
				chop.play();
			}

			// Move player to left side of tree and chop
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
			{
				playerSide = side::LEFT;
				score++;
				timeRemaining += (2 / score) + 0.15;
				spriteAxe.setPosition(AXE_POSITION_LEFT, spriteAxe.getPosition().y);
				spritePlayer.setPosition(580, 720);

				updateBranches(score);
				
				spriteLog.setPosition(810, 720);
				logSpeedX = 4000;
				isLogMoving = true;
				
				isGameAcceptingInput = false;
				chop.play();
			}
		}

		/* 
		*******************************************
		Update Scene 
		*******************************************
		*/

		if (!isGamePaused)
		{
			sf::Time deltaTime = engineClock.restart(); // Store the amount of time since clock was 0 and reset the clock

			timeRemaining -= deltaTime.asSeconds(); // Calculate the amount of time remaining each frame (in seconds)
			timeBar.setSize(sf::Vector2f(timeBarWidthPerSecond * timeRemaining, timeBarHeight)); // Resize bar graphic accordingly

			// If the timer runs out pause the game and say that the game is over.
			if (timeRemaining <= 0.0f) {
				isGamePaused = true;
				messageText.setString("Out of time!! \n\Press Enter to play again!"); // Maybe find out how to do multiline text

				sf::FloatRect textRect = messageText.getLocalBounds();
				messageText.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);

				messageText.setPosition(1920 / 2.0f, 1080 / 2.0f);
				outOfTime.play();
			}

			// Update bee movement (start movement if bee not moving)
			if (!isBeeMoving) {
				srand((int)time(0));
				beeSpeed = (rand() % 200) + 200; // Number between 200 and 399 (global bee speed)

				srand((int)time(0) * 10);
				float heightBee = (rand() % 400 + 400); // Number between 400 and 799 (local bee height as initialised in block)
				spriteBee.setPosition(2000, heightBee);
				isBeeMoving = true; // Bee should begin to move
			}
			else {
				float newBeeXPosition = spriteBee.getPosition().x - (beeSpeed * deltaTime.asSeconds());
				float newBeeYPosition = spriteBee.getPosition().y + sin(newBeeXPosition / 250) / 150 + sin(newBeeXPosition / 100) / 60;
				// Add small Fourier modes to Bee Y position to make wiggle (low amplitude low frequency, high amplitude high frequency - frequencies are around 3pi and 7pi)
				spriteBee.setPosition(newBeeXPosition, newBeeYPosition);
				// Change the x position of the sprite only to move the bee right across the screen 

				if (spriteBee.getPosition().x < -100 || spriteBee.getPosition().y > 1200) {
					isBeeMoving = false; // Reset the bee if it goes off the left or bottom of screen (latter should not happen using above values, but helps when editing)
				}
			}

			// Update Cloud Movement - This is where a class with methods/member functions would be useful
			// Cloud 1
			if (!isCloud1Moving) {
				srand((int)time(0) * 10);
				// Multiply seed by different values i.e. 10 in order to guarantee different seed even if time taken very close together for different objects
				cloud1Speed = (rand() % 200);

				srand((int)time(0) * 10);
				float cloud1Height = (rand() % 150);
				spriteCloud1.setPosition(-200, cloud1Height);
				isCloud1Moving = true;
			}
			else {
				spriteCloud1.setPosition(spriteCloud1.getPosition().x + (cloud1Speed * deltaTime.asSeconds()), spriteCloud1.getPosition().y);
				// I change the lower bound in the next line to ensure the cloud is off screen (though it should be with 1920 rather than 2000 as the origin should be top left)
				if (spriteCloud1.getPosition().x > 2000) {
					isCloud1Moving = false;
				}
			}

			// Cloud 2
			if (!isCloud2Moving) {
				srand((int)time(0) * 20);
				// Multiply seed by different values i.e. 10 in order to guarantee different seed even if time taken very close together for different objects
				cloud2Speed = (rand() % 200);

				srand((int)time(0) * 20);
				float cloud2Height = (rand() % 300) - 150;
				spriteCloud2.setPosition(-200, cloud2Height);
				isCloud2Moving = true;
			}
			else {
				spriteCloud2.setPosition(spriteCloud2.getPosition().x + (cloud2Speed * deltaTime.asSeconds()), spriteCloud2.getPosition().y);
				// I change the lower bound in the next line to ensure the cloud is off screen (though it should be with 1920 rather than 2000 as the origin should be top left)
				if (spriteCloud2.getPosition().x > 2000) {
					isCloud2Moving = false;
				}
			}

			// Cloud 3
			if (!isCloud3Moving) {
				srand((int)time(0) * 30);
				// Multiply seed by different values i.e. 10 in order to guarantee different seed even if time taken very close together for different objects
				cloud3Speed = (rand() % 200);

				srand((int)time(0) * 30);
				float cloud3Height = (rand() % 450) - 150;
				spriteCloud3.setPosition(-200, cloud3Height);
				isCloud3Moving = true;
			}
			else {
				spriteCloud3.setPosition(spriteCloud3.getPosition().x + (cloud3Speed * deltaTime.asSeconds()), spriteCloud3.getPosition().y);
				// I change the lower bound in the next line to ensure the cloud is off screen (though it should be with 1920 rather than 2000 as the origin should be top left)
				if (spriteCloud3.getPosition().x > 2000) {
					isCloud3Moving = false;
				}
			}

			// Update Score Text
			std::stringstream ss;
			ss << "Score = " << score; // Concatenate the word 'score' with the integer score using a stringstream object
			scoreText.setString(ss.str()); // Cast the stringstream object to a string and set the scoreText to this value

			// Set Branch Position Based On Height
			for (int i = 0; i < NUM_BRANCHES; i++) 
			{
				float height = i * 150;
				
				if (branchPositions[i] == side::LEFT) // Might be better to use switch here with branchPositions[i] as the expression and side::... as the case
				{
					branches[i].setPosition(610, height); // Fix sprite height
					branches[i].setRotation(180); // Flip sprite
				}
				else if (branchPositions[i] == side::RIGHT)
				{
					branches[i].setPosition(1330, height);
					branches[i].setRotation(0); // Necessary if branch changes side after falling off screen
				}
				else
				{
					// Hide branches not in use (side NONE)
					branches[i].setPosition(-500, height);
				}
			}

			// Move chopped log
			if (isLogMoving)
			{
				spriteLog.setPosition(spriteLog.getPosition().x + (logSpeedX * deltaTime.asSeconds()), spriteLog.getPosition().y + (logSpeedY * deltaTime.asSeconds()));

				// Check if the log has gone off screen
				if (spriteLog.getPosition().x < -100 || spriteLog.getPosition().x >2000)
				{
					isLogMoving = false; // Reset log for next chop (may be issue as what if new log needed before last one leaves screen? Log teleports?)
					logSpeedX = 0;
					spriteLog.setPosition(810, 720); 
				}
			}

			// Check if player squashed (check if branch at lowest level is on same side as player)
			if (branchPositions[5] == playerSide)
			{
				isGamePaused = true;
				isGameAcceptingInput = false;

				spriteRip.setPosition(525, 760);
				spritePlayer.setPosition(2000, 660);
				spriteAxe.setPosition(2000, spriteAxe.getPosition().y); // Line added as axe left floating in tree near lumberjack otherwise

				messageText.setString("SQUISHED! \n\Press Enter to play again!");
				sf::FloatRect textRect = messageText.getLocalBounds();
				messageText.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f); // Turn these blocks into a function to set origin to center of sprite
				messageText.setPosition(1920 / 2.0f, 1080 / 2.0f);
				death.play();
			}
		}
		/*
		*******************************************
		Draw Scene 
		*******************************************
		*/

		window.clear(); // Clear previous frame

		// Draw assets in order - note the assets drawn later appear over the top of those drawn earlier
		window.draw(spriteBackground);
		window.draw(spriteCloud1);
		window.draw(spriteCloud2);
		window.draw(spriteCloud3);

		for (int i = 0; i < NUM_BRANCHES; i++)
		{
			window.draw(branches[i]);
		}

		window.draw(spriteTree);
		window.draw(spriteBee);

		window.draw(scoreText);

		window.draw(timeBar);

		if (isGamePaused) {
			window.draw(messageText);
		}

		window.draw(spritePlayer);
		window.draw(spriteAxe);
		window.draw(spriteLog);
		window.draw(spriteRip);


		// Display new frame
		window.display(); // Display new frame

	}

	return 0;
}

// Function controlling the branches
void updateBranches(int seed)
{
	// We want to move all of the branches down one place
	// Note branch 0 is at the top of the screen and 5 is at the bottom (there are 6 branches indexed from 0)
	// To simulate branches falling, we want to set branch j to be on the side (position) branch j-1 was on, for all 0<j=<5 

	for (int j = NUM_BRANCHES - 1; j > 0; j--)
	{
		branchPositions[j] = branchPositions[j - 1];
	}

	// Branch 0 should take a random position to simulate a new branch being added
	// We then want to animate a branch falling to replace branch 5.

	srand((int)time(0) + seed);
	int r = (rand() % 5); // 5 here makes branch only spawn 40% of time

	switch (r) {
	case 0:
		branchPositions[0] = side::LEFT;
		break;
	case 1:
		branchPositions[0] = side::RIGHT;
		break;
	default:
		branchPositions[0] = side::NONE;
		break;
	}

}

