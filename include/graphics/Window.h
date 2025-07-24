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
    std::string title = "PixlEngine";
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

    void resize(const unsigned int& width, const unsigned int& height);
    unsigned int getWidth() const;
    unsigned int getHeight() const;
    float getAspectRatio() const;

    // Utilitaires
    void setVSync(bool enabled);

private:
    GLFWwindow* m_window = nullptr;
    unsigned int m_width = 0;
    unsigned int m_height = 0;
    ResizeCallback m_resizeCallback;

    void setFullscreen(bool fullscreen);
};

#endif //PIXLENGINE_WINDOW_H
