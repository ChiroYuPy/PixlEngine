//
// Created by ChiroYuki on 19/07/2025.
//

#ifndef PIXLENGINE_WINDOW_H
#define PIXLENGINE_WINDOW_H

#include <GLT.h>
#include <string>
#include <functional>
#include <utility>

struct WindowConfig {
    int width = 1280;
    int height = 720;
    std::string title = "voxel Engine";
    bool fullscreen = false;
    bool vsync = true;
};

class Window {
public:
    using ResizeCallback = std::function<void(int, int)>;

    Window() = default;
    ~Window();

    bool initialize(const WindowConfig& config);
    void shutdown();

    void swapBuffers();
    void pollEvents();

    bool shouldClose() const;
    void setShouldClose(bool close);

    GLFWwindow* getGLFWWindow() const { return m_window; }

    int getWidth() const { return m_width; }
    int getHeight() const { return m_height; }
    float getAspectRatio() const { return (float)m_width / (float)m_height; }

    void setResizeCallback(ResizeCallback callback) { m_resizeCallback = std::move(callback); }

    // Utilitaires
    void setVSync(bool enabled);

private:
    static void framebufferSizeCallback(GLFWwindow* window, int width, int height);

    GLFWwindow* m_window = nullptr;
    int m_width = 0;
    int m_height = 0;
    ResizeCallback m_resizeCallback;

    void setFullscreen(bool fullscreen);
};

#endif //PIXLENGINE_WINDOW_H
