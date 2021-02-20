#include "framework.h"
#include <time.h>
#if defined(LINUX) || defined(APPLEOS)
#include <unistd.h>
#endif


CLASS_DECL_ACME void __seed_srand()
{

   srand((unsigned int)(time(nullptr)));

}


//CLASS_DECL_ACME void sleep(const ::duration& dur)
//{
//
//   sleep((::u32)dur.total_milliseconds());
//
//}


CLASS_DECL_ACME void sleep(const duration & duration)
{

   if(duration.secs().m_i >= 20)
   {

      sleep(duration.secs());

   }
   else if(duration.millis().m_i >= 20)
   {

      sleep(duration.millis());

   }
   else if(duration.micros().m_i >= 20)
   {

      sleep(duration.micros());

   }
   else
   {

      sleep(duration.nanos());

   }

}



