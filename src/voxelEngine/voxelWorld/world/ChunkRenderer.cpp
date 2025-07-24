#include "voxelEngine/voxelWorld/world/ChunkRenderer.h"
#include "voxelEngine/voxelWorld/world/World.h"
#include "core/Application.h"

ChunkRenderer::ChunkRenderer(World& world, Camera& camera, Shader& shader)
        : m_world(world), m_camera(camera), m_shader(shader), m_textureColorpalette() {
    m_textureColorpalette.updateFromRegistry();
    setupRenderStates();
}

void ChunkRenderer::setupRenderStates() {
    // Configuration OpenGL de base
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);

    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
}

void ChunkRenderer::buildAll() {
    m_world.forEachChunk([&](const ChunkCoord& coord, Chunk* chunk) {
        if (chunk)
            chunk->buildMesh(m_world);
    });
}

void ChunkRenderer::renderAll() {
    setupMatrices();
    bindCommonResources();

    renderOpaquePass();
    renderTransparentPass();
}

void ChunkRenderer::setupMatrices() {
    float aspectRatio = Application::get().getWindow()->getAspectRatio();
    glm::mat4 view = m_camera.getViewMatrix();
    glm::mat4 proj = m_camera.getProjectionMatrix(aspectRatio);

    m_viewProjection = proj * view; // Pré-calcul CPU
}

void ChunkRenderer::bindCommonResources() {
    m_shader.use();
    m_shader.setMat4("u_ViewProjection", m_viewProjection);

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_1D, m_textureColorpalette.getTextureID());
    m_shader.setInt("u_ColorTex", 0);
}

void ChunkRenderer::renderOpaquePass() {
    glDepthMask(GL_TRUE);
    glDisable(GL_BLEND);

    m_world.forEachChunk([&](const ChunkCoord& coord, Chunk* chunk) {
        if (chunk)
            chunk->drawOpaque(m_shader);
    });
}

void ChunkRenderer::renderTransparentPass() {
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glDepthMask(GL_FALSE);

    m_world.forEachChunk([&](const ChunkCoord& coord, Chunk* chunk) {
        if (chunk)
            chunk->drawTransparent(m_shader);
    });

    glDepthMask(GL_TRUE);
    glDisable(GL_BLEND);
}