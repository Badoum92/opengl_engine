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

void program_init(GLFWwindow* window)
{
    Camera::init(glm::vec3(0.0f, 0.0f, 0.0f));
    ImGuiWindows::init(window);
}

int main()
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

    // clang-format off
    float vertices[] = {
         0.0f,  0.0f,  1.0f,
        -1.0f,  0.0f,  0.0f,
         1.0f,  0.0f,  0.0f,
         0.0f,  1.0f,  0.0f,
    };

    unsigned indices[] = {
        0, 1, 2,
        1, 2, 3,
        0, 1, 3,
        0, 2, 3
    };
    // clang-format on

    VertexBuffer vb{vertices, sizeof(vertices)};
    IndexBuffer ib{indices, sizeof(indices)};
    VertexBufferLayout layout;
    layout.push<float>(3);
    VertexArray va;
    va.add_buffer(vb, layout);

    while (!glfwWindowShouldClose(window))
    {
        Time::update();
        glfwPollEvents();
        process_input(window);

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        shader->bind();
        shader->uniform("u_model", glm::mat4(1));
        shader->uniform("u_view", Camera::get_view_matrix());
        shader->uniform("u_projection", Camera::get_proj_matrix());
        va.bind();
        ib.bind();
        glDrawElements(GL_TRIANGLES, ib.get_count(), GL_UNSIGNED_INT, 0);

        ImGuiWindows::render();

        glfwSwapBuffers(window);
    }

    ImGuiWindows::shutdown();
    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}
