//
// Created by camilo on 31/01/2022 15:25 <3ThomasBorregaardSorensen!!
//
#include "framework.h"
#include "pen.h"
#include "acme/prototype/prototype/factory.h"
//#include "acme/prototype/prototype/pointer.h"



namespace nano
{

namespace user
{


pen::pen()
{


}


pen::~pen()
{



}


   ::pointer<::nano::graphics::pen> create_pen(::particle * pparticle, int iWidth, color32_t color)
   {

      ::pointer<::nano::graphics::pen> ppen(e_create, pparticle, nullptr);

      ppen->m_iWidth = iWidth;

      ppen->m_color = color;

      return ppen;

   }



   } // namespace user


} // namespace nano


