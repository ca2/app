#include "framework.h"


CLASS_DECL_AURA void black_body(float * r, float * g, float * b, ::u32 dwTemp);


//HFONT wingdi_CreatePointFont(int nPointSize, const char * pszFaceName, HDC hdc, LOGFONTW *plf)
//{
//
//   LOGFONTW lF;
//
//   if (plf == nullptr)
//   {
//      plf = &lF;
//      xxf_zero(plf);
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
//   POINT32 point;
//   // 72 points/inch, 10 decipoints/point
//   point.y = ::MulDiv(::GetDeviceCaps(hdc, LOGPIXELSY), logFont.lfHeight, 720);
//   point.x = 0;
//   ::DPtoLP(hdc, &point, 1);
//   POINT32 pointOrg = { 0, 0 };
//   ::DPtoLP(hdc, &pointOrg, 1);
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


namespace draw2d
{


   HBITMAP bitmap::GetHBITMAP()
   {

      if (m_hbitmapGet != nullptr)
      {

         return m_hbitmapGet;

      }

      m_hbitmapGet = _GetHBITMAP();

      return m_hbitmapGet;

   }


   void bitmap::ReleaseHBITMAP(HBITMAP hbitmap)
   {

      if (hbitmap == nullptr)
      {

         return;

      }

      if (m_hbitmapGet == nullptr)
      {

         return;

      }

      _ReleaseHBITMAP(hbitmap);

      m_hbitmapGet = nullptr;

   }


   HBITMAP bitmap::_GetHBITMAP()
   {

      if (get_os_data() == nullptr)
      {

         return nullptr;

      }
      
      ::image_pointer pimage;

      auto estatus = ::__construct(pimage);

      if (!estatus)
      {

         return nullptr;

      }

      estatus = pimage->create(GetBitmapDimension());

      if (!estatus && pimage->is_empty())
      {

         return nullptr;

      }

      auto pgraphics = ::draw2d::create_memory_graphics();

      pgraphics->set(this);

      pimage->get_graphics()->stretch(pimage->rect(), pgraphics);

      return CreateHBITMAP(pimage);

   }


   void bitmap::_ReleaseHBITMAP(HBITMAP hbitmap)
   {

      ::DeleteObject(hbitmap);

   }


   class wingdi_font_enum
   {
   public:


      HDC                                 m_hdc;
      ::draw2d::font_enum_item_array &    m_itema;
      bool                                m_bRaster;
      bool                                m_bTrueType;
      bool                                m_bOther;
      wstring                             m_wstrTopicFaceName;
      int_array                           m_iaCharSet;


      wingdi_font_enum(::draw2d::font_enum_item_array & itema, bool bRaster, bool bTrueType, bool bOther) :
         m_itema(itema),
         m_bRaster(bRaster),
         m_bTrueType(bTrueType),
         m_bOther(bOther)
      {

         m_iaCharSet.add(CHINESEBIG5_CHARSET);
         m_iaCharSet.add(GB2312_CHARSET);
         m_iaCharSet.add(SHIFTJIS_CHARSET);
         //m_iaCharSet.add(ANSI_CHARSET);
         m_iaCharSet.add(SYMBOL_CHARSET);
         //m_iaCharSet.add(OEM_CHARSET);
         //m_iaCharSet.add(DEFAULT_CHARSET);
         m_iaCharSet.add(HEBREW_CHARSET);
         m_iaCharSet.add(ARABIC_CHARSET);
         m_iaCharSet.add(GREEK_CHARSET);
         m_iaCharSet.add(TURKISH_CHARSET);
         m_iaCharSet.add(VIETNAMESE_CHARSET);
         m_iaCharSet.add(THAI_CHARSET);
         m_iaCharSet.add(EASTEUROPE_CHARSET);
         m_iaCharSet.add(RUSSIAN_CHARSET);
         m_iaCharSet.add(JOHAB_CHARSET);
         m_iaCharSet.add(HANGUL_CHARSET);
         m_iaCharSet.add(BALTIC_CHARSET);
         //m_iaCharSet.add(MAC_CHARSET);

         m_hdc = nullptr;

         enumerate();

      }


