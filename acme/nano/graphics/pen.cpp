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
void pen::create_pen(enum_pen epen, ::f64 fWidth, const ::color::color& color)
{
   m_epen = epen;
   m_fWidth = fWidth;
   m_color = color;
   
   //throw ::interface_only();

}


void pen::set_start_cap(enum_line_cap elinecap) {
   m_elinecapStart = elinecap;
   //throw ::interface_only();
}

   void pen::set_end_cap(enum_line_cap elinecap) {
  
      m_elinecapEnd = elinecap;
//      throw ::interface_only();
   
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


