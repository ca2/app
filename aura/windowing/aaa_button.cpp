// created by Camilo <3CamiloSasukeThomasBorregaardSoerensen
// recreated by Camilo 2021-01-28 22:20
#include "framework.h"
#include "_windowing.h"


namespace windowing
{


   button::button(const ::string &psz, enum_dialog_result edialogresult) :
      m_strLabel(psz),
      m_edialogresult(edialogresult)
   {

      m_bTextRect = false;
      m_bPress = false;
      m_bHover = false;

   }


   button::~button()
   {

   }


} // namespace windowing



