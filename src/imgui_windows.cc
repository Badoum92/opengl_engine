#include "imgui_windows.hh"

#include <iostream>
#include <imgui.h>
#include <examples/imgui_impl_glfw.h>
#include <examples/imgui_impl_opengl3.h>

#include "time.hh"
#include "window.hh"
#include "camera.hh"

namespace ImGuiWindows
{
    glm::vec3 light_pos = glm::vec3(0);

    void init(GLFWwindow* window)
    {
        IMGUI_CHECKVERSION();
        ImGui::CreateContext();
        ImGui::StyleColorsDark();
        ImGui_ImplGlfw_InitForOpenGL(window, true);
        ImGui_ImplOpenGL3_Init("#version 330 core");
    }

    void shutdown()
    {
        ImGui_ImplOpenGL3_Shutdown();
        ImGui_ImplGlfw_Shutdown();
        ImGui::DestroyContext();
    }

    void info()
    {
        static bool wireframe_enabled = false;

        ImGui::Begin("Info");

        ImGui::SetWindowPos(ImVec2(0, 0));
        ImGui::SetWindowSize(ImVec2(200, 200));
        ImGui::Text("FPS: %u", Time::fps);

        ImGui::Checkbox("Wireframe", &wireframe_enabled);
        if (wireframe_enabled != Window::wireframe_enabled())
        {
            Window::set_polygon_mode(wireframe_enabled ? GL_LINE : GL_FILL);
        }

        ImGui::SliderFloat("Speed", &Camera::get_speed(), 0.0f, 500.0f);

        ImGui::SliderFloat("light x", &light_pos.x, -200, 200);
        ImGui::SliderFloat("light y", &light_pos.y, -200, 200);
        ImGui::SliderFloat("light z", &light_pos.z, -200, 200);

        ImGui::End();
    }

    void render()
    {
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        ImGuiWindows::info();

        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
    }
} // namespace ImGuiWindows
