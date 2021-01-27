#include "framework.h"
#include "_.h"


CLASS_DECL_APEX HFONT wingdi_CreatePointFont(int nPointSize, const char * lpszFaceName, HDC hdc, LOGFONTW* lpLogFont);


namespace win32
{


   font::font()
   {

      m_hfont = nullptr;

   }


   font::~font()
   {
      destroy();

   }

   bool font::create_point_font(int iPoint, const char * pszFontFamily, int iWeight)
   {

      destroy();

      HDC hdc = ::CreateCompatibleDC(nullptr);

      if (hdc == nullptr)
      {

         return false;

      }

      LOGFONTW lf;
      __zero(lf);
      lf.lfWeight = iWeight;

      m_hfont = wingdi_CreatePointFont(iPoint, pszFontFamily, hdc, &lf);

      ::DeleteDC(hdc);

      return m_hfont != nullptr;

   }


   void font::destroy()
   {

      if (m_hfont == nullptr)
      {

         return;

      }

      ::DeleteObject(m_hfont);

      m_hfont = nullptr;

   }



} //  namespace os


