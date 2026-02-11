//
//  fence.h
//  gpu_opengl
//
//  Created by camilo on 2026-02-08 22:17 <3ThomasBorregaardSørensen!!
//
#include "framework.h"
#include "fence.h"


namespace gpu_opengl
{


      
   fence::fence()
   {
      
      m_glsyncFence = nullptr;
      
   }


   fence::~fence()
   {
      
      if(m_glsyncFence != nullptr)
      {
       
         glDeleteSync(m_glsyncFence);
         
      }
      
   }


   void fence::initialize_gpu_fence(::gpu::context * pgpucontext)
   {
      
      ::gpu::fence::initialize_gpu_fence(pgpucontext);
   
      reset();
   
   }


void fence::reset()
{
   
   if(m_glsyncFence != nullptr)
   {
    
      glDeleteSync(m_glsyncFence);
      
      m_glsyncFence = nullptr;
      
   }
   
   m_glsyncFence = glFenceSync(GL_SYNC_GPU_COMMANDS_COMPLETE, 0);

   
}

   
   void fence::wait_gpu_fence()
   {
   
      if(m_glsyncFence != nullptr)
      {
      glClientWaitSync(m_glsyncFence, GL_SYNC_FLUSH_COMMANDS_BIT, GL_TIMEOUT_IGNORED);
         
       
         glDeleteSync(m_glsyncFence);
         
         m_glsyncFence = nullptr;
         
      }
      
   }

      
   
} // namespace gpu_opengl



