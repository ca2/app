#include "framework.h"
//#include "acme/operating_system.h"
//#include "acme/node/operating_system/microsecond_sleep.h"

//
//namespace os
//{
//
//
//   bool microsecond_sleep::sleep(unsigned long usec)
//   {
//
//#ifdef WINDOWS
//      LARGE_INTEGER ft;
//
//      ft.QuadPart = -(10 * (::i64)usec);
//      SetWaitableTimer(m_hTimer, &ft, 0, NULL, NULL, 0);
//      WaitForSingleObject(m_hTimer, U32_INFINITE_TIMEOUT);
//
//      return true;
//
//#else
//
//      usleep((::u32)usec);
//
//      return true;
//
//#endif
//
//   }
//
//
//} // namespace os
//
//
//
