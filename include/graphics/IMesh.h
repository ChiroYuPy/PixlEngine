//
// Created by ChiroYuki on 24/07/2025.
//

#ifndef PIXLENGINE_IMESH_H
#define PIXLENGINE_IMESH_H

class IMesh {
public:
    virtual ~IMesh() = default;

    virtual void bind() const = 0;
    virtual void unbind() const = 0;
    virtual void draw() const = 0;
};

#endif //PIXLENGINE_IMESH_H
