#include "gl_buffers/vertex_array.hh"

VertexArray::VertexArray()
{
    glGenVertexArrays(1, &id);
}

void VertexArray::add_buffer(const VertexBuffer& vb,
                             const VertexBufferLayout& layout,
                             unsigned location) const
{
    vb.bind();
    bind();
    unsigned offset = 0;
    for (unsigned i = 0; i < layout.get_elements().size(); ++i)
    {
        const auto& elt = layout.get_elements()[i];
        glVertexAttribPointer(location, elt.count, elt.type, elt.normalized,
                              layout.get_stride(), (void*)offset);
        glEnableVertexAttribArray(location++);
        offset += elt.count * sizeof(elt.type);
    }
}

VertexArray::~VertexArray()
{
    glDeleteVertexArrays(1, &id);
}

void VertexArray::bind() const
{
    glBindVertexArray(id);
}

void VertexArray::unbind() const
{
    glBindVertexArray(0);
}
