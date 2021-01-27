#include "framework.h" 
#include "acme/id.h"


CLASS_DECL_APEX void thread_touch_sockets()
{

   thread_property(id_thread_using_sockets) = true;

}


CLASS_DECL_APEX int thread_has_sockets()
{

   return (int) (iptr)thread_property(id_thread_using_sockets);

}



