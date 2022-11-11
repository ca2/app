#pragma once


//#error ""
//
//
//#ifdef _UWP
//
//#include <d2d1_1.h>
//
//#endif
//
//
//namespace draw2d
//{
//
//   class CLASS_DECL_AURA device_lock
//   {
//   public:
//
//      comptr < ID2D1Multitask > m_D2DMultitask;
//
//      device_lock(ID2D1Multitask * pmultitask) :
//         m_D2DMultitask(pmultitask)
//      {
//
//            m_D2DMultitask->Enter();
//      }
//
//      ~device_lock()
//      {
//
//
//            m_D2DMultitask->Leave();
//
//      }
//
//   };
//
//
//   class CLASS_DECL_AURA lock :
//      public synchronous_lock
//   {
//   public:
//
//      static ::pointer< ::mutex > g_pmutex;
//
//      lock() :
//         synchronous_lock(g_pmutex)
//      {
//
//      }
//
//      virtual ~lock()
//      {
//
//      }
//
//   };
//
//
//} // namespace draw2d
//
//
