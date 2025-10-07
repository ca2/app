// Created by camilo 2020-12-18 05:48 BRT <3TBS, Mummi and bilbo!!
#include "framework.h"
#include "acme/parallelization/task.h"
#include "acme/platform/acme.h"
#include "acme/platform/node.h"
#include "acme/platform/system.h"
#include "acme/windowing/windowing.h"


void task_set_name(long l, const_char_pointer psz)
{

   string strName(psz);

   thread_name_abbreviate(strName, 15);

   //bool bOk = !
   pthread_setname_np((pthread_t) l, strName);

   //return bOk;

}


void task_set_name(const ::scoped_string & scopedstrName)
{

   ::string strName(scopedstrName);

   task_set_name(pthread_self(), strName);

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

   auto psystem = ::system();

   psystem->node()->user_post(predicate);

}


//namespace platform
//{
//
//
//   void node::user_post(const ::procedure & procedure)
//   {
//
//      main_asynchronous(procedure);
//
//   }
//
//
//} // namespace platform


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


namespace platform
{


    void node::_user_post(const ::procedure &procedure)
    {

       //information() << "::platform::node::user_post going to display_post";

       system()->acme_windowing()->_user_post(procedure);

    }


} // namespace platform
