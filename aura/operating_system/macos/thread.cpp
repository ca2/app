#include "framework.h"
#include "_.h"
#include <fcntl.h>






namespace macos
{




//   thread::thread(::object * pobject) :
//   ::object(pobject),
//   ::thread_impl(pobject),
//   ::ansios::thread_impl(pobject)
//   {
//
//
//   }
//
//
//   thread::~thread()
//   {
//
//
//   }
//


} // namespace macos





bool __node_init_thread(::thread * pthread)
{

   __UNREFERENCED_PARAMETER(pthread);
   
   return true;

}



bool __node_term_thread(::thread * pthread)
{
   
//   __clear_mq(__type_name(pthread), true);
   
   __UNREFERENCED_PARAMETER(pthread);

   return true;

}







