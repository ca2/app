// From github:/tristancalderbank/OpenGL-PBR-Renderer/brdf_convolution_framebuffer.cpp by
// camilo on 2025-09-26 19:50 <3ThomasBorregaardSorensen!!
#include "framework.h"
#include "brdf_convolution_framebuffer.h"
#include "bred/gpu/context.h"
#include "bred/gpu/texture.h"
//#include "glad/glad.h"


namespace gpu
{


   namespace ibl
   {


      brdf_convolution_framebuffer::brdf_convolution_framebuffer()
      {


      }


      brdf_convolution_framebuffer::~brdf_convolution_framebuffer()
      {


      }



      void brdf_convolution_framebuffer::initialize_BrdfConvolutionFramebuffer(::graphics3d::scene_base *pscenebase,
                                                                               unsigned int width, unsigned int height)
      {

         initialize_scene_object(pscenebase);
         // m_uWidth = width;
         // m_uHeight = height;

         auto pgpurenderer = m_pgpucontext->m_pgpurenderer;

         ødefer_construct(m_ptexture);
         //m_ptexture->m_pgpurenderer = m_pgpucontext->m_pgpurenderer;

         ::gpu::texture_attributes textureattributes(int_rectangle{API_CHANGED_ARGUMENT, width, height});
         textureattributes.m_iBitsPerChannel = 16;
         textureattributes.m_iChannelCount = 2;
         textureattributes.m_iFloat = 1;


         ::gpu::texture_flags textureflags;
         textureflags.m_bRenderTarget = true;
         textureflags.m_bShaderResource = true;

         //m_ptexture->m_bRedGreen = true;
         //m_ptexture->m_bFloat = true;
         //m_ptexture->m_textureflags.m_bWithDepth = true;


         m_ptexture->initialize_texture(pgpurenderer, textureattributes, textureflags);
         //on_initialize_BrdfConvolutionFramebuffer();

         // framebuffer
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
         // // color texture
         // glGenTextures(1, &colorTextureId);
         // glBindTexture(GL_TEXTURE_2D, colorTextureId);
         // glTexImage2D(GL_TEXTURE_2D, 0, GL_RG16F, width, height, 0, GL_RG, GL_FLOAT, 0);
         // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
         // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
         // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
         // glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
         //
         // glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, colorTextureId, 0);
         //
         // glBindFramebuffer(GL_FRAMEBUFFER, 0);
      }


      void brdf_convolution_framebuffer::on_initialize_BrdfConvolutionFramebuffer()
      {

         m_ptexture->initialize_texture(m_pgpucontext->m_pgpurenderer, m_ptexture->rectangle(), true, {});

      }


      void brdf_convolution_framebuffer::bind()
      {
         //glBindFramebuffer(GL_FRAMEBUFFER, framebufferId);
      }


      unsigned int brdf_convolution_framebuffer::getWidth()
      {
         return m_ptexture->width();
      }


      unsigned int brdf_convolution_framebuffer::getHeight()
      {
         return m_ptexture->height();
      }
      //
      //
      // unsigned int brdf_convolution_framebuffer::getColorTextureId()
      // {
      //    //return m_uColorTextureId;
      //    return 0;
      // }


   } // namespace ibl


} // namespace gpu



