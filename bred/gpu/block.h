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


      block();
      ~block() override; 


      virtual void initialize_gpu_block(::gpu::context *pgpucontext);


      virtual void create_gpu_block(::gpu::context *pgpucontext);


      virtual void update_frame(::gpu::renderer * pgpurenderer);


   };


} // namespace gpu
