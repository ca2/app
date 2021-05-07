//
// Created by camilo on 2021-05-07 07:07 BRT <3ThomasBS_!!
//
#include "framework.h"


namespace regular_expression
{


   topic::topic()
   {


   }


   topic::~topic()
   {


   }


   ::count topic::get_count() const
   {

      __throw(error_interface_only);

      return 0;

   }


   string topic::get_match(::index iMatch) const
   {

      __throw(error_interface_only);

      return "";

   }


   ::e_status topic::create(const string & str)
   {

      return ::success;

   }


//   ::count topic::matches(string_array & stra, const string & str)
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



} // namespace regular_expression



