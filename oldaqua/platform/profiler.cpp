#include "framework.h"
#include "aqua/platform/profiler2.h"
#include <stdio.h>



namespace aqua
{


   namespace profiler
   {

      void initialize()
      {


      }


      CLASS_DECL_AQUA i64 micros()
      {

         return ::get_nanos() / 1000;

      }
CLASS_DECL_AQUA int profile_sleep()
{

#ifdef __DEBUG

   printf("aqua::profiler SLEEPING!!\n");
   
   return 400;

#else // __DEBUG

   return 1;

#endif // !__DEBUG


}

   } // namespace profiler


} // namespace aqua




