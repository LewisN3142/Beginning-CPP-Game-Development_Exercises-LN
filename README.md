# Beginning C++ Game Programming Second Edition by John Horton

At the recommendation of  a very helpful staff member at Rare Ltd. I have decided to work my way through the Beginning C++ Game Programming book in order to develop my programming skills specific to game development, by creating a series of small games. 
This repository will contain the exercises from this book and will be updated as I complete them. I have chosen to make this repository in order to track my progress and have made it public as a reference for those curious individuals who may want to do the same. 
A brief overview of my thought process during each project can be found below in markdown format and will eventually make their way to my personal website in PDF form, potentially with further elaboration.

For the most part, the main branch of this repository will contain the code I produced while following the formal 'solutions' to these exercises, however they may have slight deviations where I come up with ideas 'in medias res' as it were. 
A second repository entitled 'refinements' will contain cleaned up versions of the code modified in accordance with proposed extensions from the book, as well as features/bug fixes I may produce myself.
Should you want to view the clean, intended solutions, they are available on the [official Packt repository](https://github.com/PacktPublishing/Beginning-Cpp-Game-Programming-Second-Edition). 

Note that while I work on these projects, they will utilise dynamic SFML, so if you wish to compile the code locally, you will need to [download SFML](https://www.sfml-dev.org/download/sfml/2.6.1/). Once you have extracted the files from the .zip folder, copy and paste the contents of the folder ``SFML-2.6.1`` into a new folder called ``SFML`` located at the root of the project directory (in the same folder as the readme/gitignore files). Once I have completed the projects, I hope to update to static SFML so that this step is not necessary, but I will update the readme when/if this happens. Also note that the version of SFML I link to is for Visual C++17, so if you are working in Visual Studio Community, make sure that your standard is set to this if you come across any errors (VS 2019/22 Community unfortunately default to C++14 and not the newer standards). You should now be able to open the .sln files for each of the respective projects (i.e. Pong, Timber, etc) in Visual Studio Community and run the C++ code from there. Note that the build options you will need are ``Win32`` (or x86) and ``Debug``. The linker and C++ compiler should be set up appropriately by default due to the .vcxproj file included in this repository, however if Visual Studio Community fails to read this for any reason, you may need to do this manually. I recommend following John Horton's book for this; see the chapter 'Setting up SFML.' 

Note that the executable files contained in the project folders (e.g. Pong.exe) do not update when you compile the code. Instead a new executable will be created in ``Project Title > Debug`` containing your changes. You will need to copy the ``sfml-...-2.dll`` and ``sfml-...-d.2.dll`` files contained in the project folder (e.g. the Pong folder) into the same folder as the new executable in order for the program to run.

If you simply wish to run the executable file for a given project (e.g. Pong or Timber), instead of viewing or editing the source, you will need to clone/download the executable, the ``sfml-...-2.dll``, and the ``sfml-...-d-2.dll`` files from the project folder.
The .dll and .exe files must be in the same folder and not separated into sub-folders. You can then simply run the executable to play the game. 

[![Conway's Game of Life on the Plane](https://img.youtube.com/vi/f2vLxhv_Swc/0.jpg)](https://www.youtube.com/watch?v=f2vLxhv_Swc)

Click the image to view a demo of the game Timber (opens Youtube in the current window). Note that while the demo has no sound, the game itself does.

## Project 1 - Timber!
For the first project in this series, we create a clone of the game Timberman, where the player is tasked with chopping down a tree, while avoiding the branches falling on them from above.

The main elements of games programming that were addressed in some form during this project are:
 - Screen coordinates and sprite coordinates.
 - Initialising ``renderWindow()`` to display the game.
 - The game loop (take input, update game due to input/physics, draw scene to screen).
 - Assigning textures and displaying graphics.
 - Assigning audio and playing sounds.
 - Basic RNG using ``srand()`` and ``rand()``.
 - Using deltaTime to make physics etc frame-rate independent.
 - Taking user input.
 - Pausing the game and menuing.

The main components of games design that were addressed in this project are:
 - Animating sprites (displaying, hiding, moving).
 - Timers and clocks.
 - End conditions and restarts.
 - Scoring and UI.

This game project was a relatively light introduction to C++, SFML, and interactive software as a whole and as a result was mostly straightforward, modulo debugging typos. One deviation I took from the book was to not use ``using namespace sf`` at the beginning of the code, instead electing to write ``sf::`` before each function/class in the namespace. While counterintuitive as it makes the code more cumbersome and harder to read, I believe this is a constructive decision since it may not always be the case that a given namespace can be used in a large scale project, in which case it is necessary to know which functions/classes belong to which namespace.

I also investigated the SFML documentation as I worked my way through the project and made use of a number of notational optimisations in my code. In particular, when initialising an ``sf::Sprite``, rather than naming the sprite using
``sf::Sprite spriteName;``
and then assigning the corresponding ``sf::Texture`` using 
``setTexture(textureName);``
one can instead initialise the sprite with a texture loaded, by writing
``sf::Sprite spriteName(textureName);``
which is suitable for our use-case where each sprite has only one texture. A similar constructor exists for ``sf::Sound`` in terms of ``sf::SoundBuffer``. Interestingly, there does not seem to be a ``sf::Sprite`` constructor that includes the position.

I list below some further modifications I would like to make in the refinement branch over the course of the coming weeks. Some of these add gameplay features, address visual bugs, or simply improve the appearance of the animated non-gameplay elements. Other items address code optimisations such as placing multiply used code inside functions, or creating classes/arrays of objects with multiple instances.

Game elements to add in the refinement branch:
 - FPS counter.
 - Clearer UI (semi-transparent black boxes behind text).
 - Lighter and thinner trees in background.
 - Optimise code that does not need to be executed regularly (i.e. sstream) and re-write some sections using functions/classes (i.e. an array of clouds) so that they may be reused in a more efficient way.
 - Change cloud movement to be more realistic (tie speed to height and perhaps scale them).
 - Flip player sprite when on the left side of the tree as currently faces away from the tree (need to set the origin of the sprite to centre or add a translation for this).
 - Create a partial background sprite (no sky) which the clouds can move behind to add parallax.
 - Investigate whether eventPolling can be exploited as it does not check which key is released.
 - Remove unused ``sf::Time`` object at line 84 (not sure why this was added as it is never used, perhaps to track how long the player took to die/time-out? Perhaps I could implement this feature?).

One refinement I have already made within the main branch while I was working through the book's recommended code was to make the bee's motion a little less mundane (the book simply translates the bee horizontally across the screen from right to left). Instead of this, I modified the ``y`` position of the bee by some Fourier modes (sine functions) dependent on the current ``x`` position of the bee, resulting in sinusoidal motion across the screen. I used one low amplitude, low frequency mode (``sin(x/250)/150``) and one high frequency, high amplitude mode (``sin(x/100)/60``) to add some variation. 

I also added a line of code (line 220) which restarts the ``sf::Clock engineClock`` as otherwise the bee and clouds teleport when the game is restarted after a loss, instead of continuing on their previous path. This is due to the fact that the clouds and bee are moved on each unpaused frame and their movement depends on the ``sf::Time deltaTime`` since the last frame on which they moved. If the clock is not reset when the game is restarted, the deltaTime includes the of time that has passed since the previous game ended and the game was paused, hence the sprites can move a very long distance. This extra line of code makes it so that the clouds and bee move a distance which depends only on the deltaTime since the last unpaused frame.


## Project 2 - Pong
The second project in this series is based on the classic 1972 game Pong, in particular Pong-Squash, a mid-1970s variant of pong where a single player hits a ball against the far wall of the play area. See this [youtube video](https://youtu.be/u9rNMVTN-uc?si=SLkuiy0SkmkPaGRJ) by James Channel for more information on the early Pong Home Consoles, based on the General Electric IC, on which Pong-Squash appeared.

The main elements of games programming that were addressed in this project are:
- Object oriented design (objects as instances of classes, encapsulation).
- Spawning objects of a class.
- Using member variables and methods to interact with game objects and take user input.
- Collision between game objects and between a game object and the boundary of the playable area (using intersections and object bounds).

The main components of games design that were addressed in this project are:
 - Animating sprites (displaying, hiding, moving).
 - Timers and clocks.
 - Scoring and UI.

This game project was a brief introduction to the notion of object oriented programming (a concept that I had already come across from a brief period learning Java back in secondary school), covering classes, member variables, and encapsulation. This project was also pretty straightforward, though the process of setting up visual studio community on a per-project basis is a little tedious and prone to errors (in particular, remembering to set the C++ version to that compatible with the included version of SFML). I am considering writing a cmd/bash application to do this for me, taking a ``.vcxproj`` file and SFML file path as input and editing the ``.vcxproj`` file accordingly. If I do so, I will make the file available for public use on my account here. 

While working on this project, I became aware of a number of bugs in the original code, all consequences of the fairly simplistic collision that was put in place, which I would like to address in the refinements version:
 - Firstly, it is possible for the ball to bounce off one of the side walls at an angle close to 90 degrees. Should this occur, it is then possible for the ball to collide with the side of the paddle &ndash; as the code that runs when the bat and ball intersect does not check which part of the bat the ball hits and simply reverses the ``y`` velocity of the ball, it is then possible for the ball to get stuck in the paddle for a time, oscillating up and down until it falls out the other side or otherwise escapes. This could be resolved by writing some custom collision to check which part of the bat was hit by the ball, rather than using the ``intersects()`` method of the ``sf::Sprite`` class along with the ``getPosition()`` methods of ``Bat`` and ``Ball`` to get their local bounds.
 - Secondly, the player score always increases by 1 when the ball goes out of play, off the bottom of the screen. This is due to the reset position of the ball being above the play area and the ball therefore crossing the upper boundary as it returns into play; the upper boundary of the screen has collision in place (namely the ``if(ball.getPosition().top<0)`` block beginning on line ``93``) which increases the score when the ball hits it. This could be resolved either by setting the ball to reset to the middle of the screen, or checking the direction of the ball when it hits the upper boundary.

While working on this project, I had a couple of ideas for additional features, some being more stereotypical Pong features and others being more involved. These include:
 - FPS counter
 - Change speed of the ball on each hit
 - Instantiate the ball with some random angle each time otherwise the first hit is always the same
 - Add sound effects
 - Add a pause menu and game reset button
 - Difficulty settings so the player may change the game speed and paddle size
 - Different game modes including the more standard 2-player pong
 - Basic AI for the second player
 - Add a trail behind the ball as well as a center line and visible wall
 - A game mode that has different shot-types, such as spin or smash
 - Noita-like particle physics for the paddles

It is worth discussing the last point a little, since I think a game of particle physics pong would be quite interesting. The player could build up a meter that allows them to do a series of increasingly outlandish abilities including making the ball spin, creating a wooden blockade on the court, setting fire to blockades or paddles on hit, and lastly passing through other particles. In order to set this up, however, I would need to be more familiar with the cellular automata used to create Noita's particle systems, so this may well spawn a parallel project where I investigate how this is done.





