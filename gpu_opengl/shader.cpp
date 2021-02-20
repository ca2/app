#include "framework.h"
#include "_.h"


namespace opengl
{


   const char* shader_type_c_str(GLenum etype)
   {

      switch (etype)
      {
      case GL_VERTEX_SHADER:
         return "VERTEX";
      case GL_FRAGMENT_SHADER:
         return "FRAGMENT";
#if !defined(__APPLE__)
      case GL_GEOMETRY_SHADER:
         return "GEOMETRY";
#endif
      default:
         return "(Unknown Shader Type)";
      }

   }


   shader::shader()
   {


   }


   shader::~shader()
   {


   }


   unsigned int shader::create_shader(const char* pszSource, GLenum type)
   {

      unsigned int uShader;

      uShader = glCreateShader(type);

      if(!uShader)
      {

         GLenum eerror = glGetError();
         
#ifdef __APPLE__
         auto errString = gluErrorString(eerror);
         
#else

         auto errString = gluErrorString(eerror);
         
#endif
         
         TRACE("error %d \"%s\"", eerror, errString);

         return ::error_failed;

      }

      glShaderSource(uShader, 1, &pszSource, NULL);

      glCompileShader(uShader);

      string strSummary;

      ::e_status estatus = shader_compile_errors(uShader, type, strSummary);

      if (!estatus)
      {

         return 0;

      }


      return uShader;

   }


   ::e_status shader::create_shader(const char * pszVertex, const char * pszFragment, const char * pszGeometry)
   {

      unsigned int uVertex = create_shader(pszVertex, GL_VERTEX_SHADER);

      unsigned int uFragment = create_shader(pszFragment, GL_FRAGMENT_SHADER);
      
#if !defined(__APPLE__)

      unsigned int uGeometry = 0;

      bool bGeometry = ::is_set(pszGeometry) && string(pszGeometry).trimmed().has_char();

      if (bGeometry)
      {

         uGeometry = create_shader(pszGeometry, GL_GEOMETRY_SHADER);

      }
      
#endif

      m_uId = glCreateProgram();

      glAttachShader(m_uId, uVertex);

      glAttachShader(m_uId, uFragment);
      
#if !defined(__APPLE__)

      if (bGeometry)
      {

         glAttachShader(m_uId, uGeometry);

      }
      
#endif

      glLinkProgram(m_uId);
      
      // Validate program
//      glValidateProgram(m_uId);

      string strSummary;

      ::e_status estatus = program_compile_errors(m_uId, strSummary);

      if (estatus)
      {

         return estatus;

      }

      // delete the shaders
      // they're linked into our program

      glDeleteShader(uVertex);

      glDeleteShader(uFragment);

#if !defined(__APPLE__)

      if (bGeometry)
      {

         glDeleteShader(uGeometry);

      }
      
#endif

      return ::success;

   }


   // activate the shader
   // ------------------------------------------------------------------------
   void shader::use()
   {
      
      glUseProgram(m_uId);
      
   }


   void shader::setBool(const char * pszName, bool value)
   {

      GLint i = glGetUniformLocation(m_uId, pszName);

      glUniform1i(i, (int)value);

   }


   void shader::setInt(const char * pszName, int value)
   {

      GLint i = glGetUniformLocation(m_uId, pszName);

      glUniform1i(i, value);

   }


   void shader::setFloat(const char * pszName, float value)
   {

      GLint i = glGetUniformLocation(m_uId, pszName);

      glUniform1f(i, value);

   }


//   void shader::setVec2(const char * pszName, const glm::vec2& value)
//   {
//
//      GLint i = glGetUniformLocation(m_uId, pszName);
//
//      glUniform2fv(i, 1, &value[0]);
//
//   }


   void shader::setVec2(const char * pszName, float x, float y)
   {

      GLint i = glGetUniformLocation(m_uId, pszName);

      glUniform2f(i, x, y);

   }


//   void shader::setVec3(const char * pszName, const glm::vec3& value)
//   {
//
//      GLint i = glGetUniformLocation(m_uId, pszName);
//
//      glUniform3fv(i, 1, &value[0]);
//
//   }


   void shader::setVec3(const char * pszName, float x, float y, float z)
   {

      GLint i = glGetUniformLocation(m_uId, pszName);

      glUniform3f(i, x, y, z);

   }


//   void shader::setVec4(const char * pszName, const glm::vec4& value)
//   {
//
//      GLint i = glGetUniformLocation(m_uId, pszName);
//
//      glUniform4fv(i, 1, &value[0]);
//
//   }


   void shader::setVec4(const char * pszName, float x, float y, float z, float w)
   {

      GLint i = glGetUniformLocation(m_uId, pszName);

      glUniform4f(i, x, y, z, w);

   }


   void shader::setMat2(const char * pszName, const float p[2*2])
   {

      GLint i = glGetUniformLocation(m_uId, pszName);

      glUniformMatrix2fv(i, 1, GL_FALSE, p);

   }


   void shader::setMat3(const char * pszName, const float p[3*3])
   {

      GLint i = glGetUniformLocation(m_uId, pszName);

      glUniformMatrix3fv(i, 1, GL_FALSE, p);

   }


   void shader::setMat4(const char * pszName, const float p[4*4])
   {

      GLint i = glGetUniformLocation(m_uId, pszName);

      glUniformMatrix4fv(i, 1, GL_FALSE, p);

   }


   ::e_status shader::shader_compile_errors(GLuint shader, GLenum type, string & strSummary)
   {

      ::e_status estatus = ::success;

      GLint success = 0;

      GLchar infoLog[1024];

      glGetShaderiv(shader, GL_COMPILE_STATUS, &success);

      if (success)
      {

         strSummary.Format("SUCCESS::SHADER_COMPILATION (%s) \n -- --------------------------------------------------- -- \n", shader_type_c_str(type));

      }
      else
      {

         glGetShaderInfoLog(shader, sizeof(infoLog), NULL, infoLog);

         const char * psz = shader_type_c_str(type);

         const char * pszLog = infoLog;

         strSummary.Format("ERROR::SHADER_COMPILATION_ERROR of type: %s \n %s \n -- --------------------------------------------------- -- \n", psz, pszLog);

         estatus = ::error_failed;

      }

      _S_TRACE("%s", strSummary.c_str());

      return estatus;

   }


   ::e_status shader::program_compile_errors(GLuint program, string & strSummary)
   {

      ::e_status estatus = ::success;

      GLint success;

      GLchar infoLog[1024];
      
      glGetProgramiv(program, GL_LINK_STATUS, &success);

      if (success)
      {

         strSummary.Format("SUCCESS::PROGRAM_LINKING \n -- --------------------------------------------------- -- \n");

      }
      else
      {

         glGetProgramInfoLog(program, sizeof(infoLog), NULL, infoLog);

         strSummary.Format("ERROR::PROGRAM_LINKING_ERROR : \n %s \n -- --------------------------------------------------- -- \n", infoLog);

         estatus = ::error_failed;

      }

      _S_TRACE("%s", strSummary.c_str());

      return estatus;

   }


} // namespace opengl



