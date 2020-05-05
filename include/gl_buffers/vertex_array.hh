#pragma once

#include "gl_buffers/vertex_buffer.hh"
#include "gl_buffers/vertex_buffer_layout.hh"

class VertexArray
{
public:
    VertexArray();
    ~VertexArray();

    void add_buffer(const VertexBuffer& vb, const VertexBufferLayout& layout,
                    unsigned location = 0) const;

    void bind() const;
    void unbind() const;

private:
    unsigned id;
};
