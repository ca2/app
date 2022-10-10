//
// Created by camilo on 31/01/2022 15:25 <3ThomasBorregaardSørensen!!
//
#include "framework.h"
#include "_nano.h"


nano_pen::nano_pen()
{


}


nano_pen::~nano_pen()
{



}


namespace nano
{


   ::pointer<nano_pen> create_pen(::object * pobject, int iWidth, color32_t color)
   {

      ::pointer<nano_pen> ppen(e_create, pobject);

      ppen->m_iWidth = iWidth;

      ppen->m_color = color;

      return ppen;

   }


} // namespace nano



