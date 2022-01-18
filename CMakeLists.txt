cmake_minimum_required(VERSION 3.0)
project(opengllearning)
cmake_policy(VERSION 3.0)
set(CMAKE_CXX_STANDARD 17)

file(GLOB INCLUDE_DIRS lib/*/include)

include_directories(${INCLUDE_DIRS} lib/glm src)

set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

add_subdirectory(lib/glfw)

aux_source_directory(src SRC_FILES)

add_executable(opengllearning ${SRC_FILES} lib/glad/src/glad.c lib/stb_image/src/stb_image.c)
target_link_libraries(opengllearning glfw)
