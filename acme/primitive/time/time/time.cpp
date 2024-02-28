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

   uint64_t centimicroseconds = filetime.m_uFileTime ;

   centimicroseconds -= (file_time::EPOCH_DIFFERENCE_NANOS / 100);

   m_iSecond = centimicroseconds / 10'000'000;

   m_iNanosecond = (centimicroseconds % 10'000'000) * 100;

}




