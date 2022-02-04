//
// Created by camilo on 2021-05-07 07:07 BRT <3ThomasBS_!!
//
#include "framework.h"


namespace regular_expression
{


   result::result()
   {


   }


   result::~result()
   {


   }


   ::count result::get_count() const
   {

      throw ::interface_only_exception();

      return 0;

   }

   
   bool result::has_match() const
   {

      return get_count() > 0;

   }



   string result::get_match(::index iMatch) const
   {

      throw ::interface_only_exception();

      return "";

   }


   ::str::range_array & result::get_range_array()
   {

      _get_range_array();

      return m_rangea;

   }


   void result::_get_range_array()
   {


   }


} // namespace regular_expression



