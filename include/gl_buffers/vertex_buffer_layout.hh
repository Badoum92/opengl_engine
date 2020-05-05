#pragma once

#include <vector>
#include <glad/glad.h>

struct VertexBufferElement
{
    VertexBufferElement(GLint c, GLenum t, GLboolean n)
        : count(c)
        , type(t)
        , normalized(n)
    {}

    GLint count;
    GLenum type;
    GLboolean normalized;
};

class VertexBufferLayout
{
public:
    VertexBufferLayout() = default;

    const std::vector<VertexBufferElement>& get_elements() const;
    GLsizei get_stride() const;

    template <typename T>
    void push(GLint count);

private:
    std::vector<VertexBufferElement> elements;
    GLsizei stride = 0;
};
