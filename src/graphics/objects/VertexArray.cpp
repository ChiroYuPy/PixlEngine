//
// Created by ChiroYuki on 23/07/2025.
//

#include "graphics/objects/VertexArray.h"

VertexArray::VertexArray() {
    glGenVertexArrays(1, &id);
}

VertexArray::~VertexArray() {
    glDeleteVertexArrays(1, &id);
}

void VertexArray::bind() const {
    glBindVertexArray(id);
}

void VertexArray::unbind() {
    glBindVertexArray(0);
}