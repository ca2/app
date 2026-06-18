// Created by camilo on 2023-07-09 04:02 <3ThomasBorregaardSorensen!!
#include "framework.h"
#include "time.h"
#include "acme/prototype/datetime/earth_gregorian_time.h"


time::time(const ::earth::gregorian_time & gregoriantime) :
   posix_time(gregoriantime),
   nanosecond({ nanosecond_t{}, gregoriantime.m_iNanoSecond })
{


}


time::time(const ::file_time & filetime)
{

   const std::int64_t ticks100ns =
      static_cast<std::int64_t>(filetime.m_uFileTime) -
      static_cast<std::int64_t>(file_time::EPOCH_DIFFERENCE_100NS);

   m_iSecond = ticks100ns / 10'000'000ll;
   m_iNanosecond = static_cast<std::int32_t>((ticks100ns % 10'000'000ll) * 100ll);

   if (m_iNanosecond < 0)
   {
      m_iNanosecond += 1'000'000'000;
      --m_iSecond;
   }
}




