//
// Created by camilo on 31/01/2022 15:23 <3ThomasBorregaardSørensen!!
//
#include "framework.h"
#include "_nano.h"


nano_font::nano_font()
{

   m_bBold = false;

}


nano_font::~nano_font()
{



}



namespace nano
{


   __pointer(nano_font) create_point_font(::object * pobject, int iPoint, enum_font efont, bool bBold)
   {

      __pointer(nano_font) pfont(pobject);

      pfont->m_iFontSize = iPoint;
      pfont->m_strFontName = pobject->m_psystem->node()->font_name(efont);
      pfont->m_bBold = bBold;

      return pfont;

   }


} // namespace nano



