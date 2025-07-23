#include "voxelEngine/voxelWorld/world/ChunkRenderer.h"
#include "voxelEngine/voxelWorld/world/World.h"
#include "core/Application.h"

ChunkRenderer::ChunkRenderer(World& world, Camera& camera, Shader& shader)
        : m_world(world), m_camera(camera), m_shader(shader), m_palette() {
    // Initialiser la palette depuis le registry à la construction
    m_palette.updateFromRegistry();
}

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
    auto model = glm::mat4(1.0f);

    m_shader.use();
    m_shader.setMat4("u_View", view);
    m_shader.setMat4("u_Projection", proj);
    m_shader.setMat4("u_Model", model);

    // Bind la palette de couleurs 1D sur l'unité 0
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_1D, m_palette.getTextureID());
    m_shader.setInt("u_ColorTex", 0);

    glEnable(GL_DEPTH_TEST);
    glDepthMask(GL_TRUE);
    glDisable(GL_BLEND);

    m_world.forEachChunk([&](const ChunkCoord& coord, Chunk* chunk) {
        if (chunk) chunk->drawOpaque();
    });

    m_world.forEachChunk([&](const ChunkCoord& coord, Chunk* chunk) {
        if (chunk) chunk->drawEmissive();
    });

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glDepthMask(GL_FALSE);

    m_world.forEachChunk([&](const ChunkCoord& coord, Chunk* chunk) {
        if (chunk) chunk->drawTransparent();
    });

    glDepthMask(GL_TRUE);
    glDisable(GL_BLEND);
}