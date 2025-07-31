#include "framework.h"
#include "apex/operating_system.h"


//CLASS_DECL_APEX HFONT wingdi_CreatePointFont(int nPointSize, const ::scoped_string & scopedstrFaceName, HDC hdc, LOGFONTW* plf)
//{
//
//   LOGFONTW lF;
//
//   if (plf == nullptr)
//   {
//      plf = &lF;
//      zero(plf);
//      plf->lfCharSet = DEFAULT_CHARSET;
//
//   }
//
//
//
//   plf->lfHeight = nPointSize;
//
//   wstring wstr(scopedstrFaceName);
//
//
//   wstr = wstr.substr(0, sizeof(plf->lfFaceName));
//
//   wcsncpy(plf->lfFaceName, wstr, sizeof(plf->lfFaceName) / sizeof(wchar_t));
//
//   return wingdi_CreatePointFontIndirect(plf, hdc);
//
//}
//
//
//// pLogFont->nHeight is interpreted as PointSize * 10
//CLASS_DECL_APEX HFONT wingdi_CreatePointFontIndirect(LOGFONTW* pLogFont, HDC hdc)
//{
//
//   LOGFONTW& logFont = *pLogFont;
//
//
//   ::int_point point;
//   // 72 points/inch, 10 decipoints/int_point
//   point.y() = ::MulDiv(::GetDeviceCaps(hdc, LOGPIXELSY), logFont.lfHeight, 720);
//   point.x() = 0;
//   ::DPtoLP(hdc, (POINT *) &point, 1);
//   ::int_point pointOrg = { 0, 0 };
//   ::DPtoLP(hdc, (POINT *) &pointOrg, 1);
//   logFont.lfHeight = -abs(point.y() - pointOrg.y());
//
//   logFont.lfQuality = CLEARTYPE_NATURAL_QUALITY;
//
//   HFONT hfont = ::CreateFontIndirectW(&logFont);
//
//   if (::GetObjectW(hfont, sizeof(logFont), pLogFont))
//
//   {
//
//      informationf("got log font");
//   }
//
//
//
//   return hfont;
//
//}
//
//
//

//#include "framework.h"

