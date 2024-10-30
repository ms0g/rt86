# RT86- Ray Tracing on 8086/MS-DOS
## Overview
RT86 is a re-implementation of ray tracing in one weekend to run on MS-DOS. The project brings modern rendering techniques into the world of 16-bit DOS systems. With RT86, you can witness fundamental concepts like ray-object intersection, reflections, and refractions – all from within a nostalgic DOS environment.

<img src="IMG/rtraced.png" alt="image" width="700" height="auto">

## Features
+ `Anti-Aliasing:` Smoothens the output by averaging multiple rays per pixel to reduce jagged edges.
+ `Refraction & Reflection:` Simulates transparent materials like glass with Snell’s Law and internal reflection. Materials scatter or reflect light based on surface properties.
+ `Defocus Blur:` Simulates depth of field by casting rays from slightly offset origins, mimicking a camera lens's behavior to create blurred backgrounds for added realism.
+ `Recursive Ray Tracing:` Supports multiple reflection and refraction bounces for lifelike visuals.
+ `Camera System:` Simulates a basic camera with a configurable viewport and field of view.
+ `Multiple Objects:` Ability to add multiple spheres with distinct materials.
+ `Fixed Palette Output:` Optimized for VGA graphics (320x200 resolution, 256 colors).
+ `Hand-Tuned Assembly Optimizations:` Highly optimized pixel writing routine for fast VRAM operations.

## How It Works

RT86 uses ray tracing techniques to render scenes by simulating the behavior of light. For each pixel, it performs:
+ Casts a ray from the camera through the pixel into the scene.
+ If a ray hits an object, it determines how the light interacts with the surface.
+ Reflection and refraction rays are recursively traced for transparency effects.
+ Multiple rays per pixel enable anti-aliasing and defocus blur.

## Prerequisites
+ Turbo C++ (>= 3.0)
+ Turbo Assembler (>= 4.1)
+ DOSBox or a real DOS computer

## Building
If you want to build `rt86` from source, you'll need Turbo C++ and the related [build tools](https://github.com/ms0g/breakout/tree/main/TOOLS/tcpp).
```bash
C:\TC\BIN>MAKE.EXE
C:\TC\BIN>RT86.EXE
```
## License

This project is licensed under the MIT License. See the LICENSE file for details.

## Credits
This project is based on [RT in One Weekend](https://raytracing.github.io/books/RayTracingInOneWeekend.html)
