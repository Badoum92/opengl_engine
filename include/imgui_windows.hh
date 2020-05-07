#pragma once

#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

namespace ImGuiWindows
{
    extern glm::vec3 light_pos;

    void init(GLFWwindow* window);
    void shutdown();
    void info();
    void render();
} // namespace ImGuiWindows
