#include "gl_buffers/index_buffer.hh"

#include <glad/glad.h>

IndexBuffer::IndexBuffer(const unsigned* data, unsigned count)
{
    glGenBuffers(1, &id);
    bind();
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(unsigned), data,
                 GL_STATIC_DRAW);
    count_ = count;
}

IndexBuffer::~IndexBuffer()
{
    glDeleteBuffers(1, &id);
}

unsigned IndexBuffer::get_count() const
{
    return count_;
}

void IndexBuffer::update(const unsigned* data, unsigned count)
{
    glDeleteBuffers(1, &id);
    glGenBuffers(1, &id);
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
