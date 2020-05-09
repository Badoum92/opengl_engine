#include "texture.hh"

#include <glad/glad.h>
#include <iostream>

#include "window.hh"
#include "stb_image.hh"

std::unordered_map<std::string, std::shared_ptr<Texture>> Texture::textures_;

Texture::Texture()
{
    type_ = aiTextureType_NONE;
    glGenTextures(1, &id_);
    create_empty();
}

Texture::Texture(const std::string& path, aiTextureType type)
{
    type_ = type;
    glGenTextures(1, &id_);
    from_file(path);
}

Texture::~Texture()
{
    glDeleteTextures(1, &id_);
}

void Texture::create_empty()
{
    bind();
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, WIDTH, HEIGHT, 0, GL_RGB,
                 GL_UNSIGNED_BYTE, NULL);
}

void Texture::from_file(const std::string& path)
{
    bind();
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    int w, h, nb_chans;
    unsigned char* data = stbi_load(path.c_str(), &w, &h, &nb_chans, 0);
    if (data == nullptr)
    {
        std::cerr << "Texture: Could not load file: " + path;
        exit(1);
    }
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, w, h, 0,
                 nb_chans == 3 ? GL_RGB : GL_RGBA, GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);
    unbind();
    stbi_image_free(data);
}

void Texture::bind() const
{
    glBindTexture(GL_TEXTURE_2D, id_);
}

void Texture::unbind() const
{
    glBindTexture(GL_TEXTURE_2D, 0);
}

unsigned Texture::get_id() const
{
    return id_;
}

aiTextureType Texture::get_type() const
{
    return type_;
}

std::shared_ptr<Texture> Texture::get_or_create(const std::string& path,
                                                aiTextureType type)
{
    auto it = textures_.find(path);
    if (it != textures_.end() && it->second->type_ == type)
    {
        return it->second;
    }
    auto tex = std::make_shared<Texture>(path, type);
    textures_[path] = tex;
    return tex;
}

void Texture::active(unsigned i)
{
    glActiveTexture(GL_TEXTURE0 + i);
}
