//
// Created by ChiroYuki on 19/07/2025.
//

#ifndef PIXLENGINE_RENDERER_H
#define PIXLENGINE_RENDERER_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>
#include "Mesh.h"
#include "Shader.h"

struct RenderStats {
    int drawCalls = 0;
    int vertices = 0;
    int triangles = 0;
};

class Renderer {
public:
    Renderer() = default;
    ~Renderer();

    // Non-copyable but movable
    Renderer(const Renderer&) = delete;
    Renderer& operator=(const Renderer&) = delete;
    Renderer(Renderer&&) = default;
    Renderer& operator=(Renderer&&) = default;

    bool initialize();
    void shutdown();

    void beginFrame();
    void endFrame();

    void clear(const glm::vec3& color = glm::vec3(0.2f, 0.3f, 0.3f));
    void setViewport(int x, int y, int width, int height);

    // Configuration
    void enableDepthTest(bool enable = true);
    void enableFaceCulling(bool enable = true);
    void enableBlending(bool enable = true);
    void setWireframeMode(bool enabled);

    const RenderStats& getStats() const { return m_stats; }
    void resetStats() { m_stats = {}; }

    bool isInitialized() const { return m_initialized; }

private:
    RenderStats m_stats;
    bool m_initialized = false;
};

#include "Renderer.inl"

#endif //PIXLENGINE_RENDERER_H