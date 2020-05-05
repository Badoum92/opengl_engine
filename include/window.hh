#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#define WIDTH 1280
#define HEIGHT 720

class Window
{
public:
    static Window* instance();
    static GLFWwindow* glfw_window();

    static void set_cursor(bool value);
    static bool cursor_enabled();

    static void set_polygon_mode(GLenum mode);
    static bool wireframe_enabled();

private:
    Window(unsigned width, unsigned height);
    ~Window();

    unsigned width_;
    unsigned height_;
    GLFWwindow* window_;

    bool cursor_enabled_ = false;
    bool wireframe_enabled_ = false;

    static Window* instance_;
};

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
GLFWwindow* create_window();
