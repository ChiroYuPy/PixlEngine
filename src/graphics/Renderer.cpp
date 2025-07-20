//
// Created by ChiroYuki on 19/07/2025.
//

#include "graphics/Renderer.h"

#include "graphics/Renderer.h"
#include "graphics/Shader.h"
#include "graphics/Mesh.h"
#include "graphics/Shader.h"
#include <iostream>

Renderer::~Renderer() {
    shutdown();
}

bool Renderer::initialize() {
    if (!gladLoadGL()) {
        std::cerr << "Failed to initialize GLAD" << std::endl;
        return false;
    }

    std::cout << "OpenGL Version: " << glGetString(GL_VERSION) << std::endl;
    std::cout << "Graphics Card: " << glGetString(GL_RENDERER) << std::endl;

    enableDepthTest();
    enableFaceCulling();

    glEnable(GL_MULTISAMPLE);

    m_initialized = true;
    return true;
}

void Renderer::shutdown() {
    m_initialized = false;
}

void Renderer::beginFrame() {
    resetStats();
}

void Renderer::endFrame() {
    // Rien pour l'instant
}

void Renderer::clear(const glm::vec3& color) {
    glClearColor(color.r, color.g, color.b, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Renderer::setViewport(int x, int y, int width, int height) {
    glViewport(x, y, width, height);
}

void Renderer::drawMesh(const Mesh& mesh, Shader& shader, const glm::mat4& transform) {
    shader.use();
    shader.setMat4("u_Model", transform);
    mesh.draw();

    m_stats.drawCalls++;
    m_stats.vertices += mesh.getVertexCount();
    m_stats.triangles += mesh.getIndexCount() > 0 ? mesh.getIndexCount() / 3 : mesh.getVertexCount() / 3;
}

void Renderer::drawWireframe(const Mesh& mesh, Shader& shader, const glm::mat4& transform) {
    bool wasWireframe = false;
    GLint polygonMode[2];
    glGetIntegerv(GL_POLYGON_MODE, polygonMode);
    wasWireframe = (polygonMode[0] == GL_LINE);

    if (!wasWireframe) {
        setWireframeMode(true);
    }

    drawMesh(mesh, shader, transform);

    if (!wasWireframe) {
        setWireframeMode(false);
    }
}

void Renderer::enableDepthTest(bool enable) {
    if (enable) {
        glEnable(GL_DEPTH_TEST);
    } else {
        glDisable(GL_DEPTH_TEST);
    }
}

void Renderer::enableFaceCulling(bool enable) {
    if (enable) {
        glEnable(GL_CULL_FACE);
        glCullFace(GL_BACK);
    } else {
        glDisable(GL_CULL_FACE);
    }
}

void Renderer::enableBlending(bool enable) {
    if (enable) {
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    } else {
        glDisable(GL_BLEND);
    }
}

void Renderer::setWireframeMode(bool enabled) {
    glPolygonMode(GL_FRONT_AND_BACK, enabled ? GL_LINE : GL_FILL);
}