// From github:/tristancalderbank/OpenGL-PBR-Renderer/mesh.h by
// camilo on 2025-09-26 18:28 <3ThomasBorregaardSorensen!!
#include "framework.h"
#include "mesh.h"


#include <glad/glad.h>


namespace gpu
{


namespace gltf
{


   mesh::mesh()
   {


   }


   mesh::~mesh()
   {


   }


   void mesh::initialize_mesh(const ::array_base < gltf::vertex > & vertexa,
         const ::unsigned_int_array & indexa, gltf_material  *pmaterial)
   {

      m_vertexa = vertexa;
      m_indexa = indexa;
      m_pmaterial = pmaterial;

      init();

   }


   void mesh::draw(Shader &shader)
   {

      // albedo
      shader.setBool("material.useTextureAlbedo", m_pmaterial->useTextureAlbedo);
      shader.setVec3("material.albedo", m_pmaterial->albedo);
      if (m_pmaterial->useTextureAlbedo)
      {
         glActiveTexture(GL_TEXTURE0 + e_gltf_texture_albedo);
         shader.setInt("material.textureAlbedo", e_gltf_texture_albedo);
         glBindTexture(GL_TEXTURE_2D, m_pmaterial->textureAlbedo->mId);
      }

      shader.setBool("material.useTextureMetallicRoughness", m_pmaterial->useTextureMetallicRoughness);
      shader.setFloat("material.metallic", m_pmaterial->metallic);
      shader.setFloat("material.roughness", m_pmaterial->roughness);
      if (m_pmaterial->useTextureMetallicRoughness)
      {
         glActiveTexture(GL_TEXTURE0 + e_gltf_texture_metallic_roughness);
         shader.setInt("material.textureMetallicRoughness", e_gltf_texture_metallic_roughness);
         glBindTexture(GL_TEXTURE_2D, m_pmaterial->textureMetallicRoughness->mId);
      }

      shader.setBool("material.useTextureNormal", m_pmaterial->useTextureNormal);
      if (m_pmaterial->useTextureNormal)
      {
         glActiveTexture(GL_TEXTURE0 + e_gltf_texture_normal);
         shader.setInt("material.textureNormal", e_gltf_texture_normal);
         glBindTexture(GL_TEXTURE_2D, m_pmaterial->textureNormal->mId);
      }

      shader.setBool("material.useTextureAmbientOcclusion", m_pmaterial->useTextureAmbientOcclusion);
      shader.setFloat("material.ambientOcclusion", m_pmaterial->ambientOcclusion);
      if (m_pmaterial->useTextureAmbientOcclusion)
      {
         glActiveTexture(GL_TEXTURE0 + e_gltf_texture_ambient_occlusion);
         shader.setInt("material.textureAmbientOcclusion", e_gltf_texture_ambient_occlusion);
         glBindTexture(GL_TEXTURE_2D, m_pmaterial->textureAmbientOcclusion->mId);
      }

      shader.setBool("material.useTextureEmissive", m_pmaterial->useTextureEmissive);
      shader.setVec3("material.emissive", m_pmaterial->emissive);
      if (m_pmaterial->useTextureEmissive)
      {
         glActiveTexture(GL_TEXTURE0 + e_gltf_texture_emissive);
         shader.setInt("material.textureEmissive", e_gltf_texture_emissive);
         glBindTexture(GL_TEXTURE_2D, m_pmaterial->textureEmissive->mId);
      }

      glActiveTexture(GL_TEXTURE0);

      // draw mesh
      glBindVertexArray(mVAO);
      glDrawElements(GL_TRIANGLES, m_indexa.size(), GL_UNSIGNED_INT, 0);
      glBindVertexArray(0);

   }


   void mesh::init()
   {
      // create our data structures
      glGenVertexArrays(1, &mVAO);
      glGenBuffers(1, &mVBO);
      glGenBuffers(1, &mEBO);

      glBindVertexArray(mVAO); // use this VAO for subsequent calls

      glBindBuffer(GL_ARRAY_BUFFER, mVBO); // use this VBO for subsequent calls
      glBufferData(GL_ARRAY_BUFFER, mVertices.size() * sizeof(gltf::vertex), &mVertices[0],
                   GL_STATIC_DRAW); // copy over the vertex data

      glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mEBO); // use this EBO for subsequent calls
      glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_indexa.size() * sizeof(unsigned int), &m_indexa[0],
                   GL_STATIC_DRAW); // copy over the index data

      // setup the locations of vertex data
      // positions
      glEnableVertexAttribArray(0);
      glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(gltf::vertex), (void *)0);

      // normals
      glEnableVertexAttribArray(1);
      glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(gltf::vertex), (void *)offsetof(gltf::vertex, mNormal));

      // texture coordinates
      glEnableVertexAttribArray(2);
      glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(gltf::vertex), (void *)offsetof(gltf::vertex, mTextureCoordinates));

      // tangents
      glEnableVertexAttribArray(3);
      glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(gltf::vertex), (void *)offsetof(gltf::vertex, mTangent));

      // bitangents
      glEnableVertexAttribArray(4);
      glVertexAttribPointer(4, 3, GL_FLOAT, GL_FALSE, sizeof(gltf::vertex), (void *)offsetof(gltf::vertex, mBitangent));

      glBindVertexArray(0);

   }

   } // namespace gltf


} // namespace gpu
 