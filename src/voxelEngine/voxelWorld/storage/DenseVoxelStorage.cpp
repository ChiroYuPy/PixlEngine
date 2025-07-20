//
// Created by ChiroYuki on 20/07/2025.
//

#include <stdexcept>
#include "voxelEngine/voxelWorld/storage/DenseVoxelStorage.h"

DenseVoxelStorage::DenseVoxelStorage() : voxels{} {
    clear();
}

Voxel DenseVoxelStorage::get(int x, int y, int z) const {
    return voxels[index(x, y, z)];
}

void DenseVoxelStorage::set(int x, int y, int z, Voxel voxel) {
    voxels[index(x, y, z)] = voxel;
}

void DenseVoxelStorage::clear() {
    voxels.fill(Voxel(VoxelType::AIR));
}

int DenseVoxelStorage::index(int x, int y, int z) {
#ifndef NDEBUG
    if (x < 0 || x >= SIZE || y < 0 || y >= SIZE || z < 0 || z >= SIZE)
        throw std::out_of_range("Voxel position out of bounds");
#endif
    return x + SIZE * (z + SIZE * y);
}

double DenseVoxelStorage::getMemoryUsage() {
    return static_cast<double>(VOLUME) * sizeof(Voxel);
}

