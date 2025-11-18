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

      void _bind(::gpu::command_buffer *pgpucommandbuffer, ::gpu::enum_scene escene) override;
      void bind(::gpu::command_buffer *pgpucommandbuffer, ::gpu::texture *pgputextureTarget,
                ::gpu::texture *pgputextureSource) override;
      void bind(::gpu::command_buffer *pgpucommandbuffer, ::gpu::texture *pgputextureTarget) override;
      void bind(::gpu::command_buffer * pgpucommandbuffer) override;
      void unbind(::gpu::command_buffer *pgpucommandbuffer) override;
      
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

      ////virtual void setVec2(const ::scoped_string & scopedstrName, const floating_sequence2& value) override;
      //virtual void setVec2(const ::scoped_string & scopedstrName, float x, float y) override;

      ////virtual void setVec3(const ::scoped_string & scopedstrName, const floating_sequence3& value) override;
      //virtual void setVec3(const ::scoped_string & scopedstrName, float x, float y, float z) override;

      ////virtual void setVec4(const ::scoped_string & scopedstrName, const floating_sequence4& value) override;
      //virtual void setVec4(const ::scoped_string & scopedstrName, float x, float y, float z, float w) override;

      ////virtual void setMat2(const ::scoped_string & scopedstrName, const floating_matrix2& mat) override;
      ////virtual void setMat3(const ::scoped_string & scopedstrName, const floating_matrix3& mat) override;
      ////virtual void setMat4(const ::scoped_string & scopedstrName, const floating_matrix4& mat) override;
      //virtual void setMat2(const ::scoped_string & scopedstrName, const float p[2*2]) override;
      //virtual void setMat3(const ::scoped_string & scopedstrName, const float p[3*3]) override;
      //virtual void setMat4(const ::scoped_string & scopedstrName, const float p[4*4]) override;



      unsigned int create_shader(const ::block & blockVertex, GLenum type);

      virtual void shader_compile_errors(GLuint shader, GLenum type, string & strSummary);

      virtual void program_compile_errors(GLuint program, string & strSummary);
      //::gpu::payload * get_payload(const ::scoped_string & scopedestrUniform) override;


      // void setup_sampler_and_texture(const ::scoped_string &scopedstrName, int value) override;


      virtual GLint _get_uniform_location(const_char_pointer name, const_char_pointer debug) const;


      void _set_bool(const_char_pointer name, bool bSet) const;
      void _set_int(const_char_pointer name, int value) const;
      void _set_float(const_char_pointer name, float value) const;
      void _set_sequence2(const_char_pointer name, const floating_sequence2& value) const;
      void _set_sequence3(const_char_pointer name, const ::floating_sequence3 &value) const;
      void _set_sequence4(const_char_pointer name, const floating_sequence4 &value) const;
      void _set_matrix2(const_char_pointer name, const floating_matrix2& matrix) const;
      void _set_matrix3(const_char_pointer name, const floating_matrix3& matrix) const;
      void _set_matrix4(const_char_pointer name, const floating_matrix4& matrix) const;

      void push_properties(::gpu::command_buffer *pgpucommandbuffer) override;

      //void draw() override;

      void bind_source(::gpu::command_buffer *pgpucommandbuffer, ::gpu::texture *pgputexture, int iSlot) override;


      void set_bool(const ::scoped_string& scopedstrName, bool value) override;
      void set_int(const ::scoped_string& scopedstrName, int value) override;
      void set_float(const ::scoped_string& scopedstrName, float value) override;
      void set_sequence2(const ::scoped_string& scopedstrName, float x, float y) override;
      void set_sequence2(const ::scoped_string& scopedstrName, const ::floating_sequence2& a) override;
      void set_sequence3(const ::scoped_string& scopedstrName, float x, float y, float z) override;
      void set_sequence3(const ::scoped_string& scopedstrName, const ::floating_sequence3& a) override;
      void set_sequence4(const ::scoped_string& scopedstrName, float x, float y, float z, float w) override;
      void set_sequence4(const ::scoped_string& scopedstrName, const ::floating_sequence4& a) override;
      void set_matrix2(const ::scoped_string& scopedstrName, const ::floating_matrix2& a) override;
      void set_matrix3(const ::scoped_string& scopedstrName, const ::floating_matrix3& a) override;
      void set_matrix4(const ::scoped_string& scopedstrName, const floating_matrix4& a) override;


   };


} // namespace gpu_opengl



