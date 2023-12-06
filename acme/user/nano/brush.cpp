//
// Created by camilo on 31/01/2022 15:26 <3ThomasBorregaardSorensen!!
//
#include "framework.h"
#include "brush.h"
#include "acme/primitive/primitive/factory.h"
//#include "acme/primitive/primitive/pointer.h"


nano_brush::nano_brush()
{


}


nano_brush::~nano_brush()
{


}


namespace nano
{


   ::pointer<nano_brush> create_solid_brush(::particle * pparticle, color32_t color)
   {

      ::pointer<nano_brush> pbrush(e_create, pparticle, nullptr);

      pbrush->m_color = color;

      return pbrush;

   }


} // namespace nano



