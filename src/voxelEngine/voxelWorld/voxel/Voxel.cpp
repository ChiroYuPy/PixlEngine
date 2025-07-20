//
// Created by ChiroYuki on 20/07/2025.
//

#include "voxelEngine/voxelWorld/voxel/Voxel.h"

Voxel::Voxel() : ID(VoxelType::AIR) {}

Voxel::Voxel(VoxelType::ID id) : ID(id) {}

bool Voxel::isAir() const {
    return ID == VoxelType::AIR;
}

bool Voxel::operator==(const Voxel &other) const {
    return ID == other.ID;
}