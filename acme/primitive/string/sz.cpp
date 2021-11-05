#include "framework.h"


namespace sz
{

   const char * trim_left(const char * psz,const char * pszTrimmer)
   {

      if(psz == nullptr)
         return nullptr;

      while((*psz != 0) && (strchr(pszTrimmer,*psz) != nullptr))
      {
         psz = ::str::__utf8_inc(psz);
      }

      return psz;

   }

   const char * trim_left_path_sep(const char * psz)
   {

      if(psz == nullptr)
         return nullptr;

      while((*psz != 0) && (*psz == '\\' || *psz == '/'))
      {
         psz++;
      }

      return psz;

   }

} // namespace sz
