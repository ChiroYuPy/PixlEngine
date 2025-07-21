//
// Created by ChiroYuki on 20/07/2025.
//

#ifndef PIXLENGINE_VOXELARRAY_H
#define PIXLENGINE_VOXELARRAY_H


#include <vector>
#include <array>
#include "voxelEngine/voxelWorld/voxel/Voxel.h"

class VoxelArray {
public:
    static const int SIZE = 16;
    static const int AREA = SIZE * SIZE;
    static const int VOLUME = AREA * SIZE;

    VoxelArray();

    Voxel get(int x, int y, int z) const;
    void set(int x, int y, int z, Voxel voxel);

    void fill(voxel::VoxelID ID);

    double getMemoryUsage();

private:
    static int index(int x, int y, int z);

    std::array<Voxel, VOLUME> voxels;
};


#endif //PIXLENGINE_VOXELARRAY_H
