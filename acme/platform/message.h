//
// Created by camilo on 6/23/21 08:19 BRT <3ThomasBS_!!
//
#pragma once


#include "acme/primitive/primitive/property_object.h"


namespace acme
{


   class CLASS_DECL_ACME message :
      virtual public ::property_object
   {
   public:


      wparam         m_wparam;
      lparam         m_lparam;
      lresult        m_lresult;


   };


} // namespace acme



