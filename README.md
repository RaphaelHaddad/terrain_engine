# Computer Graphics: Terrain Engine

## Overview
This project involves constructing a 3D scene that includes a sky, moving water, and an island. The main goals and tasks of the project include:
- Displaying a sky using 5 images and a box
- Displaying moving water
- Displaying the reflection of the sky in the water
- Loading the island using a height map
- Double texturing the island
- Placing the island in the sea (cutting the island and adding its reflection)
- Implementing an accelerating camera

## Table of Contents
1. [Introduction and Code](#introduction-and-code)
2. [Displaying a Sky](#displaying-a-sky)
3. [Displaying Moving Water](#displaying-moving-water)
4. [Displaying the Reflection of the Sky in the Water](#displaying-the-reflection-of-the-sky-in-the-water)
5. [Loading the Island Using Height Map](#loading-the-island-using-height-map)
6. [Double Texturing the Island](#double-texturing-the-island)
7. [Placing the Island in the Sea](#placing-the-island-in-the-sea)
8. [Implementing an Accelerating Camera](#implementing-an-accelerating-camera)
9. [Tutorial](#tutorial)

## Introduction and Code
### Goal of Terrain Engine Project and Motivations
This project interested me because it represents the essence of what a graphics engine is. The goal is to display a scene with a sky, moving water, and an island. The tasks involved are essential components of a graphics engine.

## Displaying a Sky
As we only have 5 images, we cannot use the traditional method of using a box. Instead, we create the sky manually using 5 faces of a cube, textured with the images. The method to remove the edges is provided in the project tutorial. The shader uses a vector uniform variable to store the textures, and an index to retrieve the corresponding texture for each face.

## Displaying Moving Water
The water is displayed on the remaining face of the cube. A timer controls the movement of the water to ensure consistent speed without lag. The speed is adjustable via a parameter in `variables.h`.

## Displaying the Reflection of the Sky in the Water
The reflection is created by drawing a reversed cube with a symmetrical transformation. Blending is enabled, and the transparency of the ocean is adjusted in the fragment shader.

## Loading the Island Using Height Map
The height map is read from a BMP file and converted into a vector of pixel color intensities. Each iteration converts the pixel to a 2D coordinate, rescales it, and uses the intensity for the height (y-coordinate). The triangle strip method is used to get the vertex indices and form triangles.

## Double Texturing the Island
Texture coordinates are computed during the vertex loop. The low-resolution general texture is supplemented with a detailed texture using multi-texturing techniques. The textures are mixed in the fragment shader.

## Placing the Island in the Sea
The island is placed in the sea by discarding pixels below the water level in the fragment shader. The reflection is created by redrawing the island with a new model matrix and cutting the upper part of the mountain.

## Implementing an Accelerating Camera
The camera class is modified to include `minimumSpeed`, `maximumSpeed`, and `acceleration` parameters. The movement speed increases towards `maximumSpeed` when the same key is pressed for several frames and resets when another key is pressed.

## Tutorial
The code is developed and tested on a MacBook Air M2. To run the model, ensure `glad`, `glfw`, and `glm-master` are in your repository. Update paths in `CMakeLists.txt` and `variables.h`.

Steps to run the project:
1. Run the main file: `./main`
2. The model will display in a 1900 by 1200 window.
3. Use the mouse to move the camera, and `WASD` keys to move. Use `R` and `F` to move up and down.
4. Press `ESC` to close the window.

You can modify the variables in `variables.h` to customize the code.

## Author
Raphael El Haddad
