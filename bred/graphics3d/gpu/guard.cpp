// Created by camilo on 2025-06-21 23:55 <3ThomasBorregaardSørensen!!
#include "framework.h"
//#include "guard.h"
//#include "context.h"
//#include "device.h"
//
//
//namespace gpu
//{
//
//
//   context_guard::context_guard(context* pgpucontextIn)
//   {
//
//      if (::is_null(pgpucontextIn))
//      {
//
//         throw ::exception(error_wrong_state);
//
//      }
//
//      auto pgpudevice = pgpucontextIn->m_pgpudevice;
//
//      if (pgpudevice->m_pgpucontextCurrent4 == pgpucontextIn)
//      {
//
//         m_pgpucontextInner = nullptr;
//
//         return;
//
//      }
//
//      pgpudevice->make_current(pgpucontextIn);
//
//      m_pgpucontextInner = pgpucontextIn;
//
//   }
//
//
//   context_guard::~context_guard()
//   {
//
//      if (m_pgpucontextInner)
//      {
//
//         auto pgpudevice = m_pgpucontextInner->m_pgpudevice;
//
//         pgpudevice->release_current(m_pgpucontextInner);
//
//      }
//
//   }
//
//
//   rear_guard::rear_guard(context* pgpucontext)
//   {
//
//      if (::is_null(pgpucontext))
//      {
//
//         throw ::exception(error_wrong_state);
//
//         return;
//
//      }
//
//      if (::is_null(pgpucontext->m_pgpudevice))
//      {
//
//         throw ::exception(error_wrong_state);
//
//      }
//
//      auto pgpucontextOuter = pgpucontext->m_pgpudevice->current_context();
//
//      ::gpu::context::enum_type etypeContextOuter = ::gpu::context::e_type_undefined;
//
//      if (pgpucontextOuter)
//      {
//
//         etypeContextOuter = pgpucontextOuter->m_etype;
//
//      }
//
//      auto itaskOuterCurrent = pgpucontext->m_pgpudevice->m_itaskCurrentGpuContext;
//
//      if (pgpucontextOuter && pgpucontextOuter->m_itask == itaskOuterCurrent)
//      {
//
//         m_pgpucontextOuter = pgpucontextOuter;
//
//         m_itaskOuter = itaskOuterCurrent;
//
//         if (m_itaskOuter != ::current_itask())
//         {
//
//            throw ::exception(error_wrong_state);
//
//         }
//
//         m_pgpucontextOuter->release_current();
//
//      }
//      else
//      {
//
//         m_pgpucontextOuter = nullptr;
//
//      }
//
//   }
//
//
//   rear_guard::~rear_guard()
//   {
//
//      if (m_pgpucontextOuter)
//      {
//
//         if (m_itaskOuter != ::current_itask())
//         {
//
//            warning() << "rear_guard::~rear_guard() - m_itaskOuter != ::current_itask()";
//            //throw ::exception(error_wrong_state);
//
//         }
//
//         m_pgpucontextOuter->make_current();
//
//      }
//
//   }
//
//
//} // namespace gpu
//
//
//
//
