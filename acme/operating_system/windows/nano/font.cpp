//
// Created by camilo on 31/01/2022 16:06 <3ThomasBorregaardSørensen!!
//
#include "framework.h"
#include "font.h"
#include "device.h"
//#include "_nano.h"


namespace windows
{


   nano_font::nano_font()
   {

      m_pthis = this;

   }


   nano_font::~nano_font()
   {

   }


   void nano_font::update(::nano_device * pnanodevice)
   {

      if (m_bModified)
      {

         destroy();

         LOGFONTW logfontw = {};

         auto pwindowsnanodevice = dynamic_cast <::windows::nano_device *>(pnanodevice);

         m_hgdiobj = _create_point_font(m_iFontSize * 10, m_strFontName, m_bBold, pwindowsnanodevice->m_hdc, &logfontw);

         m_bModified = false;

      }


   }


   HFONT nano_font::_create_point_font(int nPointSize, const scoped_string & strFaceName, bool bBold, HDC hdc, LOGFONTW* plf)
   {

      LOGFONTW lF;

      if (plf == nullptr)
      {

         plf = &lF;

         memset(plf, 0, sizeof(*plf));

         plf->lfCharSet = DEFAULT_CHARSET;

      }

      plf->lfHeight = nPointSize;

      plf->lfWeight = bBold ? FW_BOLD : FW_NORMAL;

      wstring wstr(pszFaceName);

      wstr = wstr.substr(0, sizeof(plf->lfFaceName));

      wcsncpy(plf->lfFaceName, wstr, sizeof(plf->lfFaceName) / sizeof(wchar_t));

      return _create_point_font_indirect(plf, hdc);

   }


   // pLogFont->nHeight is interpreted as PointSize * 10
   HFONT nano_font::_create_point_font_indirect(LOGFONTW* pLogFont, HDC hdc)
   {

      LOGFONTW& logFont = *pLogFont;


      POINT_I32 point;
      // 72 points/inch, 10 decipoints/point_i32
      point.y = ::MulDiv(::GetDeviceCaps(hdc, LOGPIXELSY), logFont.lfHeight, 720);
      point.x = 0;
      ::DPtoLP(hdc, (POINT *) &point, 1);
      POINT_I32 pointOrg = { 0, 0 };
      ::DPtoLP(hdc, (POINT *) &pointOrg, 1);
      logFont.lfHeight = -abs(point.y - pointOrg.y);

      logFont.lfQuality = CLEARTYPE_NATURAL_QUALITY;

      HFONT hfont = ::CreateFontIndirectW(&logFont);

      if (::GetObjectW(hfont, sizeof(logFont), pLogFont))
      {

         output_debug_string("got log font");

      }

      return hfont;

   }


} // namespace windows



