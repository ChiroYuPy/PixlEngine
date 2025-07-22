//
// Created by ChiroYuki on 19/07/2025.
//

#ifndef PIXLENGINE_MESH_H
#define PIXLENGINE_MESH_H

#include <glm/glm.hpp>
#include <vector>
#include <functional>
#include "glad/glad.h"

struct VertexPos {
    glm::vec3 position;
};

struct VertexPosColor {
    glm::vec3 position;
    glm::vec3 color;
};

struct VertexPosNormalTexColor {
    glm::vec3 position;
    glm::vec3 normal;
    glm::vec2 texCoords;
    glm::vec3 color;
};

template<typename VertexType>
class Mesh {
public:
    Mesh();
    ~Mesh();

    // Non-copyable but movable
    Mesh(const Mesh&) = delete;
    Mesh& operator=(const Mesh&) = delete;
    Mesh(Mesh&& other) noexcept;
    Mesh& operator=(Mesh&& other) noexcept;

    // Met à jour les données CPU puis upload GPU
    void setData(const std::vector<VertexType>& verts, const std::vector<uint32_t>& inds);

    // Upload données GPU (en cas de modification partielle)
    void uploadToGPU();

    // Rendu (doit être appelé dans un contexte OpenGL actif)
    void draw() const;

    // Configuration du layout des attributs (doit être fourni par l'utilisateur)
    void setVertexAttribSetup(std::function<void()> setupFunc);

    size_t getVertexCount() const { return vertices.size(); }
    size_t getIndexCount() const { return indices.size(); }

    // Check if mesh has been properly initialized
    bool isValid() const { return vao != 0 && vbo != 0 && ebo != 0; }

private:
    // Données CPU
    std::vector<VertexType> vertices;
    std::vector<uint32_t> indices;

    GLuint vao = 0;
    GLuint vbo = 0;
    GLuint ebo = 0;
    GLsizei indexCount = 0;

    std::function<void()> vertexAttribSetup;

    void initBuffers();
    void cleanupBuffers();
    void moveFrom(Mesh&& other) noexcept;
};

#include "Mesh.inl"

#endif //PIXLENGINE_MESH_H
