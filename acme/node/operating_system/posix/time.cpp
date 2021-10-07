#include "framework.h"
#include <time.h>
#include <unistd.h>


//CLASS_DECL_ACME void sleep(const ::duration & duration)
//{
//
//   struct timespec ts;
//   ts.tv_sec = ::duration.m_i / 1000;
//   ts.tv_nsec = (::duration.m_i % 1000) * 1000000;
//   nanosleep(&ts, NULL);
//
//}





CLASS_DECL_ACME void preempt(const ::second & second)
{

   ::sleep((unsigned int) second.m_i);

}


CLASS_DECL_ACME void millis_sleep(::u64 uMillis)
{
   
   ::usleep((useconds_t) uMillis * 1'000);

}


CLASS_DECL_ACME void preempt(const ::duration & duration)
{

   millis_sleep(::duration.m_i);

}


CLASS_DECL_ACME void preempt(const microsecond & microsecond)
{

   ::usleep((unsigned int)microsecond.m_i);

}


CLASS_DECL_ACME void preempt(const nanosecond & nanosecond)
{

   struct timespec timespec;

   timespec.tv_sec = 0;

   timespec.tv_nsec = nanosecond.m_i;

   ::nanosleep(&timespec, nullptr);

}


CLASS_DECL_ACME void precision_wait_microseconds(double d)
{

   ::usleep((::u64)d);

}


CLASS_DECL_ACME void precision_wait_nanoseconds(::u64 u)
{

   struct timespec req;

   req.tv_sec = u / 1'000'000'000ULL;

   req.tv_nsec = u % 1'000'000'000ULL;

   ::nanosleep(&req, nullptr);

}


//::e_status system_time_to_time(time_t* ptime, const system_time_t* psystemtime, i32 nDST)
//{
//
//   struct tm tm;
//
//   __copy(tm, psystemtime);
//
//   *ptime = timegm(&tm);
//
//   return ::success;
//
//}
