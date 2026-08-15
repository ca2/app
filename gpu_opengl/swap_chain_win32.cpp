// Created by camilo on 2026-01-12 02:15 <3ThomasBorregaardSørensen!!
#include "platform.h"
#include "_gpu_opengl.h"
#include "swap_chain.h"
#include "bred/gpu/renderer.h"



namespace gpu_opengl
{

   void swap_chain::swap_buffers() 
   {
   
      m_pgpurenderer->m_pgpucontext->swap_buffers();

      m_gpusemaphoreaWait.clear();

   
   }

} // namespace gpu_opengl


