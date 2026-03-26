# Planet Renderer

An OpenGL-based 3D planet renderer built in C++14 that generates and renders spherical terrain using tessellation shaders.

## Features

- **Spherical Cube Geometry**
  - Generates planet-like spheres by projecting a subdivided cube onto a sphere
  - Configurable radius and tessellation resolution
- **GPU Tessellation**
  - Uses tessellation control and evaluation shaders
  - Dynamic level-of-detail terrain subdivision
- **Heightmap-based Terrain**
  - Supports displacement mapping via heightmap textures
  - Realistic surface detail generation
- **First-Person Camera**
  - Fly-through camera system with WASD movement
  - Mouse look and shift for speed boost
- **Dynamic Lighting**
  - Orbiting light source around the planet surface
- **Wireframe Toggle**
  - Press `1` for wireframe view, `0` for solid fill

## Tech Stack

- **Language:** C++14
- **Graphics API:** OpenGL (with tessellation)
- **Windowing:** GLFW 3
- **GL Loader:** GLAD
- **Math:** GLM
- **Model Loading:** Assimp
- **Image Loading:** stb_image

## Controls

| Key | Action |
|-----|--------|
| `W/A/S/D` | Move forward/left/backward/right |
| `Mouse` (hold left click) | Look around |
| `Shift` | Fast movement |
| `Space` | Reset up vector |
| `1` | Wireframe mode |
| `0` | Solid mode |
| `Esc` | Quit |

## Building

1. Open `game.sln` in Visual Studio 2022
2. Set the build configuration to **Debug** or **Release** (x64)
3. Build and run with `F5`

> **Note:** All dependencies are included in the `game/dependencies/` folder.

https://github.com/user-attachments/assets/c07c7b48-91aa-4cff-8342-60a067c4227e
