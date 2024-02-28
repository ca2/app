#include "framework.h"
#include "acme/parallelization/mutex.h"
#include "acme/parallelization/synchronous_lock.h"
#include <time.h>


//extern "C"
//struct tm *gmtime_r(const posix_time *timep,struct tm *result)
////#ifdef CENTOS_LINUX
////throw()
////#endif
//{
//
//#ifdef WINDOWS
//
//
//   if(gmtime_s(result,timep) != 0)
//      return nullptr;
//
//   return result;
//
//#else
//
//   struct tm *tmp;
//   tmp = gmtime(timep);
//   *result = *tmp;
//   return result;
//
//#endif
//
//}

#if !defined(LINUX) && !defined(__APPLE__) && !defined(ANDROID)


#endif

