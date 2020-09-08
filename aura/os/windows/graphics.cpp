#include "framework.h"


HICON load_icon(::object * pobject, string_array & straMatter, string strIcon, int cx, int cy)
{

   HICON hicon = nullptr;

   ::file::path path;

   for (auto & strMatter : straMatter)
   {

      path = strMatter;

      path = Ctx(pobject).dir().matter(path / strIcon);

      path = Ctx(pobject).get_matter_cache_path(path);

      hicon = (HICON)LoadImageW(nullptr, wstring(path), IMAGE_ICON, cx, cy, LR_LOADFROMFILE);

      if (hicon != nullptr)
      {

         break;

      }

   }

   return hicon;

}


CLASS_DECL_AURA bool os_init_imaging()
{



   return true;

}


CLASS_DECL_AURA void os_term_imaging()
{

}



HBITMAP pixmap::update_windows_dib(const ::size& size)
{

   if (m_size == size)
   {

      return nullptr;

   }

   BITMAPINFO bitmapinfo;

   xxf_zero(bitmapinfo);

   auto iScan = size.cx * 4;

   bitmapinfo.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
   bitmapinfo.bmiHeader.biWidth = (LONG)size.cx;
   bitmapinfo.bmiHeader.biHeight = (LONG)-size.cy;
   bitmapinfo.bmiHeader.biPlanes = 1;
   bitmapinfo.bmiHeader.biBitCount = 32;
   bitmapinfo.bmiHeader.biCompression = BI_RGB;
   bitmapinfo.bmiHeader.biSizeImage = (LONG)(size.cy * iScan);

   COLORREF* pcolorref = nullptr;

   HBITMAP hbitmap = ::CreateDIBSection(nullptr, &bitmapinfo, DIB_RGB_COLORS, (void**)& pcolorref, nullptr, 0);

   if (hbitmap == nullptr)
   {

      return nullptr;

   }

   init(size, pcolorref, iScan);

   return hbitmap;

}



CLASS_DECL_AURA WINBOOL imaging::window_set_mouse_cursor(oswindow , HCURSOR hcursor)
{

   if (!::SetCursor(hcursor))
   {

      return FALSE;

   }

   return TRUE;

}


int_bool delete_hcursor(HCURSOR hcursor)
{

   return ::DestroyCursor(hcursor);

}


namespace draw2d
{


   string default_font_name()
   {

      return "Arial";

   }


} // namespace draw2d


//bool similar_font(const char * pszSystem, const char *pszUser)
//{
//
//   if (::is_null(pszSystem) || ::is_null(pszUser))
//   {
//
//      return false;
//
//   }
//
//   if (!stricmp(pszSystem, pszUser))
//   {
//
//      return 1.0;
//
//   }
//
//
//}



//bool similar_font(const char* pszSystem, const char* pszUser)
//{
//
//   if (::is_null(pszSystem) || ::is_null(pszUser))
//   {
//
//      return false;
//
//   }
//
//   if (!stricmp(pszSystem, pszUser))
//   {
//
//      return 1.0;
//
//   }
//
//
//}