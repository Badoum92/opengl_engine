#include "model.hh"

#include <iostream>
#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>

#include "camera.hh"

#include "imgui_windows.hh"

Model::Model(const std::string& path)
{
    Assimp::Importer import;
    const aiScene* scene = import.ReadFile(
        path,
        aiProcess_Triangulate | aiProcess_FlipUVs | aiProcess_GenNormals
            | aiProcess_JoinIdenticalVertices | aiProcess_CalcTangentSpace);

    if (!scene)
    {
        std::cerr << "Model: Assimp: " << import.GetErrorString() << "\n";
        exit(1);
    }

    directory_ = path.substr(0, path.find_last_of('/') + 1);
    if (directory_.empty())
        directory_ = "./";
    meshes_.reserve(scene->mNumMeshes);
    process_node(scene->mRootNode, scene);
}

void Model::draw(std::shared_ptr<Shader> shader) const
{
    shader->uniform("u_model", transform_);

    for (const auto& mesh : meshes_)
    {
        mesh.draw(shader);
    }
}

void Model::reset()
{
    transform_ = glm::mat4(1);
}

Model& Model::translate(glm::vec3 v)
{
    transform_ = glm::translate(transform_, v);
    return *this;
}

Model& Model::rotate_rad(float angle, glm::vec3 v)
{
    transform_ = glm::rotate(transform_, angle, glm::normalize(v));
    return *this;
}

Model& Model::rotate_deg(float angle, glm::vec3 v)
{
    return rotate_rad(angle * AI_MATH_PI_F / 180.0f, v);
}

Model& Model::scale(glm::vec3 v)
{
    transform_ = glm::scale(transform_, v);
    return *this;
}

void Model::process_node(aiNode* node, const aiScene* scene)
{
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
