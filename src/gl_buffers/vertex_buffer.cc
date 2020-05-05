#include "gl_buffers/vertex_buffer.hh"

#include <glad/glad.h>

VertexBuffer::VertexBuffer(const float* data, unsigned count)
{
    glGenBuffers(1, &id);
    bind();
    glBufferData(GL_ARRAY_BUFFER, count * sizeof(float), data, GL_STATIC_DRAW);
}

VertexBuffer::~VertexBuffer()
{
    glDeleteBuffers(1, &id);
}

void VertexBuffer::update(const float* data, unsigned count)
{
    glDeleteBuffers(1, &id);
    glGenBuffers(1, &id);
    bind();
    glBufferData(GL_ARRAY_BUFFER, count * sizeof(float), data, GL_STATIC_DRAW);
}

void VertexBuffer::bind() const
{
    glBindBuffer(GL_ARRAY_BUFFER, id);
}

void VertexBuffer::unbind() const
{
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}
