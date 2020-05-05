#include "imgui_windows.hh"

#include <iostream>
#include <imgui.h>
#include <examples/imgui_impl_glfw.h>
#include <examples/imgui_impl_opengl3.h>

#include "time.hh"
#include "window.hh"

namespace ImGuiWindows
{
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
        ImGui::SetWindowSize(ImVec2(200, 100));
        ImGui::Text("FPS: %u", Time::fps);

        ImGui::Checkbox("Wireframe", &wireframe_enabled);
        if (wireframe_enabled != Window::wireframe_enabled())
        {
            Window::set_polygon_mode(wireframe_enabled ? GL_LINE : GL_FILL);
        }

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
