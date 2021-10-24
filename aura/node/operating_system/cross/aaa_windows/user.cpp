#include "framework.h"
#include "base/user/user/_user.h"
#if defined(LINUX)
#include "aura/os/linux/_user.h"
#elif defined(ANDROID)
#include "aura/os/android/windowing.h"
#elif defined(_UWP)
#include "aura/os/universal_windows/_uwp.h"
#elif defined(MACOS)
#include "aura/os/macos/oswindow_data.h"
#elif defined(APPLE_IOS)
#include "aura/os/ios/oswindow_data.h"
#endif
#if defined(__APPLE__) || defined(LINUX) || defined(ANDROID)
#include <iconv.h>
#else
//#include "atom/iconv/include/iconv.h"
#endif


CLASS_DECL_AURA color32_t GetSysColor(::u32 dw)
{

   switch(dw)
   {
   case COLOR_HIGHLIGHT:
      return argb(255, 200, 200, 196);
   case COLOR_BTNSHADOW:
      return argb(90, 192, 192, 187);
   case COLOR_BTNTEXT:
      return argb(255, 0, 0, 0);
   default:
      return argb(255, 0, 0, 0);
   };

}



CLASS_DECL_AURA i32 WINAPI GetSystemMetrics(i32 nIndex)
{

   switch(nIndex)
   {
   case SM_CXHSCROLL:
      return 16;
   case SM_CYHSCROLL:
      return 16;
   case SM_CYVSCROLL:
      return 16;
   case SM_CXVSCROLL:
      return 16;
   }

   return 0;

}



CLASS_DECL_AURA int_bool CopyRect(RECT32 * prectDest, const RECT32 * rectangleSource)
{

   prectDest->left      = rectangleSource->left;
   prectDest->top       = rectangleSource->top;
   prectDest->right     = rectangleSource->right;
   prectDest->bottom    = rectangleSource->bottom;

   return true;

}

CLASS_DECL_AURA int_bool PtInRect(const RECT32 * prect, const POINT32 *  ppoint)
{
   return ppoint->x >= prect->left && ppoint->x <= prect->right
          && ppoint->y >= prect->top && ppoint->y <= prect->bottom;

}

CLASS_DECL_AURA int_bool SetRect(RECT32 * prect, i32 x1, i32 y1, i32 x2, i32 y2)
{

   prect->left = x1;
   prect->top = y1;

   prect->right = x2;
   prect->bottom = y2;
   return true;
}


CLASS_DECL_AURA int_bool SetRectEmpty(RECT32 * prect)
{

   SetRect(prect, 0, 0, 0, 0);
   return true;
}


CLASS_DECL_AURA int_bool EqualRect(const RECT32 * prect1, const RECT32 * prect2)
{
   return prect1->left == prect2->left
          &&  prect1->top == prect2->top
          &&  prect1->right == prect2->right
          &&  prect1->bottom == prect2->bottom;
}


CLASS_DECL_AURA int_bool InflateRect(RECT32 * prect, i32 x, i32 y)
{
   prect->left -= x;
   prect->top -= y;
   prect->right += x;
   prect->bottom += y;
   return true;
}

CLASS_DECL_AURA int_bool OffsetRect(RECT32 * prect, i32 x, i32 y)
{
   prect->left += x;
   prect->top += y;
   prect->right += x;
   prect->bottom += y;
   return true;
}

/*
CLASS_DECL_AURA bool x_intersect_rect(RECT32 * prect, const RECT32 * prect1, const RECT32 * prect2)
{
   prect->left = maximum(prect1->left, prect2->left);
   prect->right = minimum(prect1->right, prect2->right);
   return prect->right >= prect->left;
}

CLASS_DECL_AURA bool y_intersect_rect(RECT32 * prect, const RECT32 * prect1, const RECT32 * prect2)
{
   prect->top = maximum(prect1->top, prect2->top);
   prect->bottom = minimum(prect1->bottom, prect2->bottom);
   return prect->bottom >= prect->top;
}
*/

