#include "framework.h"
#include "time.h"
#include "acme/primitive/datetime/earth_gregorian_time.h"
#include "acme/operating_system/posix/time.h"


void system_time_to_tm(tm * ptm, const system_time_t * psystemtime);


void system_time_to_earth_time(posix_time * ptime, const system_time_t * psystemtime, i32 nDST)
{

   struct tm tm;

   system_time_to_tm(&tm, psystemtime);

   ::earth::gregorian::time time;

   copy(&time, &tm);

   *ptime = time.make_utc_time();

}



