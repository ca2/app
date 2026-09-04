//
//  fence.h
//  gpu_opengl
//
//  Created by camilo on 2026-02-08 22:17 <3ThomasBorregaardSørensen!!
//
#include "platform.h"
#include "fence.h"
#include "bred/gpu/context_lock.h"
#include "_gpu_opengl.h"


namespace gpu_opengl
{



   fence::fence()
   {

      m_bPendingFence = false;

   }


   fence::~fence()
   {


   }


   void fence::initialize_gpu_fence(::gpu::context * pgpucontext, bool bCreateSignaled)
   {

      ::gpu::fence::initialize_gpu_fence(pgpucontext, bCreateSignaled);

      if (!bCreateSignaled)
      {

         reset_gpu_fence();

      }

   }


   void fence::reset_gpu_fence()
   {

      // OpenGL commands are issued immediately, and the layer lifecycle waits for
      // this fence in the same frame. Keep a pending completion point without
      // allocating a new driver-side GLsync object for every rendered layer.
      m_bPendingFence = true;


   }


   void fence::wait_gpu_fence()
   {

      if (m_bPendingFence)
      {

         ::gpu::context_lock contextlock(m_pgpucontextGpuFence);

         // This has the same blocking completion semantics as the former
         // glClientWaitSync(..., GL_TIMEOUT_IGNORED) path.
         glFinish();
         ::opengl::check_error("");

         m_bPendingFence = false;

      }

   }



} // namespace gpu_opengl



