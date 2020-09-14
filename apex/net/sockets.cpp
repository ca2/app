#include "framework.h" 
#include "apex/const/id.h" 


CLASS_DECL_APEX void thread_touch_sockets()
{

   thread_value(id_thread_using_sockets) = true;

}


CLASS_DECL_APEX int thread_has_sockets()
{

   return (int) (iptr)thread_value(id_thread_using_sockets);

}



