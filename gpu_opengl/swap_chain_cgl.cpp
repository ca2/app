// Created by camilo on 2026-01-12 02:15 <3ThomasBorregaardSørensen!!
#include "framework.h"
#include "_gpu_opengl.h"
#include "swap_chain.h"



namespace gpu_opengl
{

   void swap_chain::swap_buffers() 
   {
   
      m_pgpucontext->swap_buffers();
   
   }

} // namespace gpu_opengl


