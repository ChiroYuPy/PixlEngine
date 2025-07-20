cmake_minimum_required(VERSION 3.31)
project(PixlEngine VERSION 0.0)


# ------------[ cpp params ]------------ #
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)


# ------------[ paths ]------------ #
set(PROJECT_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)
set(PROJECT_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include)
set(EXTERNAL_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/external/src)
set(EXTERNAL_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/external/include)


# ------------[ sources and headers link ]------------ #
include_directories(${PROJECT_INCLUDE_DIR} ${EXTERNAL_INCLUDE_DIR})


# Source files
set(SOURCES
        ${EXTERNAL_SOURCE_DIR}/glad.c
        ${EXTERNAL_SOURCE_DIR}/OS2.cpp
        ${EXTERNAL_SOURCE_DIR}/IMG.cpp

        src/utils/Logger.cpp
        src/core/Application.cpp
        src/graphics/Window.cpp
        src/platform/Platform.cpp
        src/graphics/Shader.cpp
        src/scene/SceneManager.cpp
        src/graphics/Renderer.cpp
        src/input/InputManager.cpp
        src/graphics/Camera.cpp
        src/graphics/Mesh.cpp
        src/utils/MeshGenerator.cpp
        src/voxelEngine/ChunkScene.cpp
        src/voxelEngine/voxelWorld/world/VoxelWorld.cpp
        include/voxelEngine/voxelWorld/world/VoxelWorld.h
        src/voxelEngine/voxelWorld/chunk/VoxelChunk.cpp
        include/voxelEngine/voxelWorld/chunk/VoxelChunk.h
        src/voxelEngine/voxelWorld/chunk/IVoxelStorage.cpp
        include/voxelEngine/voxelWorld/chunk/IVoxelStorage.h
        src/voxelEngine/voxelWorld/world/IChunkStorage.cpp
        include/voxelEngine/voxelWorld/world/IChunkStorage.h
        src/voxelEngine/voxelWorld/storage/DenseVoxelStorage.cpp
        include/voxelEngine/voxelWorld/storage/DenseVoxelStorage.h
        src/voxelEngine/voxelWorld/storage/MapChunkStorage.cpp
        include/voxelEngine/voxelWorld/storage/MapChunkStorage.h
        src/voxelEngine/voxelWorld/voxel/Voxel.cpp
        include/voxelEngine/voxelWorld/voxel/Voxel.h
        src/voxelEngine/voxelWorld/voxel/VoxelType.cpp
        include/voxelEngine/voxelWorld/voxel/VoxelType.h
        src/voxelEngine/voxelWorld/storage/PaletteVoxelStorage.cpp
        include/voxelEngine/voxelWorld/storage/PaletteVoxelStorage.h
        src/voxelEngine/CameraController.cpp
        include/voxelEngine/CameraController.h
)

add_executable(${PROJECT_NAME} ${SOURCES} src/main.cpp)


# ------------[ libs ]------------ #
find_package(glfw3 REQUIRED) # find GLFW

target_link_libraries(${PROJECT_NAME} PRIVATE glfw) # Link GLFW


# ------------[ files ]------------ #
add_custom_target(copy_resources COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_CURRENT_SOURCE_DIR}/resources/ ${CMAKE_CURRENT_BINARY_DIR}/resources)

add_dependencies(${PROJECT_NAME} copy_resources)