// Created by camilo 2020-12-18 05:48 BRT <3TBS, Mummi and bilbo!!
#include "framework.h"


bool task_set_name(long l, const char * psz)
{

   string strName(psz);

   thread_name_abbreviate(strName, 15);

   bool bOk = !pthread_setname_np((pthread_t) l, strName);

   return bOk;

}


bool task_set_name(const char * psz)
{

   return task_set_name(pthread_self(), psz);

}


//string task_get_name()
//{
//
//   //return task_value("name").to_string();
//
//}



int get_processor_count()
{

   return sysconf(_SC_NPROCESSORS_ONLN);


}



