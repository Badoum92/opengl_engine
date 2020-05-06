#include "mesh.hh"

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
    for (unsigned i = 0; i < textures_.size(); ++i)
    {
        Texture::active(i);
        std::string name = "";
        aiTextureType type = textures_[i]->get_type();
        if (type == aiTextureType_DIFFUSE)
            name = "tex_diff" + std::to_string(diff_nb++);
        else if (type == aiTextureType_SPECULAR)
            name = "tex_spec" + std::to_string(spec_nb++);
        shader->uniform(name.c_str(), (int)i);
        textures_[i]->bind();
    }
    Texture::active(0);

    va_->bind();
    ib_->bind();
    glDrawElements(GL_TRIANGLES, ib_->get_count(), GL_UNSIGNED_INT, 0);
}

void Mesh::setup_buffers()
{
    VertexBufferLayout layout;
    layout.push<float>(3); // position
    layout.push<float>(3); // normal
    layout.push<float>(2); // tex_coords
    vb_ = std::make_shared<VertexBuffer>((float*)vertices_.data(),
                                         vertices_.size() * 8);
    ib_ = std::make_shared<IndexBuffer>(indices_.data(), indices_.size());
    va_ = std::make_shared<VertexArray>(*vb_, layout);
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
        unsigned tex_count = mat->GetTextureCount(aiTextureType_DIFFUSE)
            + mat->GetTextureCount(aiTextureType_SPECULAR);
        textures_.reserve(tex_count);
        load_material_texture_type(mat, aiTextureType_DIFFUSE);
        load_material_texture_type(mat, aiTextureType_SPECULAR);
    }
}

void Mesh::load_material_texture_type(aiMaterial* mat, aiTextureType type)
{
    for (unsigned i = 0; i < mat->GetTextureCount(type); ++i)
    {
        aiString str;
        mat->GetTexture(type, i, &str);
        std::string path = directory_ + str.C_Str();
        textures_.push_back(Texture::get(path, type));
    }
}
