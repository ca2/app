#include "framework.h"
#include "_x11.h"


x11_button::x11_button(const char * psz, enum_dialog_result edialogresult) :
   m_strLabel(psz),
   m_edialogresult(edialogresult)
{

   m_bTextRect = false;
   m_bPress = false;
   m_bHover = false;

}


x11_button::~x11_button()
{

}

