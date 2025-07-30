#include "framework.h"
#include "context.h"
#include "renderer.h"
#include "shader.h"
#include "acme/exception/interface_only.h"
#include "bred/gpu/input_layout.h"
#include "bred/gpu/pixmap.h"
//#include "_.h"
//#include "_gpu.h"


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

      m_etopology = e_topology_triangle_list;
      //m_bTextureAndSampler = false;
      //m_SamplerSlot = -1;
      //m_setbindingCubeSampler = -1;

   }


   shader::~shader()
   {


   }


   bool shader::need_rebuild()
   {

      return false;

   }


   void shader::initialize_shader(
      ::gpu::renderer * pgpurenderer,
      const ::file::path& pathVertex,
      const ::file::path& pathFragment,
      const ::array<enum_descriptor_set_slot>& eslota,
      const ::particle_pointer& pLocalDescriptorSet,
      //const ::particle_pointer& pVertexInput,
      const ::gpu::property* ppropertiesPush,
      ::gpu::input_layout* pinputlayout,
      enum_flag eflag)
   {

      m_pgpurenderer = pgpurenderer;
      m_pathVertex = pathVertex;
      m_pathFragment = pathFragment;
      m_edescriptorsetslota.copy(eslota);
      m_pLocalDescriptorSet = pLocalDescriptorSet;
      m_pinputlayout = pinputlayout;
      if (ppropertiesPush)
      {
         m_propertiesPush.set_properties(ppropertiesPush);
      }
      //if (ppropertiesInputLayout)
      //{
      //   m_propertiesInputLayout.set(ppropertiesInputLayout);
      //}
      m_eflag = eflag;

      on_initialize_shader();

   }


   void shader::initialize_shader_with_block(
      ::gpu::renderer * pgpurenderer,
      const ::block& blockVertex,
      const ::block& blockFragment,
      const ::array<enum_descriptor_set_slot>& eslota,
      const ::particle_pointer& pLocalDescriptorSet,
      //const ::particle_pointer& pVertexInput,
      const ::gpu::property* ppropertiesPush,
      ::gpu::input_layout * pinputlayout,
      enum_flag eflag)
   {

      m_pgpurenderer = pgpurenderer;
      m_memoryVertex = blockVertex;
      m_memoryFragment = blockFragment;
      m_edescriptorsetslota.copy(eslota);
      m_pLocalDescriptorSet = pLocalDescriptorSet;
      m_pinputlayout = pinputlayout;
      if (ppropertiesPush)
      {
         m_propertiesPush.set_properties(ppropertiesPush);
      }
      //if (ppropertiesInputLayout)
      //{
      //   m_propertiesInputLayout.set(ppropertiesInputLayout);

      //}
      m_eflag = eflag;

      on_initialize_shader();

   }


   void shader::on_initialize_shader()
   {


   }


   // activate the shader
   // ------------------------------------------------------------------------
   void shader::bind()
   {


   }


   void shader::bind(::gpu::texture* pgputextureTarget, ::gpu::texture* pgputextureSource)
   {

      throw ::interface_only("shader::bind(::gpu::texture*, ::gpu::texture*) not implemented at this shader implementation");

   }


   void shader::on_set_constant_buffer(const ::scoped_string& scopedstrName)
   {

      
   }

   void shader::bind(::gpu::texture* pgputextureTarget)
   {

      throw ::interface_only("shader::bind(::gpu::texture*) not implemented at this shader implementation");

   }


   void shader::bind_source(::gpu::texture* pgputextureSource, int iSlot)
   {

      throw ::interface_only("shader::bind_source(::gpu::texture*) not implemented at this shader implementation");

   }


   void shader::bind_source(::gpu::pixmap* pgpupixmapSource, int iSlot)
   {

      bind_source(pgpupixmapSource->m_pgputexture, iSlot);

   }


   void shader::unbind()
   {


   }


