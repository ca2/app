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

      throw ::interface_only_exception();

      return 0;

   }

   
   bool topic::has_match() const
   {

      return get_count() > 0;

   }



   string topic::get_match(::index iMatch) const
   {

      throw ::interface_only_exception();

      return "";

   }


   ::str::range_array & topic::get_range_array()
   {

      _get_range_array();

      return m_rangea;

   }


   void topic::_get_range_array()
   {


   }


   void topic::create(const ::string & str)
   {

      return ::success;

   }


//   ::count topic::matches(string_array & stra, const ::string & str)
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



