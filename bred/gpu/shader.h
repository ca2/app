#pragma once


#include "bred/gpu/properties.h"


namespace gpu
{

   enum enum_shader
   {

      shader_fragment,
      shader_projection,

   };

   
   struct binding
   {

      bool              m_bSet = false;
      unsigned int      m_uSet = 0;
      unsigned int      m_uBinding = 0;

      void set(unsigned int uBinding = 0)
      {

         m_bSet = true;
         m_uBinding = uBinding;

      }
      bool is_set()const { return m_bSet; }
   };

   class CLASS_DECL_BRED shader :
      virtual public ::matter
   {
   public:
      
      enum enum_flag
      {
         e_flag_none = 0,
         e_flag_clear_default_bindings_and_attributes_descriptions = 1,

      };


      /// Trying to following suggestion from:
      /// https://vkguide.dev/docs/chapter-4/descriptors/ "Mental Model"
      /// The descriptor set number 0 will be used for engine - global
      /// resources, and bound once per frame.The descriptor set number 1 will
      /// be used for per - pass resources, and bound once per pass.
      /// The descriptor set number 2 will be used for material resources,
      /// and the number 3 will be used for per - object resources.
      /// This way, the inner render loops will only be binding 
      /// descriptor sets 2 and 3, and performance will be high.

      enum enum_descriptor_set_slot
      {
         e_descriptor_set_slot_global,
         e_descriptor_set_slot_per_pass,
         e_descriptor_set_slot_material,
         e_descriptor_set_slot_local,
         e_descriptor_set_slot_s1,
         e_descriptor_set_shader_resource_view_and_sampler,

      };
      int m_iVertexLevel = -1;

      //unsigned int               m_uId;
      struct constant_buffer
      {
         ::gpu::enum_type m_etype;
         ::memory m_memory;
         int m_i1VertexShader = -1;
         int m_i2VertexShader = -1;
         int m_i1FragmentShader = -1;
         int m_i2FragmentShader = -1;
      };
      ::string_map<constant_buffer> m_mapConstantBuffer;
      struct sampler_and_texture
      {

         int m_i;
      };
      ::string_map<sampler_and_texture> m_mapSamplerAndTexture;
      bool                                m_bClearColor;
      ::color::color                      m_colorClear;

      bool m_bDisableDepthTest = false;
      bool m_bDepthTestButNoDepthWrite = false;
      bool m_bLequalDepth = false;
      bool m_bEnableBlend = false;
      bool m_bAccumulationEnable = false;
      enum_cull_mode m_ecullmode = e_cull_mode_back;
      //bool m_bHasSourceImage = false;

      binding m_bindingSampler;
      binding m_bindingCubeSampler;

      string                     m_strError;

      //string_map < payload >     m_mapLayout;

      ::pointer < renderer >     m_pgpurenderer;

      ::file::path               m_pathVertex;
      ::file::path               m_pathFragment;
      ::file::path               m_pathGeometry;

      memory                     m_memoryVertex;
      memory                     m_memoryFragment;
      memory                     m_memoryGeometry;

      //::gpu::properties          m_propertiesInputLayout;
      ::gpu::properties          m_propertiesPush;

      enum_flag                  m_eflag;
      ::comparable_array<enum_descriptor_set_slot>   m_edescriptorsetslota;
      ::particle_pointer         m_pLocalDescriptorSet;
      ::pointer < input_layout > m_pinputlayout;

      //bool m_bTextureAndSampler;


      shader();
      ~shader() override;

      
      virtual void initialize_shader(
         ::gpu::renderer * pgpurenderer,
         const ::file::path& pathVertex,
         const ::file::path& pathFragment,
         const ::array<enum_descriptor_set_slot>& eslota = {},
         const ::particle_pointer& pLocalDescriptorSet = {},
         //const ::particle_pointer& pVertexInput = {},
         const ::gpu::property* ppropertiesPush = nullptr,
         ::gpu::input_layout* pinputlayout = nullptr,
         enum_flag eflag = e_flag_none);

      virtual void initialize_shader_with_block(
         ::gpu::renderer * pgpurenderer,
         const ::block & blockVertex, 
         const ::block & blockFragment,
         const ::array<enum_descriptor_set_slot>& eslota = {},
         const ::particle_pointer& pLocalDescriptorSet = {},
         //const ::particle_pointer& pVertexInput = {},
         const ::gpu::property* ppropertiesPush = nullptr,
         ::gpu::input_layout * pinputlayout = nullptr,
         enum_flag eflag = e_flag_none);

      virtual void on_initialize_shader();

      //virtual void use();

      //virtual void setBool(const ::scoped_string & scopedstrName, bool value);

      //virtual void setInt(const ::scoped_string & scopedstrName, int value);

      //virtual void setFloat(const ::scoped_string & scopedstrName, float value);

      ////virtual void setVec2(const ::scoped_string & scopedstrName, const glm::vec2& value);
      //virtual void setVec2(const ::scoped_string & scopedstrName, float x, float y);

      ////virtual void setVec3(const ::scoped_string & scopedstrName, const glm::vec3& value);
      //virtual void setVec3(const ::scoped_string & scopedstrName, float x, float y, float z);

      ////virtual void setVec4(const ::scoped_string & scopedstrName, const glm::vec4& value);
      //virtual void setVec4(const ::scoped_string & scopedstrName, float x, float y, float z, float w);

      //virtual void setMat2(const ::scoped_string & scopedstrName, const float p[2*2]);
      //virtual void setMat3(const ::scoped_string & scopedstrName, const float p[3*3]);
      //virtual void setMat4(const ::scoped_string & scopedstrName, const float p[4*4]);

      //virtual shader * create_shader(const ::string & pszVertex, enum_shader eshader);

      //static void shader_compile_errors(GLuint shader, enum_shader eshader, string & strSummary);

      //static void program_compile_errors(GLuint program, string & strSummary);


      //virtual payload * get_uniform(const ::string & strName);

      //virtual ::gpu::payload * get_payload(const ::scoped_string & scopedstrName);
      virtual void draw();

      //virtual void on_initialize_shader();
      
      
      virtual void on_set_constant_buffer(const ::scoped_string& scopedstrName);


      virtual void bind(::gpu::texture* pgputextureTarget);
      virtual void bind(::gpu::texture * pgputextureTarget, ::gpu::texture* pgputextureSource);
      virtual void bind_source(::gpu::texture* pgputextureSource, int iSlot = 0);
      virtual void bind();
      virtual void unbind();


      virtual void push_properties();


      virtual void setup_sampler_and_texture(const ::scoped_string& scopedstrName, int value);

      virtual void set_bool(const ::scoped_string& scopedstrName, bool value);

      virtual void set_int(const ::scoped_string& scopedstrName, int value);

      virtual void set_float(const ::scoped_string& scopedstrName, float value);

      virtual void set_vec2(const ::scoped_string& scopedstrName, float x, float y);
      virtual void set_vec2(const ::scoped_string& scopedstrName, const ::glm::vec2& a);

      virtual void set_vec3(const ::scoped_string& scopedstrName, float x, float y, float z);
      virtual void set_vec3(const ::scoped_string& scopedstrName, const ::glm::vec3& a);

      virtual void set_vec4(const ::scoped_string& scopedstrName, float x, float y, float z, float w);
      virtual void set_vec4(const ::scoped_string& scopedstrName, const ::glm::vec4& a);

      virtual void set_mat2(const ::scoped_string& scopedstrName, const ::glm::mat2& a);
      virtual void set_mat3(const ::scoped_string& scopedstrName, const ::glm::mat3& a);
      virtual void set_mat4(const ::scoped_string& scopedstrName, const ::glm::mat4& a);



   };


} // namespace gpu




