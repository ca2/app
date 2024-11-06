#include "framework.h"

#ifdef LINUX
//#include <ctype.h>
#endif


namespace aura
{


   bool strn::to(const ::string & psz, int iLen, i64 & i)
   {

      const ::ansi_character * pszEnd;

      i64 iConversion = ::ansi_count_to_i64(psz, &pszEnd, 10, iLen);

      if(pszEnd == psz)
         return false;

      i = iConversion;

      return true;

   }

   bool strn::to(const ::string & psz, int iLen, int & i)
   {

      char * pszEnd;

      i64 iConversion = ::ansi_count_to_i64(psz, (const ::string &*) &pszEnd, 10, iLen);

      if(pszEnd == psz)
         return false;

      if(iConversion > numeric_info< int >::maximum ())
         return false;

      i = (int) iConversion;

      return true;

   }


   bool strn::to(const ::string & psz, int iLen, i64 & i, int iBase)
   {

      if(iBase < 0 || iBase == 1 || iBase > 36)
         return false;

      const ::ansi_character * pszEnd;

      i64 iConversion = ::ansi_count_to_i64(psz, &pszEnd, iBase, iLen);

      if(pszEnd == psz)
         return false;

      i = iConversion;

      return true;

   }

   bool strn::to(const ::string & psz, int iLen, int & i, int iBase)
   {

      if(iBase < 0 || iBase == 1 || iBase > 36)
         return false;

      const ::ansi_character * pszEnd;

      i64 iConversion = ::ansi_count_to_i64(psz, &pszEnd, iBase, iLen);

      if(pszEnd == psz)
         return false;

      if(iConversion > numeric_info < int >::maximum ())
         return false;

      i = (int) iConversion;

      return true;

   }

} // namespace aura



