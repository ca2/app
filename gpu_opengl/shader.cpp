#include "framework.h"
#include "shader.h"


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
#if !defined(__APPLE__) && !defined(ANDROID)
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


   unsigned int shader::create_shader(const ::string & strSource, GLenum type)
   {

      unsigned int uShader;

      uShader = glCreateShader(type);

      if(!uShader)
      {

         GLenum eerror = glGetError();
         
#if defined(__APPLE__) || defined(ANDROID)
//         auto errString = glErrorString(eerror);
         FORMATTED_TRACE("error %d \"%s\"", eerror);

#else

         auto errString = gluErrorString(eerror);
         FORMATTED_TRACE("error %d \"%s\"", eerror, errString);

#endif
         

         return ::error_failed;

      }

      const char * sza[1];

      sza[0] = strSource;

      glShaderSource(uShader, 1, sza, NULL);

      glCompileShader(uShader);

      //string strSummary;

      //::e_status estatus =
      
      shader_compile_errors(uShader, type, m_strError);

      //if (!estatus)
      //{

      //   return 0;

      //}
      m_strError.Empty();

      return uShader;

   }


   void shader::create_shader(const ::string & pszVertex, const ::string & pszFragment, const ::string & pszGeometry)
   {

      unsigned int uVertex = create_shader(pszVertex, GL_VERTEX_SHADER);

      unsigned int uFragment = create_shader(pszFragment, GL_FRAGMENT_SHADER);
      
#if !defined(__APPLE__) && !defined(ANDROID)

      unsigned int uGeometry = 0;

      bool bGeometry = pszGeometry.trimmed().has_char();

      if (bGeometry)
      {

         uGeometry = create_shader(pszGeometry, GL_GEOMETRY_SHADER);

      }
      
#endif

      m_uId = glCreateProgram();

      glAttachShader(m_uId, uVertex);

      glAttachShader(m_uId, uFragment);
      
#if !defined(__APPLE__) && !defined(ANDROID)

      if (bGeometry)
      {

         glAttachShader(m_uId, uGeometry);

      }
      
#endif

      glLinkProgram(m_uId);
      
      // Validate program
//      glValidateProgram(m_uId);

      string strSummary;

      ///::e_status estatus =
      
      program_compile_errors(m_uId, strSummary);

      //if(estatus.succeeded())
      //{

      //   return estatus;

      //}

      // delete the shaders
      // they're linked into our program

      glDeleteShader(uVertex);

      glDeleteShader(uFragment);

#if !defined(__APPLE__) && !defined(ANDROID)

      if (bGeometry)
      {

         glDeleteShader(uGeometry);

      }
      
#endif

      //return ::success;

   }


   // activate the shader
   // ------------------------------------------------------------------------
   void shader::use()
   {
      
      glUseProgram(m_uId);
      
   }


   void shader::setBool(const ::string & pszName, bool value)
   {

      GLint i = glGetUniformLocation(m_uId, pszName);

      glUniform1i(i, (int)value);

   }


   void shader::setInt(const ::string & pszName, int value)
   {

      GLint i = glGetUniformLocation(m_uId, pszName);

      glUniform1i(i, value);

   }


   void shader::setFloat(const ::string & pszName, float value)
   {

      GLint i = glGetUniformLocation(m_uId, pszName);

      glUniform1f(i, value);

   }


//   void shader::setVec2(const ::string & pszName, const glm::vec2& value)
//   {
//
//      GLint i = glGetUniformLocation(m_uId, pszName);
//
//      glUniform2fv(i, 1, &value[0]);
//
//   }


   void shader::setVec2(const ::string & pszName, float x, float y)
   {

      GLint i = glGetUniformLocation(m_uId, pszName);

      glUniform2f(i, x, y);

   }


//   void shader::setVec3(const ::string & pszName, const glm::vec3& value)
//   {
//
//      GLint i = glGetUniformLocation(m_uId, pszName);
//
//      glUniform3fv(i, 1, &value[0]);
//
//   }


   void shader::setVec3(const ::string & pszName, float x, float y, float z)
   {

      GLint i = glGetUniformLocation(m_uId, pszName);

      glUniform3f(i, x, y, z);

   }


//   void shader::setVec4(const ::string & pszName, const glm::vec4& value)
//   {
//
//      GLint i = glGetUniformLocation(m_uId, pszName);
//
//      glUniform4fv(i, 1, &value[0]);
//
//   }


   void shader::setVec4(const ::string & pszName, float x, float y, float z, float w)
   {

      GLint i = glGetUniformLocation(m_uId, pszName);

      glUniform4f(i, x, y, z, w);

   }


   void shader::setMat2(const ::string & pszName, const float p[2*2])
   {

      GLint i = glGetUniformLocation(m_uId, pszName);

      glUniformMatrix2fv(i, 1, GL_FALSE, p);

   }


   void shader::setMat3(const ::string & pszName, const float p[3*3])
   {

      GLint i = glGetUniformLocation(m_uId, pszName);

      glUniformMatrix3fv(i, 1, GL_FALSE, p);

   }


   void shader::setMat4(const ::string & pszName, const float p[4*4])
   {

      GLint i = glGetUniformLocation(m_uId, pszName);

      glUniformMatrix4fv(i, 1, GL_FALSE, p);

   }


   void shader::shader_compile_errors(GLuint shader, GLenum type, string & strSummary)
   {

      //::e_status estatus = ::success;

      GLint success = 0;

      GLchar infoLog[1024];

      glGetShaderiv(shader, GL_COMPILE_STATUS, &success);

      if (success)
      {

         strSummary.format("SUCCESS::SHADER_COMPILATION (%s) \n -- --------------------------------------------------- -- \n", shader_type_c_str(type));

      }
      else
      {

         glGetShaderInfoLog(shader, sizeof(infoLog), NULL, infoLog);

         const char * psz = shader_type_c_str(type);

         const char * pszLog = infoLog;

         strSummary.format("FORMATTED_ERROR::SHADER_COMPILATION_ERROR of type: %s \n %s \n -- --------------------------------------------------- -- \n", psz, pszLog);

         throw ::exception(error_failed, "Shader Compilation Error", strSummary);

      }

      INFORMATION(strSummary);

      //return estatus;

   }


   void shader::program_compile_errors(GLuint program, string & strSummary)
   {

      //::e_status estatus = ::success;

      GLint success;

      GLchar infoLog[1024];
      
      glGetProgramiv(program, GL_LINK_STATUS, &success);

      if (success)
      {

         strSummary.format("SUCCESS::PROGRAM_LINKING \n -- --------------------------------------------------- -- \n");

      }
      else
      {

         glGetProgramInfoLog(program, sizeof(infoLog), NULL, infoLog);

         strSummary.format("FORMATTED_ERROR::PROGRAM_LINKING_ERROR : \n %s \n -- --------------------------------------------------- -- \n", infoLog);

         throw ::exception(error_failed);

      }

      INFORMATION(strSummary);

      //return estatus;

   }


   ::gpu::uniform shader::get_uniform(const ::string & strUniform)
   {
      
      auto uniform = glGetUniformLocation(m_uId, strUniform);

      return uniform;

   }


} // namespace opengl



