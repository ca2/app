#pragma once
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
//      comptr < ID2D1Multithread > m_D2DMultithread;
//
//      device_lock(ID2D1Multithread * pmultithread) :
//         m_D2DMultithread(pmultithread)
//      {
//
//            m_D2DMultithread->Enter();
//      }
//
//      ~device_lock()
//      {
//
//
//            m_D2DMultithread->Leave();
//
//      }
//
//   };
//
//
//   class CLASS_DECL_AURA lock :
//      public sync_lock
//   {
//   public:
//
//      static ::mutex * g_pmutex;
//
//      lock() :
//         sync_lock(g_pmutex)
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
