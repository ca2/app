// Extracted from device_lock, Changed and Organized by camilo on 2021-09-04 05:46 BRT <3ThomasBS__!!
#include "framework.h"
#include "aura/operating_system.h"
#include "lock.h"


namespace draw2d
{


   //::mutex * lock::s_pmutex = nullptr;

   //::interlocked_count lock::s_countReference;

   
   //void lock::__s_initialize()
   //{

   //   auto count = s_countReference++;

   //   if (count == 0)
   //   {

   //      s_pmutex = memory_new ::mutex();

   //   }

   //}


   //void lock::__s_finalize()
   //{

   //   auto count = s_countReference--;

   //   if (count == 1)
   //   {

   //      delete s_pmutex;

   //   }

   //}


//   device_lock::device_lock(::user::interaction * pinteraction)
//   {
//
////#ifdef _UWP
////
////      m_psystem = pinteraction->m_psystem;
////
////      __pointer(::aura::system) psystem = m_psystem;
////
////      auto pdraw2d = psystem->draw2d();
////
////      auto pmultitask = pdraw2d->direct2d()->m_d2dMultitask.Get();
////
////      pmultitask->Enter();
////
////#endif
//
//   }
//
//
//   device_lock::~device_lock()
//   {
//
////#ifdef _UWP
////
////      //m_D2DMultitask->Leave();
////
////      __pointer(::aura::system) psystem = m_psystem;
////
////      auto pdraw2d = psystem->draw2d();
////
////      auto pmultitask = pdraw2d->direct2d()->m_d2dMultitask.Get();
////
////      pmultitask->Leave();
////
////#endif
//
//   }


} // namespace draw2d



