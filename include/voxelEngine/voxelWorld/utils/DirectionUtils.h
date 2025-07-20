//
// Created by ChiroYuki on 20/07/2025.
//

#ifndef PIXLENGINE_DIRECTIONUTILS_H
#define PIXLENGINE_DIRECTIONUTILS_H

enum class CubicDirection {
    NORTH = 0,  // +Z
    SOUTH = 1,  // -Z
    EAST = 2,   // +X
    WEST = 3,   // -X
    UP = 4,     // +Y
    DOWN = 5    // -Y
};

struct DirectionVector {
    int x, y, z;
};

namespace DirectionUtils {
    CubicDirection getOpposite(CubicDirection direction);

    DirectionVector getOffset(CubicDirection direction);

    bool isValid(CubicDirection direction);

    CubicDirection fromOffset(int x, int y, int z);
    CubicDirection fromOffset(const DirectionVector& offset);
}

#endif //PIXLENGINE_DIRECTIONUTILS_H
