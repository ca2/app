// Created by camilo on 2023-07-09 02:06 <3ThomasBorregaardSorensen!!
#include "framework.h"
#include "acme/prototype/datetime/earth_gregorian_time.h"
#include "acme/prototype/datetime/file_time.h"
#include "acme/prototype/datetime/system_time.h"


posix_time::posix_time(const ::file_time & filetime, i32 nDST) :
   posix_time(system_time(filetime), nDST)
{

}


posix_time::posix_time(const system_time & systemtime, i32 nDST) :
   posix_time(::earth::gregorian_time(systemtime))
{



}


posix_time::posix_time(const ::earth::gregorian_time & gregoriantime) :
   posix_time(gregoriantime.make_utc_time())
{

}



