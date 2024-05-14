## Overview

This project is a simple space shooter game coded and designed in C++ language using SFML (Simple and Fast Multimedia Library) graphics mode. The game is inspired by classic arcade shooters where players control a spaceship to destroy enemy ships.

## Features

- Player-controlled spaceship with smooth movement. (60-120-144-240...Hz)
- Randomly generated enemy spawn positions.

## Installation

### Prerequisites

- SFML library installed on your system. You can download it from [here](https://www.sfml-dev.org/download.php).

### Building

1. Clone the repository to your local machine:
- git clone https://github.com/Zer0-Bug/Project_SpaceShooterGame-.-SFML.git

2. Navigate to the project directory:
- cd Project_SpaceShooterGame-.-SFML

3. Compile the source code using GCC or any other C++ compiler:
- gcc main.c -o space-shooter -lsfml-graphics -lsfml-window -lsfml-system


## Usage

1. Run the compiled executable:
./space-shooter

2. Use the W and S to move the spaceship.
3. Press the spacebar to fire bullets at enemy ships.
4. Avoid collisions with enemy ships.
5. Survive as long as possible.
6. If there is a collision or you fail to hit the enemy, the game is over.

## License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.
