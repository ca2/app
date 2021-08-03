#include "framework.h"

#ifdef WINDOWS

//#include <winnls.h>

#else

//#include "acme/os/cross/windows/e.h"

#endif

namespace str
{


   namespace international
   {


      bool UnicodeToMultiByte(::u32 uCodePage, ansichar * pstrMultiByte, strsize nCount, const widechar * pcsz)
      {

         return WideCharToMultiByte2(uCodePage, 0, pcsz, -1, pstrMultiByte, (i32) nCount, nullptr, nullptr) != false;

      }


      bool UnicodeToMultiByte(::u32 uCodePage, ansichar * pstrMultiByte, strsize iMultiByteCount, const widechar * pcsz, strsize iCount)
      {

         if (65001 == uCodePage)
         {

            unichar_to_utf8(pstrMultiByte, pcsz, iCount);

            return true;

         }

         return WideCharToMultiByte2(uCodePage, 0, pcsz, (i32) iCount, pstrMultiByte, (i32) iMultiByteCount, nullptr, nullptr) != false;

      }


      bool UnicodeToMultiByte(::u32 uCodePage, string &str, const widechar * pcsz)
      {

         auto srclen = ::str::string_safe_length(pcsz);

         if (srclen <= 0)
         {

            str.Empty();

            return true;

         }

         strsize iCount = UnicodeToMultiByteCount(uCodePage, pcsz, srclen);

         char * psz = str.get_string_buffer(iCount);

         if(UnicodeToMultiByte(uCodePage, psz, iCount + 1, pcsz, srclen))
         {

            str.release_string_buffer(iCount);

            return true;

         }
         else
         {

            str.release_string_buffer(0);

            str.Empty();

            return false;

         }

         return true;

      }


      bool UnicodeToMultiByte(::u32 uCodePage, string &str, const widechar * pcsz, strsize iCount)
      {

         if(pcsz == nullptr || *pcsz == '\0' || iCount <= 0)
         {

            str.Empty();

            return true;

         }

         strsize iMultiByteCount = UnicodeToMultiByteCount(uCodePage, pcsz, iCount);

         char * psz = str.get_string_buffer(iMultiByteCount);

         if(UnicodeToMultiByte(uCodePage, psz, iMultiByteCount + 1, pcsz, iCount))
         {

            str.release_string_buffer(iMultiByteCount);

            return true;

         }
         else
         {

            str.release_string_buffer(0);

            str.Empty();

            return false;

         }

      }


      bool unicode_to_utf8(string & str, const widechar * pcsz, strsize iCount)
      {

         char * psz = str.get_string_buffer(iCount * 4); // worst guess?!?

         strsize iLen = unichar_to_utf8(psz, pcsz, iCount);

         str.release_string_buffer(iLen);

         return true;

      }


      strsize UnicodeToMultiByteCount(::u32 uCodePage, const widechar * pcsz)
      {

         return UnicodeToMultiByteCount(uCodePage, pcsz, ::str::string_safe_length(pcsz));

      }


      strsize UnicodeToMultiByteCount(::u32 uCodePage, const widechar * pcsz, strsize iCount)
      {

         if (65001 == uCodePage)
         {

            return unichar_to_utf8_len(pcsz, iCount);

         }
         else
         {

            if (iCount == -1)
            {

               return WideCharToMultiByte2(uCodePage, 0, pcsz, (i32)iCount, nullptr, 0, nullptr, nullptr) - 1;

            }
            else
            {

               return WideCharToMultiByte2(uCodePage, 0, pcsz, (i32)iCount, nullptr, 0, nullptr, nullptr);

            }

         }

      }


      strsize Utf8ToMultiByteCount(::u32 uCodePage, const char * pcsz)
      {

         return WideCharToMultiByte2(uCodePage, 0, MultiByteToUnicode(uCodePage, pcsz), -1, nullptr, 0, nullptr, nullptr) - 1;

      }


      bool MultiByteToUnicode(::u32 uCodePage, widechar * pwsz, strsize iBuffer, const char * pcsz, strsize iCount)
      {

         if(pwsz == nullptr)
         {
            if(iBuffer > 0)
               return false;
            else if(pcsz != nullptr)

               return false;
            else if(iCount > 0)
               return false;
            else
               return true;
         }

         return MultiByteToWideChar2(uCodePage, 0, pcsz, (i32) iCount, pwsz, (i32) iBuffer) != 0;

      }


