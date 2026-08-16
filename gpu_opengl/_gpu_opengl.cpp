// Created by camilo on 2025-06-15 18:14 <3ThomasBorregaardSørensen!!
#include "platform.h"
#include "_gpu_opengl.h"


namespace opengl
{


   exception::exception(const ::scoped_string& scopedstrMessage, ::i32 iGLError, const_char_pointer pszGlError, const ::scoped_string& nameFile, ::i32 iLine):
      ::exception(error_open_failed, scopedstrMessage),
      m_iGlError(iGLError)
   {

      m_strDetails += pszGlError;
      m_strFile = __FILE__; 
      m_iLine = __LINE__; 
         
   }


   exception::~exception()
   {


   }


   [[noreturn]] void throw_exception(const ::scoped_string& scopestrMessage, ::i32 iGLError, const ::scoped_string& nameFile, ::i32 iLine)
   {

      auto pszGlErrorString = ::opengl_error_string(iGLError);

      const_char_pointer pszFramebufferStatusText = nullptr;
      
      void * pCurrentContext = nullptr;

      if (iGLError == GL_INVALID_OPERATION)
      {
         
         pCurrentContext = ::opengl::operating_system_current_context();
         
      }
      else if (iGLError == GL_INVALID_FRAMEBUFFER_OPERATION)
      {

         GLenum status = glCheckFramebufferStatus(GL_FRAMEBUFFER);

         pszFramebufferStatusText = check_framebuffer_status_text(status);

         if (::is_set(pszFramebufferStatusText))
         {
            warning("glCheckFramebufferStatus(GL_FRAMEBUFFER) return \"{}\".", pszFramebufferStatusText);

         }

      }

      throw ::opengl::exception(scopestrMessage, iGLError, pszGlErrorString, __FILE__, __LINE__);

   }


   CLASS_DECL_GPU_OPENGL GLenum get_gpu_type_unit_opengl_type(::gpu::enum_type etype)
   {

      switch (etype)
      {
      case ::gpu::e_type_i32:
         return GL_INT;
      case ::gpu::e_type_f32:
         return GL_FLOAT;
      case ::gpu::e_type_seq2:
         return GL_FLOAT;
      case ::gpu::e_type_seq3:
         return GL_FLOAT;
      case ::gpu::e_type_seq4:
         return GL_FLOAT;
      case ::gpu::e_type_mat2:
         return GL_FLOAT;
      case ::gpu::e_type_mat3:
         return GL_FLOAT;
      case ::gpu::e_type_mat4:
         return GL_FLOAT;
      default:
         throw ::exception(error_not_implemented);

      }

   }


   CLASS_DECL_GPU_OPENGL GLenum as_gl_draw_mode(::gpu::enum_topology etopology)
   {

      switch (etopology)
      {
      case ::gpu::e_topology_triangle_list:
         return GL_TRIANGLES;
      case ::gpu::e_topology_triangle_strip:
         return GL_TRIANGLE_STRIP;
      case ::gpu::e_topology_line_list:
         return GL_LINES;
      default:
         throw ::exception(error_unexpected);
      }

   }


   const_char_pointer check_framebuffer_status_text(GLenum status)
   {
      const_char_pointer psz = nullptr;
      if (status != GL_FRAMEBUFFER_COMPLETE)
      {
         switch (status)
         {
            //case GL_FRAMEBUFFER_UNDEFINED: str= "undefined"; break;
            case GL_FRAMEBUFFER_INCOMPLETE_ATTACHMENT: psz= "incomplete attachment"; break;
            case GL_FRAMEBUFFER_INCOMPLETE_MISSING_ATTACHMENT: psz= "incomplete/missing attachment"; break;
            case GL_FRAMEBUFFER_INCOMPLETE_DRAW_BUFFER: psz= "incomplete draw buffer"; break;
            case GL_FRAMEBUFFER_INCOMPLETE_READ_BUFFER: psz= "incomplete read buffer"; break;
            case GL_FRAMEBUFFER_UNSUPPORTED: psz= "unsupported"; break;
            case GL_FRAMEBUFFER_INCOMPLETE_MULTISAMPLE: psz= "incomplete multisample"; break;
            default: psz = "unknown error"; break;
         }
      }

      return psz;

   }


void defer_throw_gl_error()
{
   ::i32 iGlError = glGetError();
   
   if (iGlError != 0)
   {
      
      ::string strOpenGLError;
      
      strOpenGLError.formatf("OpenGL error %d", iGlError);
      
      throw ::exception(error_failed, strOpenGLError);
      
   }
   
}

#if defined(__APPLE__)

   void insert_debug_message(const_char_pointer pszMessage)
   {
      
      
   }
   
#endif


   void check_error(const_char_pointer pszErrorMessage)
   {

      ::i32 iGlError = glGetError();

      if (iGlError != 0)
      {

         ::opengl::throw_exception(pszErrorMessage, iGlError, __FILE__, __LINE__);

      }

   }


