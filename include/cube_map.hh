#pragma once

#include <string>
#include <memory>

#include "gl_buffers/vertex_buffer.hh"
#include "gl_buffers/vertex_buffer_layout.hh"
#include "gl_buffers/vertex_array.hh"
#include "shader.hh"

class CubeMap
{
public:
    CubeMap(const std::string& path);

    void draw(std::shared_ptr<Shader> shader) const;

    void bind() const;
    void unbind() const;

private:
    unsigned id_;
    VertexBuffer vb_;
    VertexArray va_;

    void load_cubemap(const std::string files[]);
    void setup_buffers();
};
