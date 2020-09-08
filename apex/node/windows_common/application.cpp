#include "framework.h"


namespace apex
{


   void application::get_time(struct timeval* p)
   {

      FILETIME ft; // Contains a 64-bit value representing the number of 100-nanosecond intervals since January 1, 1601 (UTC).
      GetSystemTimeAsFileTime(&ft);
      u64 tt;
      ::memcpy_dup(&tt, &ft, sizeof(tt));
      tt /= 10; // make it usecs
      p->tv_sec = (long)tt / 1000000;
      p->tv_usec = (long)tt % 1000000;

   }


} // namespace apex



