#pragma once

#include <string>
#include <memory>
#include <unordered_map>

class Texture
{
public:
    Texture(const std::string& path);
    ~Texture();
    void update(const std::string& path);
    void load(const std::string& path);
    void bind() const;

    static std::shared_ptr<Texture> get_texture(const std::string& path);

private:
    unsigned id;
    std::string name;

    static std::unordered_map<std::string, std::shared_ptr<Texture>> textures;
};
