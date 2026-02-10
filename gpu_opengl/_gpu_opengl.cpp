// Created by camilo on 2025-06-15 18:14 <3ThomasBorregaardSørensen!!
#include "framework.h"
#include "_gpu_opengl.h"


namespace opengl
{


   exception::exception(const ::scoped_string& scopedstrMessage, int iGLError, const_char_pointer pszGlError, const ::scoped_string& nameFile, int iLine):
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


   [[noreturn]] void throw_exception(const ::scoped_string& scopestrMessage, int iGLError, const ::scoped_string& nameFile, int iLine)
   {

      auto pszGlErrorString = ::opengl_error_string(iGLError);

      const char *pszFramebufferStatusText = nullptr;
      
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
      case ::gpu::e_type_int:
         return GL_INT;
      case ::gpu::e_type_float:
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


   const char * check_framebuffer_status_text(GLenum status)
   {
      const char *psz = nullptr;
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
            case GL_FRAMEBUFFER_INCOMPLETE_MULTISAMPLE: psz= "incomplete multiple"; break;
            default: psz = "unknown error"; break;
         }
      }

      return psz;

   }


void defer_throw_gl_error()
{
   int iGlError = glGetError();
   
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

      int iGlError = glGetError();

      if (iGlError != 0)
      {

         ::opengl::throw_exception(pszErrorMessage, iGlError, __FILE__, __LINE__);

      }

   }


   void ensure_non_null_handle(long lHandle, const_char_pointer pszMessage)
   {

      if (!lHandle)
      {

         int iGlError = glGetError();

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



} // namespace opengl



