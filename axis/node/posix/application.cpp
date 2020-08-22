#include "framework.h"
#include <sys/time.h>

namespace axis
{


   void application::get_time(struct timeval* p)
   {

      gettimeofday(p, nullptr);

   }


} // namespace axis



