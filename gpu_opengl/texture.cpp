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

      ::gpu::texture::initialize_gpu_texture(prenderer, size);

      glGenTextures(1, &m_gluTextureID);             // 1. Generate a texture ID
      glBindTexture(GL_TEXTURE_2D, m_gluTextureID);  // 2. Bind the texture to the 2D texture target

      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

      ::memory memory;

      auto scan_area = m_size.area() * 4;

      memory.set_size(scan_area);

      auto data = memory.data();

      glTexImage2D(
         GL_TEXTURE_2D, 0, GL_RGBA,
         m_size.cx(),
         m_size.cy(),
         0, GL_RGBA, GL_UNSIGNED_BYTE, data);

      // Optional: generate mipmaps
      // glGenerateMipmap(GL_TEXTURE_2D);

      //free(data);

      glBindTexture(GL_TEXTURE_2D, 0);  // Unbind when done

   }


   void texture::blend(::gpu::texture* ptexture, const ::int_rectangle& rectangleTarget)
   {

      

   }


} // namespace gpu_opengl




