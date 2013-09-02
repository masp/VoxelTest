cmake_minimum_required(VERSION 2.8)

project(makeshift)
set(CMAKE_CPP_FLAGS "-Wall -std=c++11 -g")

find_package(PNG REQUIRED)
include_directories(${PNG_INCLUDE_DIR})
include_directories("/home/mark/libs/glm")
include_directories("include")

set(SOURCES "src/main.cpp" "src/world/chunk.cpp" "src/renderer/shaders/shader.cpp" "src/renderer/shaders/program.cpp" "src/input/camera.cpp" "src/renderer/graphics/mesh.cpp" "src/renderer/renderer.cpp" "src/renderer/graphics/texture.cpp" "src/renderer/graphics/batch.cpp" "src/utils/GLError.cpp")

#Initialize GLFW
include_directories(${GLFW_INCLDUE_DIRS})
link_directories(${GLFW_LIBRARY_DIRS})
add_definitions(${GLFW_CFLAGS_OTHER})

# Initialize OpenGL
find_package(OpenGL REQUIRED)
include_directories(${OpenGL_INCLUDE_DIRS})
link_directories(${OpenGL_LIBRARY_DIRS})
add_definitions(${OpenGL_DEFINITIONS})

add_definitions(${CMAKE_CPP_FLAGS})

add_executable(makeshift ${SOURCES})

target_link_libraries(makeshift ${OPENGL_LIBRARIES} ${PNG_LIBRARY} GLEW glfw3 X11 Xxf86vm Xrandr pthread Xi rt) 
