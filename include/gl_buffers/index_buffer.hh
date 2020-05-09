#pragma once

#include <memory>

class IndexBuffer
{
public:
    IndexBuffer();
    IndexBuffer(const unsigned* data, unsigned count);
    ~IndexBuffer();

    unsigned nb_indices() const;

    void update(const unsigned* data, unsigned count, int type);

    void bind() const;
    void unbind() const;

    static std::shared_ptr<IndexBuffer> create(const unsigned* data,
                                               unsigned count);

private:
    unsigned id;
    unsigned count_;
};
