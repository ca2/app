// Extracted from device_lock, Changed and Organized by camilo on 2021-09-04 05:46 BRT <3ThomasBS__!!
#pragma once

//#error
//
//#ifdef _UWP
//
//#include "acme/operating_system/windows_common/comptr.h"
//#include <d2d1_1.h>
//
//#endif
//


namespace draw2d
{
//
//
//   class CLASS_DECL_AURA device_lock
//   {
//   public:
//
////#ifdef _UWP
////
////      comptr < ID2D1Multithread > m_D2DMultithread;
////
////#endif
//
//      class ::system * m_psystem;
//
//      device_lock(::user::interaction * pinteraction);
//      ~device_lock();
//
//
//   };


   class CLASS_DECL_AURA lock :
      public synchronous_lock
   {
   public:

      static ::mutex *              s_pmutex;
      static interlocked_count      s_countReference;


      lock() : synchronous_lock(s_pmutex) {}
      ~lock() override{}


      static void __s_initialize();
      static void __s_finalize();


   };


} // namespace draw2d


