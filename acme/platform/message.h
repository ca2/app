//
// Created by camilo on 6/23/21 08:19 BRT <3ThomasBS_!!
//
#pragma once


////#include "acme/prototype/prototype/property_object.h"
//#include "acme/prototype/mathematics/c_number.h"
#include "acme/prototype/geometry2d/point.h"


namespace acme
{


   class CLASS_DECL_ACME message :
      virtual public ::property_object
   {
   public:


      message_union        m_union;

      class ::time         m_time;
      ::i64                m_iTimestamp;
      ::point_f64          m_pointMessage;
      wparam               m_wparam;
      lparam               m_lparam;
      lresult              m_lresult;


   };


} // namespace acme



