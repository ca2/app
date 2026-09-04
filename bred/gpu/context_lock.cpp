// Fra dx11 by camilo on 2025-06-26 01:58 <3ThomasBorregaardSørensen!!
// Created by camilo on 2025-06-25 14:44 <3ThomasBorregaardSørensen!!
#include "platform.h"
#include "context.h"
#include "device.h"
#include "context_lock.h"


namespace gpu
{


   thread_local context_lock* t_plock = nullptr;

   context_lock::context_lock() :
      m_pgpucontext(nullptr),
      m_plockUpper(nullptr),
      m_bContextSwitched(false)
   {
   
   }


   context_lock::context_lock(::gpu::context* pgpucontext) :
      m_pgpucontext(pgpucontext),
      m_plockUpper(nullptr),
      m_bContextSwitched(false)
   {
      
      lock_context(m_pgpucontext);

   }


   void context_lock::lock_context(::gpu::context * pgpucontext)
   {
   
      //pcontext->m_pgpudevice->m_pparticleSynchronization->_lock();

      if (t_plock)
      {

         if (t_plock->m_pgpucontext->m_pgpudevice != pgpucontext->m_pgpudevice)
         {

            throw ::exception(error_wrong_state);

         }

         m_plockUpper = t_plock;

         if (m_plockUpper->m_pgpucontext != pgpucontext)
         {

            // A GPU device can own multiple native contexts. In particular,
            // WGL share groups share textures and programs, but not container
            // objects such as VAOs and FBOs. Select the exact requested
            // context for a nested lock, then restore the outer context when
            // this lock leaves scope.
            m_plockUpper->m_pgpucontext->_context_unlock();

            try
            {

               pgpucontext->_context_lock();
               m_bContextSwitched = true;

            }
            catch (...)
            {

               m_plockUpper->m_pgpucontext->_context_lock();
               throw;

            }

         }

      }
      else
      {

         m_plockUpper = nullptr;

         pgpucontext->_context_lock();

         ::gpu::thread_set_gpu_device(pgpucontext->m_pgpudevice);

      }

      t_plock = this;
      
   }


   context_lock::~context_lock()
   {

      if (t_plock == this)
      {

         t_plock = m_plockUpper;

         if (m_bContextSwitched)
         {

            m_pgpucontext->_context_unlock();
            m_plockUpper->m_pgpucontext->_context_lock();

         }
         else if (!t_plock)
         {

            m_pgpucontext->_context_unlock();

         }

      }
      else
      {

         warning() << "this shouldn't happen";

      }

      //m_pcontext->m_pgpudevice->m_pparticleSynchronization->unlock();

   }




   //};



} // namespace gpu_directx11



