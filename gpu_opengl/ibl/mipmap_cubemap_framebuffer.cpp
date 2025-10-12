// From github:/tristancalderbank/OpenGL-PBR-Renderer/mipmap_cubemap_framebuffer.h by
// camilo on 2025-09-26 19:54 <3ThomasBorregaardSorensen!!
#include "framework.h"
#include "mipmap_cubemap_framebuffer.h"
#include "bred/gpu/context_lock.h"


#include <glad/glad.h>

#include "texture.h"


namespace gpu_opengl
{


   namespace ibl
   {


      mipmap_cubemap_framebuffer::mipmap_cubemap_framebuffer()
      {


      }


      mipmap_cubemap_framebuffer::~mipmap_cubemap_framebuffer()
      {


      }


      void mipmap_cubemap_framebuffer::on_initialize_mipmap_cubemap_framebuffer()
      {

         ::gpu::context_lock contextlock(m_pgpucontext);
         
         ::cast < ::gpu_opengl::texture>ptexture = m_ptexture;

         // framebuffer
         glGenFramebuffers(1, &ptexture->m_gluFbo);
         GLCheckError("");
         glBindFramebuffer(GL_FRAMEBUFFER, ptexture->m_gluFbo);
         GLCheckError("");

         auto w = ptexture->m_rectangleTarget.width();

         auto h = ptexture->m_rectangleTarget.height();

         // depth buffer
         glGenRenderbuffers(1, &ptexture->m_gluDepthStencilRBO);
         GLCheckError("");
         ptexture->m_gluType = GL_TEXTURE_CUBE_MAP;
         glBindRenderbuffer(GL_RENDERBUFFER, ptexture->m_gluDepthStencilRBO);
         GLCheckError("");
         glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT24, w, h);
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
               w,
               h,
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
         glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
         GLCheckError("");
         // trilinear filtering for the mipmap
         glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
         GLCheckError("");
         glGenerateMipmap(GL_TEXTURE_CUBE_MAP);
         GLCheckError("");

         GLenum status = glCheckFramebufferStatus(GL_FRAMEBUFFER);

         if (status != GL_FRAMEBUFFER_COMPLETE)
         {
            
            warning() << "Framebuffer incomplete! with status " << status;

         }

         glBindFramebuffer(GL_FRAMEBUFFER, 0);
         GLCheckError("");

      }


      void mipmap_cubemap_framebuffer::bind()
      {
         ::cast < ::gpu_opengl::texture>ptexture = m_ptexture;
         glBindFramebuffer(GL_FRAMEBUFFER, ptexture->m_gluFbo);
         GLCheckError("");
      }


      void mipmap_cubemap_framebuffer::setMipLevel(unsigned int level)
      {

         ::gpu::ibl::mipmap_cubemap_framebuffer::setMipLevel(level);
         // mipLevel = level;
         // mipWidth = ptexture->m_rectangleTarget.width() * std::pow(0.5, mipLevel);
         // mipHeight = ptexture->m_rectangleTarget.height() * std::pow(0.5, mipLevel);
         ::cast < ::gpu_opengl::texture>ptexture = m_ptexture;
         glBindRenderbuffer(GL_RENDERBUFFER, ptexture->m_gluDepthStencilRBO);
         GLCheckError("");
         glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT24, ptexture->m_sizeMip.cx(), ptexture->m_sizeMip.cy());
         GLCheckError("");

      }


      // unsigned int mipmap_cubemap_framebuffer::getWidth()
      // {
      //     return mipWidth;
      // }
      //
      // unsigned int mipmap_cubemap_framebuffer::getHeight()
      // {
      //     return mipHeight;
      // }

      void mipmap_cubemap_framebuffer::setCubeFace(unsigned int faceIndex)
      {

         ::gpu::ibl::mipmap_cubemap_framebuffer::setCubeFace(faceIndex);
         ::cast < ::gpu_opengl::texture>ptexture = m_ptexture;
         glFramebufferTexture2D(
            GL_FRAMEBUFFER,
            GL_COLOR_ATTACHMENT0,
            GL_TEXTURE_CUBE_MAP_POSITIVE_X + faceIndex,
            ptexture->m_gluTextureID,
            ptexture->m_mipsLevel);
         GLCheckError("");
      }


      unsigned int mipmap_cubemap_framebuffer::getCubemapTextureId()
      {
         ::cast < ::gpu_opengl::texture>ptexture = m_ptexture;
         return ptexture->m_gluTextureID;
      }


   } // namespace ibl


} // namespace gpu_opengl



