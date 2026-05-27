//
// Created by camilo on 31/01/2022 15:25 <3ThomasBorregaardSorensen!!
//
#include "framework.h"
#include "pen.h"
#include "acme/prototype/prototype/factory.h"
//#include "acme/prototype/prototype/pointer.h"



namespace nano
{

namespace graphics
{


pen::pen()
{


}


pen::~pen()
{



}
void pen::create_pen(const ::color::color& color, ::f64 fWidth)
{

   throw ::interface_only();

}

   //::pointer<::nano::graphics::pen> create_pen(::particle * pparticle, ::i32 iWidth, color32_t color)
   //{

   //   ::pointer<::nano::graphics::pen> ppen(e_create, pparticle, nullptr);

   //   ppen->m_iWidth = iWidth;

   //   ppen->m_color = color;

   //   return ppen;

   //}



   } // namespace graphics


} // namespace nano


