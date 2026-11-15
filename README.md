# 3D Game Engine Framework (C++ / OpenGL / SFML)

A modular, object-oriented **3D Graphics & Game Engine Framework** built from scratch in Modern C++17 using OpenGL and SFML. This engine demonstrates the core low-level 3D rendering pipeline without relying on external game engines.

## Core Features

- **Window & Context Management (`Engine3D`)**: Custom game loop with delta-time synchronization, depth testing (`Z-Buffer`), and real-time projection switching between **Perspective** (`glFrustum`) and **Orthogonal** (`glOrtho`) views.
- **Indexed 3D Geometry (`Cube`, `Pyramid`, `Sphere`)**: Efficient hardware-accelerated mesh rendering using `glDrawElements` with separate Vertex, Normal, Color, and UV Texture Coordinate arrays.
- **Spatial Transformations & Hierarchy (`GameObject3D`)**: Base entity class supporting independent translation, rotation, and scaling via matrix stack isolation (`glPushMatrix` / `glPopMatrix`).
- **3D Observer / Free-Look Camera (`Camera`)**: First-person style 3D navigation with Yaw/Pitch rotation and cross-product strafing mathematics.
- **Phong Lighting & Shading (`Light`)**: Real-time dynamic light source supporting Ambient, Diffuse, and Specular components, with live toggling between **Smooth (Gouraud)** and **Flat** shading models.
- **2D Texture Mapping (`BitmapHandler`)**: Image loading via SFML and OpenGL texture binding (`GL_LINEAR`, `GL_REPEAT`) with automatic procedural checkerboard fallback generation.

## Controls

| Key | Action |
| :--- | :--- |
| **`W` / `A` / `S` / `D`** | Move camera forward, left, backward, and right |
| **`Q` / `E`** | Elevate camera up and down |
| **`Arrow Keys`** | Rotate camera view (Yaw & Pitch) |
| **`P`** | Toggle between Perspective and Orthogonal projection |
| **`L`** | Toggle Phong lighting on/off |
| **`F`** | Toggle between Smooth and Flat shading models |
| **`T`** | Toggle 2D texture mapping on scene meshes |
| **`Space`** | Pause / Resume scene animation |
| **`+` / `-`** | Increase / Decrease simulation speed |
| **`R`** | Reset camera to default position |
| **`ESC`** | Exit application |

## Project Architecture

```text
3D_Engine_Proj/
├── main.cpp               # Application entry point
├── Engine3D.hpp/.cpp      # Core engine loop, projection setup, and scene orchestration
├── Camera.hpp/.cpp        # 3D observer view matrix and movement kinematics
├── Light.hpp/.cpp         # OpenGL Phong lighting and shading model controller
├── BitmapHandler.hpp/.cpp # 2D texture loading and procedural texture generation
├── GameObject3D.hpp/.cpp  # Abstract base class for 3D transformable entities
├── Cube.hpp/.cpp          # Indexed 3D cube mesh
├── Pyramid.hpp/.cpp       # Indexed 3D square-based pyramid mesh
└── Sphere.hpp/.cpp        # Procedural UV-sphere mesh with emissive light-orb support