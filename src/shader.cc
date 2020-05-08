#include "shader.hh"

#include <cstdlib>
#include <iostream>
#include <fstream>
#include <sstream>

Shader::~Shader()
{
    glDeleteShader(shader_);
}

Shader& Shader::add(const std::string& path, Type shader_type)
{
    std::string src = read_shader(path);
    shader_handles_[shader_type] = compile_shader(src.c_str(), shader_type);
    return *this;
}

std::string Shader::read_shader(const std::string& path)
{
    std::string src;
    std::ifstream shader_file;
    shader_file.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    try
    {
        shader_file.open(path);
        std::stringstream shader_stream;
        shader_stream << shader_file.rdbuf();
        shader_file.close();
        src = shader_stream.str();
    }
    catch (std::ifstream::failure e)
    {
        std::cerr << "Shader: Could not read file: " + path;
        exit(1);
    }
    return src;
}

int Shader::compile_shader(const char* src, Type shader_type)
{
    int shader = glCreateShader(shader_type);
    glShaderSource(shader, 1, &src, NULL);
    glCompileShader(shader);
    int success;
    char info_log[512];
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(shader, 512, NULL, info_log);
        std::cerr << "Shader: " << shader_type_name(shader_type)
                  << ": Compilation failed:\n"
                  << info_log << "\n";
        exit(1);
    }
    return shader;
}

void Shader::link()
{
    glDeleteProgram(shader_);
    shader_ = glCreateProgram();
    for (const auto& shader : shader_handles_)
        glAttachShader(shader_, shader.second);
    glLinkProgram(shader_);

    int success;
    char info_log[512];
    glGetProgramiv(shader_, GL_LINK_STATUS, &success);
    if (!success)
    {
        glGetProgramInfoLog(shader_, 512, NULL, info_log);
        std::cerr << "Shader: Link failed:\n" << info_log << "\n";
        exit(1);
    }
    for (const auto& shader : shader_handles_)
        glDeleteShader(shader.second);
    shader_handles_.clear();
}

void Shader::bind() const
{
    glUseProgram(shader_);
}

std::string Shader::shader_type_name(Type shader_type)
{
    switch (shader_type)
    {
    case Type::VERTEX:
        return "Vertex";
    case Type::FRAGMENT:
        return "Fragment";
    case Type::GEOMETRY:
        return "Geometry";
    }
}

GLint Shader::get_location(const char* name) const
{
    if (locations_.find(name) != locations_.end())
        return locations_[name];
    GLint location = glGetUniformLocation(shader_, name);
    locations_[name] = location;
    if (location == -1)
        std::cerr << "Shader: uniform '" << name << "' not found\n";
    return location;
}

void Shader::uniform(const char* name, const int& val, int size) const
{
    auto location = get_location(name);
    glUniform1iv(location, size, &val);
}

void Shader::uniform(const char* name, const float& val, int size) const
{
    auto location = get_location(name);
    glUniform1fv(location, size, &val);
}

void Shader::uniform(const char* name, const glm::vec2& val, int size) const
{
    auto location = get_location(name);
    glUniform2fv(location, size, &val[0]);
}

void Shader::uniform(const char* name, const glm::vec3& val, int size) const
{
    auto location = get_location(name);
    glUniform3fv(location, size, &val[0]);
}

void Shader::uniform(const char* name, const glm::vec4& val, int size) const
{
    auto location = get_location(name);
    glUniform4fv(location, size, &val[0]);
}

void Shader::uniform(const char* name, const glm::mat2& val, int size) const
{
    auto location = get_location(name);
    glUniformMatrix2fv(location, size, GL_FALSE, &val[0][0]);
}

void Shader::uniform(const char* name, const glm::mat3& val, int size) const
{
    auto location = get_location(name);
    glUniformMatrix3fv(location, size, GL_FALSE, &val[0][0]);
}

void Shader::uniform(const char* name, const glm::mat4& val, int size) const
{
    auto location = get_location(name);
    glUniformMatrix4fv(location, size, GL_FALSE, &val[0][0]);
}
