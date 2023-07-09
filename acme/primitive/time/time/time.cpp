// Created by camilo on 2023-07-09 04:02 <3ThomasBorregaardSorensen!!
#include "framework.h"
#include "time.h"
#include "acme/primitive/datetime/earth_gregorian_time.h"


time::time(const ::earth::gregorian_time & gregoriantime) :
   posix_time(gregoriantime),
   nanosecond({ nanosecond_t{}, gregoriantime.m_iNanoSecond })
{


}


time::time(const ::file_time & filetime)
{

   uint64_t nanoseconds = filetime.m_uFileTime * 100;

   nanoseconds -= file_time::EPOCH_DIFFERENCE_NANOS;

   m_iSecond = nanoseconds / 1'000'000'000;

   m_iNanosecond = nanoseconds % 1'000'000'000;

}




