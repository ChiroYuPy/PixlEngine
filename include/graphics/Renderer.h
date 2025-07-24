//
// Created by ChiroYuki on 19/07/2025.
//

#ifndef PIXLENGINE_RENDERER_H
#define PIXLENGINE_RENDERER_H

#include <GLT.h>
#include <iostream>
#include <memory>
#include "IMesh.h"
#include "Shader.h"
#include "core/Color.h"

enum class PolygonMode {
    Fill,
    Wireframe,
    Point
};

enum class PolygonFace {
    Front,
    Back,
    FrontAndBack
};

class Renderer {
public:
    Renderer();
    ~Renderer();

    bool initialize();

    void beginFrame();
    void endFrame();

    void setClearColor(const Color& color);
    void clear();
    void setViewport(unsigned int x, unsigned int y, unsigned int width, unsigned int height);

    void setViewProjection(const glm::mat4& view, const glm::mat4& projection);
    void setShader(std::shared_ptr<Shader> shader);

    void drawMesh(const IMesh& mesh, const glm::mat4& modelMatrix);

    void setRenderPolygonMode(PolygonMode mode, PolygonFace face = PolygonFace::FrontAndBack);

private:
    glm::mat4 viewMatrix;
    glm::mat4 projectionMatrix;
    std::shared_ptr<Shader> currentShader;
};

#include "Renderer.inl"

#endif //PIXLENGINE_RENDERER_H