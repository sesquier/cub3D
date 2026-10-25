*This project has been created as part of the 42 curriculum by sesquier, ale-coss.*

# cub3D — A raycasting engine with miniLibX

![Language](https://img.shields.io/badge/language-C-00599C?logo=c&logoColor=white)
![Graphics](https://img.shields.io/badge/graphics-miniLibX%20%2F%20X11-informational)
![Platform](https://img.shields.io/badge/platform-Linux-lightgrey?logo=linux&logoColor=white)
![School](https://img.shields.io/badge/42-Paris-000000)

A real-time first-person 3D engine inspired by **Wolfenstein 3D**, written in C from scratch. It turns a 2D grid map into a textured 3D maze that you can walk through, using the **DDA raycasting** algorithm.

## Description

The program reads a `.cub` scene file that defines the map layout, the wall textures and the floor and ceiling colors. It then renders a navigable 3D view at 1920×1080 with the miniLibX graphics library.

For each column of the screen, a ray is cast from the player through the camera plane. The **DDA (Digital Differential Analysis)** algorithm walks the ray across the grid one cell at a time until it hits a wall. The engine then computes the perpendicular distance to that wall (which avoids the fish-eye effect), derives the height of the wall slice, and samples the correct column of the texture for the wall's orientation.

## Features

- Real-time 3D rendering with **DDA raycasting**
- **Textured walls** with a different texture for each orientation (North, South, East, West)
- Configurable floor and ceiling colors (RGB)
- **Frame-rate independent movement**: speed and rotation are scaled by the time elapsed since the last frame (delta time)
- Smooth movement, strafing and rotation, with several keys held at once
- **Collision detection** using a player radius, so the camera never clips into walls
- **Thorough scene validation**:
  - closed-map check using **flood fill**
  - invalid character detection
  - RGB range checks
  - duplicate or missing textures
  - file extension checks
  - exactly one player spawn
- Compiled with `-O3 -march=native -flto` for smooth frame rates
- Clean shutdown: every miniLibX resource and allocation is freed in the right order, checked with Valgrind

## Instructions

### Requirements

- Linux
- `cc` / `gcc` and `make`
- X11 development libraries (`libx11-dev`, `libxext-dev`)

### Build

The Linux version of miniLibX is included in the repository.

```bash
git clone git@github.com:sesquier/cub3D.git
cd cub3D
make
```

### Usage

```bash
./cub3D map/good/subject_map.cub
```

More valid maps are in `map/good/`. The invalid maps used to test the parser are in `map/bad/`.

### Map format

```
NO ./textures/north.xpm
SO ./textures/south.xpm
WE ./textures/west.xpm
EA ./textures/east.xpm

F 220,100,0
C 225,30,0

        1111111111111111111111111
        1000000000110000000000001
        10110000011100000E0000001
        1001000000000000000000001
111111111011000001110000000000001
...
```

- `NO`, `SO`, `WE`, `EA`: paths to the `.xpm` wall textures
- `F` / `C`: floor and ceiling colors as `R,G,B` (each between 0 and 255)
- Map characters: `0` for empty space, `1` for a wall, and `N` / `S` / `E` / `W` for the player spawn and the direction it faces
- The map must come last in the file and be fully enclosed by walls

### Controls

| Key | Action |
|-----|--------|
| `W` / `↑` | Move forward |
| `S` / `↓` | Move backward |
| `A` / `D` | Strafe left / right |
| `←` / `→` | Rotate the camera |
| `ESC` or close the window | Quit |

### Cleanup

```bash
make clean    # remove object files
make fclean   # remove object files and binary
```

## Project structure

```
includes/cub3d.h     # constants, data structures and prototypes
srcs/
├── main.c
├── parsing*.c       # .cub parsing and validation (textures, colors, map, flood fill)
├── init*.c          # miniLibX, textures, player and hooks setup
├── init_ray.c       # per-column ray setup
├── dda_loop*.c      # DDA traversal, wall distance, texture sampling
├── render.c         # frame loop and delta time
├── moves*.c         # movement, rotation, collisions
├── errors.c, utils.c
map/                 # valid and invalid test scenes
textures/            # .xpm wall textures
```

## What I learned

- The math behind raycasting: direction vectors, the camera plane, the DDA grid traversal, and why the perpendicular distance removes the fish-eye effect
- Low-level rendering: writing pixels straight into an image buffer and mapping textures onto wall slices
- Writing a strict parser that rejects every invalid case without leaking memory
- Building a real-time loop with frame-independent movement

## Authors

- **sesquier**
- **ale-coss**

## Resources

### Ray-casting references

- [Lode's Computer Graphics Tutorial — Raycasting](https://lodev.org/cgtutor/raycasting.html): the main reference for the DDA algorithm, wall distance calculation and texture mapping
- [Wolfenstein 3D source code](https://github.com/id-Software/wolf3d): the original implementation, for historical reference
- [miniLibX documentation](https://harm-smits.github.io/42docs/libs/minilibx): hooks, images and window management
- [42Paris miniLibX repo](https://github.com/42Paris/minilibx-linux): the Linux version used in this project

### AI usage

Claude (Anthropic) was used throughout this project as a guided learning tool, not as a code generator. Specifically:

- **Parsing**: AI helped identify and debug issues such as stack corruption from `take_numbers`, incorrect string comparison, and RGB validation logic — always through guided diagnosis rather than direct code generation.
- **Architecture**: AI provided theory-first explanations of ray-casting concepts (direction vectors, camera plane, DDA algorithm, texture mapping) before implementation.
- **Debugging**: AI assisted in interpreting Valgrind output and identifying the root causes of segfaults and memory leaks, particularly around MiniLibX cleanup order.
- **Code review**: AI reviewed functions for correctness, norm compliance (25-line limit, 4-argument limit), and suggested refactoring approaches which were then independently implemented.

All code was written and understood by the project authors. AI was used as a coaching tool to build genuine understanding, not to bypass the learning process.
