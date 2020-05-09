#include "window.hh"

#include <iostream>
#include <stb_image.hh>

#include "input.hh"

void framebuffer_size_callback(GLFWwindow*, int width, int height)
{
    glViewport(0, 0, width, height);
}

GLFWwindow* create_window()
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window =
        glfwCreateWindow(WIDTH, HEIGHT, "glfw window", nullptr, nullptr);

    if (window == nullptr)
    {
        std::cerr << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return nullptr;
    }

    glfwSetWindowPos(window, 200, 100);
    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cerr << "Failed to initialize GLAD" << std::endl;
        return nullptr;
    }

    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetCursorPosCallback(window, mouse_callback);
    glfwSetScrollCallback(window, scroll_callback);
    glfwSetKeyCallback(window, key_callback);
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    glEnable(GL_DEPTH_TEST);

    glfwSwapInterval(0);

    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

    // glEnable(GL_CULL_FACE);
    // glCullFace(GL_BACK);
    // glFrontFace(GL_CCW);

    return window;
}

Window* Window::instance_ = nullptr;

Window* Window::instance()
{
    if (instance_ == nullptr)
    {
        instance_ = new Window(WIDTH, HEIGHT);
    }
    return instance_;
}

GLFWwindow* Window::glfw_window()
{
    return instance_->window_;
}

void Window::set_cursor(bool value)
{
    auto mode = value ? GLFW_CURSOR_NORMAL : GLFW_CURSOR_DISABLED;
    glfwSetInputMode(instance_->window_, GLFW_CURSOR, mode);
    instance_->cursor_enabled_ = value;
}

bool Window::cursor_enabled()
{
    return instance_->cursor_enabled_;
}

void Window::set_polygon_mode(GLenum mode)
{
    glPolygonMode(GL_FRONT_AND_BACK, mode);
    instance_->wireframe_enabled_ = mode == GL_LINE;
}

bool Window::wireframe_enabled()
{
    return instance_->wireframe_enabled_;
}

Window::Window(unsigned width, unsigned height)
    : width_(width)
    , height_(height)
{
    window_ = create_window();
}

Window::~Window()
{
    glfwDestroyWindow(window_);
}
