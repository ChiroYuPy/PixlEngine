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
        src/utils/MeshGenerator.cpp
        src/voxelEngine/ChunkScene.cpp
        src/voxelEngine/voxelWorld/world/World.cpp
        src/voxelEngine/voxelWorld/chunk/Chunk.cpp
        src/voxelEngine/voxelWorld/voxel/VoxelArray.cpp
        src/voxelEngine/voxelWorld/voxel/VoxelType.cpp
        src/voxelEngine/CameraController.cpp
        src/voxelEngine/voxelWorld/utils/DirectionUtils.cpp
        src/voxelEngine/voxelWorld/generation/FlatTerrainGenerator.cpp
        src/core/Color.cpp
        src/utils/ColorUtils.cpp
        src/voxelEngine/voxelWorld/generation/NaturalTerrainGenerator.cpp
        src/voxelEngine/voxelWorld/chunk/ChunkMesh.cpp
        src/voxelEngine/voxelWorld/world/ChunkRenderer.cpp
        src/voxelEngine/voxelWorld/world/WorldGenerator.cpp
        src/voxelEngine/voxelWorld/world/VoxelRaycaster.cpp
        src/voxelEngine/voxelWorld/world/BlockPlacer.cpp
        src/graphics/objects/Buffer.cpp
        include/graphics/objects/Buffer.h
        src/graphics/objects/VertexArray.cpp
        include/graphics/objects/VertexArray.h
        src/voxelEngine/voxelWorld/world/TextureColorPalette.cpp
        include/voxelEngine/voxelWorld/world/TextureColorPalette.h
)

add_executable(${PROJECT_NAME} ${SOURCES} src/main.cpp)


# ------------[ libs ]------------ #
find_package(glfw3 REQUIRED) # find GLFW

target_link_libraries(${PROJECT_NAME} PRIVATE glfw) # Link GLFW


# ------------[ files ]------------ #
add_custom_target(copy_resources COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_CURRENT_SOURCE_DIR}/resources/ ${CMAKE_CURRENT_BINARY_DIR}/resources)

add_dependencies(${PROJECT_NAME} copy_resources)