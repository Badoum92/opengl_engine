#include "texture.hh"

#include <glad/glad.h>
#include <iostream>

#include "stb_image.hh"

std::unordered_map<std::string, std::shared_ptr<Texture>> Texture::textures_;

Texture::Texture(const std::string& path, aiTextureType type)
    : type_(type)
    , id_(from_file(path))
    , path_(path)
{}

Texture::~Texture()
{
    glDeleteTextures(1, &id_);
}

unsigned Texture::from_file(const std::string& path)
{
    unsigned id = 0;
    glGenTextures(1, &id);
    glBindTexture(GL_TEXTURE_2D, id);
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
    glBindTexture(GL_TEXTURE_2D, 0);
    stbi_image_free(data);
    return id;
}

void Texture::bind() const
{
    glBindTexture(GL_TEXTURE_2D, id_);
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
