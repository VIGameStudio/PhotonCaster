# Minimum version for CMake
cmake_minimum_required(VERSION 2.8)

# Project's name
project(PhotonCaster)

# Using -std=c++11 for future development
add_definitions(-g -std=c++11)

# Add dependencies
add_subdirectory(extern)

if(CMAKE_BUILD_TYPE STREQUAL "Release")
add_definitions(-O2)
endif(CMAKE_BUILD_TYPE STREQUAL "Release")

set(SOURCE_DIR src)
set(INCLUDE_DIR include)

# Define the executable
add_executable(${PROJECT_NAME}
        ${SOURCE_DIR}/main.cpp
        ${SOURCE_DIR}/window.cpp
        ${SOURCE_DIR}/input.cpp
        ${SOURCE_DIR}/shader.cpp
        ${SOURCE_DIR}/texture.cpp
        ${SOURCE_DIR}/mesh_data.cpp
        ${SOURCE_DIR}/raycast_renderer.cpp
        ${SOURCE_DIR}/raster_renderer.cpp
        ${SOURCE_DIR}/controller.cpp
        ${SOURCE_DIR}/loader.cpp

        ${INCLUDE_DIR}/window.h
        ${INCLUDE_DIR}/input.h
        ${INCLUDE_DIR}/object.h
        ${INCLUDE_DIR}/vertex.h
        ${INCLUDE_DIR}/shader.h
        ${INCLUDE_DIR}/texture.h
        ${INCLUDE_DIR}/mesh.h
        ${INCLUDE_DIR}/mesh_data.h
        ${INCLUDE_DIR}/model.h
        ${INCLUDE_DIR}/scene.h
        ${INCLUDE_DIR}/transform.h
        ${INCLUDE_DIR}/camera.h
        ${INCLUDE_DIR}/light.h
        ${INCLUDE_DIR}/ray.h
        ${INCLUDE_DIR}/material.h
        ${INCLUDE_DIR}/sphere.h
        ${INCLUDE_DIR}/triangle.h
        ${INCLUDE_DIR}/primitives.h
        ${INCLUDE_DIR}/renderer.h
        ${INCLUDE_DIR}/raycast_renderer.h
        ${INCLUDE_DIR}/raster_renderer.h
        ${INCLUDE_DIR}/controller.h
        ${INCLUDE_DIR}/math_util.h
        ${INCLUDE_DIR}/loader.h
        ${INCLUDE_DIR}/util.h)

find_package(OpenGL REQUIRED)

# Include dirs
include_directories(
        include
        extern/glew-1.13.0/include/
        # extern/SDL2-2.0.4/include
        extern/glfw-3.1.2/include/GLFW/
        extern/glm-0.9.2.7
        # extern/glm-0.9.8.1
        extern/freetype-2.6.3/include/
        extern/soil/src/)

# Link libraries
target_link_libraries(
        ${PROJECT_NAME}
        ${OPENGL_LIBRARY}
        glew
        # SDL2
        glfw
        assimp
        soil
        freetype)
