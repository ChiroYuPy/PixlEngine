//
// Created by ChiroYuki on 20/07/2025.
//

#ifndef PIXLENGINE_VOXEL_H
#define PIXLENGINE_VOXEL_H

#include <cstdint>

#include "VoxelType.h"

struct Voxel {

    voxel::VoxelID ID;

    Voxel();

    explicit Voxel(voxel::VoxelID id);

    [[nodiscard]] bool operator==(const Voxel& other) const;

    [[nodiscard]] bool operator!=(const Voxel& other) const;

    [[nodiscard]] explicit operator voxel::VoxelID() const;
};

#endif //PIXLENGINE_VOXEL_H
