//#include "framework_c.h"
//#include "linux/byteorder/swab.h"
//#include <math.h>
//#include <float.h>


//extern "C"
//{

   //extern "C"
   CLASS_DECL_AQUA i64 get_nanos()
   {

      struct timespec ts;

      if (clock_gettime(CLOCK_MONOTONIC, &ts) != 0)
      {
         //error
         return 0;
      }

      u64 ui = ts.tv_sec;

      ui *= 1000 * 1000 * 1000;

      ui += ts.tv_nsec;

      return  ui;

   }

//} // extern "C"



















