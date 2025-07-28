//
// Created by ChiroYuki on 24/07/2025.
//

#include "graphics/RenderState.h"

void RenderState::setClearColor(float r, float g, float b, float a) {
    glClearColor(r, g, b, a);
}

void RenderState::clear() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void RenderState::enableDepthTest(bool enable) {
    if (enable) glEnable(GL_DEPTH_TEST);
    else glDisable(GL_DEPTH_TEST);
}

void RenderState::enableCullFace(bool enable) {
    if (enable) glEnable(GL_CULL_FACE);
    else glDisable(GL_CULL_FACE);
}

void RenderState::setCullFace(RenderState::PolygonFace face) {
    GLenum glFace;
    switch (face) {
        case PolygonFace::Front:        glFace = GL_FRONT; break;
        case PolygonFace::Back:         glFace = GL_BACK; break;
        case PolygonFace::FrontAndBack: glFace = GL_FRONT_AND_BACK; break;
        default: glFace = GL_BACK; break;
    }
    glCullFace(glFace);
}

void RenderState::setPolygonMode(RenderState::PolygonFace face, RenderState::PolygonMode mode) {
    GLenum glMode;
    switch (mode) {
        case PolygonMode::Fill:      glMode = GL_FILL; break;
        case PolygonMode::Wireframe: glMode = GL_LINE; break;
        case PolygonMode::Point:     glMode = GL_POINT; break;
        default: glMode = GL_FILL; break;
    }

    GLenum glFace;
    switch (face) {
        case PolygonFace::Front:        glFace = GL_FRONT; break;
        case PolygonFace::Back:         glFace = GL_BACK; break;
        case PolygonFace::FrontAndBack: glFace = GL_FRONT_AND_BACK; break;
        default: glFace = GL_FRONT_AND_BACK; break;
    }

    glPolygonMode(glFace, glMode);
}

void RenderState::enableBlend(bool enable) {
    if (enable) glEnable(GL_BLEND);
    else glDisable(GL_BLEND);
}

void RenderState::setBlendFunc() {
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}
