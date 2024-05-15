//
// Created by camilo on 31/01/2022 15:23 <3ThomasBorregaardSorensen!!
//
#include "framework.h"
#include "font.h"
#include "acme/platform/node.h"
#include "acme/platform/system.h"

namespace nano
{
   
   namespace user
   {
      
font::font()
{

   m_bBold = false;

}


font::~font()
{



}



   ::pointer<::nano::user::font>create_point_font(::particle * pparticle, int iPoint, enum_font efont, bool bBold)
   {

      ::pointer<::nano::user::font>pfont(e_create, pparticle, nullptr);

      pfont->m_iFontSize = iPoint;
      pfont->m_strFontName = pparticle->node()->font_name(efont);
      pfont->m_bBold = bBold;

      return pfont;

   }



   } // namespace user


} // namespace nano


