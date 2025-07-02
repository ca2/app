// Created by camilo on 2025-06-08 18:14 < 3ThomasBorregaardSørensen!!
#include "framework.h"
#include "lock.h"
#include "texture.h"
#include "renderer.h"
#include "bred/gpu/context_lock.h"


namespace gpu_opengl
{


   texture::texture()
   {

      m_gluTextureID = 0;
      m_gluDepthStencilRBO = 0;
      m_gluFbo = 0;

   }


   texture::~texture()
   {

   }


   void texture::initialize_gpu_texture(::gpu::renderer* prenderer, const ::int_rectangle& rectangleTarget) //, bool bCreateRenderTargetView, bool bCreateShaderResourceView)
   {

      if (m_rectangleTarget == rectangleTarget)
      {

         return;

      }

      auto sizeCurrent = m_rectangleTarget.size();

      ::gpu::texture::initialize_gpu_texture(prenderer, rectangleTarget);

      ::gpu::context_lock contextlock(m_pgpurenderer->m_pgpucontext);

      if (sizeCurrent != rectangleTarget.size())
      {

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

         auto scan_area = m_rectangleTarget.area() * 4;

         memory.set_size(scan_area);

         auto data = memory.data();

         glTexImage2D(
            GL_TEXTURE_2D, 0, GL_RGBA,
            m_rectangleTarget.width(),
            m_rectangleTarget.height(),
            0, GL_RGBA, GL_UNSIGNED_BYTE, data);
         GLCheckError("");

         // Optional: generate mipmaps
         // glGenerateMipmap(GL_TEXTURE_2D);

         //free(data);

         glBindTexture(GL_TEXTURE_2D, 0);  // Unbind when done
         GLCheckError("");

      }

   }


   //void texture::blend(::gpu::texture* ptexture, const ::int_rectangle& rectangleTarget)
   //{

   //   m_pgpurenderer->blend(this, ptexture, rectangleTarget);

   //}


   void texture::create_render_target()
   {

      if (m_gluFbo)
      {

         return;

      }

      ::gpu::context_lock contextlock(m_pgpurenderer->m_pgpucontext);


      GLuint fboSrc, fboDst;
      glGenFramebuffers(1, &m_gluFbo);
      GLCheckError("");
      glBindFramebuffer(GL_FRAMEBUFFER, m_gluFbo);
      GLCheckError("");

      if (m_gluTextureID)
      {

         glBindTexture(GL_TEXTURE_2D, m_gluTextureID);
         GLCheckError("");

         glFramebufferTexture2D(GL_DRAW_FRAMEBUFFER, GL_COLOR_ATTACHMENT0,
            GL_TEXTURE_2D, m_gluTextureID, 0);
         GLCheckError("");

         // Set draw buffer
         GLenum drawBufs[] = { GL_COLOR_ATTACHMENT0 };
         glDrawBuffers(1, drawBufs); // REQUIRED for user-defined FBOs
         GLCheckError("");

      }

      if (m_gluDepthStencilRBO)
      {

         glBindRenderbuffer(GL_RENDERBUFFER, m_gluDepthStencilRBO);
         GLCheckError("");

         glFramebufferRenderbuffer(
            GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT,
            GL_RENDERBUFFER, m_gluDepthStencilRBO);
         GLCheckError("");

      }

      GLenum status = glCheckFramebufferStatus(GL_FRAMEBUFFER);

      if (status != GL_FRAMEBUFFER_COMPLETE)
      {

         warning() << "Framebuffer attachment is not complete";

      }

      glBindFramebuffer(GL_FRAMEBUFFER, 0);

   }


   void texture::create_depth_resources()
   {

      if (m_gluDepthStencilRBO)
      {

         return;

      }

      int width = m_rectangleTarget.width();

      int height = m_rectangleTarget.height();

      glGenRenderbuffers(1, &m_gluDepthStencilRBO);
      GLCheckError("");

      glBindRenderbuffer(GL_RENDERBUFFER, m_gluDepthStencilRBO);
      GLCheckError("");

      glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, width, height);
      GLCheckError("");

      glBindRenderbuffer(GL_RENDERBUFFER, 0);
      GLCheckError("");

   }


   void texture::bind_render_target()
   {

      if (!m_gluFbo)
      {

         throw ::exception(error_wrong_state);

      }

      glBindFramebuffer(GL_FRAMEBUFFER, m_gluFbo);
      GLCheckError("");

   }


} // namespace gpu_opengl




