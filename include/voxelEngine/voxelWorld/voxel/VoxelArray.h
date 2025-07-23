//
// Created by ChiroYuki on 20/07/2025.
//

#ifndef PIXLENGINE_VOXELARRAY_H
#define PIXLENGINE_VOXELARRAY_H


#include <vector>
#include <array>
#include "voxelEngine/voxelWorld/voxel/VoxelType.h"

class VoxelArray {
public:
    static const int SIZE = 32;
    static const int VOLUME = SIZE * SIZE * SIZE;

    VoxelArray();

    voxel::ID get(int x, int y, int z) const;
    void set(int x, int y, int z, voxel::ID voxel);

    void fill(voxel::ID ID);

    double getMemoryUsage();

private:
    static int index(int x, int y, int z);

    std::array<voxel::ID, VOLUME> voxels;
};


#endif //PIXLENGINE_VOXELARRAY_H
