#include "framework.h"


CLASS_DECL_AURA void black_body(float * r, float * g, float * b, ::u32 dwTemp);


//HFONT wingdi_CreatePointFont(int nPointSize, const ::string & pszFaceName, HDC hdc, LOGFONTW *plf)
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
//HFONT wingdi_CreatePointFontIndirect(LOGFONTW* pLogFont, HDC hdc)
//
//{
//
//   LOGFONTW & logFont = *pLogFont;
//
//
//   ::point_i32 point_i32;
//   // 72 points/inch, 10 decipoints/point_i32
//   point.y() = ::MulDiv(::GetDeviceCaps(hdc, LOGPIXELSY), logFont.lfHeight, 720);
//   point.x() = 0;
//   ::DPtoLP(hdc, &point, 1);
//   ::point_i32 pointOrg = { 0, 0 };
//   ::DPtoLP(hdc, &pointOrg, 1);
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
//      output_debug_string("got log font");
//   }
//
//
//
//   return hfont;
//
//}


namespace draw2d
{


   //HBITMAP bitmap::GetHBITMAP()
   //{

   //   if (m_hbitmapGet != nullptr)
   //   {

   //      return m_hbitmapGet;

   //   }

   //   m_hbitmapGet = _GetHBITMAP();

   //   return m_hbitmapGet;

   //}


   //void bitmap::ReleaseHBITMAP(HBITMAP hbitmap)
   //{

   //   if (hbitmap == nullptr)
   //   {

   //      return;

   //   }

   //   if (m_hbitmapGet == nullptr)
   //   {

   //      return;

   //   }

   //   _ReleaseHBITMAP(hbitmap);

   //   m_hbitmapGet = nullptr;

   //}


   //HBITMAP bitmap::_GetHBITMAP()
   //{

   //   if (get_os_data() == nullptr)
   //   {

   //      return nullptr;

   //   }
   //   
   //   ::image_pointer pimage;

   //   auto estatus = ::__construct(pimage);

   //   if (!estatus)
   //   {

   //      return nullptr;

   //   }

   //   estatus = pimage->create(GetBitmapDimension());

   //   if (!estatus && pimage->is_empty())
   //   {

   //      return nullptr;

   //   }

   //   auto pgraphics = ::draw2d::create_memory_graphics();

   //   pgraphics->set(this);

   //   pimage->get_graphics()->stretch(pimage->rectangle(), pgraphics);

   //   return CreateHBITMAP(pimage);

   //}


   //void bitmap::_ReleaseHBITMAP(HBITMAP hbitmap)
   //{

   //   ::DeleteObject(hbitmap);

   //}



} // namespace draw2d


