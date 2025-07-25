//
// Created by ChiroYuki on 25/07/2025.
//

#ifndef PIXLENGINE_MEMORY_H
#define PIXLENGINE_MEMORY_H

#include <memory>

// ------------------------------------------------------------------
// Pointeur unique (ownership unique)
// ------------------------------------------------------------------
template<typename T>
using Scope = std::unique_ptr<T>;

template<typename T, typename... Args>
constexpr Scope<T> CreateScope(Args&&... args) {
    return std::make_unique<T>(std::forward<Args>(args)...);
}

// ------------------------------------------------------------------
// Pointeur partagé (ownership partagé)
// ------------------------------------------------------------------
template<typename T>
using Ref = std::shared_ptr<T>;

template<typename T, typename... Args>
constexpr Ref<T> CreateRef(Args&&... args) {
    return std::make_shared<T>(std::forward<Args>(args)...);
}

#endif //PIXLENGINE_MEMORY_H