      bool MultiByteToUnicode(::u32 uCodePage, widechar * pwsz, strsize iBuffer, const char * pcsz)
      {

         return MultiByteToUnicode(uCodePage, pwsz, iBuffer, pcsz, -1);

      }


      strsize MultiByteToUnicodeCount(::u32 uCodePage, const char * pcsz, strsize iCount)
      {

         return MultiByteToWideChar2(uCodePage, 0, pcsz, (i32) iCount, nullptr, 0);

      }


      strsize MultiByteToUnicodeCount(::u32 uCodePage, const char * pcsz)
      {

         return MultiByteToUnicodeCount(uCodePage, pcsz, -1);

      }


      wstring MultiByteToUnicode(::u32 uCodePage, const char * pcsz)
      {

         return MultiByteToUnicode(uCodePage, pcsz, -1);

      }

#define ERROR_NO_UNICODE_TRANSLATION     1113L

      wstring MultiByteToUnicode(::u32 uCodePage, const char * pcsz, strsize nCount)
      {

         strsize iBuffer = MultiByteToUnicodeCount(uCodePage, pcsz, nCount);

         if(iBuffer == ERROR_NO_UNICODE_TRANSLATION)
         {
            widechar push[]={0};
            return push;
         }
         else if(iBuffer == 0)
         {
            widechar push[]={0};
            return push;
         }
         wstring wstr;
         auto pwsz = wstr.get_string_buffer(iBuffer);
         if(MultiByteToUnicode(uCodePage, pwsz, iBuffer + 1, pcsz, nCount))

         {
            wstr.release_string_buffer(iBuffer);
            return wstr;
         }
         widechar push[]={0};
         return push;
      }

      wstring MultiByteToUnicode(::u32 uCodePage, const ::string & str)
      {
         //if(uCodePage == CP_UTF8)
         {
           // return wstring(str);
         }
         if(str.length() <= 0)
         {
            widechar push[]={0};
            return push;
         }
         strsize iBuffer = MultiByteToUnicodeCount(uCodePage, str, (strsize) str.get_length());
         if(iBuffer == ERROR_NO_UNICODE_TRANSLATION)
         {
            widechar push[]={0};
            return push;
         }
         else if(iBuffer == 0)
         {
            widechar push[]={0};
            return push;
         }

         wstring wstr;

         widechar * pwsz = wstr.get_string_buffer(iBuffer);

         if(MultiByteToUnicode(uCodePage,pwsz, iBuffer + 1, str, (strsize) str.get_length()))
         {

            wstr.release_string_buffer(iBuffer);

            return wstr;

         }

         widechar push[]={0};

         return push;

      }


      bool MultiByteToMultiByte(::u32 uCodePageDst, string & str, ::u32 uCodePageSrc, const char * pcsz)
      {

         if(uCodePageDst == uCodePageSrc)
         {
            str = pcsz;

            return true;
         }
         else
            return UnicodeToMultiByte(uCodePageDst, str, MultiByteToUnicode(uCodePageSrc, pcsz));

      }

      bool MultiByteToMultiByte(::u32 uCodePageDst, char * psz, strsize nCount, ::u32 uCodePageSrc, const char * pcsz)

      {
         return UnicodeToMultiByte(uCodePageDst, psz, nCount, MultiByteToUnicode(uCodePageSrc, pcsz));

      }

      bool MultiByteToMultiByte(::u32 uCodePageDst, string & str, ::u32 uCodePageSrc, const char * pcsz, strsize nCount)

      {
         return UnicodeToMultiByte(uCodePageDst, str, MultiByteToUnicode(uCodePageSrc, pcsz, nCount));

      }

      //bool MultiByteToOEM(::u32 uCodePage, string & str, const char * pcsz)

      //{
      //   return MultiByteToMultiByte(::GetOEMCP(), str, uCodePage, pcsz);

      //}

      //bool MultiByteToOEM(::u32 uCodePage, string & str, const char * pcsz, strsize nCount)

      //{
      //   return MultiByteToMultiByte(::GetOEMCP(), str, uCodePage, pcsz, nCount);

      //}

      //bool OEMToMultiByte(::u32 uCodePage, string & str, const char * pcsz)

