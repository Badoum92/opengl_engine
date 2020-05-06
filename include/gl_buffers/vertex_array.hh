#pragma once

#include "gl_buffers/vertex_buffer.hh"
#include "gl_buffers/vertex_buffer_layout.hh"

class VertexArray
{
public:
    VertexArray(const VertexBuffer& vb, const VertexBufferLayout& layout,
                unsigned location = 0);
    ~VertexArray();

    void bind() const;
    void unbind() const;

private:
    unsigned id;
};
