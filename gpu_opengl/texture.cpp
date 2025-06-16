// Created by camilo on 2025-06-08 18:14 < 3ThomasBorregaardSørensen!!
#include "framework.h"
#include "texture.h"
#include "renderer.h"

namespace gpu_opengl
{


   texture::texture()
   {

      m_gluTextureID = 0;

   }


   texture::~texture()
   {

   }


   void texture::initialize_gpu_texture(::gpu::renderer* prenderer, const ::int_size& size) //, bool bCreateRenderTargetView, bool bCreateShaderResourceView)
   {

      if (m_size == size)
      {

         return;

      }

      ::gpu::texture::initialize_gpu_texture(prenderer, size);

      if (!m_gluTextureID)
      {

         glGenTextures(1, &m_gluTextureID);             // 1. Generate a texture ID
         GLCheckError("");

      }

      glBindTexture(GL_TEXTURE_2D, m_gluTextureID);  // 2. Bind the texture to the 2D texture target
      GLCheckError("");



      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
      GLCheckError("");
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
      GLCheckError("");
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
      GLCheckError("");
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
      GLCheckError("");

      ::memory memory;

      auto scan_area = m_size.area() * 4;

      memory.set_size(scan_area);

      auto data = memory.data();

      glTexImage2D(
         GL_TEXTURE_2D, 0, GL_RGBA,
         m_size.cx(),
         m_size.cy(),
         0, GL_RGBA, GL_UNSIGNED_BYTE, data);
      GLCheckError("");

      // Optional: generate mipmaps
      // glGenerateMipmap(GL_TEXTURE_2D);

      //free(data);

      glBindTexture(GL_TEXTURE_2D, 0);  // Unbind when done
      GLCheckError("");

   }


   void texture::blend(::gpu::texture* ptexture, const ::int_rectangle& rectangleTarget)
   {

      m_pgpurenderer->blend(this, ptexture, rectangleTarget);

   }


} // namespace gpu_opengl




