#include "framework.h"
#include "time.h"
#include "acme/primitive/datetime/earth_gregorian_time.h"
#include "acme/primitive/datetime/earth_zone_time.h"
#ifdef FREEBSD
#undef _C11_SOURCE
#endif
#include <time.h>

#ifdef HAVE_UNISTD_H
#include "acme/primitive/datetime/microsecond_sleep.h"
#include <unistd.h>
#endif


//CLASS_DECL_ACME void sleep(const class time & time)
//{
//
//   struct timespec ts;
//   ts.tv_sec = ::time.m_i / 1000;
//   ts.tv_nsec = (::time.m_i % 1000) * 1000000;
//   nanosleep(&ts, NULL);
//
//}


#ifdef HAVE_UNISTD_H


CLASS_DECL_ACME void preempt_second(::i64 i)
{

   ::sleep((unsigned int)i);

}


CLASS_DECL_ACME void preempt_millisecond(::i64 i)
{

   ::usleep((useconds_t)i * 1'000);

}


//CLASS_DECL_ACME void preempt(const class time & time)
//{
//
//   millis_sleep(::time.m_i);
//
//}


CLASS_DECL_ACME void preempt_microsecond(::i64 i)
{

   ::usleep((unsigned int)i);

}


#endif


#if defined(ANDROID) || defined(__APPLE__) || defined(FREEBSD) || defined(LINUX)


CLASS_DECL_ACME void preempt_nanosecond(::i64 i)
{

   struct timespec timespec;

   timespec.tv_sec = i / 1'000'000'000;

   timespec.tv_nsec = i % 1'000'000'000;

   ::nanosleep(&timespec, nullptr);

}


#endif


// CLASS_DECL_ACME void precision_wait(const class time & time)
// {

//    struct timespec & timespec =  (struct timespec &) time;

//    ::nanosleep(&timespec, nullptr);

// }


//CLASS_DECL_ACME void precision_wait_nanoseconds(::u64 u)
//{
//
//   struct timespec req;
//
//   req.tv_sec = u / 1'000'000'000ULL;
//
//   req.tv_nsec = u % 1'000'000'000ULL;
//
//   ::nanosleep(&req, nullptr);
//
//}
//
//
////void system_time_to_earth_time(posix_time* ptime, const system_time_t* psystemtime, i32 nDST)
////{
////
////   struct tm tm;
////
////   copy(tm, psystemtime);
////
////   *ptime = timegm(&tm);
////
////   return ::success;
////
////}



CLASS_DECL_ACME void copy(struct timespec * ptimespec, const class ::time * ptime)
{

   ptimespec->tv_sec = ptime->m_iSecond;
   ptimespec->tv_nsec = (long) ptime->m_iNanosecond;

}



CLASS_DECL_ACME void copy(class ::time * ptime, const struct timespec * ptimespec)
{

   ptime->m_iSecond = ptimespec->tv_sec;
   ptime->m_iNanosecond = ptimespec->tv_nsec;


}


struct tm * tm_struct(struct tm * ptm, const ::posix_time & posixtime, const ::earth::time_shift & timeshift)
{

   if (::is_null(ptm))
   {

      return nullptr;

   }

   time_t timeOffset = (time_t)timeshift.m_d;

   time_t time = posixtime.m_iSecond + timeOffset;

#ifdef WINDOWS

   struct tm tmTemp;

   errno_t err = _gmtime64_s(&tmTemp, &time);

   if (err != 0)
   {
      return nullptr;    // indicates that m_posixtime was not initialized!
   }

   *ptm = tmTemp;

#else

   struct tm * ptmTemp;

   ptmTemp = gmtime(&time);

   // gmtime can return nullptr
   if (ptmTemp == nullptr)
   {

      return nullptr;

   }

   // but don't throw ::exception( exception or generate error...
   // (reason for commenting out below, fat to be erased...)
//         if(errno != 0)
        //          return nullptr;

   *ptm = *ptmTemp;

#endif

   return ptm;

}


#ifdef HAVE_UNISTD_H


bool microsecond_sleep::sleep(unsigned long usec)
{

   usleep((::u32)usec);

   return true;

}


#endif


void copy(::earth::gregorian::time * ptime, const struct ::tm * ptm, ::i64 iNanosecond)
{

   ptime->m_iNanoSecond = iNanosecond;
   ptime->m_iSecond = ptm->tm_sec;
   ptime->m_iMinute = ptm->tm_min;
   ptime->m_iHour = ptm->tm_hour;
   ptime->m_iDay = ptm->tm_mday;
   ptime->m_iMonth = ptm->tm_mon;
   ptime->m_iYear = ptm->tm_year + 1900;
   ptime->m_iDayOfWeek = ptm->tm_wday;

}



void copy(struct ::tm * ptm, const ::earth::gregorian::time * ptime)
{

   ptm->tm_sec = ptime->m_iSecond;
   ptm->tm_min = ptime->m_iMinute;
   ptm->tm_hour = ptime->m_iHour;
   ptm->tm_mday = ptime->m_iDay;
   ptm->tm_mon = ptime->m_iMonth;
   ptm->tm_year = ptime->m_iYear - 1900;
   ptm->tm_wday = ptime->m_iDayOfWeek;

}


namespace earth 
{


   namespace gregorian 
   {


      void time::set(const ::earth::time & time, ::i64 iNanosecond, const time_shift & timeshift) 
      {

         struct tm tm;

         ::tm_struct(&tm, time, timeshift);

         copy(this, &tm);

      }


   } // namespace gregorian


} // namespace earth


CLASS_DECL_ACME struct tm * GetZoneTm(struct tm * ptm, const ::earth::zone_time & zonetime)
{

   if (::is_null(ptm))
   {

      return nullptr;

   }

#ifdef WINDOWS

   struct tm tmTemp;

   time_t t = zonetime.m_iSecond;

   t += (::i32)zonetime.m_timeshift.m_d;

   errno_t err = _gmtime64_s(&tmTemp, &t);

   if (err != 0)
   {

      return nullptr;    // indicates that m_posixtime was not initialized!

   }

   *ptm = tmTemp;

#else

   struct tm * ptmTemp;

   auto t = zonetime.m_iSecond;

   t += (::i64)zonetime.m_timeshift.m_d;

   ptmTemp = gmtime(&t);

   // gmtime can return nullptr
   if (ptmTemp == nullptr)
   {

      return nullptr;

   }

   // but don't throw ::exception( exception or generate error...
   // (reason for commenting out below, fat to be erased...)
   //         if(errno != 0)
   //          return nullptr;

   *ptm = *ptmTemp;

#endif

   return ptm;

}




namespace earth
{



   ::earth::gregorian::time zone_time::get_zone_time() const
   {

      struct tm tm;

      GetZoneTm(&tm, *this);

      ::earth::gregorian::time time;

      copy(&time, &tm);

      return time;

   }


} // namespace earth



