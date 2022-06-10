//
//  windows_unicode.cpp
//  acme
//
//  Created by Camilo Sasuke <3 Thomas Borregaard Sørensen on 14/02/22.
//  15:07
//  Copyright © 2022 Camilo Sasuke Tsumanuma. All rights reserved.
//
#include "framework.h"
#include "windows_unicode.h"
#include <iconv.h>


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

        ::str().utf_to_utf(pWideCharStr, wstr.c_str(), iLen);

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

        ::str().utf_to_utf(pWideCharStr, wstr.c_str(), iLen);

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



