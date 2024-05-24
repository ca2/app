//
// Created by camilo on 31/01/2022 15:26 <3ThomasBorregaardSorensen!!
//
#include "framework.h"
#include "brush.h"
#include "acid/primitive/primitive/factory.h"
//#include "acid/primitive/primitive/pointer.h"
namespace nano
{

   namespace user
   {
   


brush::brush()
{


}


brush::~brush()
{


}






   ::pointer<brush> create_solid_brush(::particle * pparticle, color32_t color)
   {

      ::pointer<brush> pbrush(e_create, pparticle, nullptr);

      pbrush->m_color = color;

      return pbrush;

   }




   } // namespace user


} // namespace nano


