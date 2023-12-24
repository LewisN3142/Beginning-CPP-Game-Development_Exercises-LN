# Beginning C++ Game Programming Second Edition by John Horton

At the recommendation of  a very helpful staff member at Rare Ltd. I have decided to work my way through the Beginning C++ Game Programming book in order to develop my programming skills specific to game development, by creating a series of small games. 
This repository will contain the exercises from this book and will be updated as I complete them. I have chosen to make this repository in order to track my progress and have made it public as a reference for those curious individuals who may want to do the same. 
A brief overview of my thought process during each project can be found below in markdown format and will eventually make their way to my personal website in PDF form, potentially with further elaboration.

For the most part, the main branch of this repository will contain the code I produced while following the formal 'solutions' to these exercises, however they may have slight deviations where I come up with ideas 'in medias res' as it were. 
A second repository entitled 'refinements' contains cleaned up versions of the code modified in accordance with proposed extensions from the book, as well as features/bug fixes I may produce myself.
Should you want to view the clean, intended solutions, they are available on the [official Packt repository](https://github.com/PacktPublishing/Beginning-Cpp-Game-Programming-Second-Edition). 

Note that while I work on these projects, they will utilise dynamic SFML, so if you wish to compile the code locally, you will need to [download SFML](https://www.sfml-dev.org/download/sfml/2.6.1/). Once you have extracted the files from the .zip folder, copy and paste them into a new folder called 'SFML' located at the root of the project directory (in the same folder as the readme/gitignore files). You may also need to set up the linker and C++ compiler appropriately, as described in John Horton's book or any other good appropriate reference, if Visual Studio Community does not do this for you. Once I have completed the projects, I hope to update to static SFML so that this is not necessary, but I will update the readme when/if this happens. Also note that the version of SFML I link to is for Visual C++17, so if you are working in Visual Studio Community, make sure that your standard is set to this if you come across any errors (VS 2019/22 Community unfortunately default to C++14 and not the newer standards).


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
