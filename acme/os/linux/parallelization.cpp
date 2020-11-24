#include "framework.h"


bool set_thread_name(hthread_t hthread, const char * psz)
{

   string strName(psz);

   thread_name_abbreviate(strName, 15);

   return !pthread_setname_np(hthread, strName);

}


bool set_thread_name(const char * psz)
{

   return set_thread_name(pthread_self(), psz);

}


void ＿＿node_init_cross_windows_threading()
{

}


void ＿＿node_term_cross_windows_threading()
{

}



