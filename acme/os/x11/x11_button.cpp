#include "framework.h"
#include "_x11.h"


x11_button::x11_button(const char * psz, const char * pszResult) :
   m_strLabel(psz),
   m_strResult(pszResult)
{

   m_bTextRect = false;
   m_bPress = false;
   m_bHover = false;

}


x11_button::~x11_button()
{

}

