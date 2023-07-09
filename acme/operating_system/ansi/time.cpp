#include "framework.h"
#include "time.h"
#include "acme/primitive/datetime/earth_gregorian_time.h"
#include "acme/operating_system/shared_posix/time.h"


void system_time_to_tm(tm * ptm, const system_time & systemtime);


::posix_time as_posix_time(const system_time & systemtime, i32 nDST)
{

   struct tm tm;

   system_time_to_tm(&tm, psystemtime);

   ::earth::gregorian_time time;

   copy(&time, &tm);

   return time.make_utc_time();

}



