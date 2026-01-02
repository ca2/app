// From github:/tristancalderbank/OpenGL-PBR-Renderer/brdf_convolution_framebuffer.cpp by
// camilo on 2025-09-26 19:50 <3ThomasBorregaardSorensen!!
#include "framework.h"
#include "brdf_convolution_framebuffer.h"
#include "bred/gpu/context_lock.h"
#include <glad/glad.h>

#include "texture.h"


namespace gpu_opengl
{


   namespace ibl
   {


      brdf_convolution_framebuffer::brdf_convolution_framebuffer()
      {


      }

      brdf_convolution_framebuffer::~brdf_convolution_framebuffer()
      {


      }


      // void brdf_convolution_framebuffer::on_initialize_BrdfConvolutionFramebuffer()
      // {
      //
      //    ::gpu::context_lock contextlock(m_pgpucontext);
      //
      //
      //    ::cast < gpu_opengl::texture>ptexture = m_ptexture;
      //
      //
      //    // framebuffer
      //    glGenFramebuffers(1, &ptexture->m_gluFbo);
      //    GLCheckError("");
      //    glBindFramebuffer(GL_FRAMEBUFFER, ptexture->m_gluFbo);
      //    GLCheckError("");
      //
      //    auto w = ptexture->rectangle().width();
      //
      //    auto h = ptexture->rectangle().height();
      //
      //    // depth buffer
      //    glGenRenderbuffers(1, &ptexture->m_gluDepthStencilRBO);
      //    GLCheckError("");
      //    glBindRenderbuffer(GL_RENDERBUFFER, ptexture->m_gluDepthStencilRBO);
      //    GLCheckError("");
      //    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT24, w, h);
      //    GLCheckError("");
      //
      //    // attach the depth buffer
      //    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, ptexture->m_gluDepthStencilRBO);
      //    GLCheckError("");
      //
      //    // color texture
      //    glGenTextures(1, &ptexture->m_gluTextureID);
      //    GLCheckError("");
      //    ptexture->m_gluType = GL_TEXTURE_2D;
      //    glBindTexture(GL_TEXTURE_2D, ptexture->m_gluTextureID);
      //    GLCheckError("");
      //
      //    glTexImage2D(GL_TEXTURE_2D, 0, GL_RG16F, w, h, 0, GL_RG, GL_FLOAT, 0);
      //    GLCheckError("");
      //    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
      //    GLCheckError("");
      //    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
      //    GLCheckError("");
      //    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
      //    GLCheckError("");
      //    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
      //    GLCheckError("");
      //
      //    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, ptexture->m_gluTextureID, 0);
      //    GLCheckError("");
      //
      //    GLenum status = glCheckFramebufferStatus(GL_FRAMEBUFFER);
      //
      //    if (status != GL_FRAMEBUFFER_COMPLETE)
      //    {
      //
      //       warning() << "Framebuffer incomplete! with status " << status;
      //
      //    }
      //
      //    glBindFramebuffer(GL_FRAMEBUFFER, 0);
      //    GLCheckError("");
      //
      //
      // }


      void brdf_convolution_framebuffer::bind()
      {::cast < gpu_opengl::texture>ptexture = m_ptexture;
         glBindFramebuffer(GL_FRAMEBUFFER, ptexture->m_gluFbo);
         GLCheckError("");
      }


      unsigned int brdf_convolution_framebuffer::getColorTextureId()
      {::cast < gpu_opengl::texture>ptexture = m_ptexture;
         return ptexture->m_gluTextureID;
      }


   } // namespace ibl


} // namespace gpu_opengl
