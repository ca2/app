#include "framework.h"
#include "_x11.h"


x11_button::x11_button(const char * psz, int iResult) :
   m_strLabel(psz),
   m_iResult(iResult)
{

   m_bTextRect = false;
   m_bPress = false;
   m_bHover = false;

}


x11_button::~x11_button()
{

}

