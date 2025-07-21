//
// Created by ChiroYuki on 20/07/2025.
//

#include "voxelEngine/voxelWorld/world/VoxelWorld.h"
#include "voxelEngine/voxelWorld/chunk/VoxelChunk.h"
#include <stdexcept>

VoxelWorld::VoxelWorld() = default;

Voxel VoxelWorld::getVoxel(int worldX, int worldY, int worldZ) const {
    ChunkCoord chunkCoord = toChunkCoord(worldX, worldY, worldZ);
    glm::ivec3 localPos = toLocalCoord(worldX, worldY, worldZ);

    auto it = m_chunks.find(chunkCoord);
    if (it != m_chunks.end())
        return it->second->get(localPos.x, localPos.y, localPos.z);

    return Voxel{}; // Air par défaut
}

void VoxelWorld::setVoxel(int worldX, int worldY, int worldZ, Voxel voxel) {
    ChunkCoord chunkCoord = toChunkCoord(worldX, worldY, worldZ);
    glm::ivec3 localPos = toLocalCoord(worldX, worldY, worldZ);

    VoxelChunk* chunk = getOrCreateChunk(chunkCoord.x, chunkCoord.y, chunkCoord.z);
    if (chunk) {
        chunk->set(localPos.x, localPos.y, localPos.z, voxel);
        chunk->markDirty();
    }
}

void VoxelWorld::setVoxel(int worldX, int worldY, int worldZ, voxel::VoxelID type) {
    setVoxel(worldX, worldY, worldZ, Voxel{static_cast<uint8_t>(type)});
}

Voxel VoxelWorld::getVoxel(const glm::ivec3& worldPos) const {
    return getVoxel(worldPos.x, worldPos.y, worldPos.z);
}

void VoxelWorld::setVoxel(const glm::ivec3& worldPos, Voxel voxel) {
    setVoxel(worldPos.x, worldPos.y, worldPos.z, voxel);
}

void VoxelWorld::setVoxel(const glm::ivec3& worldPos, voxel::VoxelID type) {
    setVoxel(worldPos.x, worldPos.y, worldPos.z, type);
}

VoxelChunk* VoxelWorld::getOrCreateChunk(int x, int y, int z) {
    ChunkCoord chunkCoord = {x, y, z};
    auto it = m_chunks.find(chunkCoord);
    if (it != m_chunks.end())
        return it->second.get();

    auto newChunk = std::make_unique<VoxelChunk>(chunkCoord);
    VoxelChunk* ptr = newChunk.get();
    m_chunks.emplace(chunkCoord, std::move(newChunk));
    return ptr;
}

VoxelChunk* VoxelWorld::getOrCreateChunk(const glm::ivec3& pos) {
    return getOrCreateChunk(pos.x, pos.y, pos.z);
}

VoxelChunk* VoxelWorld::getChunk(int x, int y, int z) {
    ChunkCoord chunkCoord = {x, y, z};
    auto it = m_chunks.find(chunkCoord);
    if (it != m_chunks.end())
        return it->second.get();
    return nullptr;
}

VoxelChunk* VoxelWorld::getChunk(const glm::ivec3& pos) {
    return getChunk(pos.x, pos.y, pos.z);
}

void VoxelWorld::clear() {
    m_chunks.clear();
}

ChunkCoord VoxelWorld::toChunkCoord(int x, int y, int z) {
    auto divFloor = [](int v) {
        return v >= 0 ? v / VoxelArray::SIZE : (v - VoxelArray::SIZE + 1) / VoxelArray::SIZE;
    };
    return { divFloor(x), divFloor(y), divFloor(z) };
}

ChunkCoord VoxelWorld::toChunkCoord(const glm::ivec3& worldPos) {
    return toChunkCoord(worldPos.x, worldPos.y, worldPos.z);
}

glm::ivec3 VoxelWorld::toLocalCoord(int x, int y, int z) {
    auto mod = [](int v) {
        return ((v % VoxelArray::SIZE) + VoxelArray::SIZE) % VoxelArray::SIZE;
    };
    return { mod(x), mod(y), mod(z) };
}

glm::ivec3 VoxelWorld::toLocalCoord(const glm::ivec3& position) {
    return toLocalCoord(position.x, position.y, position.z);
}

glm::ivec3 VoxelWorld::toWorldPos(const glm::ivec3& chunkCoord, const glm::ivec3& localPos) {
    return {
        chunkCoord.x * VoxelArray::SIZE + localPos.x,
        chunkCoord.y * VoxelArray::SIZE + localPos.y,
        chunkCoord.z * VoxelArray::SIZE + localPos.z
    };
}

void VoxelWorld::forEachChunk(const std::function<void(const ChunkCoord &, VoxelChunk *)> &func) {
    for (auto& [coord, chunk] : m_chunks) {
        func(coord, chunk.get());
    }
}
