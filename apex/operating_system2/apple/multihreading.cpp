// Internet, 21 de Julho de 2017
// 01:00:30 (friday dawn)
// bilbo (sleeping) and Mummi (Discovery ID)!!
// (after Pizza slice and Lamen...)
// Tectuma (Stacie, Kevin and Dylan...)
// RocketBeans.TV (classical and epic Dark Souls with Colin and Etienne)
// scamwhite
// currently and for ever lasting TBS... (thomas borregaard at 2017 earth milk way) Incancilabile (Uncancelable/Undeletable)!!


#define user user2
#include <sys/param.h>
#include <sys/sysctl.h>
#undef user


int get_processor_count()
{

   int nm[2];

   size_t len = 4;

   unsigned int count;

   nm[0] = CTL_HW;

   nm[1] = HW_AVAILCPU;

   sysctl(nm, 2, &count, &len, nullptr, 0);

   if(count < 1)
   {

      nm[1] = HW_NCPU;

      sysctl(nm, 2, &count, &len, nullptr, 0);

      if(count < 1)
      {
         count = 1;

      }

   }

   return count;

   //#else
   // return sysconf(_SC_NPROCESSORS_ONLN);
   //#endif
}


