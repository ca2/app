#include "framework.h"
#include "acme/os/ansios/_pthread.h"


bool set_thread_name(hthread_t hthread, const char * psz)
{

   string strName(psz);

   thread_name_abbreviate(strName, 15);

   return !pthread_setname_np((pthread_t) hthread, strName);

}


bool set_thread_name(const char * psz)
{

   return set_thread_name((hthread_t) pthread_self(), psz);

}


void __node_init_cross_windows_threading()
{

}


void __node_term_cross_windows_threading()
{

}


int SetThreadAffinityMask(hthread_t h, unsigned int dwThreadAffinityMask)
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


