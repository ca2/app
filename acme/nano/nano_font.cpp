//
// Created by camilo on 31/01/2022 15:23 <3ThomasBorregaardSørensen!!
//
#include "framework.h"
#include "nano_font.h"


nano_font::nano_font()
{


}


nano_font::~nano_font()
{



}


void * nano_font::operating_system_data()
{

   return nullptr;

}


void nano_font::create()
{

   wstring wstrName(m_szFontName);

   HDC hdc = ::GetDC(NULL);

   int nHeight = -MulDiv(14, GetDeviceCaps(hdc, LOGPIXELSY), 72);

   m_hfont = ::CreateFontW(m_iFontSize, 0, 0, 0, m_bBold : FW_BOLD : FW_NORMAL,
                           0, 0, 0, DEFAULT_CHARSET, OUT_OUTLINE_PRECIS,
                           CLIP_DEFAULT_PRECIS, CLEARTYPE_QUALITY, FF_SWISS, wstrName);

   ::ReleaseDC(NULL, hdc);

}


