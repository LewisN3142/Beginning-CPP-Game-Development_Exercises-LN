# Beginning C++ Game Programming Second Edition by John Horton

At the recommendation of  a very helpful staff member at Rare Ltd. I have decided to work my way through the Beginning C++ Game Programming book in order to develop my programming skills specific to game development, by creating a series of small games. 
This repository will contain the exercises from this book and will be updated as I complete them. I have chosen to make this repository in order to track my progress and have made it public as a reference for those curious individuals who may want to do the same. 
A brief overview of my thought process during each project can be found below in markdown format and will eventually make their way to my personal website in PDF form, potentially with further elaboration.

For the most part, the main branch of this repository will contain the code I produced while following the formal 'solutions' to these exercises, however they may have slight deviations where I come up with ideas 'in medias res' as it were. 
A second repository entitled 'refinements' contains cleaned up versions of the code modified in accordance with proposed extensions from the book, as well as features/bug fixes I may produce myself.
Should you want to view the clean, intended solutions, they are available on the [official Packt repository](https://github.com/PacktPublishing/Beginning-Cpp-Game-Programming-Second-Edition). 

Note that while I work on these projects, they will utilise dynamic SFML, so if you wish to compile the code locally, you will need to [download SFML](https://www.sfml-dev.org/download/sfml/2.6.1/). Once you have extracted the files from the .zip folder, copy and paste them into a new folder called 'SFML' located at the root of the project directory (in the same folder as the readme/gitignore files). You may also need to set up the linker and C++ compiler appropriately, as described in John Horton's book or any other good appropriate reference, if Visual Studio Community does not do this for you. Once I have completed the projects, I hope to update to static SFML so that this is not necessary, but I will update the readme when/if this happens. Also note that the version of SFML I link to is for Visual C++17, so if you are working in Visual Studio Community, make sure that your standard is set to this if you come across any errors (VS Community unfortunately defaults to C++14 and not the newer standards).


## Project 1 - Timber!
For the first project in this series, we create a clone of the game Timberman, where the player is tasked with chopping down a tree, while avoiding the branches falling on them from above.

The main elements of games programming that were addressed in some form during this project are:
 - Screen coordinates and sprite coordinates
 - Initialising renderWindows to display the game
 - The game loop (take input, update game due to input/physics, draw scene to screen)
 - Assigning textures and displaying graphics
 - Assigning audio and playing sounds
 - Basic RNG using srand() and rand()
 - Using deltaTime to make physics etc frame-rate independent
 - Taking user input
 - Pausing the game and menuing

The main components of games design that were addressed in this project are:
 - Animating sprites (displaying, hiding, moving)
 - Timers and clocks
 - End conditions and restarts
