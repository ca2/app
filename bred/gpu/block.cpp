// Created by camilo on 2025-12-11 15:46 <3ThomasBorregaardSørensen!!
#include "framework.h"
#include "binding.h"
#include "block.h"
#include "context.h"


namespace gpu
{


   block::block()
   {


   }
   

   block::~block()
   {


   }


   //void block::initialize_gpu_block(::gpu::context * pgpucontext)
   //{

   //   ::gpu::context_object::initialize_gpu_context_object(pgpucontext);

   //}


   void block::create_gpu_block(::gpu::context * pgpucontext)
   {

      ::gpu::context_object::initialize_gpu_context_object(pgpucontext);


   }


   void block::update_frame(gpu::renderer* pgpurenderer)
   {


   }


   ::gpu::binding_slot_set *block::binding_slot_set(::gpu::command_buffer *pgpucommandbuffer,
                                                    ::gpu::binding_set *pbindingset)
   {

      if (pbindingset->size() == 1)
      {

         if (!m_pbindingslotset)
         {

            // ASSERT(::is_set(texture_albedo()));
            // ASSERT(::is_set(m_ptextureNormal));

            øconstruct(m_pbindingslotset);

            auto pbindingset = m_pgpucontext->global_ubo1_binding_set();

            m_pbindingslotset->m_pbindingset = pbindingset;

            m_pbindingslotset->ø(0).m_pbinding = pbindingset->first();
            m_pbindingslotset->ø(0).m_pblock = this;

         }

         return m_pbindingslotset;

      }
      else
      {

         throw ::exception(error_wrong_state, "No supported number of bindings");

         return nullptr;
      }


   }





} // namespace gpu



