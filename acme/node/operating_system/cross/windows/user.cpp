#include "framework.h"
#if defined(LINUX)
#include "acme/node/operating_system/linux/_user.h"
#elif defined(ANDROID)
#include "acme/node/operating_system/android/_user.h"
#elif defined(_UWP)
#include "acme/node/operating_system/uwp/_uwp.h"
#elif defined(MACOS)
//#include "acme/node/operating_system/macos/oswindow_data.h"
#elif defined(APPLE_IOS)
#include "acme/node/operating_system/ios/oswindow_data.h"
#endif
#if defined(__APPLE__) || defined(LINUX) || defined(ANDROID)
#include <iconv.h>
#else
//#include "atom/iconv/include/iconv.h"
#endif
//#include "_.h"
//#include "_windows.h"



/*
* Color Types
*/
#define CTLCOLOR_MSGBOX         0
#define CTLCOLOR_EDIT           1
#define CTLCOLOR_LISTBOX        2
#define CTLCOLOR_BTN            3
#define CTLCOLOR_DLG            4
#define CTLCOLOR_SCROLLBAR      5
#define CTLCOLOR_STATIC         6
#define CTLCOLOR_MAX            7

#define COLOR_SCROLLBAR         0
#define COLOR_BACKGROUND        1
#define COLOR_ACTIVECAPTION     2
#define COLOR_INACTIVECAPTION   3
#define COLOR_MENU              4
#define COLOR_WINDOW            5
#define COLOR_WINDOWFRAME       6
#define COLOR_MENUTEXT          7
#define COLOR_WINDOWTEXT        8
#define COLOR_CAPTIONTEXT       9
#define COLOR_ACTIVEBORDER      10
#define COLOR_INACTIVEBORDER    11
#define COLOR_APPWORKSPACE      12
#define COLOR_HIGHLIGHT         13
#define COLOR_HIGHLIGHTTEXT     14
#define COLOR_BTNFACE           15
#define COLOR_BTNSHADOW         16
#define COLOR_GRAYTEXT          17
#define COLOR_BTNTEXT           18
#define COLOR_INACTIVECAPTIONTEXT 19
#define COLOR_BTNHIGHLIGHT      20

#if(WINVER >= 0x0400)
#define COLOR_3DDKSHADOW        21
#define COLOR_3DLIGHT           22
#define COLOR_INFOTEXT          23
#define COLOR_INFOBK            24
#endif /* WINVER >= 0x0400 */

#if(WINVER >= 0x0500)
#define COLOR_HOTLIGHT          26
#define COLOR_GRADIENTACTIVECAPTION 27
#define COLOR_GRADIENTINACTIVECAPTION 28
#if(WINVER >= 0x0501)
#define COLOR_MENUHILIGHT       29
#define COLOR_MENUBAR           30
#endif /* WINVER >= 0x0501 */
#endif /* WINVER >= 0x0500 */

#if(WINVER >= 0x0400)
#define COLOR_DESKTOP           COLOR_BACKGROUND
#define COLOR_3DFACE            COLOR_BTNFACE
#define COLOR_3DSHADOW          COLOR_BTNSHADOW
#define COLOR_3DHIGHLIGHT       COLOR_BTNHIGHLIGHT
#define COLOR_3DHILIGHT         COLOR_BTNHIGHLIGHT
#define COLOR_BTNHILIGHT        COLOR_BTNHIGHLIGHT
#endif /* WINVER >= 0x0400 */







//CLASS_DECL_ACME i32 WINAPI GetSystemMetrics(i32 nIndex)
//{
//
//   switch(nIndex)
//   {
//   case SM_CXHSCROLL:
//      return 16;
//   case SM_CYHSCROLL:
//      return 16;
//   case SM_CYVSCROLL:
//      return 16;
//   case SM_CXVSCROLL:
//      return 16;
//   }
//
//   return 0;
//
//}

#

