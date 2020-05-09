#include "camera.hh"

#include "time.hh"
#include "window.hh"

glm::vec3 Camera::position_;
glm::vec3 Camera::forward_;
glm::vec3 Camera::front_;
glm::vec3 Camera::up_;
glm::vec3 Camera::right_;
glm::vec3 Camera::world_up_;
glm::mat4 Camera::projection_;
float Camera::yaw_;
float Camera::pitch_;
float Camera::movement_speed_;
float Camera::mouse_sensitivity_;
float Camera::zoom_;

void Camera::init(const glm::vec3& position, glm::vec3 up, float yaw,
                  float pitch)
{
    position_ = position;
    front_ = glm::vec3(0.0f, 0.0f, -1.0f);
    forward_ = front_;
    up_ = up;
    world_up_ = up;
    yaw_ = yaw;
    pitch_ = pitch;

    movement_speed_ = 200.0f;
    mouse_sensitivity_ = 0.1f;
    zoom_ = 45.0f;

    update_vectors();

    float near = 0.1f;
    float far = 30000.0f;
    projection_ = glm::perspective(glm::radians(zoom_),
                                   (float)WIDTH / (float)HEIGHT, near, far);
}

const glm::vec3& Camera::get_position()
{
    return position_;
}

const glm::vec3& Camera::get_front()
{
    return front_;
}

void Camera::update_vectors()
{
    glm::vec3 front;
    front.x = cos(glm::radians(yaw_)) * cos(glm::radians(pitch_));
    front.y = sin(glm::radians(pitch_));
    front.z = sin(glm::radians(yaw_)) * cos(glm::radians(pitch_));
    front_ = glm::normalize(front);
    right_ = glm::normalize(glm::cross(front_, world_up_));
    up_ = glm::normalize(glm::cross(right_, front_));
    forward_ = glm::normalize(glm::cross(world_up_, right_));
}

glm::mat4 Camera::get_view_matrix()
{
    return glm::lookAt(position_, position_ + front_, up_);
}

glm::mat4 Camera::get_proj_matrix()
{
    return projection_;
}

float& Camera::get_speed()
{
    return movement_speed_;
}

void Camera::set_speed(float speed)
{
    movement_speed_ = speed;
}

void Camera::process_keyboard(Camera::Movement direction)
{
    float velocity = movement_speed_ * Time::delta_time;
    if (direction == Movement::FORWARD)
        position_ += forward_ * velocity;
    if (direction == Movement::BACKWARD)
        position_ -= forward_ * velocity;
    if (direction == Movement::LEFT)
        position_ -= right_ * velocity;
    if (direction == Movement::RIGHT)
        position_ += right_ * velocity;
    if (direction == Movement::UP)
        position_ += world_up_ * velocity;
    if (direction == Movement::DOWN)
        position_ -= world_up_ * velocity;
}

void Camera::process_mouse_movement(float x_offset, float y_offset,
                                    GLboolean constrain_pitch)
{
    x_offset *= mouse_sensitivity_;
    y_offset *= mouse_sensitivity_;

    yaw_ += x_offset;
    pitch_ += y_offset;

    if (constrain_pitch)
    {
        if (pitch_ > 89.0f)
            pitch_ = 89.0f;
        if (pitch_ < -89.0f)
            pitch_ = -89.0f;
    }

    update_vectors();
}

void Camera::process_mouse_scroll(float y_offset)
{
    if (zoom_ >= 1.0f && zoom_ <= 45.0f)
        zoom_ -= y_offset;
    if (zoom_ <= 1.0f)
        zoom_ = 1.0f;
    if (zoom_ >= 45.0f)
        zoom_ = 45.0f;

    projection_ = glm::perspective(glm::radians(zoom_),
                                   (float)WIDTH / (float)HEIGHT, 0.1f, 1000.0f);
}
