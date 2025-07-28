//
// Created by ChiroYuki on 23/07/2025.
//

#ifndef PIXLENGINE_VERTEXARRAY_H
#define PIXLENGINE_VERTEXARRAY_H

#include <GLT.h>

class VertexArray {
public:
    VertexArray();
    ~VertexArray();

    void bind() const;
    static void unbind() ;

    GLuint getID() const { return id; }

private:
    GLuint id;
};

#endif //PIXLENGINE_VERTEXARRAY_H
