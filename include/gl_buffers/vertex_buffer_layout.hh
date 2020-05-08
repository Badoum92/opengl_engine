#pragma once

#include <vector>
#include <glad/glad.h>

struct VertexBufferElement
{
    VertexBufferElement(GLint c, GLenum t, GLboolean n, GLsizei o)
        : count(c)
        , type(t)
        , normalized(n)
        , offset(o)
    {}

    GLint count;
    GLenum type;
    GLboolean normalized;
    GLsizei offset;
};

class VertexBufferLayout
{
public:
    VertexBufferLayout() = default;

    size_t nb_elements() const;
    GLsizei get_stride() const;
    const VertexBufferElement& operator[](unsigned i) const;

    template <typename T>
    void push(GLint count);

private:
    std::vector<VertexBufferElement> elements;
    GLsizei stride = 0;
};
