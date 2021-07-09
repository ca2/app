#include "framework.h"
#include "_.h"


namespace gpu
{


   //const char* shader_type_c_str(GLenum etype)
   //{

   //   switch (etype)
   //   {
   //   case GL_VERTEX_SHADER:
   //      return "VERTEX";
   //   case GL_FRAGMENT_SHADER:
   //      return "FRAGMENT";
   //   case GL_GEOMETRY_SHADER:
   //      return "GEOMETRY";
   //   default:
   //      return "(Unknown Shader Type)";
   //   }

   //}


   shader::shader()
   {


   }


   shader::~shader()
   {


   }



   ::e_status shader::create_shader(const char * pszVertex, const char * pszFragment, const char * pszGeometry)
   {


      return ::success;

   }

   // activate the shader
   // ------------------------------------------------------------------------
   void shader::use()
   {
   }


   void shader::setBool(const char * pszName, bool value)
   {


   }


   void shader::setInt(const char * pszName, int value)
   {


   }


   void shader::setFloat(const char * pszName, float value)
   {


   }


//   void shader::setVec2(const char * pszName, const glm::vec2& value)
//   {
//
//   }


   void shader::setVec2(const char * pszName, float x, float y)
   {

   }


//   void shader::setVec3(const char * pszName, const glm::vec3& value)
//   {
//
//
//   }


   void shader::setVec3(const char * pszName, float x, float y, float z)
   {

   }


//   void shader::setVec4(const char * pszName, const glm::vec4& value)
//   {
//
//   }


   void shader::setVec4(const char * pszName, float x, float y, float z, float w)
   {

   }


   void shader::setMat2(const char * pszName, const float p[2*2])
   {

   }


   void shader::setMat3(const char * pszName, const float p[3*3])
   {

   }


   void shader::setMat4(const char * pszName, const float p[4*4])
   {

   }


   //::e_status shader::shader_compile_errors(GLuint shader, GLenum type, string & strSummary)
   //{

   //   ::e_status estatus = ::success;

   //   return estatus;

   //}


   //::e_status shader::program_compile_errors(GLuint program, string & strSummary)
   //{

   //   ::e_status estatus = ::success;


   //   return estatus;

   //}


} // namespace gpu



