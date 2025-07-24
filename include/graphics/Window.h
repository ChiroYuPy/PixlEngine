//
// Created by ChiroYuki on 19/07/2025.
//

#ifndef PIXLENGINE_WINDOW_H
#define PIXLENGINE_WINDOW_H

#include <GLT.h>
#include <string>
#include <functional>
#include <utility>

class Window {
public:
    using ResizeCallback = std::function<void(int, int)>;

    Window(unsigned int width, unsigned int height, const std::string& title);
    ~Window();

    bool initialize();

    void pollEvents();
    void swapBuffers();
    bool shouldClose() const;

    GLFWwindow* getGLFWWindow() const { return m_window; }

    void resize(const unsigned int& width, const unsigned int& height);
    unsigned int getWidth() const;
    unsigned int getHeight() const;
    float getAspectRatio() const;

private:
    GLFWwindow* m_window = nullptr;
    unsigned int m_width;
    unsigned int m_height;
    std::string m_title;
    ResizeCallback m_resizeCallback;

    void destroyGLFWwindow();
    bool initGLFWwindow();
};

#endif //PIXLENGINE_WINDOW_H
