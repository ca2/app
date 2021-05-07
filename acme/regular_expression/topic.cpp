//
// Created by camilo on 2021-05-07 07:07 BRT <3ThomasBS_!!
//
#include "result.h"


namespace regular_expression
{


   workplace::workplace(::count cMatchData) :
      m_cMatchData(cMatchData)
   {


   }


   workplace::~workplace()
   {


   }


   ::count workplace::get_count() const
   {

      __throw(error_interface_only);

      return 0;

   }


   string workplace::get_match(::index iMatch) const
   {

      __throw(error_interface_only);

      return "";

   }


} // namespace regular_expression



