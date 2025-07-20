//
// Created by ChiroYuki on 20/07/2025.
//

#ifndef PIXLENGINE_DENSEVOXELSTORAGE_H
#define PIXLENGINE_DENSEVOXELSTORAGE_H


#include <vector>
#include <array>
#include "voxelEngine/voxelWorld/voxel/Voxel.h"
#include "voxelEngine/voxelWorld/chunk/IVoxelStorage.h"

class DenseVoxelStorage : public IVoxelStorage {
public:
    DenseVoxelStorage();

    Voxel get(int x, int y, int z) const override;
    void set(int x, int y, int z, Voxel voxel) override;

    void clear() override;

    double getMemoryUsage() override;

private:
    static int index(int x, int y, int z);

    std::array<Voxel, VOLUME> voxels;
};


#endif //PIXLENGINE_DENSEVOXELSTORAGE_H