//CLASS_DECL_ACME int_bool CopyRect(RECTANGLE_I32 * prectDest, const RECTANGLE_I32 * rectSrc)
//{
//
//   prectDest->left      = rectSrc->left;
//   prectDest->top       = rectSrc->top;
//   prectDest->right     = rectSrc->right;
//   prectDest->bottom    = rectSrc->bottom;
//
//   return true;
//
//}
//
//CLASS_DECL_ACME int_bool PtInRect(const RECTANGLE_I32 * prectangle, const POINT_I32 *  ppoint)
//{
//   return ppoint->x >= prectangle->left && ppoint->x <= prectangle->right
//          && ppoint->y >= prectangle->top && ppoint->y <= prectangle->bottom;
//
//}
//
//CLASS_DECL_ACME int_bool SetRect(RECTANGLE_I32 * prectangle, i32 x1, i32 y1, i32 x2, i32 y2)
//{
//
//   prectangle->left = x1;
//   prectangle->top = y1;
//
//   prectangle->right = x2;
//   prectangle->bottom = y2;
//   return true;
//}
//
//
//CLASS_DECL_ACME int_bool SetRectEmpty(RECTANGLE_I32 * prectangle)
//{
//
//   SetRect(prectangle, 0, 0, 0, 0);
//   return true;
//}
//
//
//CLASS_DECL_ACME int_bool EqualRect(const RECTANGLE_I32 * prect1, const RECTANGLE_I32 * prect2)
//{
//   return prect1->left == prect2->left
//          &&  prect1->top == prect2->top
//          &&  prect1->right == prect2->right
//          &&  prect1->bottom == prect2->bottom;
//}
//
//
//CLASS_DECL_ACME int_bool InflateRect(RECTANGLE_I32 * prectangle, i32 x, i32 y)
//{
//   prectangle->left -= x;
//   prectangle->top -= y;
//   prectangle->right += x;
//   prectangle->bottom += y;
//   return true;
//}
//
//CLASS_DECL_ACME int_bool OffsetRect(RECTANGLE_I32 * prectangle, i32 x, i32 y)
//{
//   prectangle->left += x;
//   prectangle->top += y;
//   prectangle->right += x;
//   prectangle->bottom += y;
//   return true;
//}

/*
CLASS_DECL_ACME bool x_intersect_rect(RECTANGLE_I32 * prectangle, const RECTANGLE_I32 * prect1, const RECTANGLE_I32 * prect2)
{
   prectangle->left = maximum(prect1->left, prect2->left);
   prectangle->right = minimum(prect1->right, prect2->right);
   return prectangle->right >= prectangle->left;
}

CLASS_DECL_ACME bool y_intersect_rect(RECTANGLE_I32 * prectangle, const RECTANGLE_I32 * prect1, const RECTANGLE_I32 * prect2)
{
   prectangle->top = maximum(prect1->top, prect2->top);
   prectangle->bottom = minimum(prect1->bottom, prect2->bottom);
   return prectangle->bottom >= prectangle->top;
}
*/

//CLASS_DECL_ACME int_bool IntersectRect(RECTANGLE_I32 * prectangle, const RECTANGLE_I32 * prect1, const RECTANGLE_I32 * prect2)
//{
//   int_bool bXIntersects = x_intersect_rect(prectangle, prect1, prect2);
//   int_bool bYIntersects = y_intersect_rect(prectangle, prect1, prect2);
//   return bXIntersects && bYIntersects;
//}
//
//
//CLASS_DECL_ACME int_bool UnionRect(RECTANGLE_I32 * prectangle, const RECTANGLE_I32 * prect1, const RECTANGLE_I32 * prect2)
//{
//   prectangle->left = minimum(prect1->left, prect2->left);
//   prectangle->top = minimum(prect1->top, prect2->top);
//   prectangle->right = maximum(prect1->right, prect2->right);
//   prectangle->bottom = maximum(prect1->bottom, prect2->bottom);
//   return ((prectangle->right - prectangle->left) > 0) && ((prectangle->bottom - prectangle->top) > 0);
//}
//
//
//CLASS_DECL_ACME int_bool SubtractRect(RECTANGLE_I32 * prectangle, const RECTANGLE_I32 * prect1, const RECTANGLE_I32 * prect2)
//{
//   RECTANGLE_I32 rectangle_i32;
//   int_bool bXIntersects = x_intersect_rect(&rectangle, prect1, prect2);
//   int_bool bYIntersects = y_intersect_rect(&rectangle, prect1, prect2);
//   if(bXIntersects)
//   {
//      prectangle->left    = prectangle->left;
//      prectangle->right   = prectangle->right;
//   }
//   if(bYIntersects)
//   {
//      prectangle->top    = prectangle->top;
//      prectangle->bottom   = prectangle->bottom;
//   }
//   return bXIntersects || bYIntersects;
//}


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
//WINAPI
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
//WINAPI
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




