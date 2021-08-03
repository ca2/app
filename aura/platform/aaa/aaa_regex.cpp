#include "framework.h"


::count regex::matches(string_array& stra, const string& str)
{

   auto prangeaMatches = matches_ranges(str);

   if (!prangeaMatches || prangeaMatches->is_empty())
   {

      return 0;

   }

   stra.add(*prangeaMatches, str);

   return prangeaMatches->get_count();

}


//index regex::match(string_array & stra, const ::string & strParam, strsize iSize)
//{
//
//   stra.erase_all();
//
//   ::str::range_array rangeaMatches;
//
//   matches(rangeaMatches, str);
//
//   if (rangeaMatches.is_empty())
//   {
//
//      return 0;
//
//   }
//
//   string str(strParam);
//
//   for(index i = 0; i < matches.cMatch; i++)
//   {
//      strsize iStart   = matches.s[i];
//      strsize iEnd     = matches.e[i];
//      stra.add(str.Mid(iStart, iEnd - iStart));
//   }
//
//   return bMatch;
//
//}
//
//
