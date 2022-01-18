# OpenGL Learning
Most code are slightly modified from [Learn OpenGL](https://learnopengl.com/). The main difference is that this uses a more Object-oriented approach and organized the code a bit.  
This repository is me experimenting with OpenGL and try to understand what it does.  

# Compiling
To build, first generate the required project files
```
mkdir build
cd build
cmake ..
```
Then, either a Visual Studio solution, xcode project files or a makefile will be generated based on your system.
## Visual Studio
Open the solution, then set `opengllearning` as startup project and compile.
## Makefile
run `make` to generate the binary.

# Running
The binary has to be executed with the project root as the working directory for it to find the shader files.
