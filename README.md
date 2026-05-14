*This project has been created as part of the 42 curriculum by makhudon and tiyang*

# cub3D

## Description

cub3D is a small 3D raycasting game written in C as part of the 42 curriculum.

The goal of the project is to understand how early 3D engines work internally by building one from scratch. This includes:

- Parsing and validating `.cub` configuration/map files
- Initializing a rendering window with MiniLibX
- Raycasting with DDA per screen column
- Wall texturing and background rendering (floor/ceiling)
- Player movement, rotation, and collision checks
- Input handling (keyboard and mouse)
- Game loop and clean resource lifecycle management

This repository also includes bonus gameplay features like minimap rendering, sprite interaction/collection, door interaction, and animations.

## Features

- Raycasting renderer with textured walls
- `.cub` map parser with validation
- WASD movement and arrow-key rotation
- Mouse look support with toggle
- Minimap (bonus)
- Door interaction (bonus)
- Collectible sprites and animation (bonus)

## Instructions

### Requirements

- Linux
- C compiler (`cc`)
- `make`
- X11 development libraries (for MiniLibX on Linux)

### Build

```bash
make
```

### Run

```bash
./cub3D maps/good.cub
```

Usage expected by the program:

```bash
./cub3D <map.cub>
```

### Controls

- `W`, `A`, `S`, `D`: move
- `Left Arrow`, `Right Arrow`: rotate camera
- Mouse movement: look around (when mouse is locked)
- `M`: toggle mouse lock
- `E`: interact with doors
- `ESC`: quit

### Clean

```bash
make clean
make fclean
make re
```

### Quick Checks

```bash
./cub3D maps/good.cub
./cub3D maps/test1.cub
./cub3D maps/map_with_door.cub
```

## Project Structure

- `src/`: core source code
- `src/parsing/`: `.cub` parsing and map validation
- `src/engine/`: raycasting, DDA, and rendering
- `src/input/`: keyboard input and movement helpers
- `src/lifecycle/`: initialization and cleanup logic
- `src/bonus/`: bonus systems (minimap, sprites, interactions, animation)
- `includes/`: project headers
- `libft/`: custom standard-library implementation
- `minilibx/`: graphics library used for rendering
- `maps/`: sample maps for testing
- `textures/`: texture assets

## Resources

Common references used while building this project:

- MiniLibX documentation and examples
- Lode Vandevenne raycasting tutorials
- Linux man pages: `open(2)`, `read(2)`, `close(2)`, `malloc(3)`, `free(3)`
- 42 subject and evaluator guidelines for `cub3D`

AI usage disclosure:

- AI was used as an assistant for code review, debugging support, and documentation drafting.
- Typical AI-assisted tasks included:
  - Explaining parser edge cases and validation paths
  - Suggesting safer cleanup flows for early-return error handling
  - Proposing reproducible run/test commands
  - Improving README clarity and project presentation
- Final architectural decisions, implementation changes, and validation were performed manually in the project environment.

## Notes

- This project is intended for educational purposes inside the 42 curriculum.
- Behavior should be validated against your school evaluator and subject requirements.
