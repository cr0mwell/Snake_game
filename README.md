# Snake Game Example
(based on [Udacity C++ Nanodegree Program](https://www.udacity.com/course/c-plus-plus-nanodegree--nd213))<br>
The code for this repo was inspired by [this](https://codereview.stackexchange.com/questions/212296/snake-game-in-c-with-sdl) excellent StackOverflow post and set of responses.

<img src="snake_game.gif"/>

In this project, the Snake game was improved, by adding a bot snake that compete you and hinders to catch a 'food'.
Both snakes (user's and bot) update in the separate async tasks.
The game results are written to the results.txt file.

All the changes are documented in the [changes.txt](https://github.com/cr0mwell/Snake_game/blob/main/changes.txt) file with separation by the Rubric bullets.

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