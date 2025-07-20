//
// Created by ChiroYuki on 20/07/2025.
//

#include <stdexcept>
#include "voxelEngine/voxelWorld/utils/DirectionUtils.h"

namespace DirectionUtils {
    CubicDirection getOpposite(CubicDirection direction) {
        switch (direction) {
            case CubicDirection::NORTH: return CubicDirection::SOUTH;
            case CubicDirection::SOUTH: return CubicDirection::NORTH;
            case CubicDirection::EAST:  return CubicDirection::WEST;
            case CubicDirection::WEST:  return CubicDirection::EAST;
            case CubicDirection::UP:    return CubicDirection::DOWN;
            case CubicDirection::DOWN:  return CubicDirection::UP;
            default: throw std::invalid_argument("Invalid CubicDirection");
        }
    }

    DirectionVector getOffset(CubicDirection direction) {
        switch (direction) {
            case CubicDirection::NORTH: return {0, 0, 1};
            case CubicDirection::SOUTH: return {0, 0, -1};
            case CubicDirection::EAST:  return {1, 0, 0};
            case CubicDirection::WEST:  return {-1, 0, 0};
            case CubicDirection::UP:    return {0, 1, 0};
            case CubicDirection::DOWN:  return {0, -1, 0};
            default: throw std::invalid_argument("Invalid CubicDirection");
        }
    }

    bool isValid(CubicDirection direction) {
        return static_cast<int>(direction) >= 0 && static_cast<int>(direction) <= 5;
    }

    CubicDirection fromOffset(int x, int y, int z) {
        if (x == 0 && y == 0 && z == 1) return CubicDirection::NORTH;
        if (x == 0 && y == 0 && z == -1) return CubicDirection::SOUTH;
        if (x == 1 && y == 0 && z == 0) return CubicDirection::EAST;
        if (x == -1 && y == 0 && z == 0) return CubicDirection::WEST;
        if (x == 0 && y == 1 && z == 0) return CubicDirection::UP;
        if (x == 0 && y == -1 && z == 0) return CubicDirection::DOWN;
        throw std::invalid_argument("Invalid offset for CubicDirection");
    }

    CubicDirection fromOffset(const DirectionVector& offset) {
        return fromOffset(offset.x, offset.y, offset.z);
    }
}