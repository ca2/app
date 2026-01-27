// From github:/tristancalderbank/OpenGL-PBR-Renderer/mipmap_cubemap_framebuffer.h by
// camilo on 2025-09-26 19:54 <3ThomasBorregaardSorensen!!
#include "framework.h"
#include "../aaa_mipmap_cubemap_framebuffer.h"
#include "bred/gpu/context_lock.h"


#include <glad/glad.h>

#include "texture.h"


namespace gpu_opengl
{


   namespace ibl
   {


      aaa_mipmap_cubemap_framebuffer::aaa_mipmap_cubemap_framebuffer()
      {


      }


      aaa_mipmap_cubemap_framebuffer::~aaa_mipmap_cubemap_framebuffer()
      {


      }


      void aaa_mipmap_cubemap_framebuffer::on_initialize_mipmap_cubemap_framebuffer()
      {

         ::gpu::context_lock contextlock(m_pgpucontext);
         
         ::cast < ::gpu_opengl::texture>ptexture = m_ptexture;

         // framebuffer
         glGenFramebuffers(1, &ptexture->m_gluFbo);
         ::opengl::check_error("");
         glBindFramebuffer(GL_FRAMEBUFFER, ptexture->m_gluFbo);
         ::opengl::check_error("");

         auto w = ptexture->rectangle().width();

         auto h = ptexture->rectangle().height();

         // depth buffer
         glGenRenderbuffers(1, &ptexture->m_gluDepthStencilRBO);
         ::opengl::check_error("");
         ptexture->m_gluType = GL_TEXTURE_CUBE_MAP;
         glBindRenderbuffer(GL_RENDERBUFFER, ptexture->m_gluDepthStencilRBO);
         ::opengl::check_error("");
         glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT24, w, h);
         ::opengl::check_error("");

         // attach the depth buffer
         glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, ptexture->m_gluDepthStencilRBO);
         ::opengl::check_error("");

         // cubemap
         glGenTextures(1, &ptexture->m_gluTextureID);
         ::opengl::check_error("");
         glBindTexture(GL_TEXTURE_CUBE_MAP, ptexture->m_gluTextureID);
         ::opengl::check_error("");

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
            ::opengl::check_error("");

         }

         glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
         ::opengl::check_error("");
         glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
         ::opengl::check_error("");
         glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
         ::opengl::check_error("");
         glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
         ::opengl::check_error("");
         // trilinear filtering for the mipmap
         glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
         ::opengl::check_error("");
         glGenerateMipmap(GL_TEXTURE_CUBE_MAP);
         ::opengl::check_error("");

         GLenum status = glCheckFramebufferStatus(GL_FRAMEBUFFER);

         if (status != GL_FRAMEBUFFER_COMPLETE)
         {
            
            warning() << "Framebuffer incomplete! with status " << status;

         }

         glBindFramebuffer(GL_FRAMEBUFFER, 0);
         ::opengl::check_error("");

      }


      void aaa_mipmap_cubemap_framebuffer::bind()
      {
         ::cast < ::gpu_opengl::texture>ptexture = m_ptexture;
         glBindFramebuffer(GL_FRAMEBUFFER, ptexture->m_gluFbo);
         ::opengl::check_error("");
      }


      void aaa_mipmap_cubemap_framebuffer::set_current_mip(int iCurrentMip)
      {

         ::gpu::ibl::aaa_mipmap_cubemap_framebuffer::set_current_mip(iCurrentMip);
         // mipLevel = level;
         // mipWidth = ptexture->rectangle().width() * std::pow(0.5, mipLevel);
         // mipHeight = ptexture->rectangle().height() * std::pow(0.5, mipLevel);
         ::cast < ::gpu_opengl::texture>ptexture = m_ptexture;
         int iRbo = ptexture->m_gluDepthStencilRBO;
         glBindRenderbuffer(GL_RENDERBUFFER, ptexture->m_gluDepthStencilRBO);
         ::opengl::check_error("");
         if (iRbo > 0)
         {
            int iMipWidth = ptexture->m_sizeMip.cx;
            int iMipHeight = ptexture->m_sizeMip.cy;
            glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT24, iMipWidth, iMipHeight);
            ::opengl::check_error("");
         }

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

      void aaa_mipmap_cubemap_framebuffer::set_cube_face(int iFace)
      {

         ::gpu::ibl::aaa_mipmap_cubemap_framebuffer::set_cube_face(iFace);

         ::cast < ::gpu_opengl::texture>ptexture = m_ptexture;

         glFramebufferTexture2D(
            GL_FRAMEBUFFER,
            GL_COLOR_ATTACHMENT0,
            GL_TEXTURE_CUBE_MAP_POSITIVE_X + iFace,
            ptexture->m_gluTextureID,
            ptexture->m_iCurrentMip);

         ::opengl::check_error("");

      }


      unsigned int aaa_mipmap_cubemap_framebuffer::getCubemapTextureId()
      {
         ::cast < ::gpu_opengl::texture>ptexture = m_ptexture;
         return ptexture->m_gluTextureID;
      }


   } // namespace ibl


} // namespace gpu_opengl



