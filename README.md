# Cub3d
A “realistic” 3D graphical
representation of the inside of a maze from a
first-person perspective. You have to create this
representation using the Ray-Casting principles.

## Table of Contents
- [Introduction](#introduction)
- [Requirements](#requirements)
- [Installation](#installation)
- [Usage](#usage)
- [Features](#features)
- [Controls](#controls)
- [Preview](#preview)
- [Contributors](#contributors)
- [Resources] (#resources)
- [License](#license)

## Introduction

The **cub3d** project is a simple 3D game engine that uses a 2D map to generate 3D visuals using raycasting. The goal of the project is to get familiar with computer graphics, understanding basic rendering algorithms, and working with textures, colors, and the player perspective.

## Requirements

- **MinilibX**: The project uses the MinilibX library for graphics rendering.
- **GNU Make**: For compiling the project.
- **gcc**: GNU Compiler Collection.
- **OS**: The project is built and tested on macOS and Linux distributions.
  
## Installation

1. Clone the repository:

    ```bash
    git clone https://github.com/amineichou/Cub3d.git
    cd cub3d
    ```

2. Compile the project:

    - For mandatory part :

    ```bash
    make
    ```

    - For bonus part :

    ```bash
    make bonus
    ```

   This will generate an executable named `cub3d`.

## Usage

1. Run the program by providing a map file in `.cub` format:

    - For mandatory part :

    ```bash
    ./cub3d Mandatory/maps/valid.cub
    ```

    - For bonus part :

    ```bash
    ./cub3d_bonus Bonus/maps/valid.cub
    ```

2. In the map file `.cub`:

    - `1` represents a wall.
    - `0` represents empty space.
    - `D` represents a door.
    - `S E W N `represents player position, where :
        - **S**: Player starts facing South.
        - **E**: Player starts facing East.
        - **W**: Player starts facing West.
        - **N**: Player starts facing North.

3. The map configuration also includes `texture` paths for the walls, defined as follows:

- **NO**: Path to the texture for the north-facing wall.
- **SO**: Path to the texture for the south-facing wall.
- **WE**: Path to the texture for the west-facing wall.
- **EA**: Path to the texture for the east-facing wall.

Example:

```bash
NO textures/tx_1.png
SO textures/tx_2.png
WE textures/tx_3.png
EA textures/tx_4.png
```

4. The map also defines the colors for the floor and ceiling in RGB format:

- **F**: Floor color
- **C**: Ceiling color

Example:

floor color
```bash
F 16, 16, 255
```
ceiling color
```bash
C 135, 206 , 235
```

## Features

- `Raycasting`: Render a 3D view of the world using a raycasting algorithm.
- `Textures`: Wall textures applied.
- `Sprites & animation`: Rendering of sprites like doors and animation like shooting.
- `Minimap`: 2D overview of the map in real-time.
- `Basic` Collision Detection: Prevents the player from moving through walls.
- `Different Map Inputs`: Custom maps can be created with .cub files.

## Controls

`W`: Move forward
`S`: Move backward
`A`: Move left
`D`: Move right
`Left Arrow`: Rotate view left
`Right Arrow`: Rotate view right
`space`: gun shoot
`ESC`: Exit the game

## Preview

![Alt text](/preview/Screen%20Shot%202024-09-07%20at%205.07.30%20PM.png "screenshot")
![Alt text](/preview/Screen%20Shot%202024-09-07%20at%205.07.50%20PM.png "screenshot")
![Alt text](/preview/Screen%20Shot%202024-09-07%20at%205.10.51%20PM.png "screenshot")

## Contributors

[Amine Ichou](https://github.com/amineichou)
[Said Karim](https://github.com/mrsaidkarim)

## Resources

[raycasting - wikipedia](https://en.wikipedia.org/wiki/Ray_casting#:~:text=Ray%20casting%20is%20the%20most,scenes%20to%20two%2Ddimensional%20images.)
[raycasting - lodev](https://lodev.org/cgtutor/raycasting.html)
[raycasting - medium](https://ismailassil.medium.com/ray-casting-c-8bfae2c2fc13)

## License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.
