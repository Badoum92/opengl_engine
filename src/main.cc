#include <glad/glad.h>
#include <cassert>
#include <iostream>
#include <memory>

#include "shader.hh"
#include "camera.hh"
#include "time.hh"
#include "input.hh"
#include "window.hh"

#include "gl_buffers/vertex_array.hh"
#include "gl_buffers/vertex_buffer.hh"
#include "gl_buffers/vertex_buffer_layout.hh"
#include "gl_buffers/index_buffer.hh"

#include "imgui_windows.hh"

#include "model.hh"

void program_init(GLFWwindow* window)
{
    Camera::init(glm::vec3(0.0f, 0.0f, 0.0f));
    ImGuiWindows::init(window);
}

int main(int argc, char** argv)
{
    Window::instance();
    GLFWwindow* window = Window::glfw_window();
    if (window == nullptr)
    {
        std::cerr << "Could not create window\n";
        exit(1);
    }

    program_init(window);

    auto shader = std::make_shared<Shader>();
    shader->add("../shaders/shader.vert", Shader::Type::VERTEX)
        .add("../shaders/shader.frag", Shader::Type::FRAGMENT)
        .link();

    if (argc < 2)
    {
        std::cerr << "Expected model path\n";
        return 1;
    }

    Model model{argv[1]};

    while (!glfwWindowShouldClose(window))
    {
        Time::update();
        glfwPollEvents();
        process_input(window);

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        shader->bind();
        shader->uniform("u_view", Camera::get_view_matrix());
        shader->uniform("u_projection", Camera::get_proj_matrix());
        shader->uniform("u_light_pos", ImGuiWindows::light_pos);
        model.draw(shader);

        ImGuiWindows::render();

        glfwSwapBuffers(window);
    }

    ImGuiWindows::shutdown();
    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}
