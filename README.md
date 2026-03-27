*This project has been created as part of the 42 curriculum by oaletham, aalkhaso.*

# cub3D

## Description

**cub3D** is a 3D maze exploration engine inspired by the legendary **Wolfenstein 3D** — the world's first true First-Person Shooter. Built entirely in C using the **raycasting** technique, cub3D renders a dynamic 3D view of a 2D map in real time from a first-person perspective.

The goal of this project is to gain practical understanding of how early 3D game engines work: casting rays from the player's viewpoint into a 2D grid to compute wall distances, and projecting them onto the screen as textured vertical slices — creating the illusion of a three-dimensional world.

**Core features include:**
- Real-time raycasting engine using the DDA (Digital Differential Analyzer) algorithm
- Textured walls with distinct North, South, East, and West textures
- Configurable floor and ceiling colors (RGB)
- Smooth first-person player movement (WASD) and rotation (arrow keys)
- Collision detection against walls
- Scene configuration via `.cub` map files

**Bonus features include:**
- Interactive doors that can be opened and closed
- Collectible coin sprites with animated frames
- Minimap overlay for top-down navigation reference
- Mouse-controlled camera rotation

---

## Instructions

### Requirements

- Linux system with an **X11** display server
- `gcc` or `clang` compiler
- `make`
- `git` (used to fetch the MinilibX library during build)
- X11 development headers (`libX11-dev`, `libXext-dev`)

### Compilation

Clone the repository and build using `make`:

```bash
git clone <repository-url>
cd cup3d_mand_bonus

# Build the mandatory version
make

# Build the bonus version (doors, coins, minimap, mouse look)
make bonus

# Clean object files
make clean

# Remove executable and objects
make fclean

# Full rebuild
make re
```

> The Makefile automatically clones and builds **MinilibX** and **libft** as dependencies.

### Execution

```bash
./cub3D <path_to_map.cub>
```

**Examples:**
```bash
./cub3D maps/42.cub
./cub3D maps/omar.cub
```

### Map File Format (`.cub`)

A valid scene description file must define textures, colors, and a map:

```
NO ./textures/wall.xpm     # North wall texture
SO ./textures/wall.xpm     # South wall texture
WE ./textures/wall.xpm     # West wall texture
EA ./textures/wall.xpm     # East wall texture

F 220,10,30                # Floor color (R,G,B)
C 225,0,150                # Ceiling color (R,G,B)

1111111111111111
1000000000000001
100N000000000001           # N = player start facing North
1111111111111111
```

- `1` — Wall
- `0` — Walkable floor
- `N` / `S` / `E` / `W` — Player spawn facing that direction
- `D` — Door (bonus only)
- `C` — Coin collectible (bonus only)

### Controls

| Key / Input        | Action                   |
|--------------------|--------------------------|
| `W` `A` `S` `D`   | Move forward/left/back/right |
| `←` `→`            | Rotate camera            |
| `Mouse`            | Rotate camera (bonus)    |
| `E`                | Open / close door (bonus)|
| `ESC`              | Exit the game            |

---

## Resources

### Raycasting & 3D Graphics

- [Lode's Raycasting Tutorial](https://lodev.org/cgtutor/raycasting.html) — The definitive guide to implementing a Wolfenstein-style raycaster in C
- [Permadi's Raycasting Tutorial](https://permadi.com/1996/05/ray-casting-tutorial-table-of-contents/) — Classic in-depth explanation of the raycasting algorithm
- [Wikipedia — Ray Casting](https://en.wikipedia.org/wiki/Ray_casting) — Overview and theory
- [Wikipedia — DDA Algorithm](https://en.wikipedia.org/wiki/Digital_differential_analyzer_(graphics_algorithm)) — DDA explained for grid traversal

### MinilibX

- [42 Paris — MinilibX Documentation](https://harm-smits.github.io/42docs/libs/minilibx) — Official documentation and API reference
- [MinilibX GitHub Repository](https://github.com/42paris/minilibx-linux) — Source code and build instructions

### C Programming

- [The C Programming Language — Kernighan & Ritchie](https://en.wikipedia.org/wiki/The_C_Programming_Language) — Foundational reference
- [cppreference.com — C Standard Library](https://en.cppreference.com/w/c) — Reference for standard C functions

---

### AI Usage

AI was used during this project in the following ways:

- **Debugging:** Helping identify subtle bugs in the raycasting math (e.g., fisheye correction, off-by-one errors in wall projection)
- **Understanding algorithms:** Clarifying how the DDA algorithm traverses a grid and how to compute wall hit distances correctly
- **Code structure guidance:** Asking for advice on how to organize the bonus features (doors, animated sprites) cleanly into the existing codebase without breaking the mandatory version
- **Error interpretation:** Pasting compiler errors and segfault traces to get fast explanations and fix suggestions

AI was not used to write complete functions or modules. It was used as a learning tool and rubber duck debugger throughout the development process.
