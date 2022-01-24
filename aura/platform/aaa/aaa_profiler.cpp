#include "framework.h"
#include "aura/platform/profiler2.h"
#include <stdio.h>



namespace aura
{


   namespace profiler
   {

      void initialize()
      {


      }


      CLASS_DECL_AURA i64 microsecond()
      {

         return ::get_nanos() / 1000;

      }
CLASS_DECL_AURA int profile_sleep()
{

#ifdef __DEBUG

   printf("aura::profiler SLEEPING!!\n");
   
   return 400;

#else // __DEBUG

   return 1;

#endif // !__DEBUG


}

   } // namespace profiler


} // namespace aura




