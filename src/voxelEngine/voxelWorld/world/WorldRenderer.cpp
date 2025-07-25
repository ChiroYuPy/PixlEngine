#include "voxelEngine/voxelWorld/world/WorldRenderer.h"
#include "voxelEngine/voxelWorld/world/World.h"
#include "core/Application.h"
#include "core/Logger.h"

WorldRenderer::WorldRenderer(World& world, Camera& camera, Shader& shader)
        : m_world(world), m_camera(camera), m_shader(shader), m_textureColorpalette() {
    m_textureColorpalette.updateFromRegistry();
    setupRenderStates();
}

void WorldRenderer::setupRenderStates() {
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);

    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
}

void WorldRenderer::buildAll() {
    m_world.forEachChunk([&](const ChunkCoord& coord, Chunk* chunk) {
        if (chunk)
            chunk->buildMesh(m_world);
    });
}

void WorldRenderer::renderAll() {
    setupMatrices();
    bindCommonResources();

    renderOpaquePass();
    renderTransparentPass();
}

void WorldRenderer::setupMatrices() {
    glm::mat4 view = m_camera.getViewMatrix();
    glm::mat4 proj = m_camera.getProjectionMatrix();

    m_viewProjection = proj * view; // Pré-calcul CPU
}

void WorldRenderer::bindCommonResources() {
    m_shader.Bind();
    m_shader.setMat4("u_ViewProjection", m_viewProjection);

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_1D, m_textureColorpalette.getTextureID());
    m_shader.setInt("u_ColorTex", 0);
}

void WorldRenderer::renderOpaquePass() {
    glDepthMask(GL_TRUE);
    glDisable(GL_BLEND);

    m_world.forEachChunk([&](const ChunkCoord& coord, Chunk* chunk) {
        if (chunk)
            chunk->drawOpaque(m_shader);
    });
}

void WorldRenderer::renderTransparentPass() {
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