#include "framework.h"
#include <time.h>
#include <unistd.h>


//CLASS_DECL_ACME void sleep(const millis & millis)
//{
//
//   struct timespec ts;
//   ts.tv_sec = millis.m_i / 1000;
//   ts.tv_nsec = (millis.m_i % 1000) * 1000000;
//   nanosleep(&ts, NULL);
//
//}





CLASS_DECL_ACME void preempt(const ::secs & secs)
{

   ::sleep((unsigned int) secs.m_i);

}


CLASS_DECL_ACME void millis_sleep(::u64 uMillis)
{
   
   ::usleep((useconds_t) uMillis * 1'000);

}


CLASS_DECL_ACME void preempt(const millis & millis)
{

   millis_sleep(millis.m_i);

}


CLASS_DECL_ACME void preempt(const micros & micros)
{

   ::usleep((unsigned int)micros.m_i);

}


CLASS_DECL_ACME void preempt(const nanos & nanos)
{

   struct timespec timespec;

   timespec.tv_sec = 0;

   timespec.tv_nsec = nanos.m_i;

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
