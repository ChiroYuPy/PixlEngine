//
// Created by ChiroYuki on 20/07/2025.
//

#include "voxelEngine/voxelWorld/chunk/VoxelChunk.h"

VoxelChunk::VoxelChunk(std::unique_ptr<IVoxelStorage> storage)
: m_storage(std::move(storage)), m_neighbors{} {
    m_neighbors.fill(nullptr);
}

bool VoxelChunk::isInBounds(int x, int y, int z) {
    return x >= 0 && x < IVoxelStorage::SIZE &&
           y >= 0 && y < IVoxelStorage::SIZE &&
           z >= 0 && z < IVoxelStorage::SIZE;
}

Voxel VoxelChunk::get(int x, int y, int z) const {
    if (!isInBounds(x, y, z)) return Voxel(VoxelType::AIR);

    return m_storage->get(x, y, z);
}

void VoxelChunk::set(int x, int y, int z, Voxel voxel) {
    if (!isInBounds(x, y, z)) return;

    m_storage->set(x, y, z, voxel);
}

void VoxelChunk::clear() {
    m_storage->clear();
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
