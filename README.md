*This project has been created as part of the 42 curriculum by sesquier, abedeaux.*

# cub3D — My first RayCaster with miniLibX

## Description

cub3D is a 3D game engine inspired by Wolfenstein 3D, the first true First Person Shooter in video game history. The goal is to create a realistic 3D graphical representation of the inside of a maze from a first-person perspective, using ray-casting techniques.

The program reads a `.cub` scene file that defines the map layout, wall textures, and floor/ceiling colors, then renders a navigable 3D environment in real time using the miniLibX graphics library.

## Features

- Real-time 3D rendering using the DDA ray-casting algorithm
- Textured walls with different textures depending on wall orientation (North, South, East, West)
- Configurable floor and ceiling colors via RGB values
- Smooth player movement and rotation
- Collision detection against walls
- Robust map validation: closed map detection via flood fill, invalid character detection, RGB range checking

## Instructions

### Requirements

- Linux
- GCC
- make
- X11 development libraries (`libx11-dev`, `libxext-dev`)

### Installation

```bash
git clone git@github.com:LeBraqueurDuF/cub3D.git
cd cub3D_git
git clone https://github.com/42Paris/minilibx-linux.git
make
```

### Usage

```bash
./cub3d path/to/map.cub
```

### Map format

The `.cub` file must contain:
- Four texture paths: `NO`, `SO`, `WE`, `EA`
- Floor and ceiling colors: `F R,G,B` and `C R,G,B` (values in range 0–255)
- A valid map made of `0` (empty), `1` (wall), and one player spawn `N`/`S`/`E`/`W`

The map must be the last element in the file and must be fully enclosed by walls.

### Controls

| Key | Action |
|-----|--------|
| W / ↑ | Move forward |
| S / ↓ | Move backward |
| A | Strafe left |
| D | Strafe right |
| ← | Rotate left |
| → | Rotate right |
| ESC | Quit |

### Cleanup

```bash
make clean    # remove object files
make fclean   # remove object files and binary
```

## Resources

### Ray-casting references

- [Lode's Computer Graphics Tutorial — Raycasting](https://lodev.org/cgtutor/raycasting.html) — primary reference for the DDA algorithm, wall distance calculation, and texture mapping
- [Wolfenstein 3D source code](https://github.com/id-Software/wolf3d) — original implementation for historical reference
- [miniLibX documentation](https://harm-smits.github.io/42docs/libs/minilibx) — hooks, images, and window management
- [42Paris miniLibX repo](https://github.com/42Paris/minilibx-linux) — Linux-compatible version used in this project

### AI usage

Claude (Anthropic) was used throughout this project as a guided learning tool, not as a code generator. Specifically:

- **Parsing**: AI helped identify and debug issues such as stack corruption from `take_numbers`, incorrect string comparison, and RGB validation logic — always through guided diagnosis rather than direct code generation.
- **Architecture**: AI provided theory-first explanations of ray-casting concepts (direction vectors, camera plane, DDA algorithm, texture mapping) before implementation.
- **Debugging**: AI assisted in interpreting Valgrind output and identifying the root causes of segfaults and memory leaks, particularly around MiniLibX cleanup order.
- **Code review**: AI reviewed functions for correctness, norm compliance (25-line limit, 4-argument limit), and suggested refactoring approaches which were then independently implemented.

All code was written and understood by the project authors. AI was used as a coaching tool to build genuine understanding, not to bypass the learning process.