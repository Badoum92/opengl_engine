#include "gl_buffers/vertex_buffer.hh"

#include <glad/glad.h>

VertexBuffer::VertexBuffer()
{
    glGenBuffers(1, &id);
}

VertexBuffer::VertexBuffer(const float* data, unsigned size)
{
    glGenBuffers(1, &id);
    update(data, size, GL_STATIC_DRAW);
}

VertexBuffer::~VertexBuffer()
{
    glDeleteBuffers(1, &id);
}

void VertexBuffer::update(const float* data, unsigned size, int type)
{
    bind();
    glBufferData(GL_ARRAY_BUFFER, size, data, type);
}

void VertexBuffer::bind() const
{
    glBindBuffer(GL_ARRAY_BUFFER, id);
}

void VertexBuffer::unbind() const
{
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

std::shared_ptr<VertexBuffer> VertexBuffer::create(const float* data,
                                                   unsigned size)
{
    return std::make_shared<VertexBuffer>(data, size);
}
