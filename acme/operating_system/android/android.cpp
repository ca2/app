#include "framework.h"
//#include "android.h"
//#include "android1.h"




void CLASS_DECL_ACME __abort()
{
   //__android_term();
   abort();
}


























//
//
//
//
//namespace android
//{
//
//   int function()
//   {
//      return 0;
//   }
//
//
//   unsigned int GetTempPath(string & str)
//   {
//      return ::GetTempPathW(MAX_PATH * 8,utf8_to_unicode(str,MAX_PATH * 8));
//   }
//
//} // namespace android



#include <time.h>

int timespec_get(timespec * ptimespec, int i)
{

   if (i == TIME_UTC)
   {

      clock_gettime(CLOCK_MONOTONIC, ptimespec);

      return i;

   }

   return 0;

}



