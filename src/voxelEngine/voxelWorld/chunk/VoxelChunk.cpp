//
// Created by ChiroYuki on 20/07/2025.
//

#include "voxelEngine/voxelWorld/chunk/VoxelChunk.h"

VoxelChunk::VoxelChunk(ChunkCoord coord)
: m_neighbors{} {
    m_neighbors.fill(nullptr);
}

bool VoxelChunk::isInBounds(int x, int y, int z) {
    return x >= 0 && x < VoxelArray::SIZE &&
           y >= 0 && y < VoxelArray::SIZE &&
           z >= 0 && z < VoxelArray::SIZE;
}

Voxel VoxelChunk::get(int x, int y, int z) const {
    if (!isInBounds(x, y, z)) return Voxel(voxel::AIR);

    return m_storage.get(x, y, z);
}

void VoxelChunk::set(int x, int y, int z, Voxel voxel) {
    if (!isInBounds(x, y, z)) return;

    m_storage.set(x, y, z, voxel);
}

void VoxelChunk::clear() {
    m_storage.fill(voxel::AIR);
}

void VoxelChunk::fill(voxel::VoxelID ID) {
    m_storage.fill(ID);
}

void VoxelChunk::setNeighbor(CubicDirection direction, VoxelChunk* neighbor) {
    if (!DirectionUtils::isValid(direction))
        throw std::invalid_argument("Invalid CubicDirection");

    m_neighbors[static_cast<size_t>(direction)] = neighbor;
}

VoxelChunk* VoxelChunk::getNeighbor(CubicDirection direction) const {
    if (!DirectionUtils::isValid(direction))
        throw std::invalid_argument("Invalid CubicDirection");

    return m_neighbors[static_cast<size_t>(direction)];
}

void VoxelChunk::markDirty() {
    m_dirty = true;
}