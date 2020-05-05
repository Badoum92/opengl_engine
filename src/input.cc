#include "input.hh"

#include "camera.hh"
#include "window.hh"

void process_input(GLFWwindow* window)
{
    if (Window::cursor_enabled())
        return;

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        Camera::process_keyboard(Camera::Movement::FORWARD);
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        Camera::process_keyboard(Camera::Movement::BACKWARD);
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        Camera::process_keyboard(Camera::Movement::LEFT);
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        Camera::process_keyboard(Camera::Movement::RIGHT);
    if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
        Camera::process_keyboard(Camera::Movement::UP);
    if (glfwGetKey(window, GLFW_KEY_C) == GLFW_PRESS)
        Camera::process_keyboard(Camera::Movement::DOWN);

    if (glfwGetKey(window, GLFW_KEY_KP_ADD) == GLFW_PRESS)
        Camera::add_speed(1.0f);
    if (glfwGetKey(window, GLFW_KEY_KP_SUBTRACT) == GLFW_PRESS)
        Camera::add_speed(-1.0f);
}

void mouse_callback(GLFWwindow*, double x_pos, double y_pos)
{
    static float last_x = x_pos;
    static float last_y = y_pos;

    if (Window::cursor_enabled())
        return;

    float x_offset = x_pos - last_x;
    float y_offset = last_y - y_pos;

    last_x = x_pos;
    last_y = y_pos;

    Camera::process_mouse_movement(x_offset, y_offset);
}

void scroll_callback(GLFWwindow*, double, double y_offset)
{
    if (Window::cursor_enabled())
        return;

    Camera::process_mouse_scroll(y_offset);
}

void key_callback(GLFWwindow* window, int key, int, int action, int)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    if (glfwGetKey(window, GLFW_KEY_LEFT_ALT) == GLFW_PRESS)
    {
        Window::set_cursor(!Window::cursor_enabled());
    }
}