//
//   void shader::setBool(const ::scoped_string & scopedstrName, bool value)
//   {
//
//
//   }
//
//
//   void shader::setInt(const ::scoped_string & scopedstrName, int value)
//   {
//
//
//   }
//
//
//   void shader::setFloat(const ::scoped_string & scopedstrName, float value)
//   {
//
//
//   }
//
//
////   void shader::setVec2(const ::scoped_string & scopedstrName, const glm::vec2& value)
////   {
////
////   }
//
//
//   void shader::setVec2(const ::scoped_string & scopedstrName, float x, float y)
//   {
//
//   }
//
//
////   void shader::setVec3(const ::scoped_string & scopedstrName, const glm::vec3& value)
////   {
////
////
////   }
//
//
//   void shader::setVec3(const ::scoped_string & scopedstrName, float x, float y, float z)
//   {
//
//   }
//
//
////   void shader::setVec4(const ::scoped_string & scopedstrName, const glm::vec4& value)
////   {
////
////   }
//
//
//   void shader::setVec4(const ::scoped_string & scopedstrName, float x, float y, float z, float w)
//   {
//
//   }
//
//
//   void shader::setMat2(const ::scoped_string & scopedstrName, const float p[2*2])
//   {
//
//   }
//
//
//   void shader::setMat3(const ::scoped_string & scopedstrName, const float p[3*3])
//   {
//
//   }
//
//
//   void shader::setMat4(const ::scoped_string & scopedstrName, const float p[4*4])
//   {
//
//   }


   //void shader::shader_compile_errors(GLuint shader, GLenum type, string & strSummary)
   //{

   //   ::e_status estatus = ::success;

   //   return estatus;

   //}


   //void shader::program_compile_errors(GLuint program, string & strSummary)
   //{

   //   ::e_status estatus = ::success;


   //   return estatus;

   //}

   
   void shader::draw()
   {


   }


   void shader::_bind()
   {


   }
   

   //void shader::on_initialize_shader()
   //{


   //}


   //void shader::bind()
   //{


   //}


   void shader::push_properties()
   {


   }



   //::gpu::payload * shader::get_payload(const ::scoped_string & scopedstrPayload)
   //{

   //   auto p = m_mapLayout.plookup(scopedstrPayload);

   //   if (!p)
   //   {

   //      return nullptr;

   //   }

   //   return &p->element2();

   //   //m_iMatrixUniform = glGetUniformLocation(
   //   //   m_pprogram->m_pshader->m_uId,
   //   //   m_strMatrixUniform
   //   //return -1;
   //}


   //void shader::setup_sampler_and_texture(const ::scoped_string& scopedstrName, int i)
   //{
   //   
   //   m_mapSamplerAndTexture[scopedstrName].m_i = i;

   //}


   void shader::set_bool(const ::scoped_string& scopedstrName, bool value)
   {

      set_int(scopedstrName, value != false);

   }


   void shader::set_int(const ::scoped_string& scopedstrName, int value)
   {

      ::string strName(scopedstrName);

      auto& a = m_propertiesPush.as_int(strName);

      a = value;

   }


   void shader::set_float(const ::scoped_string& scopedstrName, float value)
   {
      
      ::string strName(scopedstrName);

      auto& a = m_propertiesPush.as_float(strName);

      a = value;

   }


   void shader::set_vec2(const ::scoped_string& scopedstrName, float x, float y)
   {

      ::string strName(scopedstrName);

      auto& a = m_propertiesPush.seq2(strName);

      a.x = x;
      a.y = y;

   }


   void shader::set_vec2(const ::scoped_string& scopedstrName, const glm::vec2& a)
   {

      ::string strName(scopedstrName);

      m_propertiesPush.seq2(strName) = a;

   }

   
   void shader::set_vec3(const ::scoped_string& scopedstrName, float x, float y, float z)
   {

      ::string strName(scopedstrName);

      auto& a = m_propertiesPush.seq3(strName);

      a.x = x;
      a.y = y;
      a.z = z;

   }


   void shader::set_vec3(const ::scoped_string& scopedstrName, const glm::vec3& a)
   {

      ::string strName(scopedstrName);

      m_propertiesPush.seq3(strName) = a;

   }


   void shader::set_vec4(const ::scoped_string& scopedstrName, float x, float y, float z, float w)
   {

      ::string strName(scopedstrName);

      auto& a = m_propertiesPush.seq4(strName);

      a.x = x;
      a.y = y;
      a.z = z;
      a.w = w;

   }


   void shader::set_vec4(const ::scoped_string& scopedstrName, const glm::vec4& a)
   {

      //auto p = m_mapConstantBuffer.plookup(scopedstrName);

      //if (p)
      //{

      //   p->m_element2.m_etype = ::gpu::e_type_seq4;
      //   p->m_element2.m_memory = ::as_memory_block(a);

      //   on_set_constant_buffer(scopedstrName);

      //}
      //else
      {

         ::string strName(scopedstrName);

         m_propertiesPush.seq4(strName) = a;

      }


   }


   void shader::set_mat2(const ::scoped_string& scopedstrName, const ::glm::mat2& a)
   {
      
      ::string strName(scopedstrName);

      m_propertiesPush.mat2(strName.c_str()) = a;

   }


   void shader::set_mat3(const ::scoped_string& scopedstrName, const ::glm::mat3& a)
   {

      ::string strName(scopedstrName);

      m_propertiesPush.mat3(strName.c_str()) = a;

   }


   void shader::set_mat4(const ::scoped_string& scopedstrName, const ::glm::mat4& a)
   {

      //auto p = m_mapConstantBuffer.plookup(scopedstrName);

      //if (p)
      //{

      //   p->m_element2.m_etype = ::gpu::e_type_mat4;
      //   p->m_element2.m_memory = ::as_memory_block(a);

      //   on_set_constant_buffer(scopedstrName);

      //}
      //else
      {

         ::string strName(scopedstrName);

         m_propertiesPush.mat4(strName) = a;

      }

   }


} // namespace gpu



