//
// Created by ChiroYuki on 23/07/2025.
//

#ifndef PIXLENGINE_BUFFER_H
#define PIXLENGINE_BUFFER_H

#include <GLT.h>

enum class BufferType {
    Vertex,
    Index,
    Uniform,
    Instance
};

class Buffer {
public:
    Buffer(BufferType type);
    ~Buffer();

    void bind() const;
    void unbind() const;

    void uploadData(const void* data, size_t size, GLenum usage) const;

    GLuint getID() const { return id; }

private:
    GLuint id;
    GLenum target; // GL_ARRAY_BUFFER, GL_ELEMENT_ARRAY_BUFFER, etc.
};
#endif //PIXLENGINE_BUFFER_H
