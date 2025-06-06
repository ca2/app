#pragma once


#include "aura/graphics/gpu/shader.h"


namespace gpu_opengl
{


   class CLASS_DECL_GPU_OPENGL shader :
      virtual public ::gpu::shader
   {
   public:


      GLuint m_ProgramID;

      //__creatable_from_base(shader, ::gpu::shader);
      
      
      shader();
      ~shader() override;


      void on_initialize_shader() override;


      void bind() override;
      void unbind() override;
      
      //virtual void initialize_shader(
      //   ::gpu::context* pgpucontext,
      //   const ::file::path& pathVertex,
      //   const ::file::path& pathFragment,
      //   const ::gpu::property* pproperties,
      //   enum_flag eflag = e_flag_none) override;

      //virtual void initialize_shader_with_block(
      //   ::gpu::context* pgpucontext,
      //   const ::block& blockVertex,
      //   const ::block& blockFragment,
      //   const ::gpu::property* pproperties,
      //   enum_flag eflag = e_flag_none) override;

      //virtual void use() override;

      //virtual void setBool(const ::scoped_string & scopedstrName, bool value) override;

      //virtual void setInt(const ::scoped_string & scopedstrName, int value) override;

      //virtual void setFloat(const ::scoped_string & scopedstrName, float value) override;

      ////virtual void setVec2(const ::scoped_string & scopedstrName, const glm::vec2& value) override;
      //virtual void setVec2(const ::scoped_string & scopedstrName, float x, float y) override;

      ////virtual void setVec3(const ::scoped_string & scopedstrName, const glm::vec3& value) override;
      //virtual void setVec3(const ::scoped_string & scopedstrName, float x, float y, float z) override;

      ////virtual void setVec4(const ::scoped_string & scopedstrName, const glm::vec4& value) override;
      //virtual void setVec4(const ::scoped_string & scopedstrName, float x, float y, float z, float w) override;

      ////virtual void setMat2(const ::scoped_string & scopedstrName, const glm::mat2& mat) override;
      ////virtual void setMat3(const ::scoped_string & scopedstrName, const glm::mat3& mat) override;
      ////virtual void setMat4(const ::scoped_string & scopedstrName, const glm::mat4& mat) override;
      //virtual void setMat2(const ::scoped_string & scopedstrName, const float p[2*2]) override;
      //virtual void setMat3(const ::scoped_string & scopedstrName, const float p[3*3]) override;
      //virtual void setMat4(const ::scoped_string & scopedstrName, const float p[4*4]) override;



      unsigned int create_shader(const ::block & blockVertex, GLenum type);

      virtual void shader_compile_errors(GLuint shader, GLenum type, string & strSummary);

      virtual void program_compile_errors(GLuint program, string & strSummary);
      //::gpu::payload * get_payload(const ::scoped_string & scopedestrUniform) override;

      void _set_int(const char* name, int value) const;
      void _set_float(const char* name, float value) const;
      void _set_vec2(const char* name, const glm::vec2& value) const;
      void _set_vec3(const char* name, const glm::vec3& value) const;
      void _set_vec4(const char* name, const glm::vec4& value) const;
      void _set_mat2(const char* name, const glm::mat2& matrix) const;
      void _set_mat3(const char* name, const glm::mat3& matrix) const;
      void _set_mat4(const char* name, const glm::mat4& matrix) const;

      void push_properties() override;

      void draw() override;


   };


} // namespace gpu_opengl



