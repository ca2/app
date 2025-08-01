#pragma once


#include "bred/gpu/shader.h"


namespace gpu_opengl
{


   class CLASS_DECL_GPU_OPENGL shader :
      virtual public ::gpu::shader
   {
   public:


      ::gpu::texture * m_ptextureBound = nullptr;
      GLuint m_ProgramID;

      //__creatable_from_base(shader, ::gpu::shader);
      
      
      shader();
      ~shader() override;


      void on_initialize_shader() override;

      void _bind() override;
      void bind(::gpu::texture* pgputextureTarget, ::gpu::texture* pgputextureSource) override;
      void bind(::gpu::texture* pgputextureTarget) override;
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


      //void setup_sampler_and_texture(const ::scoped_string& scopedstrName, int value) override;

      void _set_bool(const_char_pointer name, bool bSet) const;
      void _set_int(const_char_pointer name, int value) const;
      void _set_float(const_char_pointer name, float value) const;
      void _set_vec2(const_char_pointer name, const glm::vec2& value) const;
      void _set_vec3(const_char_pointer name, const glm::vec3& value) const;
      void _set_vec4(const_char_pointer name, const glm::vec4& value) const;
      void _set_mat2(const_char_pointer name, const glm::mat2& matrix) const;
      void _set_mat3(const_char_pointer name, const glm::mat3& matrix) const;
      void _set_mat4(const_char_pointer name, const glm::mat4& matrix) const;

      void push_properties() override;

      //void draw() override;

      void bind_source(::gpu::texture* pgputexture, int iSlot) override;


      void set_bool(const ::scoped_string& scopedstrName, bool value) override;
      void set_int(const ::scoped_string& scopedstrName, int value) override;
      void set_float(const ::scoped_string& scopedstrName, float value) override;
      void set_vec2(const ::scoped_string& scopedstrName, float x, float y) override;
      void set_vec2(const ::scoped_string& scopedstrName, const ::glm::vec2& a) override;
      void set_vec3(const ::scoped_string& scopedstrName, float x, float y, float z) override;
      void set_vec3(const ::scoped_string& scopedstrName, const ::glm::vec3& a) override;
      void set_vec4(const ::scoped_string& scopedstrName, float x, float y, float z, float w) override;
      void set_vec4(const ::scoped_string& scopedstrName, const ::glm::vec4& a) override;
      void set_mat2(const ::scoped_string& scopedstrName, const ::glm::mat2& a) override;
      void set_mat3(const ::scoped_string& scopedstrName, const ::glm::mat3& a) override;
      void set_mat4(const ::scoped_string& scopedstrName, const ::glm::mat4& a) override;


   };


} // namespace gpu_opengl



