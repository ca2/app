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



   //const_char_pointer shader_type_c_str(GLenum etype)
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
      const ::array_base<enum_descriptor_set_slot>& eslota,
      const ::particle_pointer& pLocalDescriptorSet,
      //const ::particle_pointer& pVertexInput,
      //const ::gpu::property* ppropertiesPush,
      ::gpu::input_layout* pinputlayout,
      enum_flag eflag)
   {

      m_pgpurenderer = pgpurenderer;
      m_pathVertex = pathVertex;
      m_pathFragment = pathFragment;
      m_edescriptorsetslota.copy(eslota);
      m_pLocalDescriptorSet = pLocalDescriptorSet;
      m_pinputlayout = pinputlayout;
      //if (ppropertiesPush)
      //{
      //   m_propertiesPush.set_properties(ppropertiesPush);
      //}
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
      const ::array_base<enum_descriptor_set_slot>& eslota,
      const ::particle_pointer& pLocalDescriptorSet,
      //const ::particle_pointer& pVertexInput,
      //const ::gpu::property* ppropertiesPush,
      ::gpu::input_layout * pinputlayout,
      enum_flag eflag)
   {

      m_pgpurenderer = pgpurenderer;
      m_memoryVertex = blockVertex;
      m_memoryFragment = blockFragment;
      m_edescriptorsetslota.copy(eslota);
      m_pLocalDescriptorSet = pLocalDescriptorSet;
      m_pinputlayout = pinputlayout;
      //if (ppropertiesPush)
      //{
      //   m_propertiesPush.set_properties(ppropertiesPush);
      //}
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
   void shader::bind(::gpu::command_buffer *pgpucommandbuffer)
   {


   }


   void shader::bind(::gpu::command_buffer * pgpucommandbuffer, ::gpu::texture* pgputextureTarget, ::gpu::texture* pgputextureSource)
   {

      throw ::interface_only("shader::bind(::gpu::texture*, ::gpu::texture*) not implemented at this shader implementation");

   }


   void shader::on_set_constant_buffer(const ::scoped_string& scopedstrName)
   {

      
   }

   void shader::bind(::gpu::command_buffer *pgpucommandbuffer, ::gpu::texture *pgputextureTarget)
   {

      throw ::interface_only("shader::bind(::gpu::texture*) not implemented at this shader implementation");

   }


   void shader::bind_source(::gpu::command_buffer *pgpucommandbuffer, ::gpu::texture *pgputextureSource, int iSlot)
   {

      throw ::interface_only("shader::bind_source(::gpu::texture*) not implemented at this shader implementation");

   }


   void shader::bind_source(::gpu::command_buffer *pgpucommandbuffer, ::gpu::pixmap *pgpupixmapSource, int iSlot)
   {

      bind_source(pgpucommandbuffer, pgpupixmapSource->m_pgputexture, iSlot);

   }


   void shader::unbind(::gpu::command_buffer *pgpucommandbuffer)
   {

      m_pgputextureBound = nullptr;

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
////   void shader::setVec2(const ::scoped_string & scopedstrName, const floating_sequence2& value)
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
////   void shader::setVec3(const ::scoped_string & scopedstrName, const floating_sequence3& value)
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
////   void shader::setVec4(const ::scoped_string & scopedstrName, const floating_sequence4& value)
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


   void shader::_bind(::gpu::command_buffer *pgpucommandbuffer, ::gpu::enum_scene escene)
   {


   }
   

   //void shader::on_initialize_shader()
   //{


   //}


   //void shader::bind()
   //{


   //}


   void shader::push_properties(::gpu::command_buffer *pgpucommandbuffer)
   {

      

   }


   void shader::set_push_properties(::gpu::command_buffer *pgpucommandbuffer, const ::block &block)
   {


   }



   //::gpu::payload * shader::get_payload(const ::scoped_string & scopedstrPayload)
   //{

   //   auto p = m_mapLayout.find(scopedstrPayload);

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

      if (m_propertiesPushShared.contains(scopedstrName))
      {

         auto &a = m_propertiesPushShared.as_int(strName);

         a = value;

      }
      else if (m_propertiesPushVertex.contains(scopedstrName))
      {

         auto &a = m_propertiesPushVertex.as_int(strName);

         a = value;

      }
      else if (m_propertiesPushFragment.contains(scopedstrName))
      {

         auto &a = m_propertiesPushFragment.as_int(strName);

         a = value;

      }

   }


   void shader::set_float(const ::scoped_string& scopedstrName, float value)
   {
      
      ::string strName(scopedstrName);

      if (m_propertiesPushShared.contains(scopedstrName))
      {

         auto &a = m_propertiesPushShared.as_float(strName);

         a = value;
      }
      else if (m_propertiesPushVertex.contains(scopedstrName))
      {

         auto &a = m_propertiesPushVertex.as_float(strName);

         a = value;
      }
      else if (m_propertiesPushFragment.contains(scopedstrName))
      {

         auto &a = m_propertiesPushFragment.as_float(strName);

         a = value;
      }

   }


   void shader::set_sequence2(const ::scoped_string& scopedstrName, float x, float y)
   {

      ::string strName(scopedstrName);

      if (m_propertiesPushShared.contains(scopedstrName))
      {

         auto &a = m_propertiesPushShared.seq2(strName);

         a.x = x;
         a.y = y;

      }
      else if (m_propertiesPushVertex.contains(scopedstrName))
      {

         auto &a = m_propertiesPushVertex.seq2(strName);

         a.x = x;
         a.y = y;

      }
      else if (m_propertiesPushFragment.contains(scopedstrName))
      {

         auto &a = m_propertiesPushFragment.seq2(strName);

         a.x = x;
         a.y = y;

      }


   }


   void shader::set_sequence2(const ::scoped_string& scopedstrName, const floating_sequence2& a)
   {

      ::string strName(scopedstrName);

      if (m_propertiesPushShared.contains(scopedstrName))
      {

         m_propertiesPushShared.seq2(strName) = a;

      }
      else if (m_propertiesPushVertex.contains(scopedstrName))
      {

         m_propertiesPushVertex.seq2(strName) = a;

      }
      else if (m_propertiesPushFragment.contains(scopedstrName))
      {

         m_propertiesPushFragment.seq2(strName) = a;

      }

   }

   
   void shader::set_sequence3(const ::scoped_string& scopedstrName, float x, float y, float z)
   {
      ::string strName(scopedstrName);

      if (m_propertiesPushShared.contains(scopedstrName))
      {

         auto &a = m_propertiesPushShared.seq3(strName);

         a.x = x;
         a.y = y;
         a.z = z;
      }
      else if (m_propertiesPushVertex.contains(scopedstrName))
      {

         auto &a = m_propertiesPushVertex.seq3(strName);

         a.x = x;
         a.y = y;
         a.z = z;
      }
      else if (m_propertiesPushFragment.contains(scopedstrName))
      {

         auto &a = m_propertiesPushFragment.seq3(strName);

         a.x = x;
         a.y = y;
         a.z = z;
      }



   }


   void shader::set_sequence3(const ::scoped_string& scopedstrName, const floating_sequence3& a)
   {


      ::string strName(scopedstrName);

      if (m_propertiesPushShared.contains(scopedstrName))
      {

         m_propertiesPushShared.seq3(strName) = a;
      }
      else if (m_propertiesPushVertex.contains(scopedstrName))
      {

         m_propertiesPushVertex.seq3(strName) = a;
      }
      else if (m_propertiesPushFragment.contains(scopedstrName))
      {

         m_propertiesPushFragment.seq3(strName) = a;
      }


   }


   void shader::set_sequence4(const ::scoped_string& scopedstrName, float x, float y, float z, float w)
   {

      ::string strName(scopedstrName);

      if (m_propertiesPushShared.contains(scopedstrName))
      {

         auto &a = m_propertiesPushShared.seq4(strName);

         a.x = x;
         a.y = y;
         a.z = z;
         a.w = w;
      }
      else if (m_propertiesPushVertex.contains(scopedstrName))
      {

         auto &a = m_propertiesPushVertex.seq4(strName);

         a.x = x;
         a.y = y;
         a.z = z;
         a.w = w;
      }
      else if (m_propertiesPushFragment.contains(scopedstrName))
      {

         auto &a = m_propertiesPushFragment.seq4(strName);

         a.x = x;
         a.y = y;
         a.z = z;
         a.w = w;
      }


   }


   void shader::set_sequence4(const ::scoped_string& scopedstrName, const floating_sequence4& a)
   {

      //auto p = m_mapConstantBuffer.find(scopedstrName);

      //if (p)
      //{

      //   p->m_element2.m_etype = ::gpu::e_type_seq4;
      //   p->m_element2.m_memory = ::as_memory_block(a);

      //   on_set_constant_buffer(scopedstrName);

      //}
      //else


      ::string strName(scopedstrName);

      if (m_propertiesPushShared.contains(scopedstrName))
      {

         m_propertiesPushShared.seq4(strName) = a;
      }
      else if (m_propertiesPushVertex.contains(scopedstrName))
      {

         m_propertiesPushVertex.seq4(strName) = a;
      }
      else if (m_propertiesPushFragment.contains(scopedstrName))
      {

         m_propertiesPushFragment.seq4(strName) = a;
      }



   }


   void shader::set_matrix2(const ::scoped_string& scopedstrName, const ::floating_matrix2& a)
   {
      
  

      ::string strName(scopedstrName);

      if (m_propertiesPushShared.contains(scopedstrName))
      {

         m_propertiesPushShared.mat2(strName) = a;
      }
      else if (m_propertiesPushVertex.contains(scopedstrName))
      {

         m_propertiesPushVertex.mat2(strName) = a;
      }
      else if (m_propertiesPushFragment.contains(scopedstrName))
      {

         m_propertiesPushFragment.mat2(strName) = a;
      }



   }


   void shader::set_matrix3(const ::scoped_string& scopedstrName, const ::floating_matrix3& a)
   {

      ::string strName(scopedstrName);

      if (m_propertiesPushShared.contains(scopedstrName))
      {

         m_propertiesPushShared.mat3(strName) = a;
      }
      else if (m_propertiesPushVertex.contains(scopedstrName))
      {

         m_propertiesPushVertex.mat3(strName) = a;
      }
      else if (m_propertiesPushFragment.contains(scopedstrName))
      {

         m_propertiesPushFragment.mat3(strName) = a;
      }

   }


   void shader::set_matrix4(const ::scoped_string& scopedstrName, const ::floating_matrix4& a)
   {

      //auto p = m_mapConstantBuffer.find(scopedstrName);

      //if (p)
      //{

      //   p->m_element2.m_etype = ::gpu::e_type_mat4;
      //   p->m_element2.m_memory = ::as_memory_block(a);

      //   on_set_constant_buffer(scopedstrName);

      //}
      //else

      ::string strName(scopedstrName);

      if (m_propertiesPushShared.contains(scopedstrName))
      {

         m_propertiesPushShared.mat4(strName) = m_pgpurenderer->m_pgpucontext->defer_transpose(a);
      }
      else if (m_propertiesPushVertex.contains(scopedstrName))
      {

         m_propertiesPushVertex.mat4(strName) = m_pgpurenderer->m_pgpucontext->defer_transpose(a);
      }
      else if (m_propertiesPushFragment.contains(scopedstrName))
      {

         m_propertiesPushFragment.mat4(strName) = m_pgpurenderer->m_pgpucontext->defer_transpose(a);
      }


   }


   void shader::setModelViewProjection(const floating_matrix4 &model, const floating_matrix4 &view, const floating_matrix4 &projection)
   {
      
      set_matrix4("model", model);
      set_matrix4("view", view);
      set_matrix4("projection", projection);

   }


} // namespace gpu



