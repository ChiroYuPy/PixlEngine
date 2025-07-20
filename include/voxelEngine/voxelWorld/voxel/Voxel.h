//
// Created by ChiroYuki on 20/07/2025.
//

#ifndef PIXLENGINE_VOXEL_H
#define PIXLENGINE_VOXEL_H

#include <cstdint>

#include "VoxelType.h"

struct Voxel {

    VoxelType::ID ID;

    Voxel();
    explicit Voxel(uint8_t id);

    bool isAir() const;
    bool operator==(const Voxel& other) const;
};

namespace std {
    template<>
    struct hash<Voxel> {
        std::size_t operator()(const Voxel& voxel) const {
            return std::hash<uint8_t>()(voxel.ID);
        }
    };
}

#endif //PIXLENGINE_VOXEL_H
