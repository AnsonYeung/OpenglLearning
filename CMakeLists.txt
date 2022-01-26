cmake_minimum_required(VERSION 3.10)
cmake_policy(VERSION 3.10)
project(opengllearning)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)

# libraries
# glfw
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
add_subdirectory(lib/glfw)

# spdlog
add_subdirectory(lib/spdlog)

# glad
add_library(glad "lib/glad/src/glad.c")
target_include_directories(glad PUBLIC "lib/glad/include")

# stb_iamge
add_library(stb_image "lib/stb_image/src/stb_image.c")
target_include_directories(stb_image PUBLIC "lib/stb_image/include")

aux_source_directory(src SRC_FILES)
file(GLOB_RECURSE HEADER_FILES "src/*.h")
file(GLOB_RECURSE SHADER_FILES "res/*.frag" "res/*.frag")

add_executable(app ${SRC_FILES} ${HEADER_FILES})
# glm is header only and don't have a static library so we must include it here
target_include_directories(app PRIVATE "lib/glm")

find_package(OpenGL REQUIRED)
target_link_libraries(app PRIVATE spdlog::spdlog glfw glad stb_image OpenGL::GL)

# run target
add_custom_target(run
    COMMAND $<TARGET_FILE:app>
    DEPENDS app
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
)

# trolling install part :D
install(TARGETS app DESTINATION bin)
install(FILES ${HEADER_FILES} DESTINATION include)

# doesn't work for some reason, I don't want to touch visual studio again :/
add_compile_options($<$<CXX_COMPILER_ID:MSVC>:/MP>)
