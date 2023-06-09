//
// Created by camilo on 31/01/2022 15:25 <3ThomasBorregaardSorensen!!
//
#include "framework.h"
#include "pen.h"
#include "acme/primitive/primitive/factory.h"
//#include "acme/primitive/primitive/pointer.h"


nano_pen::nano_pen()
{


}


nano_pen::~nano_pen()
{



}


namespace nano
{


   ::pointer<nano_pen> create_pen(::particle * pparticle, int iWidth, color32_t color)
   {

      ::pointer<nano_pen> ppen(e_create, pparticle);

      ppen->m_iWidth = iWidth;

      ppen->m_color = color;

      return ppen;

   }


} // namespace nano



