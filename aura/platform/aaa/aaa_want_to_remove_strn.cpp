#include "framework.h"

#ifdef LINUX
//#include <ctype.h>
#endif


namespace aura
{


   bool strn::to(const ::scoped_string & scopedstr, int iLen, long long & i)
   {

      const ::ansi_character * pszEnd;

      long long iConversion = ::ansi_count_to_long_long(scopedstr, &pszEnd, 10, iLen);

      if(scopedstrEnd == psz)
         return false;

      i = iConversion;

      return true;

   }

   bool strn::to(const ::scoped_string & scopedstr, int iLen, int & i)
   {

      char * pszEnd;

      long long iConversion = ::ansi_count_to_long_long(scopedstr, (const ::string &*) &pszEnd, 10, iLen);

      if(scopedstrEnd == psz)
         return false;

      if(iConversion > numeric_info< int >::maximum ())
         return false;

      i = (int) iConversion;

      return true;

   }


   bool strn::to(const ::scoped_string & scopedstr, int iLen, long long & i, int iBase)
   {

      if(iBase < 0 || iBase == 1 || iBase > 36)
         return false;

      const ::ansi_character * pszEnd;

      long long iConversion = ::ansi_count_to_long_long(scopedstr, &pszEnd, iBase, iLen);

      if(scopedstrEnd == psz)
         return false;

      i = iConversion;

      return true;

   }

   bool strn::to(const ::scoped_string & scopedstr, int iLen, int & i, int iBase)
   {

      if(iBase < 0 || iBase == 1 || iBase > 36)
         return false;

      const ::ansi_character * pszEnd;

      long long iConversion = ::ansi_count_to_long_long(scopedstr, &pszEnd, iBase, iLen);

      if(scopedstrEnd == psz)
         return false;

      if(iConversion > numeric_info < int >::maximum ())
         return false;

      i = (int) iConversion;

      return true;

   }

} // namespace aura



