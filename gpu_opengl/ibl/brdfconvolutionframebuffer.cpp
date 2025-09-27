// From github:/tristancalderbank/OpenGL-PBR-Renderer/BrdfConvolutionFramebuffer.cpp by
// camilo on 2025-09-26 19:50 <3ThomasBorregaardSorensen!!
#include "framework.h"
#include "ibl/brdfconvolutionframebuffer.h"
#include <glad/glad.h>


namespace gpu_opengl
{


   namespace ibl
   {


      BrdfConvolutionFramebuffer::BrdfConvolutionFramebuffer()
      {


      }

      BrdfConvolutionFramebuffer::~BrdfConvolutionFramebuffer()
      {


      }


      void BrdfConvolutionFramebuffer::on_initialize_BrdfConvolutionFramebuffer()
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

         // color texture
         glGenTextures(1, &m_uColorTextureId);
         glBindTexture(GL_TEXTURE_2D, m_uColorTextureId);
         glTexImage2D(GL_TEXTURE_2D, 0, GL_RG16F, m_uWidth, m_uHeight, 0, GL_RG, GL_FLOAT, 0);
         glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
         glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
         glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
         glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

         glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_uColorTextureId, 0);

         glBindFramebuffer(GL_FRAMEBUFFER, 0);
      }


      void BrdfConvolutionFramebuffer::bind()
      {
         glBindFramebuffer(GL_FRAMEBUFFER, m_uFramebufferId);
      }


      // unsigned int BrdfConvolutionFramebuffer::getWidth()
      // {
      //    return width;
      // }
      //
      //
      // unsigned int BrdfConvolutionFramebuffer::getHeight()
      // {
      //    return height;
      // }
      //

      unsigned int BrdfConvolutionFramebuffer::getColorTextureId()
      {
         return m_uColorTextureId;
      }


   } // namespace ibl


} // namespace gpu_opengl
