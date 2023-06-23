#include "framework.h"
#include "_.h"
#include <fcntl.h>






namespace macos
{




//   thread::thread(::particle * pparticle) :
//   ::object(pparticle),
//   ::thread_impl(pparticle),
//   ::ansios::thread_impl(pparticle)
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
   
//   __clear_mq(__type_name(pthread), true);
   
   UNREFERENCED_PARAMETER(pthread);

   return true;

}







