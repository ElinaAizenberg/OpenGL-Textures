# OpenGL: Textures
## Overview
This project is an educational application designed to demonstrate key techniques in OpenGL, including texture mapping, combining multiple textures, and rendering a skybox. The application features a textured model of Earth that can dynamically switch between daylight and nightlight modes, with additional cloud textures. Additionaly a plane orbits around the Earth. The project emphasizes the use of shader programs for rendering, providing a comprehensive learning experience for those interested in advanced OpenGL concepts.

## Features
- **Dynamic Earth textures:** the Earth model supports two texture modes: daylight with clouds and nightlight with clouds. Users can switch between these modes pressing 1.
- **Plane animation:** a 3D plane model orbits the Earth, illustrating movement in a 3D space.
- **Skybox implementation:** The scene is enclosed within a skybox filled with stars, enhancing the visual depth and realism of the environment.
- **Shader-Based rendering:** all rendering processes, including texture mapping and skybox creation, are handled through custom shader programs, highlighting the flexibility and power of shaders in modern OpenGL.

This project serves as a practical example for those learning how to implement textures, skyboxes, and shader-based rendering in OpenGL.

## Screenshots
<image src="https://github.com/user-attachments/assets/125f10ce-63d9-42f3-bcfe-0f1b2209a6a1"  width="700">

<image src="https://github.com/user-attachments/assets/623bc817-ceb8-4242-b75c-bd73d588429d"  width="700">

## Getting Started
### Prerequisites
- Compiler that supports C++
- CMake (>= 3.10)
- OpenGL (version 3.3)
- GLFW
- GLAD 

**External libraries:**
- [Tinyobjloader](https://github.com/tinyobjloader/tinyobjloader)
- [Image writer stb](https://github.com/nothings/stb/blob/master/stb_image_write.h)

### Installation
1. Clone the repo
```
git clone https://github.com/ElinaAizenberg/OpenGL-Textures
cd OpenGL-Textures
```

2. In CMakeLists.txt update the path to the folder with external libraries
```
#TODO Specify the directory where imgui and other libraries are located
set(EXTERNAL_LIB_DIR /path_to_directory/libs)
```
Go to the [GLAD website](http://glad.dav1d.de/):
1. select language **C++**;
2. in the API section select an **OpenGL version 3.3**;
3. set the profile to **Core**;
4. select **Generate a loader**;
5. generate the resulting library files.
```
#TODO Specify the directory where glad files are located
set(GLAD /path_to_directory/glad)
```

3. Build project
```
mkdir build
cd build
cmake ..
make
```

4. Run project
```
./project_4
```


