#include "framework.h"
#include "acid/platform/profiler.h"
#include <stdio.h>


namespace acid
{


   namespace profiler
   {


      void initialize()
      {


      }


      CLASS_DECL_ACID int profile_sleep()
      {

         #ifdef __DEBUG

            printf("acid::profiler SLEEPING!!\n");

            return 400;

         #else // __DEBUG

            return 1;

         #endif // !__DEBUG

      }


   } // namespace profiler


} // namespace acid



