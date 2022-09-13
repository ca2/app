#include "framework.h" 
#include "acme/id.h"


void thread_touch_sockets()
{

   task_flag().set(e_task_flag_using_sockets, true);

}


//CLASS_DECL_NETWORKING_BSD void thread_touch_sockets()
//{
//
//   task_flag().set(e_task_flag_using_sockets, true);
//
//}
//
//
//CLASS_DECL_NETWORKING_BSD bool thread_has_sockets()
//{
//
//   return task_flag().is_set(e_task_flag_using_sockets);
//
//}
