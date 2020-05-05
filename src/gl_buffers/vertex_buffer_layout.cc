#include "gl_buffers/vertex_buffer_layout.hh"

const std::vector<VertexBufferElement>& VertexBufferLayout::get_elements() const
{
    return elements;
}

GLsizei VertexBufferLayout::get_stride() const
{
    return stride;
}

template <>
void VertexBufferLayout::push<float>(GLint count)
{
    elements.emplace_back(count, GL_FLOAT, GL_FALSE);
    stride += count * sizeof(float);
}
