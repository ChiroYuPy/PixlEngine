//
// Created by ChiroYuki on 20/07/2025.
//

#ifndef PIXLENGINE_DIRECTIONUTILS_H
#define PIXLENGINE_DIRECTIONUTILS_H

#include <GLT.h>

enum class CubicDirection {
    NORTH = 0,  // +Z
    SOUTH = 1,  // -Z
    EAST = 2,   // +X
    WEST = 3,   // -X
    UP = 4,     // +Y
    DOWN = 5    // -Y
};

namespace DirectionUtils {
    CubicDirection getOpposite(CubicDirection direction);

    glm::ivec3 getOffset(CubicDirection direction);

    bool isValid(CubicDirection direction);

    CubicDirection fromOffset(int x, int y, int z);
    CubicDirection fromOffset(const glm::ivec3& offset);

    CubicDirection fromIndex(int index);
}

#endif //PIXLENGINE_DIRECTIONUTILS_H
