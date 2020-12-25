// Created by camilo 2020-12-18 05:48 BRT <3TBS, Mummi and bilbo!!
#include "framework.h"


bool set_thread_name(long l, const char * psz)
{

   string strName(psz);

   thread_name_abbreviate(strName, 15);

   bool bOk = !pthread_setname_np((pthread_t) l, strName);

   return bOk;

}


bool set_thread_name(const char * psz)
{

   return set_thread_name(pthread_self(), psz);

}


//string thread_get_name()
//{
//
//   //return task_value("name").to_string();
//
//}



int get_processor_count()
{

   return sysconf(_SC_NPROCESSORS_ONLN);


}



