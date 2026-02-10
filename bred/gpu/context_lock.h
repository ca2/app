// From dx11 by camilo on 2025-06-26 01:58 <3ThomasBorregaardSørensen!!
// Created by camilo on 2025-06-25 14:36 <3ThomasBorregaardSørensen!!
#pragma once


namespace gpu
{


   class CLASS_DECL_BRED context_lock
   {
   public:


      context* m_pgpucontext;
      context_lock* m_plockUpper;
      ::particle_pointer m_pparticleSynchronization;


      context_lock();
      context_lock(::gpu::context* pcontext);
      ~context_lock();


      void lock_context(::gpu::context * pgpucontext);


   };



} // namespace gpu



