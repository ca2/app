// From github:/tristancalderbank/OpenGL-PBR-Renderer/cubemap_framebuffer.cpp by
// camilo on 2025-09-26 19:52 <3ThomasBorregaardSorensen!!
#include "framework.h"
#include "cubemap_framebuffer.h"
#include "bred/gpu/context_lock.h"
#include "bred/gpu/shader.h"
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
         ::opengl::ensure_non_null_handle(ptexture->m_gluFbo, "glGenFramebuffers(1, ...)")
         ::opengl::check_error("");
         glBindFramebuffer(GL_FRAMEBUFFER, ptexture->m_gluFbo);
         ::opengl::check_error("");

         // depth buffer
         glGenRenderbuffers(1, &ptexture->m_gluDepthStencilRBO);
         ::opengl::check_error("");
         ptexture->m_gluType = GL_TEXTURE_CUBE_MAP;
         glBindRenderbuffer(GL_RENDERBUFFER, ptexture->m_gluDepthStencilRBO);
         ::opengl::check_error("");
         glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT24, ptexture->rectangle().width(), ptexture->rectangle().height());
         ::opengl::check_error("");

         // attach the depth buffer
         glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, ptexture->m_gluDepthStencilRBO);
         ::opengl::check_error("");

         // cubemap
         glGenTextures(1, &ptexture->m_gluTextureID);
         ::opengl::check_error("");
         glBindTexture(ptexture->m_gluType, ptexture->m_gluTextureID);
         ::opengl::check_error("");

         int width = ptexture->rectangle().width();
         int height = ptexture->rectangle().height();

         // specify/allocate each face for the cubemap
         for (auto i = 0; i < 6; i++)
         {

            glTexImage2D(
               GL_TEXTURE_CUBE_MAP_POSITIVE_X + i,
               0,
               GL_RGB16F,
               width,
               height,
               0,
               GL_RGB,
               GL_FLOAT,
               nullptr);
            ::opengl::check_error("");

         }

         glTexParameteri(ptexture->m_gluType, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
         ::opengl::check_error("");
         glTexParameteri(ptexture->m_gluType, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
         ::opengl::check_error("");
         glTexParameteri(ptexture->m_gluType, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
         ::opengl::check_error("");
         glTexParameteri(ptexture->m_gluType, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
         ::opengl::check_error("");
         glTexParameteri(ptexture->m_gluType, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
         ::opengl::check_error("");

         GLenum status = glCheckFramebufferStatus(GL_FRAMEBUFFER);

         if (status != GL_FRAMEBUFFER_COMPLETE)
         {

            warning() << "Framebuffer incomplete! with status " << status;
         }

         glBindFramebuffer(GL_FRAMEBUFFER, 0);
         ::opengl::check_error("");

      }


      void cubemap_framebuffer::bind(::gpu::command_buffer *pgpucommandbuffer)
      {::cast < gpu_opengl::texture>ptexture = m_ptexture;
         glBindFramebuffer(GL_FRAMEBUFFER, ptexture->m_gluFbo);
         ::opengl::check_error("");
      }


      void cubemap_framebuffer::generateMipmap()
      {
         ::cast < gpu_opengl::texture>ptexture = m_ptexture;
         glBindTexture(GL_TEXTURE_CUBE_MAP, ptexture->m_gluTextureID);
         ::opengl::check_error("");
         glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
         ::opengl::check_error("");
         glGenerateMipmap(GL_TEXTURE_CUBE_MAP);
         ::opengl::check_error("");
      }


      void cubemap_framebuffer::setCubeFace(unsigned int index, ::gpu::shader * pgpushader)
      {
         ::cast < gpu_opengl::texture>ptexture = m_ptexture;
         glFramebufferTexture2D(
            GL_FRAMEBUFFER,
            GL_COLOR_ATTACHMENT0,
            GL_TEXTURE_CUBE_MAP_POSITIVE_X + index,
            ptexture->m_gluTextureID,
            0);
         ::opengl::check_error("");
         
         //if (m_strSamplerUniform.has_character())
         //{
         //   pgpushader->set_int(m_strSamplerUniform, 0);
         //}

      }


      unsigned int cubemap_framebuffer::getCubemapTextureId()
      {
         ::cast < gpu_opengl::texture>ptexture = m_ptexture;
         return ptexture->m_gluTextureID;
      }


   } // namespace ibl


} // namespace gpu_opengl
