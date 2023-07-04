//
// Created by camilo on Jul/3/2023.
// From Linux parallelization.cpp <3ThomasBorregaardSorensen!!
//
#include "framework.h"
#if defined(FREEBSD)
#undef _ANSI_SOURCE
#undef _C99_SOURCE
#undef _C11_SOURCE
#endif
#include <pthread_np.h>
#if defined(FREEBSD)
#include <sched.h>
#endif


int SetThreadAffinityMask(htask_t h, unsigned int dwThreadAffinityMask)
{

   cpu_set_t c;

   CPU_ZERO(&c);

   for(int i = 0; i < sizeof(dwThreadAffinityMask) * 8; i++)
   {

      if((1 << i) & dwThreadAffinityMask)
      {

         CPU_SET(i, &c);

      }

   }

   pthread_setaffinity_np((pthread_t) h, sizeof(c), &c);

   return 1;

}