      ~wingdi_font_enum()
      {

         ::DeleteDC(m_hdc);

      }


      void enumerate()
      {

         if (m_hdc == nullptr)
         {

            m_hdc = ::CreateCompatibleDC(nullptr);

         }

         ::EnumFontFamiliesW(m_hdc, (const widechar *)nullptr, (FONTENUMPROCW)&wingdi_font_enum::callback, (LPARAM)this);

         for (auto & pitem : m_itema.ptra())
         {

            enum_cs(pitem);

         }

      }


      void enum_cs(::draw2d::font_enum_item * pitem)
      {

         ::EnumFontFamiliesW(m_hdc, pitem->m_wstrName, (FONTENUMPROCW)&wingdi_font_enum::callback_cs, (LPARAM)pitem);

      }


      static BOOL CALLBACK callback(LPLOGFONTW plf, LPNEWTEXTMETRICW lpntm, ::u32 FontType, LPVOID point);


      static BOOL CALLBACK callback_cs(LPLOGFONTW plf, LPNEWTEXTMETRICW lpntm, ::u32 FontType, LPVOID point);


   };



   void draw2d::enum_draw2d_fonts(::draw2d::font_enum_item_array& itema)
   {


       wingdi_font_enum fontenum(itema, true, true, true);


   }

   BOOL CALLBACK wingdi_font_enum::callback(LPLOGFONTW plf, LPNEWTEXTMETRICW lpntm, ::u32 dwFontType, LPVOID p)
   {

      wingdi_font_enum * penum = (wingdi_font_enum *)p;

      if (wcslen(plf->lfFaceName) > 1 && plf->lfFaceName[0] == '@')
      {

      }
      else if (dwFontType & RASTER_FONTTYPE)
      {

         if (penum->m_bRaster)
         {

            penum->m_itema.add(__new(::draw2d::font_enum_item(plf->lfFaceName)));

         }

      }
      else if (dwFontType & TRUETYPE_FONTTYPE)
      {

         if (penum->m_bTrueType)
         {

            penum->m_itema.add(__new(::draw2d::font_enum_item(plf->lfFaceName)));

         }

      }
      else
      {

         if (penum->m_bOther)
         {

            penum->m_itema.add(__new(::draw2d::font_enum_item(plf->lfFaceName)));

         }

      }

      return TRUE;

   }


   BOOL CALLBACK wingdi_font_enum::callback_cs(LPLOGFONTW plf, LPNEWTEXTMETRICW lpntm, ::u32 dwFontType, LPVOID p)
   {

      ::draw2d::font_enum_item * pitem = (::draw2d::font_enum_item *) p;

      ::e_char_set echarset = ::draw2d::wingdi_get_cs(plf->lfCharSet);

      if (echarset != ::char_set_ansi && echarset != ::char_set_default)
      {

         pitem->m_echarseta.add(echarset);

      }

      return TRUE;

   }


   CLASS_DECL_AURA void wingdi_enum_fonts(::draw2d::font_enum_item_array & itema, bool bRaster, bool bTrueType, bool bOther)
   {

     wingdi_font_enum fonts(itema, bRaster, bTrueType, bOther);

   }


