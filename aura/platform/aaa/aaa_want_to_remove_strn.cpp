#include "framework.h"

#ifdef LINUX
//#include <ctype.h>
#endif


namespace aura
{


   bool strn::to(const ::scoped_string & scopedstr, ::i32 iLen, ::i64 & i)
   {

      const ::ansi_character * pszEnd;

      ::i64 iConversion = ::ansi_count_to_i64(scopedstr, &pszEnd, 10, iLen);

      if(scopedstrEnd == psz)
         return false;

      i = iConversion;

      return true;

   }

   bool strn::to(const ::scoped_string & scopedstr, ::i32 iLen, ::i32 & i)
   {

      char_pointer pszEnd;

      ::i64 iConversion = ::ansi_count_to_i64(scopedstr, (const ::string &*) &pszEnd, 10, iLen);

      if(scopedstrEnd == psz)
         return false;

      if(iConversion > numeric_info< ::i32 >::maximum ())
         return false;

      i = (::i32) iConversion;

      return true;

   }


   bool strn::to(const ::scoped_string & scopedstr, ::i32 iLen, ::i64 & i, ::i32 iBase)
   {

      if(iBase < 0 || iBase == 1 || iBase > 36)
         return false;

      const ::ansi_character * pszEnd;

      ::i64 iConversion = ::ansi_count_to_i64(scopedstr, &pszEnd, iBase, iLen);

      if(scopedstrEnd == psz)
         return false;

      i = iConversion;

      return true;

   }

   bool strn::to(const ::scoped_string & scopedstr, ::i32 iLen, ::i32 & i, ::i32 iBase)
   {

      if(iBase < 0 || iBase == 1 || iBase > 36)
         return false;

      const ::ansi_character * pszEnd;

      ::i64 iConversion = ::ansi_count_to_i64(scopedstr, &pszEnd, iBase, iLen);

      if(scopedstrEnd == psz)
         return false;

      if(iConversion > numeric_info < ::i32 >::maximum ())
         return false;

      i = (::i32) iConversion;

      return true;

   }

} // namespace aura



