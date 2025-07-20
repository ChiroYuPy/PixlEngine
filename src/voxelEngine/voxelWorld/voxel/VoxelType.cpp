//
// Created by ChiroYuki on 20/07/2025.
//

#include "voxelEngine/voxelWorld/voxel/VoxelType.h"

namespace VoxelType {
    std::string nameOf(ID id) {
        auto it = Names.find(id);
        if (it != Names.end())
            return it->second;
        return "Invalid";
    }
}