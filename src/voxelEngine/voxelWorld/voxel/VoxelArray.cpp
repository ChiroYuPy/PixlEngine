//
// Created by ChiroYuki on 20/07/2025.
//

#include <stdexcept>
#include "voxelEngine/voxelWorld/voxel/VoxelArray.h"

VoxelArray::VoxelArray() : voxels{} {
    fill(voxel::AIR);
}

voxel::ID VoxelArray::get(int x, int y, int z) const {
    return voxels[index(x, y, z)];
}

void VoxelArray::set(int x, int y, int z, voxel::ID voxel) {
    voxels[index(x, y, z)] = voxel;
}

void VoxelArray::fill(voxel::ID ID) {
    voxels.fill(ID);
}

int VoxelArray::index(int x, int y, int z) {
#ifndef NDEBUG
    if (x < 0 || x >= SIZE || y < 0 || y >= SIZE || z < 0 || z >= SIZE)
        throw std::out_of_range("voxel position out of bounds");
#endif
    return x + SIZE * (z + SIZE * y);
}

double VoxelArray::getMemoryUsage() {
    return static_cast<double>(VOLUME) * sizeof(voxel::ID);
}

