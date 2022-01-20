# OpenGL Learning
Most code are slightly modified from [Learn OpenGL](https://learnopengl.com/). The main difference is that this uses a more Object-oriented approach and organized the code a bit.  
This repository is me experimenting with OpenGL and try to understand what it does.  

# Compiling
## Compiling for current platform
To build, first clone the repository and generate the required project files
```
git clone https://github.com/AnsonYeung/OpenglLearning.git --recursive
cd OpenglLearning
cmake -S . -B build
```
If you forgot to clone recursively, cmake will complain about `lib/glfw`, use the following command to clone the submodules
```
git submodule update --init --recursive
```
You may need to install header files for GLFW to compile. See [compiling GLFW](https://www.glfw.org/docs/latest/compile.html) for the required headers.  
On Debian and derivatives, you can use the following command to get all the dependencies.
```
sudo apt install xorg-dev
```
Then, either a Visual Studio solution, xcode project files or a makefile will be generated based on your system.
### Visual Studio
Open the solution, then set `app` as startup project and compile.
### Makefile
Use `make` to generate the binary.
## Cross-compiling on Unix for Windows
Cross compiling will static link `libgcc` and `libstdc++` as the required dll might be absent in the running environment
```
cmake -S . -B build -DCMAKE_TOOLCHAIN_FILE=cmake/x86_64-w64-mingw32.cmake ..
```
Then use `make` to generate the executable for Windows.

# Running
The binary has to be executed with the project root as the working directory for it to find the shader files.
