#include "framework.h"
#include "sz.h"
//#include "string.h"


namespace sz
{


   const_char_pointer trim_left(const_char_pointer psz, const ::scoped_string & scopedstrTrimmer)
   {

      if (psz == nullptr)
      {

         return nullptr;

      }

      while((*psz != 0) && scopedstrTrimmer.find(*psz) != nullptr)
      {
         
         unicode_increment(psz);

      }

      return psz;

   }


   const_char_pointer trim_left_path_sep(const_char_pointer psz)
   {

      if (psz == nullptr)
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