CLASS_DECL_AURA int_bool IntersectRect(RECT32 * prect, const RECT32 * prect1, const RECT32 * prect2)
{
   int_bool bXIntersects = x_intersect_rect(prect, prect1, prect2);
   int_bool bYIntersects = y_intersect_rect(prect, prect1, prect2);
   return bXIntersects && bYIntersects;
}


CLASS_DECL_AURA int_bool UnionRect(RECT32 * prect, const RECT32 * prect1, const RECT32 * prect2)
{
   prect->left = minimum(prect1->left, prect2->left);
   prect->top = minimum(prect1->top, prect2->top);
   prect->right = maximum(prect1->right, prect2->right);
   prect->bottom = maximum(prect1->bottom, prect2->bottom);
   return ((prect->right - prect->left) > 0) && ((prect->bottom - prect->top) > 0);
}


CLASS_DECL_AURA int_bool SubtractRect(RECT32 * prect, const RECT32 * prect1, const RECT32 * prect2)
{
   RECT32 rectangle;
   int_bool bXIntersects = x_intersect_rect(&rectangle, prect1, prect2);
   int_bool bYIntersects = y_intersect_rect(&rectangle, prect1, prect2);
   if(bXIntersects)
   {
      prect->left    = prect->left;
      prect->right   = prect->right;
   }
   if(bYIntersects)
   {
      prect->top    = prect->top;
      prect->bottom   = prect->bottom;
   }
   return bXIntersects || bYIntersects;
}


#ifndef _UWP

string iconv_charset_from_windows_code_page(::u32 CodePage)
{

   switch(CodePage)
   {
   case 1252:
      return "CP1252";
   case 437:
      return "CP437";
   default:
      return "UTF-8";

   }

}


i32
WINAPI
MultiByteToWideChar2(
::u32     CodePage,
::u32    dwFlags,
const char *   pMultiByteStr,
i32      cbMultiByte,
wd16char *   pWideCharStr,
i32      cchWideChar)
{
  string str(pMultiByteStr, cbMultiByte);


  if(CodePage == CP_UTF8)
  {

     str = string(pMultiByteStr, cbMultiByte);


     wstring wstr(str);

     if(cchWideChar == 0)
     {
        if(cbMultiByte < 0)
        {
           return (i32) (wstr.get_length() + 1);
        }
        else
        {
           return (i32) wstr.get_length();
        }
     }

     i32 iLen = (i32) minimum(cchWideChar, wstr.get_length());

     if(pWideCharStr != nullptr)
     {

        ::str::utf_to_utf(pWideCharStr, wstr.c_str(), iLen);

        if(cchWideChar > 0 && cbMultiByte < 0)
        {

           pWideCharStr[iLen] = L'\0';


        }

     }

     if(cbMultiByte < 0)
     {
        return iLen + 1;
     }
     else
     {
        return iLen;
     }

  }
  else
  {

     size_t sIn;

     if(cbMultiByte < 0)
        sIn = strlen(pMultiByteStr);

     else
        sIn = cbMultiByte;

     if(cchWideChar <= 0)
     {

        wd16string wstr;

        size_t sOut = sIn * 4;

        wstr.get_string_buffer(sOut);

        sOut *= sizeof(wd16char);

        wd16char * psz = (wd16char *) (const wd16char *) wstr;


        pWideCharStr = psz;


        iconv_t iconvPlease = iconv_open("UTF-16LE", iconv_charset_from_windows_code_page(CodePage));

        size_t sOutIn = sOut;

        iconv(iconvPlease, (char **) &pMultiByteStr, &sIn, (char **) &psz, &sOut);


        iconv_close(iconvPlease);

        return (i32) (((sOutIn - sOut) / sizeof(wd16char)) + (cbMultiByte < 0 ? 1 : 0));

     }
     else
     {

        wd16char * psz = (wd16char *) (const wd16char *) pWideCharStr;


        size_t sOut = cchWideChar * sizeof(wd16char);

        iconv_t iconvPlease = iconv_open("UTF-16LE", iconv_charset_from_windows_code_page(CodePage));

        size_t sOutIn = sOut;

        iconv(iconvPlease, (char **) &pMultiByteStr, &sIn, (char **) &psz, &sOut);


        iconv_close(iconvPlease);

        return (i32) (((sOutIn - sOut) / sizeof(wd16char))  + (cbMultiByte < 0 ? 1 : 0));

     }

  }





}



