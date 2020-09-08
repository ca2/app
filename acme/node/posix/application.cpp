#include "framework.h"
#include <sys/time.h>

namespace acme
{


   void application::get_time(struct timeval* p)
   {

      gettimeofday(p, nullptr);

   }


} // namespace acme



