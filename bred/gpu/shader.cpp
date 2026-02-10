#include "framework.h"
#include "binding.h"
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
      //const ::array_base<enum_descriptor_set_slot>& eslota,
      //const ::particle_pointer& pLocalDescriptorSet,
      //const ::particle_pointer& pVertexInput,
      //const ::gpu::property* ppropertiesPush,
      ::gpu::input_layout* pinputlayout,
      enum_flag eflag)
   {

      m_pgpurenderer = pgpurenderer;
      m_pathVertex = pathVertex;
      m_pathFragment = pathFragment;
      //m_edescriptorsetslota.copy(eslota);
      //m_pLocalDescriptorSet = pLocalDescriptorSet;
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
      ::gpu::input_layout * pinputlayout,
      enum_flag eflag)
   {

      m_pgpurenderer = pgpurenderer;
      m_memoryVertex = blockVertex;
      m_memoryFragment = blockFragment;
      //m_edescriptorsetslota.copy(eslota);
      //m_pLocalDescriptorSet = pLocalDescriptorSet;
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


   ::gpu::binding_set *shader::binding_set(int iSet, ::gpu::binding_set *pgpubindingset)
   {

      if (iSet < 0)
      {

         throw ::exception(error_bad_argument);

      }
      else if (iSet > 16) // 16: a reasonable maximum number of binding sets?
      {

         throw ::exception(error_bad_argument);

      }

      auto &pbindingset = binding_set_array()->ø(iSet);

      if (::is_set(pgpubindingset))
      {

         pbindingset = pgpubindingset;

      }
      
      if (!pbindingset)
      {

         øconstruct(pbindingset);

         auto & pbindingslotset = binding_slot_set_array()->ø(iSet);

         if (ødefer_construct(pbindingslotset))
         {

            pbindingslotset->m_iSet = iSet;

            pbindingslotset->m_pbindingset = pbindingset;

         }

      }

      return pbindingset;

   }


   ::gpu::binding *shader::binding(int iSet, int iSlot)
   {

      auto pbindingset = binding_set(iSet);

      if (iSlot < 0)
      {

         throw ::exception(error_bad_argument);

      }
      else if (iSlot > 20) // 20: a reasonable maximum number of
                           // slots/bindings in a binding set?
      {

         throw ::exception(error_bad_argument);

      }

      auto pbinding = pbindingset->binding(iSlot);

      auto &pbindingslotset = binding_slot_set_array()->element_at(iSet);

      ASSERT(::is_set(pbindingslotset));

      auto &bindingslot = pbindingslotset->ø(iSlot);

      if (::is_null(bindingslot.m_pbinding))
      {

         bindingslot.m_iSet = iSet;

         bindingslot.m_iSlot = iSlot;

         bindingslot.m_pbinding = pbinding;

      }

      return pbinding;

   }




   ::gpu::binding_slot_set * shader::binding_slot_set(int iSet, ::gpu::binding_set * pgpubindingset)
   {

      if (iSet < 0)
      {

         throw ::exception(error_bad_argument);

      }
      else if (iSet > 16) // 16: a reasonable maximum number of binding sets?
      {

         throw ::exception(error_bad_argument);

      }

      auto &pbindingslotset = binding_slot_set_array()->ø(iSet);

      if (!pbindingslotset)
      {

         øconstruct(pbindingslotset);

      }

      if (::is_set(pgpubindingset))
      {
         
         pbindingslotset->m_pbindingset = pgpubindingset;
         
      }
      else if (binding_slot_set_array()->m_pbindingseta)
      {

         if (!pbindingslotset->m_pbindingset)
         {

            if (iSet < binding_slot_set_array()->m_pbindingseta->size())
            {

               pbindingslotset->m_pbindingset = binding_slot_set_array()->m_pbindingseta->element_at(iSet);

            }

         }

      }

      pbindingslotset->m_iSet = iSet;

      return pbindingslotset;

   }


   ::gpu::binding_slot *shader::binding_slot(int iSet, int iSlot, ::gpu::binding *pgpubinding)
   {

      auto pbindingslotset = binding_slot_set(iSet);

      if (iSlot < 0)
      {

         throw ::exception(error_bad_argument);

      }
      else if (iSlot > 20) // 20: a reasonable maximum number of 
         // slots/bindings in a binding set?
      {

         throw ::exception(error_bad_argument);

      }

      auto pbindingslot = pbindingslotset->binding_slot(iSlot);

      if (::is_set(pgpubinding))
      {

         pbindingslot->m_pbinding = pgpubinding;

      }

      return pbindingslot;

   }


   bool shader::has_image_sampler()
   {

      auto pbindingslot = get_first_image_sampler_binding_slot();

      return ::is_set(pbindingslot) && ::is_set(pbindingslot->m_pbinding);

   }


   bool shader::has_global_ubo()
   {

      return ::is_set(m_pbindingslotseta) && m_pbindingslotseta->has_global_ubo();

   }


   void shader::set_global_ubo()
   {

      if (!has_global_ubo())
      {

         auto pbindingGlobalUbo = this->binding();

         pbindingGlobalUbo->m_strUniform = "GlobalUbo";

         pbindingGlobalUbo->m_ebinding = ::gpu::e_binding_global_ubo1;

         pbindingGlobalUbo->m_iBindingPoint2 = 0;

      }


   }


   ::gpu::binding_slot_set * shader::get_first_image_sampler_binding_slot_set()
   {

      if (!m_pbindingslotseta)
      {

         return nullptr;
      }

      for (auto &pbindingslotset: *m_pbindingslotseta)
      {

         if (!pbindingslotset->m_pbindingset)
         {

            continue;
         }

         int iBinding = -1;

         for (auto &bindingslot: *pbindingslotset)
         {

            iBinding++;

            if (!bindingslot.m_pbinding)
            {

               continue;
            }

            if (bindingslot.m_pbinding->is_image_sampler())
            {

               return pbindingslotset;

            }

         }

      }

      return nullptr;

   }



      ::gpu::binding_slot *shader::get_first_image_sampler_binding_slot()
   {

      if (!m_pbindingslotseta)
      {

         return nullptr;
      }

      for (auto &pbindingslotset: *m_pbindingslotseta)
      {

         if (!pbindingslotset->m_pbindingset)
         {

            continue;
         }

         int iBinding = -1;

         for (auto &bindingslot: *pbindingslotset)
         {

            iBinding++;

            if (!bindingslot.m_pbinding)
            {

               continue;
            }

            if (bindingslot.m_pbinding->is_image_sampler())
            {

               return &bindingslot;
            }
         }
      }

      return nullptr;
   }



   ::gpu::binding_set *shader::_001GetSingularImageBindingSet(int &iSet)
   {

      if (!m_pbindingslotseta)
      {

         return nullptr;

      }

      for (auto &pbindingslotset: *m_pbindingslotseta)
      {

         if (!pbindingslotset->m_pbindingset)
         {

            continue;

         }

         if (pbindingslotset->m_pbindingset->size() != 1)
         {

            continue;

         }

         if (pbindingslotset->m_pbindingset->first()->is_image_sampler())
         {

            iSet = pbindingslotset->m_iSet;

            return pbindingslotset->m_pbindingset;

         }

      }

      return nullptr;

   }


   //// activate the shader
   //// ------------------------------------------------------------------------
   //void shader::bind(::gpu::command_buffer *pgpucommandbuffer)
   //{


   //}


   //void shader::bind(::gpu::command_buffer * pgpucommandbuffer, ::gpu::texture* pgputextureTarget, ::gpu::texture* pgputextureSource)
   //{

   //   throw ::interface_only("shader::bind(::gpu::texture*, ::gpu::texture*) not implemented at this shader implementation");

   //}


   void shader::on_set_constant_buffer(const ::scoped_string& scopedstrName)
   {

      
   }


   //void shader::on_before_draw(::gpu::command_buffer * pgpucommandbuffer)
   //{


   //}

   void shader::bind(::gpu::command_buffer *pgpucommandbuffer, ::gpu::texture *pgputextureTarget)
   {

      throw ::interface_only("shader::bind(::gpu::texture*) not implemented at this shader implementation");

   }


   void shader::on_bind_already_bound(::gpu::command_buffer *pgpucommandbuffer,
                                              ::gpu::texture *pgputextureTarget)
   {


   }


   void shader::bind_block(::gpu::command_buffer *pgpucommandbuffer, ::gpu::block *pgpublock, int iSlot)
   {

      throw ::interface_only("shader::bind_block(::gpu::block*) not implemented at this shader implementation");
   }


   void shader::bind_slot_set(::gpu::command_buffer *pgpucommandbuffer, int iSet,
                              ::gpu::binding_slot_set * pgpubindingslotset)
   {

      throw ::interface_only("shader::bind_slot_set(::gpu::binding_slot_set*) not implemented at this shader implementation");

   }

   void shader::bind_source(::gpu::command_buffer *pgpucommandbuffer, ::gpu::texture *pgputextureSource, int iSlot)
   {

      throw ::interface_only("shader::bind_source(::gpu::texture*) not implemented at this shader implementation");

   }


   void shader::bind_source(::gpu::command_buffer *pgpucommandbuffer, ::gpu::pixmap *pgpupixmapSource, int iSlot)
   {

      bind_source(pgpucommandbuffer, pgpupixmapSource->m_pgputexture, iSlot);

   }


   void shader::bind_source2(gpu::command_buffer* pgpucommandbuffer, int iIndex, const char* pszPayloadName, gpu::texture* pgputextureSource)
   {


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


   //void shader::_bind(::gpu::command_buffer *pgpucommandbuffer, ::gpu::enum_scene escene)
   //{


   //}
   

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
      else
      {

         ::string strErrorMessage;

         strErrorMessage = "uniform name not found in the property bags."
                           "Is it just a shader uniform";

         warning(strErrorMessage);

         throw ::exception(error_wrong_state, strErrorMessage);

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
         auto &s = m_propertiesPushShared.seq3(strName);

         s= a;
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

         auto &matrixTarget = m_propertiesPushShared.mat4(strName);

         matrixTarget = m_pgpurenderer->m_pgpucontext->defer_transpose(a);

         //informationf("lets check at least once it wrong: mat[0][0]=%f", matrixTarget[0][0]);
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


   ::gpu::binding_set_array * shader::binding_set_array()
   {

      auto & pbindingseta = binding_slot_set_array()->m_pbindingseta;

      ødefer_construct(pbindingseta);

      return pbindingseta;

   }


   ::gpu::binding_slot_set_array *shader::binding_slot_set_array()
   {

      ødefer_construct(m_pbindingslotseta);

      return m_pbindingslotseta;

   }


   void shader::update_binding_slots()
   { 
      
      auto parray = binding_slot_set_array();

      if (::is_null(parray))
      {

         return;

      }

      parray->update_binding_slots();

   }


} // namespace gpu



