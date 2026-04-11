*This project has been created as part of the 42 curriculum by [YOUR_USER_NAME].*

# cub3D — My First RayCaster with miniLibX

## Description

**cub3D** is a 3D maze exploration game inspired by the legendary [Wolfenstein 3D](https://en.wikipedia.org/wiki/Wolfenstein_3D), widely considered the world's first successful FPS. The project is developed as part of the 42 School curriculum and serves as a fundamental introduction to the technique of ray-casting.

The goal is to build a functional first-person 3D engine from scratch using only the **miniLibX** graphics library and the **C** programming language. The engine transforms a 2D map grid into a pseudo-3D perspective by calculating the distance from the player to the walls in real-time.

### Key Features

- **DDA Ray-Casting**: Implements the Digital Differential Analysis algorithm for efficient wall detection and rendering.
- **Textured Walls**: Loads and renders distinct XPM textures for each cardinal wall orientation (North, South, East, West).
- **Configurable Environment**: Floor and ceiling colors are read from the map configuration file as RGB values.
- **Smooth Interaction**: Handles movement, rotation, and simultaneous key presses for a low-latency gameplay experience.
- **Robust Map Validation**: A thorough parsing process validates the `.cub` file format, ensures the map is fully enclosed by walls, and checks for valid character placements.
- **Memory Management**: Exits cleanly on `ESC` or when the window's close button is pressed, ensuring all allocated memory is properly freed.

---

## Instructions

### Requirements

- **OS**: Linux or macOS.
- **Compiler**: `gcc` or `clang` with `-Wall -Wextra -Werror`.
- **Dependencies**: miniLibX (`mlx`) and its required graphical dependencies (like X11).

### Compilation

Clone the repository and run:

```bash
git clone <repository-url>
cd cub3d
make
TargetDescriptionmakeCompiles the projectmake cleanRemoves object filesmake fcleanRemoves objects and the executable binarymake rePerforms a full recompilation (clean + all)ExecutionBash./cub3D <path_to_map.cub>
Example:Bash./cub3D maps/office.cub
ControlsKeyActionW, A, S, DMovement (Forward, Left, Back, Right)← / →Camera Rotation (Left/Right)ESCQuit the gameResourcesRay-Casting & 3D RenderingLode's Raycasting Tutorial — The primary technical reference used for understanding the DDA algorithm and wall texture mapping.miniLibX Documentation (42 Docs) — Official guide for using the miniLibX graphics library in the 42 curriculum.Wolfenstein 3D Mechanics — Contextual and historical information about the game that inspired this project.AI UsageAI assistance (via Claude) was utilized during the development of this project for the following specific tasks:Mathematical Concept Clarification: Used to break down the trigonometric and algebraic calculations required for the DDA ray-casting logic and camera projection.Debugging and Logic: Provided assistance in identifying potential edge cases for map validation and reviewing the overall logic of the rendering loop.Documentation: Aided in structuring and refining the technical descriptions within this README file to ensure clarity and professional standards