   ::e_char_set wingdi_get_cs(int iCs)
   {

     if (iCs == CHINESEBIG5_CHARSET)
     {

        return ::char_set_chinesebig5;

     }
     else if (iCs == GB2312_CHARSET)
     {

        return ::char_set_gb2312;

     }
     else if (iCs == SHIFTJIS_CHARSET)
     {

        return ::char_set_shiftjis;

     }
     else if (iCs == ANSI_CHARSET)
     {

        return ::char_set_ansi;

     }
     else if (iCs == SYMBOL_CHARSET)
     {

        return ::char_set_symbol;

     }
     else if (iCs == OEM_CHARSET)
     {

        return ::char_set_default;

     }
     else if (iCs == DEFAULT_CHARSET)
     {

        return ::char_set_default;

     }
     else if (iCs == HEBREW_CHARSET)
     {

        return ::char_set_hebrew;

     }
     else if (iCs == ARABIC_CHARSET)
     {

        return ::char_set_arabic;

     }
     else if (iCs == GREEK_CHARSET)
     {

        return ::char_set_greek;

     }
     else if (iCs == TURKISH_CHARSET)
     {

        return ::char_set_turkish;

     }
     else if (iCs == VIETNAMESE_CHARSET)
     {

        return ::char_set_vietnamese;

     }
     else if (iCs == THAI_CHARSET)
     {

        return ::char_set_thai;

     }
     else if (iCs == EASTEUROPE_CHARSET)
     {

        return ::char_set_easteurope;

     }
     else if (iCs == RUSSIAN_CHARSET)
     {

        return ::char_set_russian;

     }
     else if (iCs == JOHAB_CHARSET)
     {

        return ::char_set_johab;

     }
     else if (iCs == HANGUL_CHARSET)
     {

        return ::char_set_hangul;

     }
     else if (iCs == BALTIC_CHARSET)
     {

        return ::char_set_baltic;

     }
     else if (iCs == MAC_CHARSET)
     {

        return ::char_set_mac;

     }
     else
     {

        output_debug_string("OTHER char SET");

     }

     return ::char_set_default;

   }


} // namespace draw2d


CLASS_DECL_AURA HBITMAP CreateAlphaBitmapV5(const ::image * pimage)
{

  if (!pimage->is_ok())
  {

     return nullptr;

  }

  //   HDC hMemDC;
  ::u32 dwWidth, dwHeight;
  BITMAPV5HEADER bi;
  // HBITMAP hOldBitmap;
  HBITMAP hBitmap;
  void *pBits;

  HCURSOR hAlphaCursor = nullptr;

  dwWidth = pimage->width();  // width of the Bitmap V5 Dib bitmap
  dwHeight = pimage->height();  // height of the Bitmap V5 Dib bitmap

  ZeroMemory(&bi, sizeof(BITMAPV5HEADER));
  bi.bV5Size = sizeof(BITMAPV5HEADER);
  bi.bV5Width = dwWidth;
  bi.bV5Height = -(::i32)dwHeight;
  bi.bV5Planes = 1;
  bi.bV5BitCount = 32;
  bi.bV5Compression = BI_BITFIELDS;
  // The following mask specification specifies a supported 32 BPP
  // alpha format for Windows XP.
  bi.bV5RedMask = 0x00FF0000;
  bi.bV5GreenMask = 0x0000FF00;
  bi.bV5BlueMask = 0x000000FF;
  bi.bV5AlphaMask = 0xFF000000;

  HDC hdc;
  hdc = GetDC(nullptr);

  // Create the DIB section with an alpha channel.
  hBitmap = CreateDIBSection(hdc, (BITMAPINFO *)&bi, DIB_RGB_COLORS, (void **)&pBits, nullptr, (::u32)0);


  //hMemDC = CreateCompatibleDC(hdc);
  ReleaseDC(nullptr, hdc);

  // Draw something on the DIB section.
  //hOldBitmap = (HBITMAP)set(hMemDC,hBitmap);
  //PatBlt(hMemDC,0,0,dwWidth,dwHeight,WHITENESS);
  //SetTextColor(hMemDC,RGB(0,0,0));
  //SetBkMode(hMemDC,TRANSPARENT);
  //text_out(hMemDC,0,9,"rgba",4);
  //set(hMemDC,hOldBitmap);
  //DeleteDC(hMemDC);

  // Set the alpha values for each pixel in the cursor so that
  // the complete cursor is semi-transparent.

  int iStrideDst = dwWidth * sizeof(color32_t);

  ::copy_colorref((color32_t *)pBits, pimage->width(), pimage->height(), iStrideDst, pimage->get_data(), pimage->scan_size());

  return hBitmap;

}


