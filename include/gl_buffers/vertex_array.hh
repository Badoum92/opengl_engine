#pragma once

#include <memory>

#include "gl_buffers/vertex_buffer.hh"
#include "gl_buffers/vertex_buffer_layout.hh"

class VertexArray
{
public:
    VertexArray();
    VertexArray(const VertexBuffer& vb, const VertexBufferLayout& layout);
    ~VertexArray();

    void add_buffer(const VertexBuffer& vb, const VertexBufferLayout& layout);

    void bind() const;
    void unbind() const;

    static std::shared_ptr<VertexArray>
    create(const VertexBuffer& vb, const VertexBufferLayout& layout);

private:
    unsigned id;
};
