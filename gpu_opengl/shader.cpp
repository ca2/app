#include "framework.h"
//#include "lock.h"
#include "input_layout.h"
#include "render_target.h"
#include "renderer.h"
#include "shader.h"
#include "texture.h"
#include "acme/filesystem/filesystem/file_context.h"
#include "bred/gpu/bred_approach.h"
#include "bred/gpu/context.h"
#include "bred/gpu/context_lock.h"
#include "bred/gpu/device.h"
#include "bred/gpu/frame.h"
#include "bred/gpu/renderer.h"
#include "bred/gpu/types.h"


namespace gpu_opengl
{


   const_char_pointer shader_type_c_str(GLenum etype)
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


   unsigned int shader::create_shader(const ::block& blockSource, GLenum type)
   {

      ::gpu::context_lock contextlock(m_pgpurenderer->m_pgpucontext);

      unsigned int uShader;

      uShader = glCreateShader(type);

      if (!uShader)
      {

         GLenum eerror = glGetError();

         auto errString = opengl_error_string(eerror);

         informationf("error %d \"%s\"", eerror, errString);

         throw ::exception(::error_failed);

      }

      const_char_pointer sza[1];

      sza[0] = (const_char_pointer )blockSource.begin();

      GLint ia[1];

      ia[0] = (int)blockSource.size();

      glShaderSource(uShader, 1, sza, ia);

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


   void shader::on_initialize_shader()
   {

      if (m_memoryVertex.is_empty())
      {

         m_memoryVertex = file()->as_memory(m_pgpurenderer->m_pgpucontext->m_pgpudevice->shader_path(m_pathVertex));

      }

      if (m_memoryFragment.is_empty())
      {

         m_memoryFragment = file()->as_memory(m_pgpurenderer->m_pgpucontext->m_pgpudevice->shader_path(m_pathFragment));

      }

      unsigned int uVertex = create_shader(m_memoryVertex, GL_VERTEX_SHADER);

      unsigned int uFragment = create_shader(m_memoryFragment, GL_FRAGMENT_SHADER);

      //#if !defined(__APPLE__) && !defined(__ANDROID__)
      //
      //      unsigned int uGeometry = 0;
      //
      //      bool bGeometry = pszGeometry.trimmed().has_character();
      //
      //      if (bGeometry)
      //      {
      //
      //         uGeometry = create_shader(scopedstrGeometry, GL_GEOMETRY_SHADER);
      //
      //      }
      //      
      //#endif

      m_ProgramID = glCreateProgram();

      glAttachShader(m_ProgramID, uVertex);

      glAttachShader(m_ProgramID, uFragment);

      //#if !defined(__APPLE__) && !defined(__ANDROID__)
      //
      //      if (bGeometry)
      //      {
      //
      //         glAttachShader(m_ProgramID, uGeometry);
      //
      //      }
      //      
      //#endif

      glLinkProgram(m_ProgramID);

      // Validate program
//      glValidateProgram(m_ProgramID);

      string strSummary;

      ///::e_status estatus =

      program_compile_errors(m_ProgramID, strSummary);

      //if(estatus.succeeded())
      //{

      //   return estatus;

      //}


      // delete the shaders
      // they're linked into our program

      glDeleteShader(uVertex);

      glDeleteShader(uFragment);

      //#if !defined(__APPLE__) && !defined(__ANDROID__)
      //
      //      if (bGeometry)
      //      {
      //
      //         glDeleteShader(uGeometry);
      //
      //      }
      //      
      //#endif

            //return ::success;

   }


   // activate the shader
   // ------------------------------------------------------------------------
   void shader::bind(::gpu::texture* pgputextureTarget, ::gpu::texture* pgputextureSource)
   {

      bind(pgputextureTarget);

      bind_source(pgputextureSource, 0);

   }

   void shader::bind()
   {

      ::cast < render_target> prendertarget = m_pgpurenderer->m_pgpurendertarget;

      ::cast < texture > ptexture = prendertarget->current_texture(::gpu::current_frame());

      bind(ptexture);

   }


   void shader::bind(::gpu::texture* pgputextureTarget)
   {

      _bind();

      ::cast < texture > ptexture = pgputextureTarget;

      if (!ptexture->m_gluFbo)
      {

         ptexture->create_render_target();

      }

      //glBindFramebuffer(GL_DRAW_FRAMEBUFFER, ptexture->m_gluFbo);
      //GLCheckError("");

      glBindFramebuffer(GL_FRAMEBUFFER, ptexture->m_gluFbo);
      GLCheckError("");

      glDrawBuffer(GL_COLOR_ATTACHMENT0);
      GLCheckError("");

      //glBindFramebuffer(GL_READ_FRAMEBUFFER, 0);
      //GLCheckError("");

      {

         GLint drawFbo = 0;
         glGetIntegerv(GL_DRAW_FRAMEBUFFER_BINDING, &drawFbo);

         GLint readFbo = 0;
         glGetIntegerv(GL_READ_FRAMEBUFFER_BINDING, &readFbo);

         ::string strMessage;

         strMessage.formatf("ø shader_bind drawFbo=%d readFbo=%d", drawFbo, readFbo);

         glDebugMessageInsert(GL_DEBUG_SOURCE_APPLICATION,
            GL_DEBUG_TYPE_MARKER,
            0,
            GL_DEBUG_SEVERITY_NOTIFICATION,
            -1,
            strMessage);

      }




   }


   void shader::_bind()
   {

      if (m_bEnableBlend)
      {

         glEnable(GL_BLEND);
         glBlendFunc(GL_ONE, GL_ONE_MINUS_SRC_ALPHA);

      }
      else
      {

         glDisable(GL_BLEND);

      }


      if (m_bDisableDepthTest)
      {

         glDisable(GL_DEPTH_TEST);
         glDepthMask(GL_FALSE);

      }
      else
      {

         glEnable(GL_DEPTH_TEST);
         
         if (m_bDepthTestButNoDepthWrite)
         {

            glDepthMask(GL_FALSE);

         }
         else
         {

            glDepthMask(GL_TRUE);

         }

         if (m_bLequalDepth)
         {

            glDepthFunc(GL_LEQUAL);

         }
         else
         {

            glDepthFunc(GL_LESS);

         }

      }

      glUseProgram(m_ProgramID);
      GLCheckError("");

   }



   void shader::unbind()
   {

      if (m_ptextureBound)
      {

         ::cast < texture > ptextureBound = m_ptextureBound;

         glBindTexture(ptextureBound->m_gluType, 0);
         GLCheckError("");

         m_ptextureBound = nullptr;

      }

      glUseProgram(0);
      GLCheckError("");

   }


   void shader::bind_source(::gpu::texture* pgputexture, int iSlot)
   {

      glActiveTexture(GL_TEXTURE0);
      GLCheckError("");

      ::cast < texture > ptexture = pgputexture;

      GLuint tex = ptexture->m_gluTextureID;

      glBindTexture(ptexture->m_gluType, tex);
      GLCheckError("");

      ::string strUniform;

      if (m_bindingSampler.is_set())
         strUniform = m_bindingSampler.m_strUniform;
      else if(m_bindingCubeSampler.is_set())
         strUniform = m_bindingCubeSampler.m_strUniform;

      if (strUniform.is_empty())
      {

         strUniform = "uTexture";

      }

      _set_int(strUniform, iSlot);

      m_ptextureBound = ptexture;

   }


   //   void shader::setBool(const ::scoped_string & scopedstrName, bool value)
   //   {
   //
   //      auto p = get_payload(scopedstrName);
   //
   //      if (!p)
   //      {
   //
   //         throw ::exception(error_not_found, "property not found");
   //
   //      }
   //
   //      glUniform1i(p->m_iUniform, (int)value);
   //
   //   }
   //
   //
   //   void shader::setInt(const ::scoped_string & scopedstrName, int value)
   //   {
   //
   //      auto p = get_payload(scopedstrName);
   //
   //      if (!p)
   //      {
   //
   //         throw ::exception(error_not_found, "property not found");
   //
   //      }
   //
   //      glUniform1i(p->m_iUniform, value);
   //
   //   }
   //
   //
   //   void shader::setFloat(const ::scoped_string & scopedstrName, float value)
   //   {
   //
   //      auto p = get_payload(scopedstrName);
   //
   //      if (!p)
   //      {
   //
   //         throw ::exception(error_not_found, "property not found");
   //
   //      }
   //
   //      glUniform1f(p->m_iUniform, value);
   //
   //   }
   //
   //
   ////   void shader::setVec2(const ::scoped_string & scopedstrName, const glm::vec2& value)
   ////   {
   ////
   ////      GLint i = glGetUniformLocation(m_ProgramID, pszName);
   ////
   ////      glUniform2fv(i, 1, &value[0]);
   ////
   ////   }
   //
   //
   //   void shader::setVec2(const ::scoped_string & scopedstrName, float x, float y)
   //   {
   //
   //      auto p = get_payload(scopedstrName);
   //
   //      if (!p)
   //      {
   //
   //         throw ::exception(error_not_found, "property not found");
   //
   //      }
   //
   //      glUniform2f(p->m_iUniform, x, y);
   //
   //   }
   //
   //
   ////   void shader::setVec3(const ::scoped_string & scopedstrName, const glm::vec3& value)
   ////   {
   ////
   ////      GLint i = glGetUniformLocation(m_ProgramID, pszName);
   ////
   ////      glUniform3fv(i, 1, &value[0]);
   ////
   ////   }
   //
   //
   //   void shader::setVec3(const ::scoped_string & scopedstrName, float x, float y, float z)
   //   {
   //
   //      auto p = get_payload(scopedstrName);
   //
   //      if (!p)
   //      {
   //
   //         throw ::exception(error_not_found, "property not found");
   //
   //      }
   //
   //      glUniform3f(p->m_iUniform, x, y, z);
   //
   //   }
   //
   //
   ////   void shader::setVec4(const ::scoped_string & scopedstrName, const glm::vec4& value)
   ////   {
   ////
   ////      GLint i = glGetUniformLocation(m_ProgramID, pszName);
   ////
   ////      glUniform4fv(i, 1, &value[0]);
   ////
   ////   }
   //
   //
   //   void shader::setVec4(const ::scoped_string & scopedstrName, float x, float y, float z, float w)
   //   {
   //
   //      auto p = get_payload(scopedstrName);
   //
   //      if (!p)
   //      {
   //
   //         throw ::exception(error_not_found, "property not found");
   //
   //      }
   //
   //      glUniform4f(p->m_iUniform, x, y, z, w);
   //
   //   }
   //
   //
   //   void shader::setMat2(const ::scoped_string & scopedstrName, const float a[2*2])
   //   {
   //
   //      auto p = get_payload(scopedstrName);
   //
   //      if (!p)
   //      {
   //
   //         throw ::exception(error_not_found, "property not found");
   //
   //      }
   //
   //      glUniformMatrix2fv(p->m_iUniform, 1, GL_FALSE, a);
   //
   //   }
   //
   //
   //   void shader::setMat3(const ::scoped_string & scopedstrName, const float a[3*3])
   //   {
   //
   //      auto p = get_payload(scopedstrName);
   //
   //      if (!p)
   //      {
   //
   //         throw ::exception(error_not_found, "property not found");
   //
   //      }
   //
   //      glUniformMatrix3fv(p->m_iUniform, 1, GL_FALSE, a);
   //
   //   }
   //
   //
   //   void shader::setMat4(const ::scoped_string & scopedstrName, const float a[4*4])
   //   {
   //
   //      auto p = get_payload(scopedstrName);
   //
   //      if (!p)
   //      {
   //
   //         throw ::exception(error_not_found, "property not found");
   //
   //      }
   //
   //      glUniformMatrix4fv(p->m_iUniform, 1, GL_FALSE, a);
   //
   //   }
   //

   void shader::shader_compile_errors(GLuint shader, GLenum type, string& strSummary)
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

         const_char_pointer psz = shader_type_c_str(type);

         const_char_pointer pszLog = infoLog;

         strSummary.formatf("error::SHADER_COMPILATION_ERROR of type: %s \n %s \n -- --------------------------------------------------- -- \n", psz, pszLog);

         warning() << strSummary;

         throw ::exception(error_failed, "Shader Compilation Error", strSummary);

      }

