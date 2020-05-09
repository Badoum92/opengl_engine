#pragma once

#include <memory>

class VertexBuffer
{
public:
    VertexBuffer();
    VertexBuffer(const float* data, unsigned size);
    ~VertexBuffer();

    void update(const float* data, unsigned size, int type);

    void bind() const;
    void unbind() const;

    static std::shared_ptr<VertexBuffer> create(const float* data,
                                                unsigned size);

private:
    unsigned id;
};
