// Created by camilo on 2022-03-25 11:50 <3ThomasBorregaardSorensen!! (Thomas likes number 5!!)
#include "framework.h"
#include "host.h"


namespace draw2d
{


   host::host()
   {

      m_dScreenScaler = 1.0;
      m_dFontScaler = 1.0;

   }


   host::~host()
   {

   }


   double host::point_dpi(double d)
   {

      return d;

   }


   double host::dpiy(double d)
   {

      return d;

   }


} // namespace draw2d



