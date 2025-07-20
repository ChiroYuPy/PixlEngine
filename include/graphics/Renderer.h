//
// Created by ChiroYuki on 19/07/2025.
//

#ifndef PIXLENGINE_RENDERER_H
#define PIXLENGINE_RENDERER_H

#include <GLT.h>
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

    bool initialize();
    void shutdown();

    void beginFrame();
    void endFrame();

    void clear(const glm::vec3& color = glm::vec3(0.2f, 0.3f, 0.3f));
    void setViewport(int x, int y, int width, int height);

    // Rendu basique
    void drawMesh(const Mesh& mesh, Shader& shader, const glm::mat4& transform);
    void drawWireframe(const Mesh& mesh, Shader& shader, const glm::mat4& transform);

    // Configuration
    void enableDepthTest(bool enable = true);
    void enableFaceCulling(bool enable = true);
    void enableBlending(bool enable = true);
    void setWireframeMode(bool enabled);

    const RenderStats& getStats() const { return m_stats; }
    void resetStats() { m_stats = {}; }

private:
    RenderStats m_stats;
    bool m_initialized = false;
};

#endif //PIXLENGINE_RENDERER_H
