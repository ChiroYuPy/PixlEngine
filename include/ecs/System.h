//
// Created by ChiroYuki on 24/07/2025.
//

#ifndef PIXLENGINE_SYSTEM_H
#define PIXLENGINE_SYSTEM_H

#include <set>

#include "Entity.h"

class System {
public:
    std::set<Entity> entities;
};

#endif //PIXLENGINE_SYSTEM_H
