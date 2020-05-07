#pragma once

#include <glm/glm.hpp>
#include <vector>
#include <unordered_set>
#include <string>
#include <memory>
#include <assimp/scene.h>

#include "gl_buffers/index_buffer.hh"
#include "gl_buffers/vertex_array.hh"
#include "gl_buffers/vertex_buffer.hh"
#include "gl_buffers/vertex_buffer_layout.hh"

#include "texture.hh"
#include "shader.hh"

class Mesh
{
public:
    Mesh(aiMesh* mesh, const aiScene* scene, const std::string& directory);

    void draw(std::shared_ptr<Shader> shader) const;

private:
    struct Vertex
    {
        glm::vec3 position;
        glm::vec3 normal;
        glm::vec2 tex_coords;
        glm::vec3 tangent;
        glm::vec3 bitangent;
    };

    const std::string& directory_;
    std::vector<Vertex> vertices_;
    std::vector<unsigned> indices_;
    std::unordered_set<std::shared_ptr<Texture>> textures_;

    std::shared_ptr<VertexArray> va_;
    std::shared_ptr<VertexBuffer> vb_;
    std::shared_ptr<IndexBuffer> ib_;

    void setup_buffers();
    void load_vertices(aiMesh* mesh);
    void load_indices(aiMesh* mesh);
    void load_material_textures(aiMesh* mesh, const aiScene* scene);
    void load_material_texture_type(aiMaterial* mat, aiTextureType type);
};
