//#include "framework_c.h"
//#include "linux/byteorder/swab.h"
//#include <math.h>
//#include <float.h>


//extern "C"
//{

   //extern "C"
   CLASS_DECL_APEX i64 get_nanos()
   {

      struct timespec ts;

      if (clock_gettime(CLOCK_MONOTONIC, &ts) != 0)
      {
         //error
         return 0;
      }

      u64 u = ts.tv_sec;

      u *= 1000 * 1000 * 1000;

      u += ts.tv_nsec;

      return  u;

   }

//} // extern "C"



















