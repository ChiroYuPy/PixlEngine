#pragma once

#include <iostream>
#include <utility>

template<typename VertexType>
Mesh<VertexType>::Mesh() {
    initBuffers();
}

template<typename VertexType>
Mesh<VertexType>::~Mesh() {
    cleanupBuffers();
}

template<typename VertexType>
Mesh<VertexType>::Mesh(Mesh&& other) noexcept {
    moveFrom(std::move(other));
}

template<typename VertexType>
Mesh<VertexType>& Mesh<VertexType>::operator=(Mesh&& other) noexcept {
    if (this != &other) {
        cleanupBuffers();
        moveFrom(std::move(other));
    }
    return *this;
}

template<typename VertexType>
void Mesh<VertexType>::moveFrom(Mesh&& other) noexcept {
    vertices = std::move(other.vertices);
    indices = std::move(other.indices);
    vao = other.vao;
    vbo = other.vbo;
    ebo = other.ebo;
    indexCount = other.indexCount;
    vertexAttribSetup = std::move(other.vertexAttribSetup);

    // Reset other's OpenGL handles
    other.vao = 0;
    other.vbo = 0;
    other.ebo = 0;
    other.indexCount = 0;
}

template<typename VertexType>
void Mesh<VertexType>::initBuffers() {
    glGenVertexArrays(1, &vao);
    glGenBuffers(1, &vbo);
    glGenBuffers(1, &ebo);

    if (vao == 0 || vbo == 0 || ebo == 0) {
        std::cerr << "Error: Failed to generate OpenGL buffers for mesh" << std::endl;
        cleanupBuffers();
    }
}

template<typename VertexType>
void Mesh<VertexType>::cleanupBuffers() {
    if (ebo != 0) {
        glDeleteBuffers(1, &ebo);
        ebo = 0;
    }
    if (vbo != 0) {
        glDeleteBuffers(1, &vbo);
        vbo = 0;
    }
    if (vao != 0) {
        glDeleteVertexArrays(1, &vao);
        vao = 0;
    }
}

template<typename VertexType>
void Mesh<VertexType>::setData(const std::vector<VertexType>& verts, const std::vector<uint32_t>& inds) {
    vertices = verts;
    indices = inds;
    indexCount = static_cast<GLsizei>(indices.size());
    uploadToGPU();
}

template<typename VertexType>
void Mesh<VertexType>::uploadToGPU() {
    if (!isValid()) {
        std::cerr << "Error: Cannot upload to GPU - mesh buffers not initialized" << std::endl;
        return;
    }

    if (vertices.empty()) {
        std::cerr << "Warning: Uploading empty vertex data to GPU" << std::endl;
    }

    glBindVertexArray(vao);

    // Upload vertex data
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER,
                 vertices.size() * sizeof(VertexType),
                 vertices.empty() ? nullptr : vertices.data(),
                 GL_STATIC_DRAW);

    // Upload index data
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER,
                 indices.size() * sizeof(uint32_t),
                 indices.empty() ? nullptr : indices.data(),
                 GL_STATIC_DRAW);

    // Setup vertex attributes
    if (vertexAttribSetup) {
        vertexAttribSetup();
    } else {
        std::cerr << "Warning: vertexAttribSetup() not set before uploading data." << std::endl;
    }

    // Unbind VAO
    glBindVertexArray(0);

    // Check for OpenGL errors
    GLenum error = glGetError();
    if (error != GL_NO_ERROR) {
        std::cerr << "OpenGL error during mesh upload: " << error << std::endl;
    }
}

template<typename VertexType>
void Mesh<VertexType>::draw() const {
    if (!isValid() || indexCount == 0) {
        return;
    }

    glBindVertexArray(vao);
    glDrawElements(GL_TRIANGLES, indexCount, GL_UNSIGNED_INT, nullptr);
    glBindVertexArray(0);
}

template<typename VertexType>
void Mesh<VertexType>::setVertexAttribSetup(std::function<void()> setupFunc) {
    vertexAttribSetup = std::move(setupFunc);
}