// Created by camilo on 2025-12-11 15:46 <3ThomasBorregaardSørensen!!
#pragma once


#include "bred/gpu/context_object.h"
#include "bred/gpu/properties.h"


namespace gpu
{

   
   class CLASS_DECL_BRED block :
      virtual public ::gpu::context_object, 
      virtual public ::gpu::properties
   {
   public:

      ::collection::index                    m_iBlockSerial;
      ::string                               m_strBlockName;
      ::pointer<::gpu::binding_slot_set>     m_pbindingslotset;


      block();
      ~block() override; 


      //virtual void initialize_gpu_block(::gpu::context *pgpucontext);


      virtual void create_gpu_block(::gpu::context *pgpucontext);


      virtual void update_frame(::gpu::renderer * pgpurenderer);


      virtual ::gpu::binding_slot_set * binding_slot_set(::gpu::command_buffer * pgpucommandbuffer, ::gpu::binding_set *pbindingset);


   };


} // namespace gpu
