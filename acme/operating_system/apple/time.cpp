//
//  time.cpp
//  acme
//
//  Created by Camilo Sasuke Thomas Borregaard Sørensen on 15/10/21.
//  Copyright © 2021 Camilo Sasuke Thomas Borregaard Sørensen. All rights reserved.
//
#include "framework.h"
//#include <mach/mach_init.h>
#include <mach/mach.h>
#include <mach/clock.h>


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


static __mach_timespec g_machtimespec;

void utc_timespec(timespec * ptimespec)
{
   
   g_machtimespec.get(ptimespec);

}





void utc_timespec(timespec * ptimespec);


int mach_timespec_get(timespec * ptimespec, int i)
{
   
   utc_timespec(ptimespec);
   
   return i;
   
}
