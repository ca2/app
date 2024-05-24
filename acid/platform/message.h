//
// Created by camilo on 6/23/21 08:19 BRT <3ThomasBS_!!
//
#pragma once


////#include "acid/primitive/primitive/property_object.h"
//#include "acid/primitive/mathematics/c_number.h"
#include "acid/primitive/geometry2d/point.h"


namespace acid
{


   class CLASS_DECL_ACID message :
      virtual public ::property_object
   {
   public:


      message_union                 m_union;

      class ::time      m_time;
      ::point_f64       m_pointMessage;
      wparam            m_wparam;
      lparam            m_lparam;
      lresult           m_lresult;


   };


} // namespace acid