      //{
      //   return MultiByteToMultiByte(uCodePage, str, ::GetOEMCP(), pcsz);

      //}

      //bool OEMToMultiByte(::u32 uCodePage, string & str, const char * pcsz, strsize nCount)

      //{
      //   return MultiByteToMultiByte(uCodePage, str, ::GetOEMCP(), pcsz, nCount);

      //}

      string unicode_to_utf8(const widechar * pcsz)

      {
         string str;
         unicode_to_utf8(str, pcsz);

         return str;
      }
//
//#ifndef WINDOWS
//
//      string unicode_to_utf8(const wchar_t * pcsz)
//
//      {
//         string str;
//         unicode_to_utf8(str, pcsz);
//
//         return str;
//      }
//
//#endif

      bool MultiByteToMultiByte(::u32 uCodePageDst, memory & str, ::u32 uCodePageSrc, const char * pcsz)

      {
         return UnicodeToMultiByte(uCodePageDst, str, MultiByteToUnicode(uCodePageSrc, pcsz));

      }

      bool MultiByteToMultiByte(::u32 uCodePageDst, memory & str, ::u32 uCodePageSrc, const char * pcsz, strsize nCount)

      {
         return UnicodeToMultiByte(uCodePageDst, str, MultiByteToUnicode(uCodePageSrc, pcsz, nCount));

      }

      bool UnicodeToMultiByte(::u32 uCodePage, memory & memstorage, const widechar * pcsz)

      {
         memstorage.set_size(UnicodeToMultiByteCount(uCodePage, pcsz));

         return UnicodeToMultiByte(uCodePage, (char *) memstorage.get_data(), (strsize) memstorage.get_size(), pcsz);

      }

      //bool OEMToMultiByte(::u32 uCodePage, memory & str, const char * pcsz)

      //{
      //   return MultiByteToMultiByte(uCodePage, str, ::GetOEMCP(), pcsz);

      //}

      //bool OEMToMultiByte(::u32 uCodePage, memory & str, const char * pcsz, strsize nCount)

      //{
      //   return MultiByteToMultiByte(uCodePage, str, ::GetOEMCP(), pcsz, nCount);

      //}

      ///////////////////////////////////////////////////////////////
      // ACP ( GetACP() function) conversion
      ///////////////////////////////////////////////////////////////

      string UnicodeToMultiByte(::u32 uCodePage, const widechar * pcsz)

      {
         string str;
         UnicodeToMultiByte(uCodePage, str, pcsz);

         return str;
      }

/*      bool UnicodeToACP(string & str, const widechar * pcsz)

      {
         return UnicodeToMultiByte(g_uiACP, str, pcsz);

      }

      bool UnicodeToACP(char * pstrUnicode, strsize nCount, const widechar * pcsz)

      {
         return UnicodeToMultiByte(g_uiACP, pstrUnicode, nCount, pcsz);

      }


      string UnicodeToACP(const widechar * pcsz)

      {
         return UnicodeToMultiByte(CP_ACP, pcsz);

      }


      bool ACPToUnicode(widechar * pstrUnicode, strsize nCount, const char * pcsz)

      {
         return MultiByteToUnicode(g_uiACP, pstrUnicode, nCount, pcsz);

      }

      wstring  ACPToUnicode(const char * pcsz)

      {
         return MultiByteToUnicode(g_uiACP, pcsz).detach();

      }

      wstring  ACPToUnicode(const char * pcsz, strsize iSize)

      {
         return MultiByteToUnicode(g_uiACP, pcsz, iSize).detach();

      }*/

      ///////////////////////////////////////////////////////////////
      // OEM ( GetOEM() function) conversion
      ///////////////////////////////////////////////////////////////

/*      bool UnicodeToOEM(string & str, const widechar * pcsz)

      {
         return UnicodeToMultiByte(CodePageOem, str, pcsz);

      }

      bool UnicodeToOEM(char * pstrUnicode, strsize nCount, const widechar * pcsz)

      {
         return UnicodeToMultiByte(CodePageOem, pstrUnicode, nCount, pcsz);

      }



      bool OEMToUnicode(widechar * pstrUnicode, strsize nCount, const char * pcsz)

      {
         return MultiByteToUnicode(CodePageOem, pstrUnicode, nCount, pcsz);

      }

      wstring OEMToUnicode(const char * pcsz)

      {
         return MultiByteToUnicode(CodePageOem, pcsz).detach();

      } */

