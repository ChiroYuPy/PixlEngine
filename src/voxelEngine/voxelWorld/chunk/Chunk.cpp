//
// Created by ChiroYuki on 20/07/2025.
//

#include "voxelEngine/voxelWorld/chunk/Chunk.h"

Chunk::Chunk(ChunkCoord coord)
: m_position(coord) {}

bool Chunk::isInBounds(int x, int y, int z) {
    return x >= 0 && x < VoxelArray::SIZE &&
           y >= 0 && y < VoxelArray::SIZE &&
           z >= 0 && z < VoxelArray::SIZE;
}

voxel::ID Chunk::get(int x, int y, int z) const {
    if (!isInBounds(x, y, z)) return voxel::AIR;
    return m_storage.get(x, y, z);
}

voxel::ID Chunk::get(const glm::ivec3& pos) const {
    return get(pos.x, pos.y, pos.z);
}

void Chunk::set(int x, int y, int z, voxel::ID voxel) {
    if (!isInBounds(x, y, z)) return;
    m_storage.set(x, y, z, voxel);
    markDirty();
}

void Chunk::set(const glm::ivec3& pos, voxel::ID voxel) {
    set(pos.x, pos.y, pos.z, voxel);
}

void Chunk::fill(voxel::ID ID) {
    m_storage.fill(ID);
    markDirty();
}

void Chunk::markDirty() {
    m_dirty = true;
}

glm::ivec3 Chunk::getPosition() const {
    return {m_position.x, m_position.y, m_position.z};
}

void Chunk::buildMesh(const World& world) {
    if (!m_dirty) return;
    if (!m_mesh) m_mesh = std::make_unique<ChunkMesh>(glm::ivec3{m_position.x, m_position.y, m_position.z});
    m_mesh->build(*this, world);
    m_dirty = false;
}

const ChunkMesh* Chunk::getMesh() const {
    return m_mesh.get();
}
