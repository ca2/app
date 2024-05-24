// Created by camilo 2020-12-18 05:48 BRT <3TBS, Mummi and bilbo!!
#include "framework.h"
#include "acid/parallelization/task.h"
#include "acid/platform/acid.h"
#include "acid/platform/node.h"
#include "acid/platform/system.h"


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

   auto psystem = this->platform()->system();

   psystem->node()->user_post(predicate);

}


namespace acid
{


   void node::user_post(const ::procedure & procedure)
   {

      main_asynchronous(procedure);

   }


} // namespace acid


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





void _do_tasks()
{


}