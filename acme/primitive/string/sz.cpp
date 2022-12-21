#include "framework.h"
#include "sz.h"
#include "string.h"


namespace sz
{

   const char * trim_left(const ::ansi_character * psz,const ::ansi_character * pszTrimmer)
   {

      if (psz == nullptr)
      {

         return nullptr;

      }

      while((*psz != 0) && (strchr(pszTrimmer,*psz) != nullptr))
      {
         
         unicode_increment(psz);

      }

      return psz;

   }

   const char * trim_left_path_sep(const ::ansi_character * psz)
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
