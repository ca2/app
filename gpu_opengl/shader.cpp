#include "framework.h"
#include "shader.h"


namespace gpu_opengl
{


   const char* shader_type_c_str(GLenum etype)
   {

      switch (etype)
      {
      case GL_VERTEX_SHADER:
         return "VERTEX";
      case GL_FRAGMENT_SHADER:
         return "FRAGMENT";
#if !defined(__APPLE__) && !defined(__ANDROID__)
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
         
         auto errString = opengl_error_string(eerror);

         informationf("error %d \"%s\"", eerror, errString);

         return ::error_failed;

      }

      const char * sza[1];

      sza[0] = strSource;

      glShaderSource(uShader, 1, sza, NULL);

      glCompileShader(uShader);

      information() << "compiling shader : " << sza[0];

      //string strSummary;

      //::e_status estatus =
      
      shader_compile_errors(uShader, type, m_strError);

      //if (!estatus)
      //{

      //   return 0;

      //}
      m_strError.empty();

      return uShader;

   }


   void shader::create_shader(const ::string & pszVertex, const ::string & pszFragment, const ::string & pszGeometry)
   {

      unsigned int uVertex = create_shader(pszVertex, GL_VERTEX_SHADER);

      unsigned int uFragment = create_shader(pszFragment, GL_FRAGMENT_SHADER);
      
#if !defined(__APPLE__) && !defined(__ANDROID__)

      unsigned int uGeometry = 0;

      bool bGeometry = pszGeometry.trimmed().has_character();

      if (bGeometry)
      {

         uGeometry = create_shader(pszGeometry, GL_GEOMETRY_SHADER);

      }
      
#endif

      m_uId = glCreateProgram();

      glAttachShader(m_uId, uVertex);

      glAttachShader(m_uId, uFragment);
      
#if !defined(__APPLE__) && !defined(__ANDROID__)

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

#if !defined(__APPLE__) && !defined(__ANDROID__)

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


   void shader::setBool(const ::scoped_string & scopedstrName, bool value)
   {

      auto p = get_payload(scopedstrName);

      if (!p)
      {

         throw ::exception(error_not_found, "property not found");

      }

      glUniform1i(p->m_iUniform, (int)value);

   }


   void shader::setInt(const ::scoped_string & scopedstrName, int value)
   {

      auto p = get_payload(scopedstrName);

      if (!p)
      {

         throw ::exception(error_not_found, "property not found");

      }

      glUniform1i(p->m_iUniform, value);

   }


   void shader::setFloat(const ::scoped_string & scopedstrName, float value)
   {

      auto p = get_payload(scopedstrName);

      if (!p)
      {

         throw ::exception(error_not_found, "property not found");

      }

      glUniform1f(p->m_iUniform, value);

   }


//   void shader::setVec2(const ::scoped_string & scopedstrName, const glm::vec2& value)
//   {
//
//      GLint i = glGetUniformLocation(m_uId, pszName);
//
//      glUniform2fv(i, 1, &value[0]);
//
//   }


   void shader::setVec2(const ::scoped_string & scopedstrName, float x, float y)
   {

      auto p = get_payload(scopedstrName);

      if (!p)
      {

         throw ::exception(error_not_found, "property not found");

      }

      glUniform2f(p->m_iUniform, x, y);

   }


//   void shader::setVec3(const ::scoped_string & scopedstrName, const glm::vec3& value)
//   {
//
//      GLint i = glGetUniformLocation(m_uId, pszName);
//
//      glUniform3fv(i, 1, &value[0]);
//
//   }


   void shader::setVec3(const ::scoped_string & scopedstrName, float x, float y, float z)
   {

      auto p = get_payload(scopedstrName);

      if (!p)
      {

         throw ::exception(error_not_found, "property not found");

      }

      glUniform3f(p->m_iUniform, x, y, z);

   }


//   void shader::setVec4(const ::scoped_string & scopedstrName, const glm::vec4& value)
//   {
//
//      GLint i = glGetUniformLocation(m_uId, pszName);
//
//      glUniform4fv(i, 1, &value[0]);
//
//   }


   void shader::setVec4(const ::scoped_string & scopedstrName, float x, float y, float z, float w)
   {

      auto p = get_payload(scopedstrName);

      if (!p)
      {

         throw ::exception(error_not_found, "property not found");

      }

      glUniform4f(p->m_iUniform, x, y, z, w);

   }


   void shader::setMat2(const ::scoped_string & scopedstrName, const float a[2*2])
   {

      auto p = get_payload(scopedstrName);

      if (!p)
      {

         throw ::exception(error_not_found, "property not found");

      }

      glUniformMatrix2fv(p->m_iUniform, 1, GL_FALSE, a);

   }


   void shader::setMat3(const ::scoped_string & scopedstrName, const float a[3*3])
   {

      auto p = get_payload(scopedstrName);

      if (!p)
      {

         throw ::exception(error_not_found, "property not found");

      }

      glUniformMatrix3fv(p->m_iUniform, 1, GL_FALSE, a);

   }


   void shader::setMat4(const ::scoped_string & scopedstrName, const float a[4*4])
   {

      auto p = get_payload(scopedstrName);

      if (!p)
      {

         throw ::exception(error_not_found, "property not found");

      }

      glUniformMatrix4fv(p->m_iUniform, 1, GL_FALSE, a);

   }


   void shader::shader_compile_errors(GLuint shader, GLenum type, string & strSummary)
   {

      //::e_status estatus = ::success;

      GLint success = 0;

      GLchar infoLog[1024];

      glGetShaderiv(shader, GL_COMPILE_STATUS, &success);

      if (success)
      {

         strSummary.formatf("SUCCESS::SHADER_COMPILATION (%s) \n -- --------------------------------------------------- -- \n", shader_type_c_str(type));

      }
      else
      {

         glGetShaderInfoLog(shader, sizeof(infoLog), NULL, infoLog);

         const char * psz = shader_type_c_str(type);

         const char * pszLog = infoLog;

         strSummary.formatf("error::SHADER_COMPILATION_ERROR of type: %s \n %s \n -- --------------------------------------------------- -- \n", psz, pszLog);

         warning() << strSummary;

         throw ::exception(error_failed, "Shader Compilation Error", strSummary);

      }

      information() << strSummary;

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

         strSummary.formatf("SUCCESS::PROGRAM_LINKING \n -- --------------------------------------------------- -- \n");

      }
      else
      {

         glGetProgramInfoLog(program, sizeof(infoLog), NULL, infoLog);

         strSummary.formatf("error::PROGRAM_LINKING_ERROR : \n %s \n -- --------------------------------------------------- -- \n", infoLog);

         throw ::exception(error_failed);

      }

      information() << strSummary;

      //return estatus;

   }


   ::gpu::payload * shader::get_payload(const ::scoped_string & scopedstrUniform)
   {
      
      auto p = m_mapLayout.plookup(scopedstrUniform);

      if (!p)
      {

         ::gpu::payload payload;

         payload.m_iUniform = glGetUniformLocation(m_uId, scopedstrUniform);

         m_mapLayout.set_at(scopedstrUniform, payload);
         
         auto p = m_mapLayout.plookup(scopedstrUniform);

      }

      return &p->element2();

   }


} // namespace gpu_opengl



