cmake_minimum_required(VERSION 3.10)
cmake_policy(VERSION 3.10)
project(opengllearning)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)

set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

add_subdirectory(lib/glfw)
add_subdirectory(lib/spdlog)

aux_source_directory(src SRC_FILES)
file(GLOB_RECURSE HEADER_FILES "src/*.h")

add_library(GLAD "lib/glad/src/glad.c")
target_include_directories(GLAD PUBLIC "lib/glad/include")
add_library(STB_IMAGE "lib/stb_image/src/stb_image.c")
target_include_directories(STB_IMAGE PUBLIC "lib/stb_image/include")

configure_file(.editorconfig .editorconfig COPYONLY)

# including the header files as a hack for visual studio to recognize there are header files.
add_executable(app ${SRC_FILES} ${HEADER_FILES})
target_include_directories(app PRIVATE "lib/glm")

find_package(OpenGL REQUIRED)
target_link_libraries(app PRIVATE spdlog::spdlog glfw GLAD STB_IMAGE OpenGL::GL)

# trolling install part :D
install(TARGETS app DESTINATION bin)
install(FILES ${HEADER_FILES} DESTINATION include)

add_compile_options($<$<CXX_COMPILER_ID:MSVC>:/MP>)
