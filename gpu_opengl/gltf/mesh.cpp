// From github:/tristancalderbank/OpenGL-PBR-Renderer/mesh.h by
// camilo on 2025-09-26 18:28 <3ThomasBorregaardSorensen!!
#include "framework.h"
#include "mesh.h"
#include "bred/gltf/vertex.h"
#include "gpu_opengl/texture.h"
#include "bred/gpu/command_buffer.h"
#include "bred/gpu/context.h"
#include "bred/gpu/render_target.h"
#include "bred/gpu/renderer.h"
#include "bred/graphics3d/render_systems/gltf_render_system.h"
#include "bred/graphics3d/render_system.h"

#include <glad/glad.h>


namespace gpu_opengl
{


   namespace gltf
   {


      mesh::mesh()
      {


      }


      mesh::~mesh()
      {


      }


      //void mesh::initialize_gpu_gltf_mesh(const ::array_base<::gpu::gltf::vertex> &vertexa,
      //                             const ::unsigned_int_array &indexa, ::gpu::gltf::material *pmaterial)
      //{

      //   m_vertexa = vertexa;
      //   m_indexa = indexa;
      //   m_pmaterial = pmaterial;

      //   init();

      //}


      void mesh::draw(::gpu::command_buffer *pcommandbuffer)
      {
         // // albedo
         // shader.setBool("material.useTextureAlbedo", m_pmaterial->useTextureAlbedo);
         // shader.setVec3("material.albedo", m_pmaterial->albedo);
         // if (m_pmaterial->useTextureAlbedo)
         // {
         //    glActiveTexture(GL_TEXTURE0 + e_gltf_texture_albedo);
         //    shader.setInt("material.textureAlbedo", e_gltf_texture_albedo);
         //    glBindTexture(GL_TEXTURE_2D, m_pmaterial->textureAlbedo->mId);
         // }
         //
         // shader.setBool("material.useTextureMetallicRoughness", m_pmaterial->useTextureMetallicRoughness);
         // shader.setFloat("material.metallic", m_pmaterial->metallic);
         // shader.setFloat("material.roughness", m_pmaterial->roughness);
         // if (m_pmaterial->useTextureMetallicRoughness)
         // {
         //    glActiveTexture(GL_TEXTURE0 + e_gltf_texture_metallic_roughness);
         //    shader.setInt("material.textureMetallicRoughness", e_gltf_texture_metallic_roughness);
         //    glBindTexture(GL_TEXTURE_2D, m_pmaterial->textureMetallicRoughness->mId);
         // }
         //
         // shader.setBool("material.useTextureNormal", m_pmaterial->useTextureNormal);
         // if (m_pmaterial->useTextureNormal)
         // {
         //    glActiveTexture(GL_TEXTURE0 + e_gltf_texture_normal);
         //    shader.setInt("material.textureNormal", e_gltf_texture_normal);
         //    glBindTexture(GL_TEXTURE_2D, m_pmaterial->textureNormal->mId);
         // }
         //
         // shader.setBool("material.useTextureAmbientOcclusion", m_pmaterial->useTextureAmbientOcclusion);
         // shader.setFloat("material.ambientOcclusion", m_pmaterial->ambientOcclusion);
         // if (m_pmaterial->useTextureAmbientOcclusion)
         // {
         //    glActiveTexture(GL_TEXTURE0 + e_gltf_texture_ambient_occlusion);
         //    shader.setInt("material.textureAmbientOcclusion", e_gltf_texture_ambient_occlusion);
         //    glBindTexture(GL_TEXTURE_2D, m_pmaterial->textureAmbientOcclusion->mId);
         // }
         //
         // shader.setBool("material.useTextureEmissive", m_pmaterial->useTextureEmissive);
         // shader.setVec3("material.emissive", m_pmaterial->emissive);
         // if (m_pmaterial->useTextureEmissive)
         // {
         //    glActiveTexture(GL_TEXTURE0 + e_gltf_texture_emissive);
         //    shader.setInt("material.textureEmissive", e_gltf_texture_emissive);
         //    glBindTexture(GL_TEXTURE_2D, m_pmaterial->textureEmissive->mId);
         // }
         //
         // glActiveTexture(GL_TEXTURE0);
         //
         // // draw mesh
         // glBindVertexArray(mVAO);
         // glDrawElements(GL_TRIANGLES, m_indexa.size(), GL_UNSIGNED_INT, 0);
         // glBindVertexArray(0);

         auto pshader = pcommandbuffer->m_pgpurendertarget->m_pgpurenderer->m_pgpucontext->m_pshaderBound;
         auto erendersystem = pcommandbuffer->m_prendersystem->m_erendersystem;
         if (erendersystem == ::graphics3d::e_render_system_skybox_ibl)
         {


         }
         else  if (erendersystem == ::graphics3d::e_render_system_gltf_ibl)
         {
            // albedo
            ::cast<::graphics3d::gltf_render_system> prendersystem = pcommandbuffer->m_prendersystem;
            bool bAlbedo = !prendersystem->m_bDisableAlbedo && m_pmaterial->useTextureAlbedo;
            pshader->set_int("material.useTextureAlbedo", bAlbedo);
            floating_sequence3 seq3Albedo= {};
            if (prendersystem->m_bForceDefaultAmbientOcclusionFactor)
            {

               seq3Albedo = prendersystem->m_seq3DefaultAlbedo;
            }
            else
            {

               seq3Albedo = m_pmaterial->m_seq3Albedo;
            }

            pshader->set_sequence3("material.albedo", seq3Albedo);
            if (bAlbedo)
            {
               int iTextureIndex = ::gpu::e_gltf_texture_albedo;
               GLenum textureIndex = GL_TEXTURE0 + iTextureIndex;
               glActiveTexture(textureIndex);
               pshader->set_int("material.textureAlbedo", iTextureIndex);

               ::cast<::gpu_opengl::texture> ptextureAlbedo = m_pmaterial->m_ptextureAlbedo;
               glBindTexture(GL_TEXTURE_2D, ptextureAlbedo->m_gluTextureID);
            }

            bool bMetallicRoughness =
               !prendersystem->m_bDisableMetallicRoughness && m_pmaterial->useTextureMetallicRoughness;

            pshader->set_int("material.useTextureMetallicRoughness", bMetallicRoughness);
            float fMetallic = 0.0f;
            if (prendersystem->m_bForceDefaultMetallicFactor)
            {

               fMetallic = prendersystem->m_fDefaultMetallicFactor;

            }
            else
            {

               fMetallic = m_pmaterial->m_fMetallic;

            }
            float fRoughness = 0.0f;
            if (prendersystem->m_bForceDefaultRoughnessFactor)
            {

               fRoughness = prendersystem->m_fDefaultRoughnessFactor;
            }
            else
            {

               fRoughness = m_pmaterial->m_fRoughness;
            }
            pshader->set_float("material.metallic", fMetallic);
            pshader->set_float("material.roughness", fRoughness);
            if (bMetallicRoughness)
            {
               int iTextureIndex = ::gpu::e_gltf_texture_metallic_roughness;
               GLenum textureIndex = GL_TEXTURE0 + iTextureIndex;
               glActiveTexture(textureIndex);
               pshader->set_int("material.textureMetallicRoughness", iTextureIndex);
               ::cast<::gpu_opengl::texture> ptextureMetallicRoughness = m_pmaterial->m_ptextureMetallicRoughness;
               glBindTexture(GL_TEXTURE_2D, ptextureMetallicRoughness->m_gluTextureID);
            }

            bool bNormal = !prendersystem->m_bDisableNormal && m_pmaterial->useTextureNormal;
            pshader->set_int("material.useTextureNormal", bNormal);
            if (bNormal)
            {
               glActiveTexture(GL_TEXTURE0 + ::gpu::e_gltf_texture_normal);
               pshader->set_int("material.textureNormal", ::gpu::e_gltf_texture_normal);
               ::cast<::gpu_opengl::texture> ptextureNormal = m_pmaterial->m_ptextureNormal;
               glBindTexture(GL_TEXTURE_2D, ptextureNormal->m_gluTextureID);
            }

            bool bAmbientOcclusion =
               !prendersystem->m_bDisableAmbientOcclusion && m_pmaterial->useTextureAmbientOcclusion;
            pshader->set_int("material.useTextureAmbientOcclusion", bAmbientOcclusion);
            float fAmbientOcclusion = 0.0f;
            if (prendersystem->m_bForceDefaultAmbientOcclusionFactor)
            {

               fAmbientOcclusion = prendersystem->m_fDefaultAmbientOcclusionFactor;
            }
            else
            {

               fAmbientOcclusion = m_pmaterial->m_fAmbientOcclusion;
            }
            pshader->set_float("material.ambientOcclusion", fAmbientOcclusion);
            if (bAmbientOcclusion)
            {
               glActiveTexture(GL_TEXTURE0 + ::gpu::e_gltf_texture_ambient_occlusion);
               pshader->set_int("material.textureAmbientOcclusion", ::gpu::e_gltf_texture_ambient_occlusion);
               ::cast<::gpu_opengl::texture> ptextureAmbientOcclusion = m_pmaterial->m_ptextureAmbientOcclusion;
               glBindTexture(GL_TEXTURE_2D, ptextureAmbientOcclusion->m_gluTextureID);
            }

            bool bEmissive = !prendersystem->m_bDisableEmissive && m_pmaterial->useTextureEmissive;
            pshader->set_int("material.useTextureEmissive", bEmissive);
            floating_sequence3 seq3Emission = {};
            if (prendersystem->m_bForceDefaultEmission)
            {

               seq3Emission = prendersystem->m_seq3DefaultEmission;
            }
            else
            {

               seq3Emission = m_pmaterial->m_seq3Emissive;
            }
            pshader->set_sequence3("material.emissive", seq3Emission);
            if (bEmissive)
            {
               glActiveTexture(GL_TEXTURE0 + ::gpu::e_gltf_texture_emissive);
               pshader->set_int("material.textureEmissive", ::gpu::e_gltf_texture_emissive);
               ::cast<::gpu_opengl::texture> ptextureEmissive = m_pmaterial->m_ptextureEmissive;
               glBindTexture(GL_TEXTURE_2D, ptextureEmissive->m_gluTextureID);
            }

            glActiveTexture(GL_TEXTURE0);

         }
         else if (erendersystem == ::graphics3d::e_render_system_gltf_scene)
         {
            // albedo
                        //;
            //pshader->set_int("material.useTextureAlbedo", m_pmaterial->useTextureAlbedo);
            //pshader->set_sequence3("material.albedo", m_pmaterial->m_seq3Albedo);
            if (m_pmaterial->useTextureAlbedo)
            {
               int iTextureIndex = ::gpu::e_gltf_texture_albedo;
               GLenum textureIndex = GL_TEXTURE0 + iTextureIndex;
               glActiveTexture(textureIndex);
               pshader->set_int("material.textureAlbedo", iTextureIndex);

               ::cast<::gpu_opengl::texture> ptextureAlbedo = m_pmaterial->m_ptextureAlbedo;
               glBindTexture(GL_TEXTURE_2D, ptextureAlbedo->m_gluTextureID);
            }

            //pshader->set_int("material.useTextureMetallicRoughness", m_pmaterial->useTextureMetallicRoughness);
            //pshader->set_float("material.metallic", m_pmaterial->m_fMetallic);
            //pshader->set_float("material.roughness", m_pmaterial->m_fRoughness);
            //if (m_pmaterial->useTextureMetallicRoughness)
            //{
            //   int iTextureIndex = ::gpu::e_gltf_texture_metallic_roughness;
            //   GLenum textureIndex = GL_TEXTURE0 + iTextureIndex;
            //   glActiveTexture(textureIndex);
            //   pshader->set_int("material.textureMetallicRoughness", iTextureIndex);
            //   ::cast<::gpu_opengl::texture> ptextureMetallicRoughness = m_pmaterial->m_ptextureMetallicRoughness;
            //   glBindTexture(GL_TEXTURE_2D, ptextureMetallicRoughness->m_gluTextureID);
            //}

            pshader->set_int("material.useTextureNormal", m_pmaterial->useTextureNormal);
            if (m_pmaterial->useTextureNormal)
            {
               glActiveTexture(GL_TEXTURE0 + ::gpu::e_gltf_texture_normal);
               pshader->set_int("material.textureNormal", ::gpu::e_gltf_texture_normal);
               ::cast<::gpu_opengl::texture> ptextureNormal = m_pmaterial->m_ptextureNormal;
               glBindTexture(GL_TEXTURE_2D, ptextureNormal->m_gluTextureID);
            }
            else
            {

               //information() << "are there gltf models without normal?";

            }

            //pshader->set_int("material.useTextureAmbientOcclusion", m_pmaterial->useTextureAmbientOcclusion);
            //pshader->set_float("material.ambientOcclusion", m_pmaterial->m_fAmbientOcclusion);
            //if (m_pmaterial->useTextureAmbientOcclusion)
            //{
            //   glActiveTexture(GL_TEXTURE0 + ::gpu::e_gltf_texture_ambient_occlusion);
            //   pshader->set_int("material.textureAmbientOcclusion", ::gpu::e_gltf_texture_ambient_occlusion);
            //   ::cast<::gpu_opengl::texture> ptextureAmbientOcclusion = m_pmaterial->m_ptextureAmbientOcclusion;
            //   glBindTexture(GL_TEXTURE_2D, ptextureAmbientOcclusion->m_gluTextureID);
            //}

            //pshader->set_int("material.useTextureEmissive", m_pmaterial->useTextureEmissive);
            //pshader->set_sequence3("material.emissive", m_pmaterial->m_seq3Emissive);
            //if (m_pmaterial->useTextureEmissive)
            //{
            //   glActiveTexture(GL_TEXTURE0 + ::gpu::e_gltf_texture_emissive);
            //   pshader->set_int("material.textureEmissive", ::gpu::e_gltf_texture_emissive);
            //   ::cast<::gpu_opengl::texture> ptextureEmissive = m_pmaterial->m_ptextureEmissive;
            //   glBindTexture(GL_TEXTURE_2D, ptextureEmissive->m_gluTextureID);
            //}

            glActiveTexture(GL_TEXTURE0);



         }
         else
         {

            warning() << "unexpected enum_render_system in gpu_opengl::gltf::mesh::draw";

            throw ::exception(error_wrong_state, "unexpected enum_render_system in gpu_opengl::gltf::mesh::draw");

         }

            // draw mesh
         glBindVertexArray(m_uVAO);
         glDrawElements(GL_TRIANGLES, m_indexa.size(), GL_UNSIGNED_INT, 0);
         glBindVertexArray(0);

      }


