//
// Created by camilo on 31/01/2022 15:26 <3ThomasBorregaardSørensen!!
//
#include "framework.h"
#include "_nano.h"


nano_brush::nano_brush()
{


}


nano_brush::~nano_brush()
{


}


namespace nano
{


   __pointer(nano_brush) create_solid_brush(::object * pobject, color32_t color)
   {

      __pointer(nano_brush) pbrush(e_create_new, pobject);

      pbrush->m_color = color;

      return pbrush;

   }


} // namespace nano



