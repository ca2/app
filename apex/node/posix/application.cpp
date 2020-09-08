#include "framework.h"
#include <sys/time.h>

namespace apex
{


   void application::get_time(struct timeval* p)
   {

      gettimeofday(p, nullptr);

   }


} // namespace apex