      information() << strSummary;

      //return estatus;

   }


   void shader::program_compile_errors(GLuint program, string& strSummary)
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


   //void shader::setup_sampler_and_texture(const ::scoped_string& scopedstrName, int i)
   //{

   //   if (i == 0)
   //   {

   //      glActiveTexture(GL_TEXTURE0);
   //      GLCheckError("");

   //   }

   //   set_int(scopedstrName, i);

   //}


   void shader::_set_bool(const_char_pointer name, bool b) const
   {

      _set_int(name, b ? 0 : 1);

   }


   void shader::_set_int(const_char_pointer name, int i) const
   {
      //Bind();  // Ensure the shader program is bound
      GLint location = glGetUniformLocation(m_ProgramID, name);
      GLCheckError("");
      if (location == -1) {
         warning() << "Uniform " << name << " not found!";
         throw ::exception(error_not_found);
         return;
      }
      glUniform1i(location, i);
      int iGlErrorSetInt = glGetError();
      GLCheckError("");
      if (iGlErrorSetInt != 0)
      {
         warning() << "Uniform " << name << " not set!";

      }
   }
   void shader::_set_float(const_char_pointer name, float value) const
   {
      //Bind();  // Ensure the shader program is bound
      GLint location = glGetUniformLocation(m_ProgramID, name);
      GLCheckError("");
      if (location == -1) {
         warning() << "Uniform " << name << " not found!";
         throw ::exception(error_not_found);
         return;
      }
      glUniform1f(location, value);
      GLCheckError("");
   }
   void shader::_set_vec2(const_char_pointer name, const glm::vec2& value) const {
      //Bind();  // Ensure the shader program is bound
      GLint location = glGetUniformLocation(m_ProgramID, name);
      GLCheckError("");
      if (location == -1) {
         warning() << "Uniform " << name << " not found!";
         throw ::exception(error_not_found);
         return;
      }
      glUniform2f(location, value.x, value.y);
      GLCheckError("");
   }
   void shader::_set_vec3(const_char_pointer name, const glm::vec3& value) const {
      //Bind();  // Ensure the shader program is bound
      GLint location = glGetUniformLocation(m_ProgramID, name);
      GLCheckError("");
      if (location == -1) {
         warning() << "Uniform " << name << " not found!";
         throw ::exception(error_not_found);
         return;
      }
      glUniform3f(location, value.x, value.y, value.z);
      GLCheckError("");
   }
   void shader::_set_vec4(const_char_pointer name, const glm::vec4& value) const {
      //Bind();  // Ensure the shader program is bound
      GLint location = glGetUniformLocation(m_ProgramID, name);
      //GLCheckError("");
      if (location == -1) {
         warning() << "Uniform " << name << " not found!";
         throw ::exception(error_not_found);

         return;
      }
      glUniform4f(location, value.x, value.y, value.z, value.w);
      GLCheckError("");
   }

   void shader::_set_mat2(const_char_pointer name, const glm::mat2& matrix) const
   {
      GLint location = glGetUniformLocation(m_ProgramID, name);
      GLCheckError("");
      if (location == -1) {
         warning() << "Uniform " << name << " not found!";
         throw ::exception(error_not_found);
         return;
      }
      glUniformMatrix2fv(location, 1, GL_FALSE, glm::value_ptr(matrix));
      GLCheckError("");
   }


   void shader::_set_mat3(const_char_pointer name, const glm::mat3& matrix) const
   {
      GLint location = glGetUniformLocation(m_ProgramID, name);
      GLCheckError("");
      if (location == -1) {
         warning() << "Uniform " << name << " not found!";
         throw ::exception(error_not_found);
         return;
      }
      glUniformMatrix3fv(location, 1, GL_FALSE, glm::value_ptr(matrix));
      GLCheckError("");
   }

   void shader::_set_mat4(const_char_pointer name, const glm::mat4& matrix) const
   {
      GLint location = glGetUniformLocation(m_ProgramID, name);
      GLCheckError("");
      if (location == -1) {
         warning() << "Uniform " << name << " not found!";
         throw ::exception(error_not_found);
         return;
      }
      glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(matrix));
      GLCheckError("");
   }


   void shader::push_properties()
   {

      auto p = m_propertiesPush.m_pproperties;

      int iLen = 0;

      while (true)
      {

         if (::is_null(p->m_pszName))
         {

            break;

         }

         switch (p->m_etype)
         {
         case ::gpu::e_type_int:
            _set_int(p->m_pszName, *(int*)(m_propertiesPush.data() + iLen));
            break;
         case ::gpu::e_type_float:
            _set_float(p->m_pszName, *(float*)(m_propertiesPush.data() + iLen));
            break;
         case ::gpu::e_type_seq2:
            _set_vec2(p->m_pszName, *(glm::vec2*)(m_propertiesPush.data() + iLen));
            break;
         case ::gpu::e_type_seq3:
            _set_vec3(p->m_pszName, *(glm::vec3*)(m_propertiesPush.data() + iLen));
            break;
         case ::gpu::e_type_seq4:
            _set_vec4(p->m_pszName, *(glm::vec4*)(m_propertiesPush.data() + iLen));
            break;
         case ::gpu::e_type_mat2:
            _set_mat2(p->m_pszName, *(glm::mat2*)(m_propertiesPush.data() + iLen));
            break;
         case ::gpu::e_type_mat3:
            _set_mat3(p->m_pszName, *(glm::mat3*)(m_propertiesPush.data() + iLen));
            break;
         case ::gpu::e_type_mat4:
            _set_mat4(p->m_pszName, *(glm::mat4*)(m_propertiesPush.data() + iLen));
            break;

         }

         auto iLenItem = ::gpu::get_type_size(p->m_etype);

         iLen += iLenItem;

         p++;

      }




   }


   //::gpu::payload * shader::get_payload(const ::scoped_string & scopedstrUniform)
   //{
   //   
   //   auto p = m_mapLayout.plookup(scopedstrUniform);

   //   if (!p)
   //   {

   //      ::gpu::payload payload;

   //      payload.m_iUniform = glGetUniformLocation(m_ProgramID, scopedstrUniform);

   //      m_mapLayout.set_at(scopedstrUniform, payload);
   //      
   //      auto p = m_mapLayout.plookup(scopedstrUniform);

   //   }

   //   return &p->element2();

   //}



   //void shader::draw()
   //{

   //   glDrawArrays(GL_TRIANGLES, 0, 6);

   //}


   void shader::set_bool(const ::scoped_string& scopedstrName, bool value)
   {

      if (m_propertiesPush.m_pproperties)
      {

         ::gpu::shader::set_bool(scopedstrName, value);

      }
      else
      {

         _set_bool(::string(scopedstrName), value);

      }

   }


   void shader::set_int(const ::scoped_string& scopedstrName, int value)
   {

      if (m_propertiesPush.m_pproperties)
      {

         ::gpu::shader::set_int(scopedstrName, value);

      }
      else
      {

         _set_int(::string(scopedstrName), value);

      }

   }
   
   
   void shader::set_float(const ::scoped_string& scopedstrName, float value)
   {

      if (m_propertiesPush.m_pproperties)
      {

         ::gpu::shader::set_float(scopedstrName, value);

      }
      else
      {

         _set_float(::string(scopedstrName), value);

      }

   }
   
   
   void shader::set_vec2(const ::scoped_string& scopedstrName, float x, float y)
   {

      if (m_propertiesPush.m_pproperties)
      {

         ::gpu::shader::set_vec2(scopedstrName, x, y);

      }
      else
      {

         _set_vec2(::string(scopedstrName), { x, y });

      }

   }
   
   
   void shader::set_vec2(const ::scoped_string& scopedstrName, const ::glm::vec2& a)
   {

      if (m_propertiesPush.m_pproperties)
      {

         ::gpu::shader::set_vec2(scopedstrName, a);

      }
      else
      {

         _set_vec2(::string(scopedstrName), a);

      }

   }
   
   
   void shader::set_vec3(const ::scoped_string& scopedstrName, float x, float y, float z)
   {

      if (m_propertiesPush.m_pproperties)
      {

         ::gpu::shader::set_vec3(scopedstrName, x, y, z);

      }
      else
      {

         _set_vec3(::string(scopedstrName), { x, y, z });

      }

   }
   
   
   void shader::set_vec3(const ::scoped_string& scopedstrName, const ::glm::vec3& a)
   {

      if (m_propertiesPush.m_pproperties)
      {

         ::gpu::shader::set_vec3(scopedstrName, a);

      }
      else
      {

         _set_vec3(::string(scopedstrName), a);

      }

   }


   void shader::set_vec4(const ::scoped_string& scopedstrName, float x, float y, float z, float w)
   {

      if (m_propertiesPush.m_pproperties)
      {

         ::gpu::shader::set_vec4(scopedstrName, x, y, z, w);

      }
      else
      {

         _set_vec4(::string(scopedstrName), { x, y, z, w });

      }

   }


   void shader::set_vec4(const ::scoped_string& scopedstrName, const ::glm::vec4& a)
   {

      if (m_propertiesPush.m_pproperties)
      {

         ::gpu::shader::set_vec4(scopedstrName, a);

      }
      else
      {

         _set_vec4(::string(scopedstrName), a);

      }

   }


   void shader::set_mat2(const ::scoped_string& scopedstrName, const ::glm::mat2& a)
   {

      if (m_propertiesPush.m_pproperties)
      {

         ::gpu::shader::set_mat2(scopedstrName, a);

      }
      else
      {

         _set_mat2(::string(scopedstrName), a);

      }

   }


   void shader::set_mat3(const ::scoped_string& scopedstrName, const ::glm::mat3& a)
   {

      if (m_propertiesPush.m_pproperties)
      {

         ::gpu::shader::set_mat3(scopedstrName, a);

      }
      else
      {

         _set_mat3(::string(scopedstrName), a);

      }

   }


   void shader::set_mat4(const ::scoped_string& scopedstrName, const ::glm::mat4& a)
   {

      if (m_propertiesPush.m_pproperties)
      {

         ::gpu::shader::set_mat4(scopedstrName, a);

      }
      else
      {

         _set_mat4(::string(scopedstrName), a);

      }

   }


} // namespace gpu_opengl



