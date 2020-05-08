#pragma once

#include <string>
#include <vector>
#include <memory>
#include <assimp/scene.h>

#include "shader.hh"
#include "mesh.hh"

class Model
{
public:
    Model(const std::string& path);

    void draw(std::shared_ptr<Shader> shader) const;

private:
    std::string directory_;
    std::vector<Mesh> meshes_;
    glm::mat4 transform_ = glm::mat4(1);

    void process_node(aiNode* node, const aiScene* scene);
};