i32
WINAPI
MultiByteToWideChar2(
::u32     CodePage,
::u32    dwFlags,
const char *   pMultiByteStr,
i32      cbMultiByte,
wd32char *   pWideCharStr,
i32      cchWideChar)
{
  string str(pMultiByteStr, cbMultiByte);


  if(CodePage == CP_UTF8)
  {

     str = string(pMultiByteStr, cbMultiByte);


     wstring wstr(str);

     if(cchWideChar == 0)
     {
        if(cbMultiByte < 0)
        {
           return (i32) (wstr.get_length() + 1);
        }
        else
        {
           return (i32) wstr.get_length();
        }
     }

     i32 iLen = (i32) minimum(cchWideChar, wstr.get_length());

     if(pWideCharStr != nullptr)
     {

        ::str::utf_to_utf(pWideCharStr, wstr.c_str(), iLen);

        if(cchWideChar > 0 && cbMultiByte < 0)
        {

           pWideCharStr[iLen] = L'\0';


        }

     }

     if(cbMultiByte < 0)
     {
        return iLen + 1;
     }
     else
     {
        return iLen;
     }

  }
  else
  {

     size_t sIn;

     if(cbMultiByte < 0)
        sIn = strlen(pMultiByteStr);

     else
        sIn = cbMultiByte;

     if(cchWideChar <= 0)
     {

        wd32string wstr;

        size_t sOut = sIn * 4;

        wstr.get_string_buffer(sOut);

        sOut *= sizeof(wd32char);

        wd32char * psz = (wd32char *) (const wd32char *) wstr;


        pWideCharStr = psz;


        iconv_t iconvPlease = iconv_open("UTF-32LE", iconv_charset_from_windows_code_page(CodePage));

        size_t sOutIn = sOut;

        iconv(iconvPlease, (char **) &pMultiByteStr, &sIn, (char **) &psz, &sOut);


        iconv_close(iconvPlease);

        return (i32) (((sOutIn - sOut) / sizeof(wd32char)) + (cbMultiByte < 0 ? 1 : 0));

     }
     else
     {

        wd32char * psz = (wd32char *) (const wd32char *) pWideCharStr;


        size_t sOut = cchWideChar * sizeof(wd32char);

        iconv_t iconvPlease = iconv_open("UTF-32LE", iconv_charset_from_windows_code_page(CodePage));

        size_t sOutIn = sOut;

        iconv(iconvPlease, (char **) &pMultiByteStr, &sIn, (char **) &psz, &sOut);


        iconv_close(iconvPlease);

        return (i32) (((sOutIn - sOut) / sizeof(wd32char))  + (cbMultiByte < 0 ? 1 : 0));

     }

  }





}




i32 WINAPI WideCharToMultiByte2(
::u32     CodePage,
::u32    dwFlags,
const widechar *  pWideCharStr,
i32      cchWideChar,
char *   pMultiByteStr,
i32      cbMultiByte,
const char *   pDefaultChar,
int_bool *  pUsedDefaultChar)
{

  wstring wstr(pWideCharStr, cchWideChar);

  string str;

  if(CodePage == CP_UTF8)
  {

     auto len = unichar_to_utf8_len(wstr);

     char * psz = str.get_string_buffer(len);

     unichar_to_utf8(psz, wstr, len);

  }
  else
  {

     size_t sIn = wstr.get_length() * 2;

     char * psz = str.get_string_buffer(sIn);


     size_t sOut = wstr.get_length() * 8;

     string strCodePage = iconv_charset_from_windows_code_page(CodePage);

     iconv_t iconvPlease = iconv_open(strCodePage, "UTF-16LE");

     iconv(iconvPlease, (char **) &pWideCharStr, &sIn, &psz, &sOut);


     iconv_close(iconvPlease);

  }

  str.release_string_buffer();

  if(cbMultiByte == 0)
  {
     if(cchWideChar < 0)
     {
        return (i32) str.get_length() + 1;
     }
     else
     {
        return (i32) str.get_length();
     }
  }

  i32 iLen = (i32) minimum(cbMultiByte, str.get_length());

  if(pMultiByteStr != nullptr)

  {

     ansi_count_copy(pMultiByteStr, str, iLen);


     if(cbMultiByte > 0 && cchWideChar < 0)
     {

        pMultiByteStr[iLen] = '\0';


     }

  }

  if(cchWideChar < 0)
  {
     return iLen + 1;
  }
  else
  {
     return iLen;
  }

}


