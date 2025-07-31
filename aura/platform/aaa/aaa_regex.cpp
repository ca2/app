#include "framework.h"


::collection::count regex::matches(string_array& stra, const ::scoped_string & scopedstr)
{

   auto prangeaMatches = matches_ranges(str);

   if (!prangeaMatches || prangeaMatches->is_empty())
   {

      return 0;

   }

   stra.add(*prangeaMatches, str);

   return prangeaMatches->get_count();

}


//index regex::match(string_array & stra, const ::scoped_string & scopedstrParam, character_count iSize)
//{
//
//   stra.erase_all();
//
//   ::strsize_range_array rangeaMatches;
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
//   for(::collection::index i = 0; i < matches.cMatch; i++)
//   {
//      character_count iStart   = matches.s[i];
//      character_count iEnd     = matches.e[i];
//      stra.add(str.substr(iStart, iEnd - iStart));
//   }
//
//   return bMatch;
//
//}
//
//
