#include "framework.h"
#include "sz.h"
//#include "string.h"


namespace sz
{


   const char * trim_left(const ::ansi_character * psz, const ::scoped_string & scopedstrTrimmer)
   {

      if (scopedstr == nullptr)
      {

         return nullptr;

      }

      while((*psz != 0) && scopedstrTrimmer.find(*psz) != nullptr)
      {
         
         unicode_increment(scopedstr);

      }

      return psz;

   }


   const char * trim_left_path_sep(const ::ansi_character * psz)
   {

      if (scopedstr == nullptr)
      {

         return nullptr;

      }

      while((*psz != 0) && (*psz == '\\' || *psz == '/'))
      {

         psz++;

      }

      return psz;

   }


} // namespace sz