CLASS_DECL_AURA string get_last_error_message(u32 dwError)
{

   string str;

   return str;

}


#endif


CLASS_DECL_AURA int_bool IsRectEmpty(const RECT32 * prect)
{

   return prect == nullptr || prect->right <= prect->left || prect->bottom <= prect->top;

}


int_bool IsChild(oswindow oswindowParent, ::oswindow oswindowcandidateChildOrDescendant)
{

   auto puiParent = ::oswindow_interaction(oswindowParent);

   auto puiChild = ::oswindow_interaction(oswindowcandidateChildOrDescendant);

   if(::is_null(puiParent))
   {

      return false;

   }

   if(::is_null(puiChild))
   {

      return false;

   }

   return puiParent->is_child(puiChild);

}


oswindow WINAPI get_parent(::oswindow oswindow)
{

   if(::is_null(oswindow))
   {

      return nullptr;

   }

   return oswindow->get_parent();

}


oswindow WINAPI SetParent(::oswindow oswindow, ::oswindow oswindowNewParent)
{

   if(::is_null(oswindow))
   {

      return nullptr;

   }

   return oswindow->set_parent(oswindowNewParent);

}


#ifndef _UWP


int_bool show_window(::oswindow oswindow, ::e_display edisplay)
{

   if(::is_null(oswindow))
   {

      return false;

   }

   return oswindow->show_window(edisplay);

}


#endif


::i32 WINAPI GetWindowLongA(::oswindow oswindow, int nIndex)
{

   if(::is_null(oswindow))
   {

      return 0;

   }

   return (::i32) oswindow->get_window_long_ptr(nIndex);

}


::i32 WINAPI SetWindowLongA(::oswindow oswindow, int nIndex, ::i32 l)
{

   if(::is_null(oswindow))
   {

      return 0;

   }

   return (::i32) oswindow->set_window_long_ptr(nIndex, (::i32) l);

}


LONG_PTR WINAPI GetWindowLongPtrA(::oswindow oswindow, int nIndex)
{

   if(::is_null(oswindow))
   {

      return 0;

   }

   return oswindow->get_window_long_ptr(nIndex);

}


LONG_PTR WINAPI SetWindowLongPtrA(::oswindow oswindow, int nIndex, LONG_PTR l)
{

   if(::is_null(oswindow))
   {

      return 0;

   }

   return oswindow->set_window_long_ptr(nIndex, (int)l);

}


int_bool WINAPI client_to_screen(::oswindow oswindow, POINT32 * ppoint)
{

   if(::is_null(oswindow))
   {

      return false;

   }

   return oswindow->client_to_screen(ppoint);

}


int_bool WINAPI screen_to_client(::oswindow oswindow, POINT32 * ppoint)
{

   if(::is_null(oswindow))
   {

      return false;

   }

   return oswindow->screen_to_client(ppoint);

}


int_bool WINAPI is_iconic(::oswindow oswindow)
{

   if(::is_null(oswindow))
   {

      return false;

   }

   return oswindow->is_iconic();

}


int_bool WINAPI IsWindowVisible(::oswindow oswindow)
{

   if(::is_null(oswindow))
   {

      return false;

   }

   return oswindow->is_window_visible();

}


#ifndef _UWP

#define GetWindowLong GetWindowLongA
#define SetWindowLong SetWindowLongA

#endif

CLASS_DECL_AURA int_bool is_window(oswindow oswindow);



extern "C"
CLASS_DECL_AURA i32 os_message_box_w(oswindow oswindow, const WCHAR * pszText, const WCHAR * pszCaption, u32 uFlags)
{

   return ::os_message_box(oswindow, string(pszText), string(pszCaption), uFlags);

}
