cmake_minimum_required(VERSION 3.10)
cmake_policy(VERSION 3.10)
project(opengllearning)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)

file(GLOB INCLUDE_DIRS lib/*/include)

set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

add_subdirectory(lib/glfw)

aux_source_directory(src SRC_FILES)
file(GLOB_RECURSE HEADER_FILES "src/*.h")

include_directories(${INCLUDE_DIRS} lib/glm)
add_library(GLAD "lib/glad/src/glad.c")
add_library(STB_IMAGE "lib/stb_image/src/stb_image.c")

add_executable(app ${SRC_FILES} ${HEADER_FILES})
target_include_directories(app INTERFACE src)
target_link_libraries(app PUBLIC glfw GLAD STB_IMAGE)
install(TARGETS app DESTINATION bin)
install(FILES ${HEADER_FILES} DESTINATION include)