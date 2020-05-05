#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

class Camera
{
public:
    enum class Movement
    {
        FORWARD,
        BACKWARD,
        LEFT,
        RIGHT,
        UP,
        DOWN
    };

    static void init(const glm::vec3& position,
                     glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f),
                     float yaw = -90.0f, float pitch = 0.0f);

    static const glm::vec3& get_position();
    static const glm::vec3& get_front();

    static glm::mat4 get_view_matrix();
    static glm::mat4 get_proj_matrix();

    static void process_keyboard(Movement direction);
    static void process_mouse_movement(float x_offset, float y_offset,
                                       GLboolean constrain_pitch = true);
    static void process_mouse_scroll(float y_offset);

    static void add_speed(float speed);

private:
    static glm::vec3 position_;
    static glm::vec3 forward_;
    static glm::vec3 front_;
    static glm::vec3 up_;
    static glm::vec3 right_;
    static glm::vec3 world_up_;
    static glm::mat4 projection_;

    static float yaw_;
    static float pitch_;
    static float movement_speed_;
    static float mouse_sensitivity_;
    static float zoom_;

    static void update_vectors();
};
