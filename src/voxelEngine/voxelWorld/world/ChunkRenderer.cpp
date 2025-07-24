#include "voxelEngine/voxelWorld/world/ChunkRenderer.h"
#include "voxelEngine/voxelWorld/world/World.h"
#include "core/Application.h"

ChunkRenderer::ChunkRenderer(World& world, Camera& camera, Shader& shader)
        : m_world(world), m_camera(camera), m_shader(shader), m_textureColorpalette() {
    m_textureColorpalette.updateFromRegistry();

    // État OpenGL initial
    setupRenderStates();
}

void ChunkRenderer::setupRenderStates() {
    // Configuration des états de rendu pour optimiser les commutations
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
}

void ChunkRenderer::buildAll() {
    m_world.forEachChunk([&](const ChunkCoord& coord, Chunk* chunk) {
        if (chunk) {
            chunk->buildMesh(m_world);
        }
    });
}

void ChunkRenderer::renderAll() {
    // Préparation des matrices
    setupMatrices();

    // Bind des ressources communes
    bindCommonResources();

    // Rendu en 2 passes optimisées
    renderOpaquePass();
    renderTransparentPass();
}

void ChunkRenderer::setupMatrices() {
    auto* window = Application::getInstance().getWindow();
    float aspectRatio = window->getAspectRatio();

    glm::mat4 view = m_camera.getViewMatrix();
    glm::mat4 proj = m_camera.getProjectionMatrix(aspectRatio);
    m_viewProjection = proj * view; // Pré-calcul côté CPU
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
        if (chunk) {
            chunk->drawOpaque(m_shader);
        }
    });
}

void ChunkRenderer::renderTransparentPass() {
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glDepthMask(GL_FALSE);

    // TODO: Trier les chunks par distance pour un rendu correct de la transparence
    std::vector<std::pair<float, Chunk*>> sortedChunks;
    glm::vec3 cameraPos = m_camera.getPosition();

    m_world.forEachChunk([&](const ChunkCoord& coord, Chunk* chunk) {
        if (chunk) {
            glm::vec3 chunkCenter = glm::vec3(coord.x, coord.y, coord.z) * float(VoxelArray::SIZE);
            float distance = glm::distance(cameraPos, chunkCenter);
            sortedChunks.emplace_back(distance, chunk);
        }
    });

    // Tri par distance décroissante
    std::sort(sortedChunks.begin(), sortedChunks.end(),
              [](const auto& a, const auto& b) { return a.first > b.first; });

    // Rendu des chunks triés
    for (const auto& [distance, chunk] : sortedChunks)
        chunk->drawTransparent(m_shader);

    // Restauration des états
    glDepthMask(GL_TRUE);
    glDisable(GL_BLEND);
}