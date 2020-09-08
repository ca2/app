#include "framework.h"
#include <sys/time.h>

namespace aqua
{


   void application::get_time(struct timeval* p)
   {

      gettimeofday(p, nullptr);

   }


} // namespace aqua