      void mesh::init()
      {
         // // create our data structures
         // glGenVertexArrays(1, &mVAO);
         // glGenBuffers(1, &mVBO);
         // glGenBuffers(1, &mEBO);
         //
         // glBindVertexArray(mVAO); // use this VAO for subsequent calls
         //
         // glBindBuffer(GL_ARRAY_BUFFER, mVBO); // use this VBO for subsequent calls
         // glBufferData(GL_ARRAY_BUFFER, mVertices.size() * sizeof(::gpu::gltf::vertex), &mVertices[0],
         //              GL_STATIC_DRAW); // copy over the vertex data
         //
         // glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mEBO); // use this EBO for subsequent calls
         // glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_indexa.size() * sizeof(unsigned int), &m_indexa[0],
         //              GL_STATIC_DRAW); // copy over the index data
         //
         // // setup the locations of vertex data
         // // positions
         // glEnableVertexAttribArray(0);
         // glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(::gpu::gltf::vertex), (void *)0);
         //
         // // normals
         // glEnableVertexAttribArray(1);
         // glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(::gpu::gltf::vertex), (void *)offsetof(::gpu::gltf::vertex, mNormal));
         //
         // // texture coordinates
         // glEnableVertexAttribArray(2);
         // glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(::gpu::gltf::vertex),
         //                       (void *)offsetof(::gpu::gltf::vertex, mTextureCoordinates));
         //
         // // tangents
         // glEnableVertexAttribArray(3);
         // glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(::gpu::gltf::vertex),
         //                       (void *)offsetof(::gpu::gltf::vertex, mTangent));
         //
         // // bitangents
         // glEnableVertexAttribArray(4);
         // glVertexAttribPointer(4, 3, GL_FLOAT, GL_FALSE, sizeof(::gpu::gltf::vertex),
         //                       (void *)offsetof(::gpu::gltf::vertex, mBitangent));
         //
         // glBindVertexArray(0);
         //
         // create our data structures
         glGenVertexArrays(1, &m_uVAO);
         glGenBuffers(1, &m_uVBO);
         glGenBuffers(1, &m_uEBO);

         glBindVertexArray(m_uVAO); // use this VAO for subsequent calls

         auto vertexSize =m_vertexa.size();
         auto vertexData = m_vertexa.data();

         glBindBuffer(GL_ARRAY_BUFFER, m_uVBO); // use this VBO for subsequent calls
         glBufferData(GL_ARRAY_BUFFER, vertexSize * sizeof(::gpu::gltf::vertex),
            vertexData,GL_STATIC_DRAW); // copy over the vertex data

         auto indexSize = m_indexa.size();
         auto indexData = m_indexa.data();

         glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_uEBO); // use this EBO for subsequent calls
         glBufferData(GL_ELEMENT_ARRAY_BUFFER, indexSize * sizeof(unsigned int),
            indexData,GL_STATIC_DRAW); // copy over the index data

         // setup the locations of vertex data
         // positions
         glEnableVertexAttribArray(0);
         glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(::gpu::gltf::vertex), (void *)0);

         // normals
         glEnableVertexAttribArray(1);
         glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(::gpu::gltf::vertex), (void *)offsetof(::gpu::gltf::vertex, normal));

         // texture coordinates
         glEnableVertexAttribArray(2);
         glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(::gpu::gltf::vertex), (void *)offsetof(::gpu::gltf::vertex, uv));

         // color
         glEnableVertexAttribArray(3);
         glVertexAttribPointer(3, 4, GL_FLOAT, GL_FALSE, sizeof(::gpu::gltf::vertex), (void *)offsetof(::gpu::gltf::vertex, color));

         // tangent with .w = handness
         glEnableVertexAttribArray(4);
         glVertexAttribPointer(4, 4, GL_FLOAT, GL_FALSE, sizeof(::gpu::gltf::vertex), (void *)offsetof(::gpu::gltf::vertex, tangent));

         glBindVertexArray(0);
      }

   } // namespace gltf


} // namespace gpu_opengl
