#include "framework.h"
#include "apex/operating_system.h"


//CLASS_DECL_APEX HFONT wingdi_CreatePointFont(int nPointSize, const char* pszFaceName, HDC hdc, LOGFONTW* plf)
//{
//
//   LOGFONTW lF;
//
//   if (plf == nullptr)
//   {
//      plf = &lF;
//      __zero(plf);
//      plf->lfCharSet = DEFAULT_CHARSET;
//
//   }
//
//
//
//   plf->lfHeight = nPointSize;
//
//   wstring wstr(pszFaceName);
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
//   POINT_I32 point;
//   // 72 points/inch, 10 decipoints/point_i32
//   point.y = ::MulDiv(::GetDeviceCaps(hdc, LOGPIXELSY), logFont.lfHeight, 720);
//   point.x = 0;
//   ::DPtoLP(hdc, (POINT *) &point, 1);
//   POINT_I32 pointOrg = { 0, 0 };
//   ::DPtoLP(hdc, (POINT *) &pointOrg, 1);
//   logFont.lfHeight = -abs(point.y - pointOrg.y);
//
//   logFont.lfQuality = CLEARTYPE_NATURAL_QUALITY;
//
//   HFONT hfont = ::CreateFontIndirectW(&logFont);
//
//   if (::GetObjectW(hfont, sizeof(logFont), pLogFont))
//
//   {
//
//      output_debug_string("got log font");
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

