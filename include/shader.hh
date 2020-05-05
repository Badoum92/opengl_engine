#pragma once

#include <glad/glad.h>
#include <string>
#include <unordered_map>
#include <glm/glm.hpp>
#include <vector>

class Shader
{
public:
    enum Type
    {
        VERTEX = GL_VERTEX_SHADER,
        FRAGMENT = GL_FRAGMENT_SHADER,
        GEOMETRY = GL_GEOMETRY_SHADER
    };

    Shader() = default;
    ~Shader();

    Shader& add(const std::string& path, Type shader_type);
    void link();
    void bind() const;

    void uniform(const char* name, const bool& val) const;
    void uniform(const char* name, const int& val) const;
    void uniform(const char* name, const float& val) const;
    void uniform(const char* name, const glm::vec2& val) const;
    void uniform(const char* name, const glm::vec3& val) const;
    void uniform(const char* name, const glm::vec4& val) const;
    void uniform(const char* name, const glm::mat2& val) const;
    void uniform(const char* name, const glm::mat3& val) const;
    void uniform(const char* name, const glm::mat4& val) const;

private:
    int shader_;
    std::unordered_map<int, int> shader_handles_;
    mutable std::unordered_map<std::string, GLint> locations_;

    GLint get_location(const char* name) const;
    std::string read_shader(const std::string& path);
    int compile_shader(const char* src, Type shader_type);
    static std::string shader_type_name(Type shader_type);
};
