//
//  windows_unicode.cpp
//  acme
//
//  Created by Camilo Sasuke <3 Thomas Borregaard Soerensen on 14/02/22.
//  15:07
//  Copyright (c) 2022 Camilo Sasuke Thomas Borregaard Soerensen. All rights reserved.
//
#include "framework.h"
#include "windows_unicode.h"

#include <iconv.h>


#ifndef UNIVERSAL_WINDOWS

string iconv_charset_from_windows_code_page(unsigned int CodePage)
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


int
MultiByteToWideChar2(
unsigned int     CodePage,
unsigned int    dwFlags,
const_char_pointer pMultiByteStr,
int      cbMultiByte,
::wd16_character *   pWideCharStr,
int      cchWideChar)
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
           return (int) (wstr.length() + 1);
        }
        else
        {
           return (int) wstr.length();
        }
     }

     int iLen = (int) minimum(cchWideChar, wstr.length());

     if(pWideCharStr != nullptr)
     {

        ::utf_to_utf(pWideCharStr, wstr.c_str(), iLen);

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
        sIn = ansi_len(pMultiByteStr);

     else
        sIn = cbMultiByte;

     if(cchWideChar <= 0)
     {

        wd16_string wstr;

        size_t sOut = sIn * 4;

        wstr.get_buffer(sOut);

        sOut *= sizeof(::wd16_character);

        ::wd16_character * psz = (::wd16_character *) (const ::wd16_character *) wstr;


        pWideCharStr = psz;


        iconv_t iconvPlease = iconv_open("UTF-16LE", iconv_charset_from_windows_code_page(CodePage));

        size_t sOutIn = sOut;

        iconv(iconvPlease, (char **) &pMultiByteStr, &sIn, (char **) &psz, &sOut);


        iconv_close(iconvPlease);

        return (int) (((sOutIn - sOut) / sizeof(::wd16_character)) + (cbMultiByte < 0 ? 1 : 0));

     }
     else
     {

        ::wd16_character * psz = (::wd16_character *) (const ::wd16_character *) pWideCharStr;


        size_t sOut = cchWideChar * sizeof(::wd16_character);

        iconv_t iconvPlease = iconv_open("UTF-16LE", iconv_charset_from_windows_code_page(CodePage));

        size_t sOutIn = sOut;

        iconv(iconvPlease, (char **) &pMultiByteStr, &sIn, (char **) &psz, &sOut);


        iconv_close(iconvPlease);

        return (int) (((sOutIn - sOut) / sizeof(::wd16_character))  + (cbMultiByte < 0 ? 1 : 0));

     }

  }

}


int
MultiByteToWideChar2(
unsigned int     CodePage,
unsigned int    dwFlags,
const_char_pointer pMultiByteStr,
int      cbMultiByte,
::wd32_character *   pWideCharStr,
int      cchWideChar)
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
           return (int) (wstr.length() + 1);
        }
        else
        {
           return (int) wstr.length();
        }
     }

     int iLen = (int) minimum(cchWideChar, wstr.length());

     if(pWideCharStr != nullptr)
     {

        ::utf_to_utf(pWideCharStr, wstr.c_str(), iLen);

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
        sIn = ansi_len(pMultiByteStr);

     else
        sIn = cbMultiByte;

     if(cchWideChar <= 0)
     {

        wd32_string wstr;

        size_t sOut = sIn * 4;

        wstr.get_buffer(sOut);

        sOut *= sizeof(::wd32_character);

        ::wd32_character * psz = (::wd32_character *) (const ::wd32_character *) wstr;


        pWideCharStr = psz;


        iconv_t iconvPlease = iconv_open("UTF-32LE", iconv_charset_from_windows_code_page(CodePage));

        size_t sOutIn = sOut;

        iconv(iconvPlease, (char **) &pMultiByteStr, &sIn, (char **) &psz, &sOut);


        iconv_close(iconvPlease);

        return (int) (((sOutIn - sOut) / sizeof(::wd32_character)) + (cbMultiByte < 0 ? 1 : 0));

     }
     else
     {

        ::wd32_character * psz = (::wd32_character *) (const ::wd32_character *) pWideCharStr;


        size_t sOut = cchWideChar * sizeof(::wd32_character);

        iconv_t iconvPlease = iconv_open("UTF-32LE", iconv_charset_from_windows_code_page(CodePage));

        size_t sOutIn = sOut;

        iconv(iconvPlease, (char **) &pMultiByteStr, &sIn, (char **) &psz, &sOut);


        iconv_close(iconvPlease);

        return (int) (((sOutIn - sOut) / sizeof(::wd32_character))  + (cbMultiByte < 0 ? 1 : 0));

     }

  }

}


int  WideCharToMultiByte2(
unsigned int     CodePage,
unsigned int    dwFlags,
const ::wide_character *  pWideCharStr,
int      cchWideChar,
char *   pMultiByteStr,
int      cbMultiByte,
const_char_pointer pDefaultChar,
int_bool *  pUsedDefaultChar)
{

  wstring wstr(pWideCharStr, cchWideChar);

  string str;

  if(CodePage == CP_UTF8)
  {

     auto len = unichar_to_utf8_len(wstr);

     char * psz = str.get_buffer(len);

     unichar_to_utf8(psz, wstr, len);

  }
  else
  {

     size_t sIn = wstr.length() * 2;

     char * psz = str.get_buffer(sIn);


     size_t sOut = wstr.length() * 8;

     string strCodePage = iconv_charset_from_windows_code_page(CodePage);

     iconv_t iconvPlease = iconv_open(strCodePage, "UTF-16LE");

     iconv(iconvPlease, (char **) &pWideCharStr, &sIn, &psz, &sOut);


     iconv_close(iconvPlease);

  }

  str.release_buffer();

  if(cbMultiByte == 0)
  {
     if(cchWideChar < 0)
     {
        return (int) str.length() + 1;
     }
     else
     {
        return (int) str.length();
     }
  }

  int iLen = (int) minimum(cbMultiByte, str.length());

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


//CLASS_DECL_ACME string ::windows::last_error_message(unsigned int dwError)
//{
//
//   string str;
//
//   return str;
//
//}


#endif