HCURSOR CreateAlphaIcon(const ::image * pimage, bool bIcon, int xHotSpot, int yHotSpot)
{

  if (!pimage->is_ok())
  {

     return nullptr;

  }

  HBITMAP hBitmap = ::CreateAlphaBitmapV5(pimage);

  // Create an empty mask bitmap.
  HBITMAP hMonoBitmap = CreateBitmap(pimage->width(), pimage->height(), 1, 1, nullptr);

  if (bIcon)
  {
     xHotSpot = 0;
     yHotSpot = 0;
  }

  ICONINFO ii;
  ii.fIcon = bIcon ? TRUE : FALSE;  // Change fIcon to TRUE to create an alpha icon
  ii.xHotspot = xHotSpot;
  ii.yHotspot = yHotSpot;
  ii.hbmMask = hMonoBitmap;
  ii.hbmColor = hBitmap;

  // Create the alpha cursor with the alpha DIB section.
  HICON hicon = CreateIconIndirect(&ii);

  DeleteObject(hBitmap);
  DeleteObject(hMonoBitmap);

  return hicon;
}


HCURSOR context_image::CreateAlphaCursor(oswindow window, const ::image * pimage, int xHotSpot, int yHotSpot)
{

   if (::not_ok(pimage))
   {

      return nullptr;

   }

   return (HCURSOR) ::CreateAlphaIcon(pimage, false, xHotSpot, yHotSpot);

}



//HCURSOR context_image::load_default_cursor(e_cursor ecursor)
//{
//
//   auto pcursor = windows_get_system_cursor(ecursor);
//
//   if (pcursor == nullptr)
//   {
//
//      return NULL;
//
//   }
//
//   return ::LoadCursor(NULL, pcursor);
//
//}


//
//// CreateHITMAP (adapted)
//// Adapted from
//// Marius Bancila's Blog
//// C++,.NET,Windows programming & others
//// (CAmiloST's opinion [Sato's opinion] why 's and .NET?, isn't ++ enough or needed more .Net or exquisite type of coffe?!?!?! or snake or something else?!?!
//// Marius Bancila
//// Software Developer
//// Microsoft MVP VisualC++
//// Cofounder of Codexpert
//// www.mariusbancila.ro
//// http://mariusbancila.ro/blog/tag/wic/
//// Display images as you type in C++
//// Marius Bancila C++ 2011 - 08 - 04 1 comment
//
//


CLASS_DECL_AURA HBITMAP CreateHBITMAP(pixmap * ppixmap)
{

   pixmap pixmap;

   pixmap.m_iScan = ppixmap->width() * sizeof(color32_t);

   pixmap.m_size = ppixmap->size();

   HBITMAP hbitmap = CreateHBITMAP2(&pixmap);

   if (hbitmap == nullptr)
   {

      return nullptr;

   }

   ::copy_colorref(ppixmap, &pixmap);

   return hbitmap;

}


CLASS_DECL_AURA HBITMAP CreateHBITMAP2(pixmap * ppixmap)
{

   HBITMAP hbmp = nullptr;

   BITMAPINFO bminfo;

   ZeroMemory(&bminfo, sizeof(bminfo));
   bminfo.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
   bminfo.bmiHeader.biWidth = ppixmap->width();
   bminfo.bmiHeader.biHeight = -((::i32)ppixmap->height());
   bminfo.bmiHeader.biPlanes = 1;
   bminfo.bmiHeader.biBitCount = 32;
   bminfo.bmiHeader.biCompression = BI_RGB;

   color32_t * pvImageBits = nullptr;

   HDC hdcScreen = GetDC(nullptr);

   hbmp = CreateDIBSection(hdcScreen, &bminfo, DIB_RGB_COLORS, (void **)&ppixmap->m_pcolorrefRaw, nullptr, 0);

   ReleaseDC(nullptr, hdcScreen);

   if (hbmp == nullptr)
   {

      return nullptr;

   }

   ppixmap->m_iScan = ppixmap->width() * sizeof(color32_t);

   return hbmp;

}


