#include "framework.h"


bool set_thread_name(const char * psz)
{

   string strName(psz);

   thread_name_abbreviate(strName, 15);

   return !pthread_setname_np(pthread_self(), strName);

}



