//
// Created by camilo on 6/23/21 08:19 BRT <3ThomasBS_!!
//
#pragma once


////#include "acme/primitive/primitive/property_object.h"
//#include "acme/primitive/mathematics/c_number.h"
#include "acme/primitive/geometry2d/_geometry2d.h"


namespace acme
{


   class CLASS_DECL_ACME message :
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


} // namespace acme



