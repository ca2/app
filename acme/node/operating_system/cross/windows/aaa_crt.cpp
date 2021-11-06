#include "framework.h"
#include "_windows.h"


#define EUNKNOWN        37               // Unknown error


CLASS_DECL_ACME errno_t _ctime64_s(char * buf, i32 iSize, const time_t * timer )
{

   char * ret = nullptr;

   if((ret = ctime(timer)) == nullptr)
   {
      if(errno == 0)
         return EUNKNOWN;
      else
         return errno;
   }

   i32 iLen;

   if(((iLen = (i32) strlen(ret)) + 1) > iSize)
      return ERANGE;

   ansi_count_copy(buf, ret, minimum(iSize, iLen));

   return 0;

}
