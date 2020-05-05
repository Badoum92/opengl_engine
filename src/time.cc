#include "time.hh"

#include <GLFW/glfw3.h>
#include <iostream>

float Time::delta_time = 0.0f;
float Time::last_frame = 0.0f;
unsigned Time::fps = 0;

void Time::update()
{
    float current_frame = glfwGetTime();
    delta_time = current_frame - last_frame;
    last_frame = current_frame;

    fps = 1.0f / Time::delta_time;
}
