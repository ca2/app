// From github:/tristancalderbank/OpenGL-PBR-Renderer/MipmapCubemapFramebuffer.h by
// camilo on 2025-09-26 19:54 <3ThomasBorregaardSorensen!!
#include "framework.h"
#include "mipmapcubemapframebuffer.h"


#include <glad/glad.h>


namespace gpu_opengl
{


   namespace ibl
   {


      MipmapCubemapFramebuffer::MipmapCubemapFramebuffer()
      {


      }


      MipmapCubemapFramebuffer::~MipmapCubemapFramebuffer()
      {


      }


      void MipmapCubemapFramebuffer::on_initialize_MipmapCubemapFramebuffer()
      {
         // framebuffer
         glGenFramebuffers(1, &m_uFramebufferId);
         glBindFramebuffer(GL_FRAMEBUFFER, m_uFramebufferId);

         // depth buffer
         glGenRenderbuffers(1, &m_uDepthRenderbufferId);
         glBindRenderbuffer(GL_RENDERBUFFER, m_uDepthRenderbufferId);
         glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT24, m_uWidth, m_uHeight);

         // attach the depth buffer
         glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, m_uDepthRenderbufferId);

         // cubemap
         glGenTextures(1, &m_uCubemapTextureId);
         glBindTexture(GL_TEXTURE_CUBE_MAP, m_uCubemapTextureId);

         // specify/allocate each face for the cubemap
         for (auto i = 0; i < 6; i++)
         {
            glTexImage2D(
               GL_TEXTURE_CUBE_MAP_POSITIVE_X + i,
               0,
               GL_RGB16F,
               m_uWidth,
               m_uHeight,
               0,
               GL_RGB,
               GL_FLOAT,
               nullptr);
         }

         glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
         glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
         glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
         glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
         // trilinear filtering for the mipmap
         glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
         glGenerateMipmap(GL_TEXTURE_CUBE_MAP);

         glBindFramebuffer(GL_FRAMEBUFFER, 0);
      }


      void MipmapCubemapFramebuffer::bind()
      {
         glBindFramebuffer(GL_FRAMEBUFFER, m_uFramebufferId);
      }


      void MipmapCubemapFramebuffer::setMipLevel(unsigned int level)
      {

         ::gpu::ibl::MipmapCubemapFramebuffer::setMipLevel(level);
         // mipLevel = level;
         // mipWidth = m_uWidth * std::pow(0.5, mipLevel);
         // mipHeight = m_uHeight * std::pow(0.5, mipLevel);

         glBindRenderbuffer(GL_RENDERBUFFER, m_uDepthRenderbufferId);
         glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT24, m_uMipWidth, m_uMipHeight);
      }


      // unsigned int MipmapCubemapFramebuffer::getWidth()
      // {
      //     return mipWidth;
      // }
      //
      // unsigned int MipmapCubemapFramebuffer::getHeight()
      // {
      //     return mipHeight;
      // }

      void MipmapCubemapFramebuffer::setCubeFace(unsigned int faceIndex)
      {

         ::gpu::ibl::MipmapCubemapFramebuffer::setCubeFace(faceIndex);
         glFramebufferTexture2D(
            GL_FRAMEBUFFER,
            GL_COLOR_ATTACHMENT0,
            GL_TEXTURE_CUBE_MAP_POSITIVE_X + faceIndex,
            m_uCubemapTextureId,
            m_uMipLevel);
      }


      unsigned int MipmapCubemapFramebuffer::getCubemapTextureId()
      {
         return m_uCubemapTextureId;
      }


   } // namespace ibl


} // namespace gpu_opengl



