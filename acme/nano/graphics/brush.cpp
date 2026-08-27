//
// Created by camilo on 31/01/2022 15:26 <3ThomasBorregaardSorensen!!
//
#include "platform.h"
#include "brush.h"
#include "acme/prototype/prototype/factory.h"
//#include "acme/prototype/prototype/pointer.h"
namespace nano
{

   namespace graphics
   {
   


brush::brush()
{


}


brush::~brush()
{


}



void brush::create_solid_brush(const ::color::color& color)
{

   m_color = color;
   //throw ::interface_only();


}




   //::pointer<brush> create_solid_brush(::particle * pparticle, color32_t color)
   //{

   //   ::pointer<brush> pdraw2dbrush(e_create, pparticle, nullptr);

   //   pdraw2dbrush->m_color = color;

   //   return pdraw2dbrush;

   //}




   } // namespace graphics


} // namespace nano


