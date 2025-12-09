// From github:/tristancalderbank/OpenGL-PBR-Renderer/cubemap_framebuffer.cpp by
// camilo on 2025-09-26 19:52 <3ThomasBorregaardSorensen!!
#include "framework.h"
#include "cubemap_framebuffer.h"
#include "bred/gpu/context.h"
#include "bred/gpu/shader.h"
#include "bred/gpu/texture.h"

//#include <glad/glad.h>


namespace gpu
{


   namespace ibl
   {


      cubemap_framebuffer::cubemap_framebuffer()
      {


      }


      cubemap_framebuffer::~cubemap_framebuffer()
      {


      }


      void cubemap_framebuffer::initialize_cubemap_framebuffer(::gpu::context * pgpucontext, int width,
                                                               int height)
      {

         initialize_gpu_context_object(pgpucontext);

         ødefer_construct(m_ptexture);

         auto pgpurenderer = m_pgpucontext->m_pgpurenderer;

         ::int_rectangle rectangleTarget;

         rectangleTarget.set(0, 0, width, height);
         
         // m_ptexture->m_pgpurenderer = m_pgpucontext->m_pgpurenderer;
         //
         // m_ptexture->m_rectangleTarget.left=0;
         // m_ptexture->m_rectangleTarget.top=0;
         // m_ptexture->m_rectangleTarget.right=width;
         // m_ptexture->m_rectangleTarget.bottom=height;
         // m_ptexture->m_bRenderTarget = true;
         // m_ptexture->m_bShaderResourceView = true;
         //

         int iMipCount = floor(log2(maximum(width, height)));

         m_ptexture->initialize_mipmap_cubemap_texture(pgpurenderer, rectangleTarget,
            iMipCount, true, true);

         //on_initialize_cubemap_framebuffer();

         //
         //
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
         // for (auto i = 0; i < 6;  i++) {
         //     glTexImage2D(
         //         GL_TEXTURE_CUBE_MAP_POSITIVE_X + i,
         //         0,
         //         GL_RGB16F,
         //         width,
         //         height,
         //         0,
         //         GL_RGB,
         //         GL_FLOAT,
         //         nullptr);
         // }
         //
         // glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
         // glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
         // glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
         // glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
         // glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
         //
         // glBindFramebuffer(GL_FRAMEBUFFER, 0);
      }


      void cubemap_framebuffer::on_initialize_cubemap_framebuffer()
      {


      }



      void cubemap_framebuffer::bind(::gpu::command_buffer *pgpucommandbuffer)
      {
         //glBindFramebuffer(GL_FRAMEBUFFER, framebufferId);
      }


      void cubemap_framebuffer::generateMipmap()
      {

         m_ptexture->generate_mipmap();

      }


      void cubemap_framebuffer::set_cube_face(unsigned int iIndex, ::gpu::shader * pgpushader)
      {

         m_ptexture->set_cube_face(iIndex);
         //pgpushader->m_pg
         // glFramebufferTexture2D(
         //    GL_FRAMEBUFFER,
         //    GL_COLOR_ATTACHMENT0,
         //    GL_TEXTURE_CUBE_MAP_POSITIVE_X + index,
         //    cubemapTextureId,
         //    0);
      }


      // unsigned int cubemap_framebuffer::getCubemapTextureId()
      // {
      //    //return m_uCubemapTextureId;
      //    return 0;
      // }


   } // namespace ibl


} // namespace gpu
