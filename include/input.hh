#pragma once

#include <GLFW/glfw3.h>

void process_input(GLFWwindow* window);
void mouse_callback(GLFWwindow*, double x_pos, double y_pos);
void scroll_callback(GLFWwindow*, double x_offset, double y_offset);
void key_callback(GLFWwindow* window, int key, int scancode, int action,
                  int mods);
