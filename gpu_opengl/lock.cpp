// Created by camilo on 2025-06-22 12:22 <3ThomasBorregaardSørensen!!
#include "framework.h"
#include "_gpu_opengl.h"
#include "context.h"
#include "device.h"
#include "lock.h"

//
//namespace gpu_opengl
//{
//
//
//   thread_local opengl_lock* t_plock = nullptr;
//
//
//   opengl_lock::opengl_lock(::gpu::context* pcontext) :
//      m_pcontext(dynamic_cast < context * >(pcontext))
//   {
//
//      pcontext->m_pgpudevice->m_pparticleSynchronization->_lock();
//
//      if (t_plock)
//      {
//
//         if (t_plock->m_pcontext->m_pgpudevice != pcontext->m_pgpudevice)
//         {
//
//            throw ::exception(error_wrong_state);
//
//         }
//
//         m_plockUpper = t_plock;
//
//      }
//      else
//      {
//
//         m_plockUpper = nullptr;
//
//         m_pcontext->_opengl_lock();
//
//      }
//
//      t_plock = this;
//
//   }
//
//
//   opengl_lock::~opengl_lock()
//   {
//
//      if (t_plock)
//      {
//
//         t_plock = t_plock->m_plockUpper;
//
//         if (!t_plock)
//         {
//
//            m_pcontext->_opengl_unlock();
//
//         }
//
//      }
//      else
//      {
//
//         warning() << "this shouldn't happen";
//
//      }
//
//      m_pcontext->m_pgpudevice->m_pparticleSynchronization->unlock();
//
//   }
//
//
//
//
//   //};
//
//
//
//} // namespace gpu_opengl
//
//
//
