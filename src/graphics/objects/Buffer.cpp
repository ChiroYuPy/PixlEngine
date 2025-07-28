//
// Created by ChiroYuki on 23/07/2025.
//

#include "graphics/objects/Buffer.h"

Buffer::Buffer(BufferType type) {
    glGenBuffers(1, &id);

    switch (type) {
        case BufferType::Vertex:
        case BufferType::Instance:
            target = GL_ARRAY_BUFFER;
            break;
        case BufferType::Index:
            target = GL_ELEMENT_ARRAY_BUFFER;
            break;
        case BufferType::Uniform:
            target = GL_UNIFORM_BUFFER;
            break;
    }
}

Buffer::~Buffer() {
    glDeleteBuffers(1, &id);
}

void Buffer::bind() const {
    glBindBuffer(target, id);
}

void Buffer::unbind() const {
    glBindBuffer(target, 0);
}

void Buffer::uploadData(const void* data, size_t size, GLenum usage) const {
    bind();
    glBufferData(target, static_cast<GLsizeiptr>(size), data, usage);
}