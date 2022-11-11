//
// Created by camilo on 31/01/2022 15:23 <3ThomasBorregaardSørensen!!
//
#include "framework.h"
#include "font.h"
#include "acme/platform/node.h"
#include "acme/platform/system.h"


nano_font::nano_font()
{

   m_bBold = false;

}


nano_font::~nano_font()
{



}



namespace nano
{


   ::pointer<nano_font>create_point_font(::particle * pparticle, int iPoint, enum_font efont, bool bBold)
   {

      ::pointer<nano_font>pfont(e_create, pparticle);

      pfont->m_iFontSize = iPoint;
      pfont->m_strFontName = pparticle->acmenode()->font_name(efont);
      pfont->m_bBold = bBold;

      return pfont;

   }


} // namespace nano



