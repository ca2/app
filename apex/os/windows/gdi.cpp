#include "framework.h"
#include "apex/operating_system.h"


CLASS_DECL_APEX HFONT wingdi_CreatePointFont(int nPointSize, const char* pszFaceName, HDC hdc, LOGFONTW* plf)
{

   LOGFONTW lF;

   if (plf == nullptr)
   {
      plf = &lF;
      __zero(plf);
      plf->lfCharSet = DEFAULT_CHARSET;

   }



   plf->lfHeight = nPointSize;

   wstring wstr(pszFaceName);


   wstr = wstr.substr(0, sizeof(plf->lfFaceName));

   wcsncpy(plf->lfFaceName, wstr, sizeof(plf->lfFaceName) / sizeof(wchar_t));

   return wingdi_CreatePointFontIndirect(plf, hdc);

}


// pLogFont->nHeight is interpreted as PointSize * 10
CLASS_DECL_APEX HFONT wingdi_CreatePointFontIndirect(LOGFONTW* pLogFont, HDC hdc)
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




//#include "framework.h"



// http://stackoverflow.com/questions/7375003/how-to-convert-hicon-to-hbitmap-in-vc

// answered Aug 12 at 15:34
// befzz
// 10714


CLASS_DECL_APEX HBITMAP get_icon_hbitmap(HICON hICON)
{

   //HICON hICON = /*your code here*/
   HBITMAP hBITMAPcopy;
   ICONINFOEX IconInfo;
   //BITMAP BM_32_bit_color;
   //BITMAP BM_1_bit_mask;

   // 1. From HICON to HBITMAP for color and mask separately
   //.cbSize required
   //__memset((void*)&IconInfo, 0, sizeof(ICONINFOEX));
   IconInfo.cbSize = sizeof(ICONINFOEX);
   GetIconInfoEx(hICON, &IconInfo);


   //HBITMAP IconInfo.hbmColor is 32bit per pxl, however alpha bytes can be zeroed or can be not.
   //HBITMAP IconInfo.hbmMask is 1bit per pxl

   // 2. From HBITMAP to BITMAP for color
   //    (HBITMAP without raw data -> HBITMAP with raw data)
   //         LR_CREATEDIBSECTION - DIB section will be created,
   //         so .bmBits pointer will not be null
   hBITMAPcopy = (HBITMAP)CopyImage(IconInfo.hbmColor, IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION);
   //    (HBITMAP to BITMAP)
   //GetObject(hBITMAPcopy,sizeof(BITMAP),&BM_32_bit_color);
   //Now: BM_32_bit_color.bmBits pointing to BGRA data.(.bmWidth * .bmHeight * (.bmBitsPixel/8))

   // 3. From HBITMAP to BITMAP for mask
   //hBITMAPcopy = (HBITMAP)CopyImage(IconInfo.hbmMask,IMAGE_BITMAP,0,0,LR_CREATEDIBSECTION);
   //GetObject(hBITMAPcopy,sizeof(BITMAP),&BM_1_bit_mask);
   //Now: BM_1_bit_mask.bmBits pointing to mask data (.bmWidth * .bmHeight Bits!)

   return hBITMAPcopy;
}



