#pragma once

#include <string>
#include <unordered_map>
#include <memory>
#include <assimp/scene.h>
#include <glad/glad.h>

class Texture
{
public:
    Texture(unsigned width, unsigned height);
    Texture(const std::string& path, aiTextureType type);
    ~Texture();

    void bind() const;
    void unbind() const;

    unsigned get_id() const;
    aiTextureType get_type() const;

    static std::shared_ptr<Texture> get_or_create(const std::string& path,
                                                  aiTextureType type);
    static void active(unsigned i);

private:
    aiTextureType type_;
    unsigned id_;

    void create_empty(unsigned width, unsigned height,
                      int type = GL_UNSIGNED_BYTE);
    void from_file(const std::string& path);

    static std::unordered_map<std::string, std::shared_ptr<Texture>> textures_;
};
