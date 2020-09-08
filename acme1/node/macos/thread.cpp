#include "framework.h"
#include "_.h"
#include <fcntl.h>






namespace macos
{




//   thread::thread(::generic * pobject) :
//   ::generic(pobject),
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

   UNREFERENCED_PARAMETER(pthread);
   
   return true;

}



bool __node_term_thread(::thread * pthread)
{
   
//   __clear_mq(pthread->type_name(), true);
   
   UNREFERENCED_PARAMETER(pthread);

   return true;

}







