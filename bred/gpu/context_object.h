// Created by camilo on 2025-06-29 15:57 <3ThomasBorregaardSørensen!!
#pragma once


#include "bred/gpu/context_pointer.h"


namespace gpu
{


   class CLASS_DECL_BRED context_object :
      virtual public ::particle
   {
   public:


      ::gpu::context_pointer m_pgpucontext;


      context_object();
      ~context_object() override;


      virtual void initialize_gpu_context_object(::gpu::context* pgpucontext);

      virtual void on_initialize_gpu_context_object();


      ::gpu::context* context();


   };



} // namespace gpu