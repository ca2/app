// Created by camilo on 2025-06-15 18:14 <3ThomasBorregaardSørensen!!
#include "framework.h"


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


   [[noreturn]] void throw_opengl_exception(const ::scoped_string& scopestrMessage, int iGLError, const ::scoped_string& nameFile, int iLine)
   {

      auto pszGlErrorString = ::opengl_error_string(iGLError);

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


} // namespace opengl


void defer_throw_gl_error()
{

   int iGlError = glGetError();

   if (iGlError != 0)
   {

      ::string strOpenGLError;

      strOpenGLError.format("OpenGL error {}", iGlError);

      throw ::exception(error_failed, strOpenGLError);

   }

}
