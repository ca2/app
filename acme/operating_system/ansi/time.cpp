#include "framework.h"
#include "time.h"


void system_time_to_tm(tm * ptm, const system_time_t * psystemtime);


void system_time_to_earth_time(posix_time * ptime, const system_time_t * psystemtime, i32 nDST)
{

   struct tm tm;

   system_time_to_tm(&tm, psystemtime);

   *ptime = timegm(&tm);

}



