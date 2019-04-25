# Voxel project

Purpose : permit to render and create a voxel world using a GUI.

## Getting Started

During the ILOG courses, we had the chance to produce a software.
Interested into the graphic programming, we choosed to develop a software
to create and manipulate a voxel world.
Voxel is the contraction of volume and pixel, which means basically a cube.

### Prerequisites

We developped this on debian-based system.
You'll need to install the following packages

```
apt-get install libsdl2-dev mesa-utils libgl1-mesa-dev mesa-common-dev
```

### Compile

You just have to run the Makefile

```
make
```

## Running the program

Launch the binary file

```
./voxel
```

## How it works

For the moment the software is not finished. If you launch the program,
you'll get into a scene where you can click on the gameObjects to modify
their attributes and/or behaviors.

If you press ESC, you can switch between the scene management and the
moving of the camera.

## Built With

* [OpenGL](https://www.opengl.org/) - API for rendering 2D and 3D
* [ImGui](https://github.com/ocornut/imgui) - GUI for C++
* [TinyXML](http://www.grinninglizard.com/tinyxml/) - C++ XML parser
