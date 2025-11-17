// From github:/tristancalderbank/OpenGL-PBR-Renderer/mipmap_cubemap_framebuffer.h by
// camilo on 2025-09-26 19:54 <3ThomasBorregaardSorensen!!
#include "framework.h"
#include "mipmap_cubemap_framebuffer.h"
#include "bred/gpu/context.h"
#include <math.h>

#include "bred/gpu/texture.h"


namespace gpu
{


   namespace ibl
   {


      mipmap_cubemap_framebuffer::mipmap_cubemap_framebuffer()
      {

      }


      mipmap_cubemap_framebuffer::~mipmap_cubemap_framebuffer()
      {


      }


      void mipmap_cubemap_framebuffer::initialize_mipmap_cubemap_framebuffer(::graphics3d::scene_base *pscenebase,
                                                                             int iWidth, int iHeight)

      {

         initialize_scene_object(pscenebase);

         // m_uWidth = width;
         // m_uHeight = height;
         // m_uMipLevel = 0;
         //

         ødefer_construct(m_ptexture);

         m_ptexture->m_pgpurenderer = m_pgpucontext->m_pgpurenderer;

         m_ptexture->m_rectangleTarget.left()=0;
         m_ptexture->m_rectangleTarget.top()=0;
         m_ptexture->m_rectangleTarget.right()= iWidth;
         m_ptexture->m_rectangleTarget.bottom()= iHeight;
         m_ptexture->m_iMipCount=floor(log2(maximum(iWidth, iHeight)));
         m_ptexture->m_bRenderTarget = true;
         m_ptexture->m_bShaderResourceView = true;

         on_initialize_mipmap_cubemap_framebuffer();

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


      void mipmap_cubemap_framebuffer::on_initialize_mipmap_cubemap_framebuffer()
      {

      }


      void mipmap_cubemap_framebuffer::bind()
      {
         ///glBindFramebuffer(GL_FRAMEBUFFER, framebufferId);
      }


      void mipmap_cubemap_framebuffer::set_current_mip(int iCurrentMip)
      {

         m_ptexture->m_iCurrentMip = iCurrentMip;
         m_ptexture->m_sizeMip.cx() =
            (int)((double) m_ptexture->m_rectangleTarget.width() * ::pow((double)0.5, (double)iCurrentMip));
         m_ptexture->m_sizeMip.cy() =
            (int)((double) m_ptexture->m_rectangleTarget.height() * ::pow((double)0.5, (double)iCurrentMip));

      }


      int mipmap_cubemap_framebuffer::mip_width()
      {

         return m_ptexture->m_sizeMip.width();

      }


      int mipmap_cubemap_framebuffer::mip_height()
      {

         return m_ptexture->m_sizeMip.height();

      }


      void mipmap_cubemap_framebuffer::set_cube_face(int iFace)
      {
         // glFramebufferTexture2D(
         //    GL_FRAMEBUFFER,
         //    GL_COLOR_ATTACHMENT0,
         //    GL_TEXTURE_CUBE_MAP_POSITIVE_X + faceIndex,
         //    m_uCubemapTextureId,
         //    m_uMipLevel);
      }

      //
      // unsigned int mipmap_cubemap_framebuffer::getCubemapTextureId()
      // {
      //    //return m_uCubemapTextureId;
      //
      //    return 0;
      // }


   } // namespace ibl


} // namespace gpu
