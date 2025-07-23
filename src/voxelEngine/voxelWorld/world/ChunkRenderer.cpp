//
// Created by ChiroYuki on 22/07/2025.
//

#include "voxelEngine/voxelWorld/world/ChunkRenderer.h"
#include "voxelEngine/voxelWorld/world/World.h"
#include "core/Application.h"

ChunkRenderer::ChunkRenderer(World& world, Camera& camera, Shader& shader)
: m_world(world), m_camera(camera), m_shader(shader) {}

void ChunkRenderer::buildAll() {
    m_world.forEachChunk([&](const ChunkCoord& coord, Chunk* chunk) {
        if (chunk) chunk->buildMesh(m_world);
    });
}

void ChunkRenderer::renderAll() {
    auto* window = Application::getInstance().getWindow();
    float aspectRatio = window->getAspectRatio();

    glm::mat4 view = m_camera.getViewMatrix();
    glm::mat4 proj = m_camera.getProjectionMatrix(aspectRatio);

    m_shader.use();
    m_shader.setMat4("u_View", view);
    m_shader.setMat4("u_Projection", proj);

    m_world.forEachChunk([&](const ChunkCoord& coord, Chunk* chunk) {
        if (chunk) chunk->draw(m_shader);
    });
}