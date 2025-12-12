// Created by camilo on 2025-12-11 15:46 <3ThomasBorregaardSørensen!!
#include "framework.h"
#include "block.h"


namespace gpu
{


   block::block()
   {


   }
   

   block::~block()
   {


   }


   void block::initialize_gpu_block(::gpu::context * pgpucontext)
   {

      ::gpu::context_object::initialize_gpu_context_object(pgpucontext);

   }


   void block::create_gpu_block(::gpu::context * pgpucontext)
   {



   }


   void block::update_frame(gpu::renderer* pgpurenderer)
   {


   }


} // namespace gpu



