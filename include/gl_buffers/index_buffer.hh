#pragma once

class IndexBuffer
{
public:
    IndexBuffer();
    IndexBuffer(const unsigned* data, unsigned count);
    ~IndexBuffer();

    unsigned nb_indices() const;

    void update(const unsigned* data, unsigned count);

    void bind() const;
    void unbind() const;

private:
    unsigned id;
    unsigned count_;
};
