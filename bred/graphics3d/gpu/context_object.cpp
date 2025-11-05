// Created by camilo on 2025-06-29 15:57 <3ThomasBorregaardSørensen!!
#include "framework.h"
#include "context.h"
#include "context_object.h"


namespace gpu
{


   context_object::context_object()
   {

   }


   context_object::~context_object()
   {

   }


   void context_object::initialize_gpu_context_object(::gpu::context* pgpucontext)
   {

      m_pgpucontext = pgpucontext;

      on_initialize_gpu_context_object();

   }


   void context_object::on_initialize_gpu_context_object()
   {


   }


   ::gpu::context* context_object::context()
   {
      
      return m_pgpucontext; 
   
   }


} // namespace gpu



