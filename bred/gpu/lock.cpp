// Fra dx11 by camilo on 2025-06-26 01:58 <3ThomasBorregaardSørensen!!
// Created by camilo on 2025-06-25 14:44 <3ThomasBorregaardSørensen!!
#include "framework.h"
#include "context.h"
#include "device.h"
#include "lock.h"


namespace gpu
{


   thread_local context_lock* t_plock = nullptr;


   context_lock::context_lock(::gpu::context* pcontext) :
      m_pcontext(pcontext)
   {

      //pcontext->m_pgpudevice->m_pparticleSynchronization->_lock();

      if (t_plock)
      {

         if (t_plock->m_pcontext->m_pgpudevice != pcontext->m_pgpudevice)
         {

            throw ::exception(error_wrong_state);

         }

         m_plockUpper = t_plock;

      }
      else
      {

         m_plockUpper = nullptr;

         m_pcontext->_context_lock();

      }

      t_plock = this;

   }


   context_lock::~context_lock()
   {

      if (t_plock)
      {

         t_plock = t_plock->m_plockUpper;

         if (!t_plock)
         {

            m_pcontext->_context_unlock();

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



