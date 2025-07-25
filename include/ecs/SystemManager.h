//
// Created by ChiroYuki on 24/07/2025.
//

#ifndef PIXLENGINE_SYSTEMMANAGER_H
#define PIXLENGINE_SYSTEMMANAGER_H


#pragma once
#include <unordered_map>
#include <memory>
#include <typeindex>
#include "System.h"
#include "Entity.h"

class SystemManager {
public:
    template<typename T>
    std::shared_ptr<T> RegisterSystem() {
        const char* typeName = typeid(T).name();
        auto system = std::make_shared<T>();
        systems[typeName] = system;
        return system;
    }

    template<typename T>
    void SetSignature(Signature signature) {
        const char* typeName = typeid(T).name();
        signatures[typeName] = signature;
    }

    void EntityDestroyed(Entity entity) {
        for (auto const& [_, system] : systems) {
            system->entities.erase(entity);
        }
    }

    void EntitySignatureChanged(Entity entity, Signature entitySignature) {
        for (auto const& [typeName, system] : systems) {
            auto const& systemSignature = signatures[typeName];
            if ((entitySignature & systemSignature) == systemSignature) {
                system->entities.insert(entity);
            } else {
                system->entities.erase(entity);
            }
        }
    }

private:
    std::unordered_map<const char*, Signature> signatures{};
    std::unordered_map<const char*, std::shared_ptr<System>> systems{};
};

#endif //PIXLENGINE_SYSTEMMANAGER_H
