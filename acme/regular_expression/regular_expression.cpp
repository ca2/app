//
// Recreated by camilo on 2021-05-05 22:52 <3ThomasBS_!!
//
#include "framework.h"


namespace regular_expression
{


   regular_expression::regular_expression()
   {

      m_pRegularExpression = nullptr;
      m_iRangeCount = 0;

   }


   regular_expression::~regular_expression()
   {


   }


   ::e_status regular_expression::create(const string& str)
   {

      m_str = str;

      return ::success;

   }


//   ::count regular_expression::calculate_range_count()
//   {
//
//
//
//      auto psz = m_str.c_str();
//
//      auto pszSearch = psz;
//
//      ::count c = 0;
//
//      if(*pszSearch == '(')
//      {
//
//         pszSearch++;
//
//         c++;
//
//      }
//
//
//      do
//      {
//
//         pszSearch = strchr(pszSearch, '(');
//
//         if(::is_null(pszSearch))
//         {
//
//            break;
//
//         }
//
//         if((pszSearch-1))
//         {
//
//            c++;
//
//         }
//
//
//      }
//
//
//   }



   __pointer(topic) regular_expression::create_topic(const string & str)
   {

      return nullptr;

   }



//   ::count regular_expression::matches(string_array & stra, const string & str)
//   {
//
//      auto prangeaMatches = matches_ranges(str);
//
//      if (!prangeaMatches || prangeaMatches->is_empty())
//      {
//
//         return 0;
//
//      }
//
//      stra.add(*prangeaMatches, str);
//
//      return prangeaMatches->get_count();
//
//   }


   //index regex::match(string_array & stra, const string & strParam, strsize iSize)
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
   bool regular_expression::replace(string & strFind, const string & strReplace, string & strResult)
   {

      return false;

   }



} // namespace regular_expression