      bool unicode_to_utf8(string & str, const widechar * pcsz)

      {
         return UnicodeToMultiByte(CodePageUtf8, str, pcsz);

      }
//
//#ifndef WINDOWS
//
//      bool unicode_to_utf8(string & str, const wchar_t * pcsz)
//
//      {
//
//         str = wd32_to_ansi(pcsz, wcslen(pcsz));
//
//
//         return true;
//
//      }
//
//#endif


      wstring utf8_to_unicode(const char * pcsz)
      {
         return MultiByteToUnicode(CodePageUtf8, pcsz);

      }


      wstring utf8_to_unicode(const ::string & str)
      {

         return MultiByteToUnicode(CodePageUtf8, str);

      }


      wstring utf8_to_unicode(const ::payload & payload)
      {

         return MultiByteToUnicode(CodePageUtf8, (const string &) payload);

      }


      strsize utf8_to_unicode_count(const char * pcsz, strsize count)
      {

         return MultiByteToUnicodeCount(CodePageUtf8, pcsz, (strsize) count);

      }


      strsize utf8_to_unicode_count(const ::string & str)
      {

         return MultiByteToUnicodeCount(CodePageUtf8, str, (strsize) str.get_length());

      }


      string multibyte_to_utf8(::u32 uCodePageSrc, const char * pcsz)
      {

         string str;

         if (!MultiByteToMultiByte(65001, str, uCodePageSrc, pcsz))

         {

            return "";

         }

         return str;

      }


      bool multibyte_to_utf8(::u32 uCodePageSrc, string & str, const char * pcsz)

      {
         return MultiByteToMultiByte(65001, str, uCodePageSrc, pcsz);

      }

      bool multibyte_to_utf8(::u32 uCodePageSrc, string & str, const char * pcsz, strsize nCount)

      {
         return MultiByteToMultiByte(65001, str, uCodePageSrc, pcsz, nCount);

      }

/*
      bool OemToUtf8(string & str, const char * pcsz)

      {
         return MultiByteToMultiByte(CP_UTF8, str, CP_OEMCP, pcsz);

      }

      bool OemToUtf8(string & str, const char * pcsz, strsize nCount)

      {
         return MultiByteToMultiByte(CP_UTF8, str, CP_OEMCP, pcsz, nCount);

      }
*/
      wstring utf8_to_unicode(const char * pcsz, strsize iCount)

      {
         return MultiByteToUnicode(65001, pcsz, (strsize) iCount);

      }

      bool utf8_to_unicode(widechar * pwsz, strsize iBuffer, const char * pcsz, strsize iCount)

      {
         return MultiByteToUnicode(65001, pwsz, (strsize) iBuffer, pcsz, (strsize) iCount);

      }

      bool utf8_to_unicode(widechar * pwsz, strsize iBuffer, const char * pcsz)

      {
         return utf8_to_unicode(pwsz, (strsize) iBuffer, pcsz, -1);

      }

      bool utf8_to_multibyte(::u32 uCodePage, string & str, const char * pcsz)

      {
         return MultiByteToMultiByte(CodePageUtf8, str, uCodePage, pcsz);

      }

      bool utf8_to_multibyte(::u32 uCodePage, string & str, const char * pcsz, strsize nCount)

      {
         return MultiByteToMultiByte(CodePageUtf8, str, uCodePage, pcsz, nCount);

      }

      bool utf8_to_multibyte(::u32 uCodePage, char * psz, strsize nCount, const char * pcsz)

      {
         return MultiByteToMultiByte(CodePageUtf8, psz, nCount, uCodePage, pcsz);

      }


      //bool AcpToUtf8(char * pstrUnicode, strsize nCount, const char * pcsz)

      //{
      //   return MultiByteToMultiByte(CP_UTF8, pstrUnicode, nCount, g_uiACP, pcsz);

      //}

      //bool AcpToUtf8(string & str, const char * pcsz, strsize iSize)

      //{
      //   return MultiByteToMultiByte(CP_UTF8, str, g_uiACP, pcsz, iSize);

      //}


   } // namespace international


} // namespace str


