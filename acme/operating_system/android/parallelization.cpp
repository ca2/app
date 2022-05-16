// Created by camilo 2020-12-18 05:48 BRT <3TBS, Mummi and bilbo!!
#include "framework.h"


void task_set_name(long l, const char * psz)
{

   string strName(psz);

   thread_name_abbreviate(strName, 15);

   //bool bOk = !
   pthread_setname_np((pthread_t) l, strName);

   //return bOk;

}


void task_set_name(const char * psz)
{

   task_set_name(pthread_self(), psz);

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



extern class system * g_psystem;

void main_asynchronous(const ::procedure & procedure)
{

   if (is_main_thread())
   {

      procedure();

      return;

   }

   auto predicate = [procedure]()
   {

      procedure();

   };

   g_psystem->windowing_post(predicate);

}





void system::windowing_post(const ::procedure & procedure)
{


   main_asynchronous(procedure);

   //::nano::display::g_p->display_post(procedure);

}







bool __os_init_thread()
{

   return true;

}


bool __os_term_thread()
{

   //   __clear_mq("__os_term_thread", true);

      //thread_shutdown();

   return true;

}


