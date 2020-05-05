#pragma once

struct Time
{
    static float delta_time;
    static float last_frame;
    static unsigned fps;
    static void update();
};
