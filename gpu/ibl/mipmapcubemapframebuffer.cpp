// From github:/tristancalderbank/OpenGL-PBR-Renderer/MipmapCubemapFramebuffer.h by
// camilo on 2025-09-26 19:54 <3ThomasBorregaardSorensen!!
#include "framework.h"
#include "mipmapcubemapframebuffer.h"

#include <math.h>


namespace gpu
{


   namespace ibl
   {


      MipmapCubemapFramebuffer::MipmapCubemapFramebuffer()
      {


      }


      MipmapCubemapFramebuffer::~MipmapCubemapFramebuffer()
      {


      }


      void MipmapCubemapFramebuffer::initialize_MipmapCubemapFramebuffer(unsigned int width, unsigned int height)

      {

         m_uWidth = width;
         m_uHeight = height;
         m_uMipLevel = 0;


         on_initialize_MipmapCubemapFramebuffer();

         // // framebuffer
         // glGenFramebuffers(1, &framebufferId);
         // glBindFramebuffer(GL_FRAMEBUFFER, framebufferId);
         //
         // // depth buffer
         // glGenRenderbuffers(1, &depthRenderbufferId);
         // glBindRenderbuffer(GL_RENDERBUFFER, depthRenderbufferId);
         // glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT24, width, height);
         //
         // // attach the depth buffer
         // glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, depthRenderbufferId);
         //
         // // cubemap
         // glGenTextures(1, &cubemapTextureId);
         // glBindTexture(GL_TEXTURE_CUBE_MAP, cubemapTextureId);
         //
         // // specify/allocate each face for the cubemap
         // for (auto i = 0; i < 6; i++)
         // {
         //    glTexImage2D(
         //       GL_TEXTURE_CUBE_MAP_POSITIVE_X + i,
         //       0,
         //       GL_RGB16F,
         //       width,
         //       height,
         //       0,
         //       GL_RGB,
         //       GL_FLOAT,
         //       nullptr);
         // }
         //
         // glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
         // glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
         // glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
         // glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
         // // trilinear filtering for the mipmap
         // glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
         // glGenerateMipmap(GL_TEXTURE_CUBE_MAP);
         //
         // glBindFramebuffer(GL_FRAMEBUFFER, 0);
      }


      void MipmapCubemapFramebuffer::on_initialize_MipmapCubemapFramebuffer()
      {

      }


      void MipmapCubemapFramebuffer::bind()
      {
         ///glBindFramebuffer(GL_FRAMEBUFFER, framebufferId);
      }


      void MipmapCubemapFramebuffer::setMipLevel(unsigned int level)
      {
         m_uMipLevel = level;
         m_uMipWidth = (unsigned int)((double) m_uWidth * ::pow((double)0.5, (double) m_uMipLevel));
         m_uMipHeight = (unsigned int)((double) m_uHeight * ::pow((double)0.5, (double) m_uMipLevel));
         //
         // glBindRenderbuffer(GL_RENDERBUFFER, m_uDepthRenderbufferId);
         // glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT24, m_uMipWidth, m_uMipHeight);
      }


      unsigned int MipmapCubemapFramebuffer::getWidth()
      {
         return m_uMipWidth;
      }


      unsigned int MipmapCubemapFramebuffer::getHeight()
      {
         return m_uMipHeight;
      }


      void MipmapCubemapFramebuffer::setCubeFace(unsigned int faceIndex)
      {
         // glFramebufferTexture2D(
         //    GL_FRAMEBUFFER,
         //    GL_COLOR_ATTACHMENT0,
         //    GL_TEXTURE_CUBE_MAP_POSITIVE_X + faceIndex,
         //    m_uCubemapTextureId,
         //    m_uMipLevel);
      }

      //
      // unsigned int MipmapCubemapFramebuffer::getCubemapTextureId()
      // {
      //    //return m_uCubemapTextureId;
      //
      //    return 0;
      // }


   } // namespace ibl


} // namespace gpu
