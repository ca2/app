// From github:/tristancalderbank/OpenGL-PBR-Renderer/cubemap_framebuffer.cpp by
// camilo on 2025-09-26 19:52 <3ThomasBorregaardSorensen!!
#include "framework.h"
#include "cubemap_framebuffer.h"
#include "bred/gpu/context_lock.h"

#include <glad/glad.h>

#include "texture.h"


namespace gpu_opengl
{


   namespace ibl
   {


      cubemap_framebuffer::cubemap_framebuffer()
      {


      }


      cubemap_framebuffer::~cubemap_framebuffer()
      {


      }


      void cubemap_framebuffer::on_initialize_cubemap_framebuffer()
      {

         ::gpu::context_lock contextlock(m_pgpucontext);

         ::cast < gpu_opengl::texture>ptexture = m_ptexture;

         // framebuffer
         glGenFramebuffers(1, &ptexture->m_gluFbo);
         GLCheckError("");
         glBindFramebuffer(GL_FRAMEBUFFER, ptexture->m_gluFbo);
         GLCheckError("");

         // depth buffer
         glGenRenderbuffers(1, &ptexture->m_gluDepthStencilRBO);
         GLCheckError("");
         ptexture->m_gluType = GL_TEXTURE_CUBE_MAP;
         glBindRenderbuffer(GL_RENDERBUFFER, ptexture->m_gluDepthStencilRBO);
         GLCheckError("");
         glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT24, ptexture->m_rectangleTarget.width(), ptexture->m_rectangleTarget.height());
         GLCheckError("");

         // attach the depth buffer
         glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, ptexture->m_gluDepthStencilRBO);
         GLCheckError("");

         // cubemap
         glGenTextures(1, &ptexture->m_gluTextureID);
         GLCheckError("");
         glBindTexture(GL_TEXTURE_CUBE_MAP, ptexture->m_gluTextureID);
         GLCheckError("");

         // specify/allocate each face for the cubemap
         for (auto i = 0; i < 6; i++)
         {

            glTexImage2D(
               GL_TEXTURE_CUBE_MAP_POSITIVE_X + i,
               0,
               GL_RGB16F,
               ptexture->m_rectangleTarget.width(),
               ptexture->m_rectangleTarget.height(),
               0,
               GL_RGB,
               GL_FLOAT,
               nullptr);
            GLCheckError("");

         }

         glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
         GLCheckError("");
         glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
         GLCheckError("");
         glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
         GLCheckError("");
         glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
         GLCheckError("");
         glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
         GLCheckError("");

         GLenum status = glCheckFramebufferStatus(GL_FRAMEBUFFER);

         if (status != GL_FRAMEBUFFER_COMPLETE)
         {

            warning() << "Framebuffer incomplete! with status " << status;
         }

         glBindFramebuffer(GL_FRAMEBUFFER, 0);
         GLCheckError("");

      }


      void cubemap_framebuffer::bind()
      {::cast < gpu_opengl::texture>ptexture = m_ptexture;
         glBindFramebuffer(GL_FRAMEBUFFER, ptexture->m_gluFbo);
         GLCheckError("");
      }


      void cubemap_framebuffer::generateMipmap()
      {
         ::cast < gpu_opengl::texture>ptexture = m_ptexture;
         glBindTexture(GL_TEXTURE_CUBE_MAP, ptexture->m_gluTextureID);
         GLCheckError("");
         glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
         GLCheckError("");
         glGenerateMipmap(GL_TEXTURE_CUBE_MAP);
         GLCheckError("");
      }


      void cubemap_framebuffer::setCubeFace(unsigned int index)
      {
         ::cast < gpu_opengl::texture>ptexture = m_ptexture;
         glFramebufferTexture2D(
            GL_FRAMEBUFFER,
            GL_COLOR_ATTACHMENT0,
            GL_TEXTURE_CUBE_MAP_POSITIVE_X + index,
            ptexture->m_gluTextureID,
            0);
         GLCheckError("");
      }


      unsigned int cubemap_framebuffer::getCubemapTextureId()
      {
         ::cast < gpu_opengl::texture>ptexture = m_ptexture;
         return ptexture->m_gluTextureID;
      }


   } // namespace ibl


} // namespace gpu_opengl
