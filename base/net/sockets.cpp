#include "framework.h" 
#include "aura/const/id.h" 


CLASS_DECL_BASE void thread_touch_sockets()
{

   thread_value(id_thread_using_sockets) = true;

}


CLASS_DECL_BASE int thread_has_sockets()
{

   return (int) (iptr)thread_value(id_thread_using_sockets);

}



