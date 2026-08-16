// Created by camilo on 2025-06-29 15:57 <3ThomasBorregaardSørensen!!
#include "platform.h"
#include "context.h"
#include "context_lease.h"
#include "context_object.h"
#include "apex/gpu/approach.h"
#include "bred/gpu/device.h"


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


   ::gpu::context_lease context_object::acquire_context()
   {
      
      if (m_pgpucontext)
      {

         auto pgpudevice = m_pgpucontext->m_pgpudevice;

         return {pgpudevice, m_pgpucontext, true};

      }

      auto pacmeuserinteractionMain = m_papplication->main_acme_user_interaction();

      auto pacmewindowingwindow = pacmeuserinteractionMain->m_pacmewindowingwindow;

      auto pgpudevice = m_papplication->get_gpu_approach()->get_gpu_device(pacmewindowingwindow);

      _synchronous_lock synchronouslock(pgpudevice->synchronization());

      auto pgpucontextlease = pgpudevice->acquire_gpu_context(::gpu::e_output_none, {});

      return pgpucontextlease;
   
   }


} // namespace gpu



