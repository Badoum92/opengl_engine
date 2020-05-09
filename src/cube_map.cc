#include "cube_map.hh"

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <filesystem>
#include <iostream>

#include "stb_image.hh"
#include "camera.hh"

CubeMap::CubeMap(const std::string& path)
{
    if (!std::filesystem::is_directory(path))
    {
        std::cerr << "CubeMap: " << path << " is not a directory\n";
        exit(1);
    }

    glGenTextures(1, &id_);

    // clang-format off
    const std::string files[] = {
        path + "/right.jpg",
        path + "/left.jpg",
        path + "/top.jpg",
        path + "/bottom.jpg",
        path + "/front.jpg",
        path + "/back.jpg",
    };
    // clang-format on

    load_cubemap(files);
    setup_buffers();
}

void CubeMap::draw(std::shared_ptr<Shader> shader) const
{
    glDepthFunc(GL_LEQUAL);
    shader->bind();
    shader->uniform("u_view", glm::mat4(glm::mat3(Camera::get_view_matrix())));
    shader->uniform("u_projection", Camera::get_proj_matrix());
    va_.bind();
    bind();
    glDrawArrays(GL_TRIANGLES, 0, 36);
    glDepthFunc(GL_LESS);
}

void CubeMap::bind() const
{
    glBindTexture(GL_TEXTURE_CUBE_MAP, id_);
}

void CubeMap::unbind() const
{
    glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
}

void CubeMap::load_cubemap(const std::string files[])
{
    bind();
    int w, h, nb_chans;
    for (unsigned i = 0; i < 6; ++i)
    {
        unsigned char* data = stbi_load(files[i].c_str(), &w, &h, &nb_chans, 0);
        if (data)
        {
            glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGB, w, h, 0,
                         nb_chans == 3 ? GL_RGB : GL_RGBA, GL_UNSIGNED_BYTE,
                         data);
        }
        else
        {
            std::cerr << "CubeMap: Could not load file '" << files[i] << "'\n";
            exit(1);
        }
        stbi_image_free(data);
    }
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
    unbind();
}

void CubeMap::setup_buffers()
{
    // clang-format off
    float vertices[] = {
        -0.5f,  0.5f, -0.5f,
        -0.5f, -0.5f, -0.5f,
         0.5f, -0.5f, -0.5f,
         0.5f, -0.5f, -0.5f,
         0.5f,  0.5f, -0.5f,
        -0.5f,  0.5f, -0.5f,

        -0.5f, -0.5f,  0.5f,
        -0.5f, -0.5f, -0.5f,
        -0.5f,  0.5f, -0.5f,
        -0.5f,  0.5f, -0.5f,
        -0.5f,  0.5f,  0.5f,
        -0.5f, -0.5f,  0.5f,

         0.5f, -0.5f, -0.5f,
         0.5f, -0.5f,  0.5f,
         0.5f,  0.5f,  0.5f,
         0.5f,  0.5f,  0.5f,
         0.5f,  0.5f, -0.5f,
         0.5f, -0.5f, -0.5f,

        -0.5f, -0.5f,  0.5f,
        -0.5f,  0.5f,  0.5f,
         0.5f,  0.5f,  0.5f,
         0.5f,  0.5f,  0.5f,
         0.5f, -0.5f,  0.5f,
        -0.5f, -0.5f,  0.5f,

        -0.5f,  0.5f, -0.5f,
         0.5f,  0.5f, -0.5f,
         0.5f,  0.5f,  0.5f,
         0.5f,  0.5f,  0.5f,
        -0.5f,  0.5f,  0.5f,
        -0.5f,  0.5f, -0.5f,

        -0.5f, -0.5f, -0.5f,
        -0.5f, -0.5f,  0.5f,
         0.5f, -0.5f, -0.5f,
         0.5f, -0.5f, -0.5f,
        -0.5f, -0.5f,  0.5f,
         0.5f, -0.5f,  0.5f
    };
    // clang-format on

    VertexBufferLayout layout;
    layout.push<float>(3); // position
    vb_.update(vertices, sizeof(vertices));
    va_.add_buffer(vb_, layout);
}
