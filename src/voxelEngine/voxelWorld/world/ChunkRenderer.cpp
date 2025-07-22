//
// Created by ChiroYuki on 22/07/2025.
//

#include "voxelEngine/voxelWorld/world/ChunkRenderer.h"
#include "voxelEngine/voxelWorld/world/World.h"

ChunkRenderer::ChunkRenderer(World& world, Shader& shader) : m_world(world), m_shader(shader) {

}

void ChunkRenderer::buildAll() {
    m_world.forEachChunk([&](const ChunkCoord& coord, Chunk* chunk) {
        if (chunk) chunk->buildMesh(m_world);
    });
}

void ChunkRenderer::renderAll() {
    m_world.forEachChunk([&](const ChunkCoord& coord, Chunk* chunk) {
        if (chunk) {
            const ChunkMesh* mesh = chunk->getMesh();
            if (mesh) mesh->render(m_shader);
        }
    });
}