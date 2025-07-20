//
// Created by ChiroYuki on 19/07/2025.
//

#ifndef PIXLENGINE_MESH_H
#define PIXLENGINE_MESH_H

#include <glm/glm.hpp>
#include <vector>
#include "glad/glad.h"

struct Vertex {
    glm::vec3 position;
    glm::vec3 normal;
    glm::vec2 texCoords;
    glm::vec3 color = glm::vec3(1.0f);
};

class Mesh {
public:
    Mesh() = default;
    ~Mesh();

    void setVertices(const std::vector<Vertex>& vertices);
    void setIndices(const std::vector<unsigned int>& indices);
    void upload();

    void draw() const;
    void drawInstanced(int count) const;

    bool isUploaded() const { return m_uploaded; }
    int getVertexCount() const { return m_vertexCount; }
    int getIndexCount() const { return m_indexCount; }

private:
    void cleanup();

    GLuint m_VAO = 0;
    GLuint m_VBO = 0;
    GLuint m_EBO = 0;

    int m_vertexCount = 0;
    int m_indexCount = 0;
    bool m_uploaded = false;
};

#endif //PIXLENGINE_MESH_H
