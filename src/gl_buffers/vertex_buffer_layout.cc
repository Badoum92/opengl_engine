#include "gl_buffers/vertex_buffer_layout.hh"

size_t VertexBufferLayout::nb_elements() const
{
    return elements.size();
}

GLsizei VertexBufferLayout::get_stride() const
{
    return stride;
}

const VertexBufferElement& VertexBufferLayout::operator[](unsigned i) const
{
    return elements[i];
}

template <>
void VertexBufferLayout::push<float>(GLint count)
{
    auto prev = elements.rbegin();
    GLsizei offset = 0;
    if (prev != elements.rend())
        offset = prev->offset + sizeof(prev->type) * prev->count;
    elements.emplace_back(count, GL_FLOAT, GL_FALSE, offset);
    stride += count * sizeof(float);
}
