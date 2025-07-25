//
// Created by ChiroYuki on 20/07/2025.
//

#include "voxelEngine/voxelWorld/world/World.h"
#include "voxelEngine/voxelWorld/chunk/Chunk.h"
#include "voxelEngine/voxelWorld/generation/FlatTerrainGenerator.h"
#include "core/Logger.h"
#include "voxelEngine/voxelWorld/generation/NaturalTerrainGenerator.h"
#include <stdexcept>
#include <format>
#include <iostream>

World::World() {
    m_generator = std::make_unique<NaturalTerrainGenerator>(0);
    // m_generator = std::make_unique<FlatTerrainGenerator>(0);
}

voxel::ID World::getVoxel(int worldX, int worldY, int worldZ) const {
    ChunkCoord chunkCoord = toChunkCoord(worldX, worldY, worldZ);
    glm::ivec3 localPos = toLocalCoord(worldX, worldY, worldZ);

    auto it = m_chunks.find(chunkCoord);
    if (it != m_chunks.end())
        return it->second->get(localPos.x, localPos.y, localPos.z);

    return voxel::AIR; // Air par défaut
}

void World::setVoxel(int worldX, int worldY, int worldZ, voxel::ID ID) {
    ChunkCoord chunkCoord = toChunkCoord(worldX, worldY, worldZ);
    glm::ivec3 localPos = toLocalCoord(worldX, worldY, worldZ);

    Chunk* chunk = getOrCreateChunk(chunkCoord.x, chunkCoord.y, chunkCoord.z);
    if (chunk) {
        chunk->set(localPos.x, localPos.y, localPos.z, ID);
        chunk->markDirty();
    }
}

voxel::ID World::getVoxel(const glm::ivec3& worldPos) const {
    return getVoxel(worldPos.x, worldPos.y, worldPos.z);
}


void World::setVoxel(const glm::ivec3& worldPos, voxel::ID type) {
    setVoxel(worldPos.x, worldPos.y, worldPos.z, type);
}

Chunk* World::getOrCreateChunk(int x, int y, int z) {
    ChunkCoord chunkCoord = {x, y, z};
    auto it = m_chunks.find(chunkCoord);
    if (it != m_chunks.end())
        return it->second.get();

    auto newChunk = std::make_unique<Chunk>(chunkCoord);
    Chunk* ptr = newChunk.get();
    m_chunks.emplace(chunkCoord, std::move(newChunk));
    return ptr;
}

Chunk* World::getOrCreateChunk(const glm::ivec3& pos) {
    return getOrCreateChunk(pos.x, pos.y, pos.z);
}

Chunk* World::getChunk(int x, int y, int z) {
    ChunkCoord chunkCoord = {x, y, z};
    auto it = m_chunks.find(chunkCoord);
    if (it != m_chunks.end())
        return it->second.get();
    return nullptr;
}

Chunk* World::getChunk(const glm::ivec3& pos) {
    return getChunk(pos.x, pos.y, pos.z);
}

void World::clear() {
    m_chunks.clear();
}

ChunkCoord World::toChunkCoord(int x, int y, int z) {
    auto divFloor = [](int v) {
        return v >= 0 ? v / VoxelArray::SIZE : (v - VoxelArray::SIZE + 1) / VoxelArray::SIZE;
    };
    return { divFloor(x), divFloor(y), divFloor(z) };
}

ChunkCoord World::toChunkCoord(const glm::ivec3& worldPos) {
    return toChunkCoord(worldPos.x, worldPos.y, worldPos.z);
}

glm::ivec3 World::toLocalCoord(int x, int y, int z) {
    auto mod = [](int v) {
        return ((v % VoxelArray::SIZE) + VoxelArray::SIZE) % VoxelArray::SIZE;
    };
    return { mod(x), mod(y), mod(z) };
}

glm::ivec3 World::toLocalCoord(const glm::ivec3& position) {
    return toLocalCoord(position.x, position.y, position.z);
}

glm::ivec3 World::toWorldPos(const glm::ivec3& chunkCoord, const glm::ivec3& localPos) {
    return {
        chunkCoord.x * VoxelArray::SIZE + localPos.x,
        chunkCoord.y * VoxelArray::SIZE + localPos.y,
        chunkCoord.z * VoxelArray::SIZE + localPos.z
    };
}

void World::forEachChunk(const std::function<void(const ChunkCoord &, Chunk *)> &func) {
    for (auto& [coord, chunk] : m_chunks)
        func(coord, chunk.get());
}

void World::generateArea(const glm::ivec3 &startPos, const glm::ivec3 &endPos) {
    for (auto& [coord, chunk] : m_chunks)
        chunk->fill(voxel::AIR);

    const int total = (endPos.x - startPos.x + 1) *
                      (endPos.y - startPos.y + 1) *
                      (endPos.z - startPos.z + 1);

    int current = 0;
    for (int cx = startPos.x; cx <= endPos.x; ++cx)
        for (int cy = startPos.y; cy <= endPos.y; ++cy)
            for (int cz = startPos.z; cz <= endPos.z; ++cz) {
                Chunk* chunk = getOrCreateChunk(cx, cy, cz);
                m_generator->generateChunk(*chunk);
                ++current;

                float progress = static_cast<float>(current) / total;
                Logger::info() << "Generation Percent: " << progress * 100 << "%";
            }
    Logger::info();
}