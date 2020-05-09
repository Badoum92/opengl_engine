#include "gl_buffers/vertex_array.hh"

VertexArray::VertexArray()
{
    glGenVertexArrays(1, &id);
}

VertexArray::VertexArray(const VertexBuffer& vb,
                         const VertexBufferLayout& layout)
{
    glGenVertexArrays(1, &id);
    add_buffer(vb, layout);
}

void VertexArray::add_buffer(const VertexBuffer& vb,
                             const VertexBufferLayout& layout)
{
    vb.bind();
    bind();
    for (unsigned i = 0; i < layout.nb_elements(); ++i)
    {
        const auto& elt = layout[i];
        glVertexAttribPointer(i, elt.count, elt.type, elt.normalized,
                              layout.get_stride(), (void*)elt.offset);
        glEnableVertexAttribArray(i);
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

std::shared_ptr<VertexArray>
VertexArray::create(const VertexBuffer& vb, const VertexBufferLayout& layout)
{
    return std::make_shared<VertexArray>(vb, layout);
}
