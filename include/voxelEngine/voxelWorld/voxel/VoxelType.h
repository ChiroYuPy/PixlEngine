//
// Created by ChiroYuki on 20/07/2025.
//

#ifndef PIXLENGINE_VOXELTYPE_H
#define PIXLENGINE_VOXELTYPE_H

#include <cstdint>
#include <unordered_map>
#include <string>

namespace VoxelType {

    using ID = uint8_t; // 256 types (air is one of them)

    enum : ID {
        AIR   = 0,
        DIRT  = 1,
        GRASS = 2,
        STONE = 3,
    };

    inline const std::unordered_map<ID, std::string> Names = {
            { AIR, "Air" },
            { DIRT, "Dirt" },
            { GRASS, "Grass" },
            { STONE, "Stone" },
    };

    inline std::string nameOf(ID id);
}

#endif //PIXLENGINE_VOXELTYPE_H
