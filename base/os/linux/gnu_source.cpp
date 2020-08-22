#ifndef _GNU_SOURCE
#define _GNU_SOURCE
#endif

#include <pthread.h>

typedef pthread_t pthread;

typedef pthread HTHREAD;


int SetThreadAffinityMask(HTHREAD h, unsigned int dwThreadAffinityMask)
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

   pthread_setaffinity_np(h, sizeof(c), &c);

   return 1;

}
