// Extracted from device_lock, Changed and Organized by camilo on 2021-09-04 05:46 BRT <3ThomasBS__!!
#include "framework.h"
#include "lock.h"



//#include "acme/_operating_system.h"


namespace draw2d
{


   //::pointer< ::mutex > lock::s_pmutex = nullptr;

   //::interlocked_count lock::s_countReference;

   
   //void lock::__s_initialize()
   //{

   //   auto count = s_countReference++;

   //   if (count == 0)
   //   {

   //      s_pmutex = memory_new ::pointer < ::mutex >();

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
////#ifdef UNIVERSAL_WINDOWS
////
////      acmesystem() = pinteraction->acmesystem();
////
////      ::pointer<::aura::system>psystem = acmesystem();
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
////#ifdef UNIVERSAL_WINDOWS
////
////      //m_D2DMultitask->Leave();
////
////      ::pointer<::aura::system>psystem = acmesystem();
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