i32  WideCharToMultiByte2(
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


CLASS_DECL_ACME string get_last_error_message(u32 dwError)
{

   string str;

   return str;

}


#endif


CLASS_DECL_ACME int_bool IsRectEmpty(const RECTANGLE_I32 * prectangle)
{

   return prectangle == nullptr || prectangle->right <= prectangle->left || prectangle->bottom <= prectangle->top;

}


//int_bool IsChild(::windowing::window * pwindowParent, ::::windowing::window * pwindowcandidateChildOrDescendant)
//{
//
//   auto puiParent = ::oswindow_interaction(oswindowParent);
//
//   auto puiChild = ::oswindow_interaction(oswindowcandidateChildOrDescendant);
//
//   if(::is_null(puiParent))
//   {
//
//      return false;
//
//   }
//
//   if(::is_null(puiChild))
//   {
//
//      return false;
//
//   }
//
//   return puiParent->is_child(puiChild);
//
//}
//
//
//oswindow WINAPI get_parent(::::windowing::window * pwindow)
//{
//
//   if(::is_null(oswindow))
//   {
//
//      return nullptr;
//
//   }
//
//   return oswindow->get_parent();
//
//}


//oswindow WINAPI SetParent(::::windowing::window * pwindow, ::::windowing::window * pwindowNewParent)
//{
//
//   if(::is_null(oswindow))
//   {
//
//      return nullptr;
//
//   }
//
//   return oswindow->set_parent(oswindowNewParent);
//
//}


//#ifndef _UWP
//
//
//int_bool show_window(::::windowing::window * pwindow, ::e_display edisplay)
//{
//
//   if(::is_null(oswindow))
//   {
//
//      return false;
//
//   }
//
//   return oswindow->show_window(edisplay);
//
//}
//
//
//#endif
//

//::i32 WINAPI GetWindowLongA(::::windowing::window * pwindow, int nIndex)
//{
//
//   if(::is_null(oswindow))
//   {
//
//      return 0;
//
//   }
//
//   return (::i32) oswindow->get_window_long_ptr(nIndex);
//
//}


//::i32 WINAPI SetWindowLongA(::::windowing::window * pwindow, int nIndex, ::i32 l)
//{
//
//   if(::is_null(oswindow))
//   {
//
//      return 0;
//
//   }
//
//   return (::i32) oswindow->set_window_long_ptr(nIndex, (::i32) l);
//
//}


//LONG_PTR WINAPI GetWindowLongPtrA(::::windowing::window * pwindow, int nIndex)
//{
//
//   if(::is_null(oswindow))
//   {
//
//      return 0;
//
//   }
//
//   return oswindow->get_window_long_ptr(nIndex);
//
//}


//LONG_PTR WINAPI SetWindowLongPtrA(::::windowing::window * pwindow, int nIndex, LONG_PTR l)
//{
//
//   if(::is_null(oswindow))
//   {
//
//      return 0;
//
//   }
//
//   return oswindow->set_window_long_ptr(nIndex, (int)l);
//
//}

//
//int_bool WINAPI client_to_screen(::::windowing::window * pwindow, POINT_I32 * ppoint)
//{
//
//   if(::is_null(oswindow))
//   {
//
//      return false;
//
//   }
//
//   return oswindow->client_to_screen(ppoint);
//
//}


//int_bool WINAPI screen_to_client(::::windowing::window * pwindow, POINT_I32 * ppoint)
//{
//
//   if(::is_null(oswindow))
//   {
//
//      return false;
//
//   }
//
//   return oswindow->screen_to_client(ppoint);
//
//}


//int_bool WINAPI is_iconic(::::windowing::window * pwindow)
//{
//
//   if(::is_null(oswindow))
//   {
//
//      return false;
//
//   }
//
//   return oswindow->is_iconic();
//
//}

//
//int_bool WINAPI IsWindowVisible(::::windowing::window * pwindow)
//{
//
//   if(::is_null(oswindow))
//   {
//
//      return false;
//
//   }
//
//   return oswindow->is_window_visible();
//
//}

//
//#ifndef _UWP
//
//#define GetWindowLong GetWindowLongA
//#define SetWindowLong SetWindowLongA
//
//#endif
//
//CLASS_DECL_ACME int_bool is_window(::windowing::window * pwindow);
//
//
//
//extern "C"
//CLASS_DECL_ACME i32 os_message_box_w(::windowing::window * pwindow, const WCHAR * pszText, const WCHAR * pszCaption, u32 uFlags)
//{
//
//   return ::os_message_box(oswindow, string(pszText), string(pszCaption), uFlags);
//
//}