////
////Gdiplus::Status HBitmapToBitmap(HBITMAP source, Gdiplus::PixelFormat pixel_format, Gdiplus::Bitmap** result_out)
////{
////   BITMAP source_info = { 0 };
////   if (!::GetObject(source, sizeof(source_info), &source_info))
////      return Gdiplus::GenericError;
////
////   Gdiplus::Status s;
////
////   std::auto_ptr< Gdiplus::Bitmap > target(new Gdiplus::Bitmap(source_info.bmWidth, source_info.bmHeight, pixel_format));
////   if (!target.get())
////      return Gdiplus::OutOfMemory;
////   if ((s = target->GetLastStatus()) != Gdiplus::Ok)
////      return s;
////
////   Gdiplus::BitmapData target_info;
////   Gdiplus::Rect rect(0, 0, source_info.bmWidth, source_info.bmHeight);
////
////   s = target->LockBits(&rect, Gdiplus::ImageLockModeWrite, pixel_format, &target_info);
////   if (s != Gdiplus::Ok)
////      return s;
////
////   if (target_info.Stride != source_info.bmWidthBytes)
////      return Gdiplus::InvalidParameter; // pixel_format is wrong!
////
////   CopyMemory(target_info.Scan0, source_info.bmBits, source_info.bmWidthBytes * source_info.bmHeight);
////
////   s = target->UnlockBits(&target_info);
////   if (s != Gdiplus::Ok)
////      return s;
////
////   *result_out = target.release();
////
////   return Gdiplus::Ok;
////}
//
//
//
////HBITMAP image32_from_freeimage(FIBITMAP *pfibitmap)
////{
////
////   if (pfibitmap == nullptr)
////   {
////
////      return nullptr;
////
////   }
////
////   FIBITMAP * image32 = FreeImage_ConvertTo32Bits(pfibitmap);
////
////   if (image32 == nullptr)
////   {
////
////      return nullptr;
////
////   }
////
////   BITMAPINFO * pbi = FreeImage_GetInfo(image32);
////
////   void * pdata = FreeImage_GetBits(image32);
////
////   color32_t * pcolorref = nullptr;
////
////   BITMAPINFO info;
////
////   __memset(&info, 0, sizeof(info));
////
////   info.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
////   info.bmiHeader.biWidth = pbi->bmiHeader.biWidth;
////   info.bmiHeader.biHeight = pbi->bmiHeader.biHeight;
////   info.bmiHeader.biPlanes = 1;
////   info.bmiHeader.biBitCount = 32;
////   info.bmiHeader.biCompression = BI_RGB;
////   info.bmiHeader.biSizeImage = pbi->bmiHeader.biWidth * pbi->bmiHeader.biHeight * 4;
////
////
////   HBITMAP hDib = ::CreateDIBSection(nullptr, &info, DIB_RGB_COLORS, (void **)&pcolorref, nullptr, 0);
////
////   if (hDib != nullptr)
////   {
////      HDC hdc = ::GetDC(nullptr);
////
////      if (pbi->bmiHeader.biHeight != SetDIBits(
////         hdc,
////         hDib,
////         0,
////         pbi->bmiHeader.biHeight,
////         pdata,
////         pbi,
////         DIB_RGB_COLORS))
////      {
////
////         ASSERT(FALSE);
////      }
////
////      ::ReleaseDC(nullptr, hdc);
////
////   }
////
////   FreeImage_Unload(image32);
////
////   FreeImage_Unload(pimage);
////
////   return hDib;
////
////}
//
//
CLASS_DECL_AURA float os_get_dpi()
{

   return 96.0f;

}
