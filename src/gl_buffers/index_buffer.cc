#include "gl_buffers/index_buffer.hh"

#include <glad/glad.h>

IndexBuffer::IndexBuffer()
{
    glGenBuffers(1, &id);
}

IndexBuffer::IndexBuffer(const unsigned* data, unsigned count)
{
    glGenBuffers(1, &id);
    update(data, count);
}

IndexBuffer::~IndexBuffer()
{
    glDeleteBuffers(1, &id);
}

unsigned IndexBuffer::nb_indices() const
{
    return count_;
}

void IndexBuffer::update(const unsigned* data, unsigned count)
{
    bind();
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(unsigned), data,
                 GL_STATIC_DRAW);
    count_ = count;
}

void IndexBuffer::bind() const
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id);
}

void IndexBuffer::unbind() const
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}
