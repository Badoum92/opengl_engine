#include "model.hh"

#include <iostream>
#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>

#include "camera.hh"

Model::Model(const std::string& path)
{
    Assimp::Importer import;
    const aiScene* scene = import.ReadFile(
        path,
        aiProcess_Triangulate | aiProcess_FlipUVs | aiProcess_GenNormals
            | aiProcess_JoinIdenticalVertices);

    if (!scene)
    {
        std::cerr << "Model: Assimp: " << import.GetErrorString() << "\n";
        exit(1);
    }

    directory_ = path.substr(0, path.find_last_of('/') + 1);
    if (directory_.empty())
        directory_ = "./";
    process_node(scene->mRootNode, scene);
}

void Model::draw(std::shared_ptr<Shader> shader) const
{
    shader->bind();
    shader->uniform("u_model", glm::mat4(1));
    shader->uniform("u_view", Camera::get_view_matrix());
    shader->uniform("u_projection", Camera::get_proj_matrix());

    for (const auto& mesh : meshes_)
    {
        mesh.draw(shader);
    }
}

void Model::process_node(aiNode* node, const aiScene* scene)
{
    meshes_.reserve(node->mNumMeshes);
    for (unsigned i = 0; i < node->mNumMeshes; ++i)
    {
        aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
        meshes_.emplace_back(mesh, scene, directory_);
    }
    for (unsigned i = 0; i < node->mNumChildren; ++i)
    {
        process_node(node->mChildren[i], scene);
    }
}
