#pragma once

template<typename VertexType>
void Renderer::drawMesh(const Mesh<VertexType>& mesh, Shader& shader, const glm::mat4& transform) {
    if (!m_initialized) {
        std::cerr << "Error: Renderer not initialized" << std::endl;
        return;
    }

    if (!mesh.isValid() || mesh.getIndexCount() == 0) {
        return; // Skip empty or invalid meshes
    }

    shader.use();
    shader.setMat4("u_Model", transform);
    mesh.draw();

    m_stats.drawCalls++;
    m_stats.vertices += static_cast<int>(mesh.getVertexCount());
    m_stats.triangles += mesh.getIndexCount() > 0 ?
                         static_cast<int>(mesh.getIndexCount()) / 3 :
                         static_cast<int>(mesh.getVertexCount()) / 3;
}

template<typename VertexType>
void Renderer::drawWireframe(const Mesh<VertexType>& mesh, Shader& shader, const glm::mat4& transform) {
    if (!m_initialized) {
        std::cerr << "Error: Renderer not initialized" << std::endl;
        return;
    }

    if (!mesh.isValid() || mesh.getIndexCount() == 0) {
        return; // Skip empty or invalid meshes
    }

    // Save current polygon mode
    GLint polygonMode[2];
    glGetIntegerv(GL_POLYGON_MODE, polygonMode);
    bool wasWireframe = (polygonMode[0] == GL_LINE);

    if (!wasWireframe) {
        setWireframeMode(true);
    }

    drawMesh(mesh, shader, transform);

    if (!wasWireframe) {
        setWireframeMode(false);
    }
}