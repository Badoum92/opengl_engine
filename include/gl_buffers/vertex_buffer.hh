#pragma once

class VertexBuffer
{
public:
    VertexBuffer();
    VertexBuffer(const float* data, unsigned count);
    ~VertexBuffer();

    void update(const float* data, unsigned count);

    void bind() const;
    void unbind() const;

private:
    unsigned id;
};
