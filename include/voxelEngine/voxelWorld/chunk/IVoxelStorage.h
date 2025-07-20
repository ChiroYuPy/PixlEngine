//
// Created by ChiroYuki on 20/07/2025.
//

#ifndef PIXLENGINE_IVOXELSTORAGE_H
#define PIXLENGINE_IVOXELSTORAGE_H

#include "voxelEngine/voxelWorld/voxel/Voxel.h"

class IVoxelStorage {
public:
    static const int SIZE = 16;
    static const int AREA = SIZE * SIZE;
    static const int VOLUME = AREA * SIZE;

    virtual ~IVoxelStorage() = default;

    virtual Voxel get(int x, int y, int z) const = 0;
    virtual void set(int x, int y, int z, Voxel voxel) = 0;

    virtual double getMemoryUsage() = 0;

    virtual void clear() = 0;
};

#endif //PIXLENGINE_IVOXELSTORAGE_H
