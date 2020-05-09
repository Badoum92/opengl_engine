#include "mesh.hh"

#include <iostream>

Mesh::Mesh(aiMesh* mesh, const aiScene* scene, const std::string& directory)
    : directory_(directory)
{
    load_vertices(mesh);
    load_indices(mesh);
    load_material_textures(mesh, scene);
    setup_buffers();
}

void Mesh::draw(std::shared_ptr<Shader> shader) const
{
    unsigned diff_nb = 0;
    unsigned spec_nb = 0;
    unsigned normal_nb = 0;
    unsigned i = 0;
    for (const auto& tex : textures_)
    {
        Texture::active(i);
        std::string name = "";
        aiTextureType type = tex->get_type();
        if (type == aiTextureType_DIFFUSE)
            name = "tex_diff" + std::to_string(diff_nb++);
        else if (type == aiTextureType_SPECULAR)
            name = "tex_spec" + std::to_string(spec_nb++);
        else if (type == aiTextureType_NORMALS)
            name = "tex_normal" + std::to_string(normal_nb++);
        else if (type == aiTextureType_HEIGHT)
            name = "tex_normal" + std::to_string(normal_nb++);
        shader->uniform(name.c_str(), (int)i);
        tex->bind();
        i++;
    }
    Texture::active(0);

    va_->bind();
    ib_->bind();
    glDrawElements(GL_TRIANGLES, ib_->nb_indices(), GL_UNSIGNED_INT, 0);
}

void Mesh::setup_buffers()
{
    VertexBufferLayout layout;
    layout.push<float>(3); // position
    layout.push<float>(3); // normal
    layout.push<float>(2); // tex_coords
    layout.push<float>(3); // tangent
    layout.push<float>(3); // bitangent
    vb_ = VertexBuffer::create((float*)vertices_.data(),
                               vertices_.size() * sizeof(Vertex));
    ib_ = IndexBuffer::create(indices_.data(), indices_.size());
    va_ = VertexArray::create(*vb_, layout);
}

void Mesh::load_vertices(aiMesh* mesh)
{
    vertices_.reserve(mesh->mNumVertices);
    for (unsigned i = 0; i < mesh->mNumVertices; ++i)
    {
        Vertex v;
        v.position.x = mesh->mVertices[i].x;
        v.position.y = mesh->mVertices[i].y;
        v.position.z = mesh->mVertices[i].z;
        v.normal.x = mesh->mNormals[i].x;
        v.normal.y = mesh->mNormals[i].y;
        v.normal.z = mesh->mNormals[i].z;
        v.tex_coords.x = 0;
        v.tex_coords.y = 0;
        if (mesh->mTextureCoords[0])
        {
            v.tex_coords.x = mesh->mTextureCoords[0][i].x;
            v.tex_coords.y = mesh->mTextureCoords[0][i].y;
        }
        v.tangent.x = mesh->mTangents[i].x;
        v.tangent.y = mesh->mTangents[i].y;
        v.tangent.z = mesh->mTangents[i].z;
        v.bitangent.x = mesh->mBitangents[i].x;
        v.bitangent.y = mesh->mBitangents[i].y;
        v.bitangent.z = mesh->mBitangents[i].z;
        vertices_.push_back(v);
    }
}

void Mesh::load_indices(aiMesh* mesh)
{
    indices_.reserve(mesh->mNumFaces * 3);
    for (unsigned i = 0; i < mesh->mNumFaces; ++i)
    {
        aiFace& face = mesh->mFaces[i];
        if (face.mNumIndices != 3)
            continue;
        for (unsigned j = 0; j < face.mNumIndices; ++j)
        {
            indices_.push_back(face.mIndices[j]);
        }
    }
}

void Mesh::load_material_textures(aiMesh* mesh, const aiScene* scene)
{
    if (mesh->mMaterialIndex >= 0)
    {
        aiMaterial* mat = scene->mMaterials[mesh->mMaterialIndex];
        load_material_texture_type(mat, aiTextureType_DIFFUSE);
        load_material_texture_type(mat, aiTextureType_SPECULAR);
        load_material_texture_type(mat, aiTextureType_NORMALS);
        load_material_texture_type(mat, aiTextureType_HEIGHT);
    }
}

void Mesh::load_material_texture_type(aiMaterial* mat, aiTextureType type)
{
    for (unsigned i = 0; i < mat->GetTextureCount(type); ++i)
    {
        aiString str;
        mat->GetTexture(type, i, &str);
        std::string path = directory_ + str.C_Str();
        textures_.insert(Texture::get_or_create(path, type));
    }
}
