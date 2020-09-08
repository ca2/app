#include "framework.h"
#include "apex/platform/profiler2.h"
#include <stdio.h>



namespace apex
{


   namespace profiler
   {

      void initialize()
      {


      }


      CLASS_DECL_APEX i64 micros()
      {

         return ::get_nanos() / 1000;

      }
CLASS_DECL_APEX int profile_sleep()
{

#ifdef __DEBUG

   printf("apex::profiler SLEEPING!!\n");
   
   return 400;

#else // __DEBUG

   return 1;

#endif // !__DEBUG


}

   } // namespace profiler


} // namespace apex




