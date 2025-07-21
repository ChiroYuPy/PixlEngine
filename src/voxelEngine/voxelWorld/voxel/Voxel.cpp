//
// Created by ChiroYuki on 20/07/2025.
//

#include "voxelEngine/voxelWorld/voxel/Voxel.h"

Voxel::Voxel()
        : ID(voxel::AIR) {}

Voxel::Voxel(voxel::VoxelID id)
        : ID(id) {}

bool Voxel::operator==(const Voxel &other) const {
    return ID == other.ID;
}

bool Voxel::operator!=(const Voxel &other) const {
    return ID != other.ID;
}

Voxel::operator voxel::VoxelID() const {
    return ID;
}
