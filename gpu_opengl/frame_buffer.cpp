// Created by camilo on 2025-05-24 20:56 <3ThomasBorregaardSorensen!!
#include "framework.h"
#include "frame_buffer.h"


namespace gpu_opengl
{


   frame_buffer::frame_buffer()
   {

      m_fbo = 0;
      m_tex = 0;
      m_rbo = 0;
      m_bWithDepthBuffer = false;

   }


   frame_buffer::~frame_buffer()
   {

      destroy();

   }


   void frame_buffer::create(const ::int_size& sizeNew, bool bWithDepthBuffer)
   {

      if (sizeNew.is_empty())
      {

         throw ::exception(::error_bad_argument, "framebuffer");

      }

      if (sizeNew == m_size)
      {

         return;

      }

      //destroy();

      if (!m_fbo)
      {

         glGenFramebuffers(1, &m_fbo);

      }
      glBindFramebuffer(GL_FRAMEBUFFER, m_fbo);

      if (!m_tex)
      {
         glGenTextures(1, &m_tex);
         int iGlError = glGetError();
         if (iGlError != 0)
         {

            warning() << "glGenTextures : " << opengl_error_string(iGlError);

         }
         glBindTexture(GL_TEXTURE_2D, m_tex);
         glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, sizeNew.width(), sizeNew.height(), 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);
         glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
         glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
         glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_tex, 0);
      }
      else
      {
         glBindTexture(GL_TEXTURE_2D, m_tex);
         glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, sizeNew.width(), sizeNew.height(), 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);
      }

      if (bWithDepthBuffer)
      {

         // Depth attachment
         glGenRenderbuffers(1, &m_rbo);
         glBindRenderbuffer(GL_RENDERBUFFER, m_rbo);
         glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT24, sizeNew.width(), sizeNew.height());
         glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, m_rbo);

      }

      auto status = glCheckFramebufferStatus(GL_FRAMEBUFFER);

      if (status != GL_FRAMEBUFFER_COMPLETE)
      {

         printf("Framebuffer not complete! %d\n", status);

      }

      glBindFramebuffer(GL_FRAMEBUFFER, 0);

      m_size = sizeNew;

   }


   void frame_buffer::bind()
   {

      GLint drawFboId = 0, readFboId = 0;

      glGetIntegerv(GL_DRAW_FRAMEBUFFER_BINDING, &drawFboId);
      glGetIntegerv(GL_READ_FRAMEBUFFER_BINDING, &readFboId);

      if (drawFboId != m_fbo)
      {

         glBindFramebuffer(GL_FRAMEBUFFER, m_fbo);

      }

      if (drawFboId != m_fbo)
      {

         glViewport(0, 0, m_size.cx(), m_size.cy());

      }
      //glBindFramebuffer(GL_FRAMEBUFFER, m_fbo);

   }


   void frame_buffer::unbind()
   {

      GLint drawFboId = 0, readFboId = 0;

      glGetIntegerv(GL_DRAW_FRAMEBUFFER_BINDING, &drawFboId);
      glGetIntegerv(GL_READ_FRAMEBUFFER_BINDING, &readFboId);

      if (drawFboId != m_fbo)
      {

         throw ::exception(error_wrong_state);

      }

      glBindFramebuffer(GL_FRAMEBUFFER, 0);

   }


   void frame_buffer::destroy()
   {

      if (m_size.area() > 0)
      {

         if (m_bWithDepthBuffer)
         {

            m_bWithDepthBuffer = false;

            glDeleteRenderbuffers(1, &m_rbo);

         }

         glDeleteTextures(1, &m_tex);
         glDeleteFramebuffers(1, &m_fbo);

         m_fbo = 0;
         m_tex = 0;

         m_size = {};

      }

   }


} // namespace gpu_opengl



