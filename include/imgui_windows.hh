#pragma once

#include <GLFW/glfw3.h>

namespace ImGuiWindows
{
    void init(GLFWwindow* window);
    void shutdown();
    void info();
    void render();
} // namespace ImGuiWindows