   void ensure_non_null_handle(long lHandle, const_char_pointer pszMessage)
   {

      if (!lHandle)
      {

         ::i32 iGlError = glGetError();

         if (iGlError != 0)
         {

            auto pszGlErrorString = ::opengl_error_string(iGlError);

            ::string strError(pszGlErrorString);

            if (::has_character(pszMessage))
            {

               strError = ::string(pszMessage) + " : " + strError;

            }

            strError += " : Handle is null and it shouldn't be null.";

            ::warning(strError);

            ::opengl::throw_exception(strError, iGlError, __FILE__, __LINE__);

         }
         else
         {

            ::string strError;

            if (::has_character(pszMessage))
            {

               strError = ::string(pszMessage) + " : " + strError;

            }

            if (strError.has_character())
            {

               strError += " : ";

            }

            strError += "Handle is null and it shouldn't be null.";

            throw ::exception(error_wrong_state, strError);

         }

      }

   }


   GLint get_framebuffer_sample_count(GLuint framebuffer)
   {

      GLint previousDrawFramebuffer = 0;

      glGetIntegerv(GL_DRAW_FRAMEBUFFER_BINDING, &previousDrawFramebuffer);

      glBindFramebuffer(GL_DRAW_FRAMEBUFFER, framebuffer);

      GLint sampleBuffers = 0;
      GLint samples = 0;

      glGetIntegerv(GL_SAMPLE_BUFFERS, &sampleBuffers);
      glGetIntegerv(GL_SAMPLES, &samples);

      glBindFramebuffer(GL_DRAW_FRAMEBUFFER, static_cast<GLuint>(previousDrawFramebuffer));

      if (sampleBuffers == 0)
      {

         return 0;
      }

      return samples;
   }


   bool create_resolve_framebuffer(resolve_framebuffer &resolve, int width, int height,
                                   GLenum internalFormat, GLenum format,
                                   GLenum type)
   {

      GLint previousFramebuffer = 0;
      GLint previousTexture = 0;

      glGetIntegerv(GL_FRAMEBUFFER_BINDING, &previousFramebuffer);

      glGetIntegerv(GL_TEXTURE_BINDING_2D, &previousTexture);

      resolve.m_width = width;
      resolve.m_height = height;

      glGenFramebuffers(1, &resolve.m_framebuffer);

      glBindFramebuffer(GL_FRAMEBUFFER, resolve.m_framebuffer);

      glGenTextures(1, &resolve.m_texture);

      glBindTexture(GL_TEXTURE_2D, resolve.m_texture);

      glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, width, height, 0, format, type, nullptr);

      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);

      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

      glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, resolve.m_texture, 0);

      glDrawBuffer(GL_COLOR_ATTACHMENT0);
      glReadBuffer(GL_COLOR_ATTACHMENT0);

      GLenum status = glCheckFramebufferStatus(GL_FRAMEBUFFER);

      glBindTexture(GL_TEXTURE_2D, static_cast<GLuint>(previousTexture));

      glBindFramebuffer(GL_FRAMEBUFFER, static_cast<GLuint>(previousFramebuffer));

      if (status != GL_FRAMEBUFFER_COMPLETE)
      {

         glDeleteTextures(1, &resolve.m_texture);

         glDeleteFramebuffers(1, &resolve.m_framebuffer);

         resolve = {};

         return false;
      }

      return true;
   }

   bool resolve_multisampled_framebuffer(GLuint sourceFramebuffer, const resolve_framebuffer &destination, int width,
                                         int height, GLenum sourceReadBuffer)
   {

      GLint samples = get_framebuffer_sample_count(sourceFramebuffer);

      if (samples <= 1)
      {

         // No resolve is necessary.
         return false;
      }

      GLint previousReadFramebuffer = 0;
      GLint previousDrawFramebuffer = 0;

      glGetIntegerv(GL_READ_FRAMEBUFFER_BINDING, &previousReadFramebuffer);

      glGetIntegerv(GL_DRAW_FRAMEBUFFER_BINDING, &previousDrawFramebuffer);

      glBindFramebuffer(GL_READ_FRAMEBUFFER, sourceFramebuffer);

      glReadBuffer(sourceReadBuffer);

      GLenum sourceStatus = glCheckFramebufferStatus(GL_READ_FRAMEBUFFER);

      if (sourceStatus != GL_FRAMEBUFFER_COMPLETE)
      {

         glBindFramebuffer(GL_READ_FRAMEBUFFER, static_cast<GLuint>(previousReadFramebuffer));

         glBindFramebuffer(GL_DRAW_FRAMEBUFFER, static_cast<GLuint>(previousDrawFramebuffer));

         return false;
      }

      glBindFramebuffer(GL_DRAW_FRAMEBUFFER, destination.m_framebuffer);

      glDrawBuffer(GL_COLOR_ATTACHMENT0);

      GLenum destinationStatus = glCheckFramebufferStatus(GL_DRAW_FRAMEBUFFER);

      if (destinationStatus != GL_FRAMEBUFFER_COMPLETE)
      {

         glBindFramebuffer(GL_READ_FRAMEBUFFER, static_cast<GLuint>(previousReadFramebuffer));

         glBindFramebuffer(GL_DRAW_FRAMEBUFFER, static_cast<GLuint>(previousDrawFramebuffer));

         return false;
      }

      glBlitFramebuffer(0, 0, width, height, 0, 0, destination.m_width, destination.m_height, GL_COLOR_BUFFER_BIT,
                        GL_NEAREST);

      GLenum error = glGetError();

      glBindFramebuffer(GL_READ_FRAMEBUFFER, static_cast<GLuint>(previousReadFramebuffer));

      glBindFramebuffer(GL_DRAW_FRAMEBUFFER, static_cast<GLuint>(previousDrawFramebuffer));

      return error == GL_NO_ERROR;
   }
} // namespace opengl



