//
// Created by ChiroYuki on 19/07/2025.
//

#include "graphics/Renderer.h"
#include "graphics/Shader.h"
#include "graphics/IMesh.h"
#include "core/Logger.h"

Renderer::Renderer()
: currentShader(nullptr) {}

Renderer::~Renderer() {

}

bool Renderer::initialize() {
    if (!gladLoadGL()) {
        std::cerr << "Failed to initialize GLAD" << std::endl;
        return false;
    }

    glEnable(GL_MULTISAMPLE);

    return true;
}

void Renderer::beginFrame() {
    //TODO: render stats recording
}

void Renderer::endFrame() {
    //TODO: render stats calculating and logging
}

void Renderer::setClearColor(const Color& color) {
    glClearColor(color.getRf(), color.getGf(), color.getBf(), 1.0f);
}

void Renderer::clear() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Renderer::setViewport(unsigned int x, unsigned int y, unsigned int width, unsigned int height) {
    glViewport(x, y, width, height);
}

void Renderer::setViewProjection(const glm::mat4& view, const glm::mat4& projection) {
    viewMatrix = view;
    projectionMatrix = projection;
}

void Renderer::setShader(std::shared_ptr<Shader> shader) {
    currentShader = shader;
    if (currentShader) currentShader->use();
}

void Renderer::drawMesh(const IMesh& mesh, const glm::mat4& modelMatrix) {
    if (!currentShader) {
        Logger::warn("[Renderer] No shader set before drawMesh()");
        return;
    }

    currentShader->setMat4("u_Model", modelMatrix); // not yet used
    currentShader->setMat4("u_ViewProjection", viewMatrix * projectionMatrix);

    currentShader->use();
    mesh.bind();
    mesh.draw();
    mesh.unbind();
    currentShader->unuse();
}

void Renderer::setRenderPolygonMode(PolygonMode mode, PolygonFace face) {
    GLenum glMode;
    switch (mode) {
        case PolygonMode::Fill: glMode = GL_FILL; break;
        case PolygonMode::Wireframe: glMode = GL_LINE; break;
        case PolygonMode::Point: glMode = GL_POINT; break;
    }

    GLenum glFace;
    switch (face) {
        case PolygonFace::Front:        glFace = GL_FRONT; break;
        case PolygonFace::Back:         glFace = GL_BACK; break;
        case PolygonFace::FrontAndBack: glFace = GL_FRONT_AND_BACK; break;
    }

    glPolygonMode(glFace, glMode);
}