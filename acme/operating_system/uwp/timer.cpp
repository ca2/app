#include "framework.h"

//
//bool timer::impl_start()
//{
//
//   ::winrt::Windows::Foundation::TimeSpan span;
//
//   span.Duration = m_dwMillis * 1000 * 10;
//
//   auto pred = [this](ThreadPoolTimer ^)
//   {
//
//      try
//      {
//
//         __pointer(timer) ptimer = this;
//
//         ptimer->call_on_timer();
//
//      }
//      catch (...)
//      {
//
//      }
//
//   };
//
//   {
//
//      m_timer = ThreadPoolTimer::CreateTimer(ref memory_new TimerElapsedHandler(pred), span);
//
//      if (m_timer == nullptr)
//      {
//
//         return false;
//
//      }
//
//   }
//
//   return true;
//
//}
//
//
//void timer::impl_init()
//{
//
//   m_timer = nullptr;
//
//}
//
//
//void timer::impl_term()
//{
//
//   if (m_timer != nullptr)
//   {
//
//      m_timer->Cancel();
//
//      m_timer = nullptr;
//
//   }
//
//}
//
//
//void timer::impl_stop()
//{
//
//   if (m_timer != nullptr)
//   {
//
//      m_timer->Cancel();
//
//      m_timer = nullptr;
//
//   }
//
//}
//
//
//bool timer::impl_restart()
//{
//
//   if (m_timer != nullptr)
//   {
//
//      m_timer->Cancel();
//
//      m_timer = nullptr;
//
//   }
//
//   ::winrt::Windows::Foundation::TimeSpan span;
//
//   span.Duration = m_dwMillis * 1000 * 10;
//
//   __pointer(timer) pthis = this;
//
//   auto pred = [pthis](ThreadPoolTimer ^)
//   {
//
//      try
//      {
//
//         pthis->call_on_timer();
//
//      }
//      catch (...)
//      {
//
//      }
//
//   };
//
//   m_timer = ThreadPoolTimer::CreateTimer(ref memory_new TimerElapsedHandler(pred), span);
//
//   return true;
//
//}
//
//
//
//
