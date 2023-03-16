#include "framework.h"
#include <time.h>
#include <unistd.h>


//CLASS_DECL_ACME void sleep(const class time & time)
//{
//
//   struct timespec ts;
//   ts.tv_sec = ::time.m_i / 1000;
//   ts.tv_nsec = (::time.m_i % 1000) * 1000000;
//   nanosleep(&ts, NULL);
//
//}





CLASS_DECL_ACME void preempt_second(::i64 i)
{

   ::sleep((unsigned int) i);

}


CLASS_DECL_ACME void preempt_millisecond(::i64 i)
{
   
   ::usleep((useconds_t) i * 1'000);

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


CLASS_DECL_ACME void preempt_nanosecond(::i64 i)
{

   struct timespec timespec;

   timespec.tv_sec = i / 1'000'000'000;

   timespec.tv_nsec = i % 1'000'000'000;

   ::nanosleep(&timespec, nullptr);

}


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
////void system_time_to_earth_time(time_t* ptime, const system_time_t* psystemtime, i32 nDST)
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
