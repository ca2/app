//
//  time.cpp
//  acid
//
//  Created by Camilo Sasuke Thomas Borregaard Soerensen on 15/10/21.
//  Copyright (c) 2021 Camilo Sasuke Thomas Borregaard Soerensen. All rights reserved.
//
#include "framework.h"
//#include <mach/mach_init.h>
#include <mach/mach.h>
#include <mach/clock.h>
#include <time.h>


struct __mach_timespec
{
   
   
   clock_serv_t m_clock;
   
   
   __mach_timespec()
   {
      
      host_get_clock_service(mach_host_self(), CALENDAR_CLOCK, &m_clock);

   }
   
   
   ~__mach_timespec()
   {
      
      mach_port_deallocate(mach_task_self(), m_clock);
      
   }
   
   
   void get(timespec * ptimespec)
   {

      mach_timespec_t mts;
      
      clock_get_time(m_clock, &mts);
      
      ptimespec->tv_sec = mts.tv_sec;
      
      ptimespec->tv_nsec = mts.tv_nsec;
      
   }

};


//static __mach_timespec g_machtimespec;

//void utc_timespec(timespec * ptimespec)
//{
   
  // g_machtimespec.get(ptimespec);

//}





//void utc_timespec(timespec * ptimespec);


void utc_timespec(timespec * ptimespec)
{
   
   __mach_timespec machtimespec;
   
   machtimespec.get(ptimespec);
   
}



//class ::time & time::Now()
//{
//
//   struct timespec timespec;
//
//   if (timespec_get(&timespec, TIME_UTC) != TIME_UTC)
//   {
//
//      throw "timespec_get failed!!";
//
//   }
//
//   m_iSecond = timespec.tv_sec;
//
//   m_iNanosecond = timespec.tv_nsec;
//
//   return *this;
//
//}


class ::time & time::Now()
{

   struct timespec timespec;
   
   if (__builtin_available(macOS 10.15, *))
   {
      
      if (timespec_get(&timespec, TIME_UTC) != TIME_UTC)
      {
         
         throw "timespec_get failed!!";
         
      }
      
   }
   else
   {
      
      utc_timespec(&timespec);

   }
   
   m_iSecond = timespec.tv_sec;

   m_iNanosecond = timespec.tv_nsec;

   return *this;

}

