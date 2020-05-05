#include "texture.hh"

#include <glad/glad.h>
#include <iostream>
#include <cstdlib>

#include "stb_image.hh"

std::unordered_map<std::string, std::shared_ptr<Texture>> Texture::textures;

Texture::Texture(const std::string& path)
{
    load(path);
    name = path;
}

Texture::~Texture()
{
    glDeleteTextures(1, &id);
}

void Texture::update(const std::string& path)
{
    glDeleteTextures(1, &id);
    id = 0;
    load(path);
}

void Texture::load(const std::string& path)
{
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
        std::cerr << "Could not load texture: " + path;
        exit(1);
    }
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, w, h, 0,
                 nb_chans == 3 ? GL_RGB : GL_RGBA, GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);
    stbi_image_free(data);
    glBindTexture(GL_TEXTURE_2D, 0);
}

void Texture::bind() const
{
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, id);
}

std::shared_ptr<Texture> Texture::get_texture(const std::string& path)
{
    if (textures.find(path) != textures.end())
    {
        return textures[path];
    }
    auto texture = std::make_shared<Texture>(path);
    textures[path] = texture;
    return texture;
}
