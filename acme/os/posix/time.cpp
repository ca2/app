#include "framework.h"
#include <time.h>


//CLASS_DECL_ACME void sleep(const millis & millis)
//{
//
//   struct timespec ts;
//   ts.tv_sec = millis.m_iMilliseconds / 1000;
//   ts.tv_nsec = (millis.m_iMilliseconds % 1000) * 1000000;
//   nanosleep(&ts, NULL);
//
//}





CLASS_DECL_ACME void sleep(const ::secs & secs)
{

   ::sleep((unsigned int) (secs.m_iSeconds * 1'000));

}


CLASS_DECL_ACME void sleep(const millis & millis)
{

   ::usleep((useconds_t) millis.m_iMilliseconds * 1'000);

}


CLASS_DECL_ACME void sleep(const micros & micros)
{

   ::usleep(micros.m_iMicroseconds);

}


CLASS_DECL_ACME void sleep(const nanos & nanos)
{

   struct timespec timespec;

   timespec.tv_sec = 0;

   timespec.tv_nsec = nanos.m_iNanoseconds;

   ::nanosleep(&timespec, nullptr);

}


CLASS_DECL_ACME void sleep(const duration & duration)
{

   if(duration.secs().m_iSeconds >= 20)
   {

      sleep(duration);

   }
   else if(duration.millis().m_iMilliseconds >= 20)
   {

      sleep(duration);

   }
   else if(duration.micros().m_iMicroseconds >= 20)
   {

      sleep(duration);

   }
   else
   {

      sleep(duration);

   }

}
