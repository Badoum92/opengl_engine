#pragma once

class IndexBuffer
{
public:
    IndexBuffer() = default;
    IndexBuffer(const unsigned* data, unsigned count);
    ~IndexBuffer();

    unsigned get_count() const;

    void update(const unsigned* data, unsigned count);

    void bind() const;
    void unbind() const;

private:
    unsigned id;
    unsigned count_;
};
