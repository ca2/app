// From tristancalderbank/OpenGL-PBR-Renderer/mesh.h by
// camilo on 2025-09-26 18:28 <3ThomasBorregaardSorensen!!
#include "gltf_mesh.h"
#include "framework.h"


#include "mesh.h"

#include <glad/glad.h>

namespace gpu_opengl
{

   Mesh::Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, Material material) :
       mVertices(vertices), mIndices(indices), mMaterial(material)
   {
      init();
   }

   void Mesh::Draw(Shader &shader)
   {

      // albedo
      shader.setBool("material.useTextureAlbedo", mMaterial.useTextureAlbedo);
      shader.setVec3("material.albedo", mMaterial.albedo);
      if (mMaterial.useTextureAlbedo)
      {
         glActiveTexture(GL_TEXTURE0 + TEXTURE_UNIT_ALBEDO);
         shader.setInt("material.textureAlbedo", TEXTURE_UNIT_ALBEDO);
         glBindTexture(GL_TEXTURE_2D, mMaterial.textureAlbedo->mId);
      }

      shader.setBool("material.useTextureMetallicRoughness", mMaterial.useTextureMetallicRoughness);
      shader.setFloat("material.metallic", mMaterial.metallic);
      shader.setFloat("material.roughness", mMaterial.roughness);
      if (mMaterial.useTextureMetallicRoughness)
      {
         glActiveTexture(GL_TEXTURE0 + TEXTURE_UNIT_METALLIC_ROUGHNESS);
         shader.setInt("material.textureMetallicRoughness", TEXTURE_UNIT_METALLIC_ROUGHNESS);
         glBindTexture(GL_TEXTURE_2D, mMaterial.textureMetallicRoughness->mId);
      }

      shader.setBool("material.useTextureNormal", mMaterial.useTextureNormal);
      if (mMaterial.useTextureNormal)
      {
         glActiveTexture(GL_TEXTURE0 + TEXTURE_UNIT_NORMAL);
         shader.setInt("material.textureNormal", TEXTURE_UNIT_NORMAL);
         glBindTexture(GL_TEXTURE_2D, mMaterial.textureNormal->mId);
      }

      shader.setBool("material.useTextureAmbientOcclusion", mMaterial.useTextureAmbientOcclusion);
      shader.setFloat("material.ambientOcclusion", mMaterial.ambientOcclusion);
      if (mMaterial.useTextureAmbientOcclusion)
      {
         glActiveTexture(GL_TEXTURE0 + TEXTURE_UNIT_AMBIENT_OCCLUSION);
         shader.setInt("material.textureAmbientOcclusion", TEXTURE_UNIT_AMBIENT_OCCLUSION);
         glBindTexture(GL_TEXTURE_2D, mMaterial.textureAmbientOcclusion->mId);
      }

      shader.setBool("material.useTextureEmissive", mMaterial.useTextureEmissive);
      shader.setVec3("material.emissive", mMaterial.emissive);
      if (mMaterial.useTextureEmissive)
      {
         glActiveTexture(GL_TEXTURE0 + TEXTURE_UNIT_EMISSIVE);
         shader.setInt("material.textureEmissive", TEXTURE_UNIT_EMISSIVE);
         glBindTexture(GL_TEXTURE_2D, mMaterial.textureEmissive->mId);
      }

      glActiveTexture(GL_TEXTURE0);

      // draw mesh
      glBindVertexArray(mVAO);
      glDrawElements(GL_TRIANGLES, mIndices.size(), GL_UNSIGNED_INT, 0);
      glBindVertexArray(0);
   }

   void Mesh::init()
   {
      // create our data structures
      glGenVertexArrays(1, &mVAO);
      glGenBuffers(1, &mVBO);
      glGenBuffers(1, &mEBO);

      glBindVertexArray(mVAO); // use this VAO for subsequent calls

      glBindBuffer(GL_ARRAY_BUFFER, mVBO); // use this VBO for subsequent calls
      glBufferData(GL_ARRAY_BUFFER, mVertices.size() * sizeof(Vertex), &mVertices[0],
                   GL_STATIC_DRAW); // copy over the vertex data

      glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mEBO); // use this EBO for subsequent calls
      glBufferData(GL_ELEMENT_ARRAY_BUFFER, mIndices.size() * sizeof(unsigned int), &mIndices[0],
                   GL_STATIC_DRAW); // copy over the index data

      // setup the locations of vertex data
      // positions
      glEnableVertexAttribArray(0);
      glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *)0);

      // normals
      glEnableVertexAttribArray(1);
      glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *)offsetof(Vertex, mNormal));

      // texture coordinates
      glEnableVertexAttribArray(2);
      glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *)offsetof(Vertex, mTextureCoordinates));

      // tangents
      glEnableVertexAttribArray(3);
      glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *)offsetof(Vertex, mTangent));

      // bitangents
      glEnableVertexAttribArray(4);
      glVertexAttribPointer(4, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void *)offsetof(Vertex, mBitangent));

      glBindVertexArray(0);
   }


} // namespace gpu_opengl
