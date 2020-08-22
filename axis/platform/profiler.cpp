#include "framework.h"
#include "aura/platform/profiler2.h"
#include <stdio.h>



namespace axis
{


   namespace profiler
   {

      void initialize()
      {


      }


      CLASS_DECL_AXIS i64 micros()
      {

         return ::get_nanos() / 1000;

      }
CLASS_DECL_AXIS int profile_sleep()
{

#ifdef __DEBUG

   printf("aura::profiler SLEEPING!!\n");
   
   return 400;

#else // __DEBUG

   return 1;

#endif // !__DEBUG


}

   } // namespace profiler


} // namespace axis




