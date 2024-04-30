//
// Created by camilo on 2021-05-07 07:07 BRT <3ThomasBS_!!
//
#include "framework.h"
#include "result.h"
#include "acme/exception/interface_only.h"


namespace regular_expression
{


   result::result()
   {


   }


   result::~result()
   {


   }


   ::raw::count result::get_count() const
   {

      throw ::interface_only();

      return 0;

   }

   
   bool result::has_match() const
   {

      return get_count() > 0;

   }



   string result::get_match(::raw::index iMatch) const
   {

      throw ::interface_only();

      return "";

   }


   ::strsize_range_array & result::get_range_array()
   {

      _get_range_array();

      return m_rangea;

   }


   void result::_get_range_array()
   {


   }


} // namespace regular_expression



