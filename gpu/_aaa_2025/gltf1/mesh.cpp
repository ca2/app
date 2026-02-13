// From github:/tristancalderbank/OpenGL-PBR-Renderer/mesh.h by
// camilo on 2025-09-26 18:28 <3ThomasBorregaardSorensen!!
#include "framework.h"
#include "mesh.h"
#include "bred/gltf/vertex.h"
#include "bred/gpu/command_buffer.h"
#include "bred/gpu/context.h"
#include "bred/gpu/model_buffer.h"

#include <glad/glad.h>

#include "bred/gpu/render_target.h"
#include "bred/gpu/renderer.h"


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


      void mesh::initialize_gpu_gltf_mesh( //const ::gpu::model_data<gltf::vertex> &modeldata,
                                          ::gpu::gltf::material *pmaterial)
      {
         /// model data must had been set
         if (m_modeldata.is_empty())
         {

            throw ::exception(error_wrong_state);

         }

         //m_modeldata = modeldata;
         //m_modeldata.m_indexes = indexa;
         m_pmaterial = pmaterial;

         on_initialize_gpu_gltf_mesh();

      }


      void mesh::draw2(::gpu::command_buffer *pcommandbuffer)
      {

         // auto pshader = pcommandbuffer->m_pgpurendertarget->m_pgpurenderer->m_pgpucontext->m_pshaderBound;
         //
         // // albedo
         // pshader->set_int("material.useTextureAlbedo", m_pmaterial->useTextureAlbedo);
         // pshader->set_sequence3("material.albedo", m_pmaterial->albedo);
         // if (m_pmaterial->useTextureAlbedo)
         // {
         //    glActiveTexture(GL_TEXTURE0 + e_gltf_texture_albedo);
         //    pshader->setInt("material.textureAlbedo", e_gltf_texture_albedo);
         //    glBindTexture(GL_TEXTURE_2D, m_pmaterial->textureAlbedo->mId);
         // }
         //
         // pshader->set_int("material.useTextureMetallicRoughness", m_pmaterial->useTextureMetallicRoughness);
         // pshader->setFloat("material.metallic", m_pmaterial->metallic);
         // pshader->setFloat("material.roughness", m_pmaterial->roughness);
         // if (m_pmaterial->useTextureMetallicRoughness)
         // {
         //    glActiveTexture(GL_TEXTURE0 + e_gltf_texture_metallic_roughness);
         //    pshader->setInt("material.textureMetallicRoughness", e_gltf_texture_metallic_roughness);
         //    glBindTexture(GL_TEXTURE_2D, m_pmaterial->textureMetallicRoughness->mId);
         // }
         //
         // pshader->set_int("material.useTextureNormal", m_pmaterial->useTextureNormal);
         // if (m_pmaterial->useTextureNormal)
         // {
         //    glActiveTexture(GL_TEXTURE0 + e_gltf_texture_normal);
         //    pshader->setInt("material.textureNormal", e_gltf_texture_normal);
         //    glBindTexture(GL_TEXTURE_2D, m_pmaterial->textureNormal->mId);
         // }
         //
         // pshader->set_int("material.useTextureAmbientOcclusion", m_pmaterial->useTextureAmbientOcclusion);
         // pshader->setFloat("material.ambientOcclusion", m_pmaterial->ambientOcclusion);
         // if (m_pmaterial->useTextureAmbientOcclusion)
         // {
         //    glActiveTexture(GL_TEXTURE0 + e_gltf_texture_ambient_occlusion);
         //    pshader->setInt("material.textureAmbientOcclusion", e_gltf_texture_ambient_occlusion);
         //    glBindTexture(GL_TEXTURE_2D, m_pmaterial->textureAmbientOcclusion->mId);
         // }
         //
         // pshader->set_int("material.useTextureEmissive", m_pmaterial->useTextureEmissive);
         // pshader->set_sequence3("material.emissive", m_pmaterial->emissive);
         // if (m_pmaterial->useTextureEmissive)
         // {
         //    glActiveTexture(GL_TEXTURE0 + e_gltf_texture_emissive);
         //    pshader->setInt("material.textureEmissive", e_gltf_texture_emissive);
         //    glBindTexture(GL_TEXTURE_2D, m_pmaterial->textureEmissive->mId);
         // }
         //
         // glActiveTexture(GL_TEXTURE0);
         //
         // // draw mesh
         // glBindVertexArray(m_uVAO);
         // glDrawElements(GL_TRIANGLES, m_indexa.size(), GL_UNSIGNED_INT, 0);
         // glBindVertexArray(0);

      }


      void mesh::on_initialize_gpu_gltf_mesh()
      {
         // // create our data structures
         // glGenVertexArrays(1, &m_uVAO);
         // glGenBuffers(1, &m_uVBO);
         // glGenBuffers(1, &m_uEBO);
         //
         // glBindVertexArray(m_uVAO); // use this VAO for subsequent calls
         //
         // glBindBuffer(GL_ARRAY_BUFFER, m_uVBO); // use this VBO for subsequent calls
         // glBufferData(GL_ARRAY_BUFFER, m_vertexa.size() * sizeof(gltf::vertex), m_vertexa.data(),
         //              GL_STATIC_DRAW); // copy over the vertex data
         //
         // glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_uEBO); // use this EBO for subsequent calls
         // glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_indexa.size() * sizeof(unsigned int), m_indexa.data(),
         //              GL_STATIC_DRAW); // copy over the index data
         //
         // // setup the locations of vertex data
         // // positions
         // glEnableVertexAttribArray(0);
         // glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(gltf::vertex), (void *)0);
         //
         // // normals
         // glEnableVertexAttribArray(1);
         // glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(gltf::vertex), (void *)offsetof(gltf::vertex, mNormal));
         //
         // // texture coordinates
         // glEnableVertexAttribArray(2);
         // glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(gltf::vertex), (void *)offsetof(gltf::vertex, mTextureCoordinates));
         //
         // // tangents
         // glEnableVertexAttribArray(3);
         // glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(gltf::vertex), (void *)offsetof(gltf::vertex, mTangent));
         //
         // // bitangents
         // glEnableVertexAttribArray(4);
         // glVertexAttribPointer(4, 3, GL_FLOAT, GL_FALSE, sizeof(gltf::vertex), (void *)offsetof(gltf::vertex, mBitangent));
         //
         // glBindVertexArray(0);

         øconstruct(m_pmodelbuffer);

         m_pmodelbuffer->initialize_gpu_context_object(m_pgpucontext);

         m_pmodelbuffer->set_data(m_modeldata);

      }

   } // namespace gltf


} // namespace gpu
