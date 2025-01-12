# Snake Game Example
(based on [Udacity C++ Nanodegree Program](https://www.udacity.com/course/c-plus-plus-nanodegree--nd213))<br>
The code for this repo was inspired by [this](https://codereview.stackexchange.com/questions/212296/snake-game-in-c-with-sdl) excellent StackOverflow post and set of responses.

<img src="snake_game.gif"/>

In this project, the Snake game was improved, by adding a bot snake that compete you and hinders to catch a 'food'.
Both snakes (user's and bot) update in the separate async tasks.
The game results are written to the results.txt file.

## Rubric bullets fulfilment
### README
* A README with instructions is included with the project;
* The README indicates the new features you added to the game;
* The README includes information about each rubric point addressed;

### Compiling and Testing
* The submission must compile and run without errors on the Udacity project workspace;

### Loops, Functions, I/O
* The project demonstrates an understanding of C++ functions and control structures
  * main.cpp:
      * line 9: results outputs are put into the function;
  * snake.cpp:
      * line 50: a distance to the target cell is calculated in a function;
* The project reads data from a file and process the data, or the program writes data to a file
  * main.cpp:
    * line 14-21: writing the results to the file; 
* The project uses data structures and immutable variables
  * main.cpp:
      * line 25-29: using constants from structures.h

### Object Oriented Programming
* One or more classes are added to the project with appropriate access specifiers for class members
	* snake.h:
		* line 48: added SnakeBot class, inherited from the Snake class;
* Class constructors utilize member initialization lists
	* all classes use initialization lists for their constructors;
* Overloaded functions allow the same function to operate on different parameters:
	* snake.h:
		* There are multiple constructors created for the Snake class to accept different set of parameters;
* Classes follow an appropriate inheritance hierarchy with virtual and override functions:
	* snake.h
		* class Snake uses a virtual function UpdateHead on line 39 that later gets overriden in SnakeBot class (line 54);

### Memory Management 
* The project makes use of references in function declarations:
	* snake.h:
		* line 13, 19, 40: using arguments sending by-reference;
* The project uses scope / Resource Acquisition Is Initialization (RAII) where appropriate:
	* snake.h:
		* line 36: using shared pointer that follows the Resource Acquisition Is Initialization pattern;
* The project uses move semantics to move data instead of copying it, where possible
	* main.cpp:
		* line 34: sending the controller and the renderer objects using move semantics;
* The project uses smart pointers instead of raw pointers
	* snake.h:
		* line 36: using shared pointer;

### Concurrency
* The project uses multithreading or async tasks
	* game.cpp:
		* lines 36, 40: using async tasks for Game::Update member method;
* A mutex or lock is used in the project
	* game.cpp:
		* lines 92, 105: using mutex to protect the data that is shared across multiple threads;

## Dependencies for Running Locally
This project has been built on:
* Ubuntu 22.04
* C++ standard v17
* gcc >= 11.4 (installed by default)
* cmake >= 3.22 (see the [installation instructions](https://cmake.org/resources/))
* make >= 4.3 (installed by default)
* SDL2 >= 2.0 (see the [installation instructions](https://wiki.libsdl.org/Installation))

## Basic Build Instructions

1. Clone this repo
   ```shell
   cd ~
   git clone https://github.com/cr0mwell/Snake_game.git
   ```
2. Make a build directory in the top level directory: `mkdir build && cd build`
3. Compile: `cmake .. && make`
4. Run it: `./SnakeGame`.

## CC Attribution-ShareAlike 4.0 International

Shield: [![CC BY-SA 4.0][cc-by-sa-shield]][cc-by-sa]

This work is licensed under a
[Creative Commons Attribution-ShareAlike 4.0 International License][cc-by-sa].

[![CC BY-SA 4.0][cc-by-sa-image]][cc-by-sa]

[cc-by-sa]: http://creativecommons.org/licenses/by-sa/4.0/
[cc-by-sa-image]: https://licensebuttons.net/l/by-sa/4.0/88x31.png
[cc-by-sa-shield]: https://img.shields.io/badge/License-CC%20BY--SA%204.0-lightgrey.svg