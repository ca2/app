#include "framework.h"

#ifdef WINDOWS

//#include <winnls.h>

#else

#include "acme/os/cross/windows/e.h"

#endif

namespace str
{


   namespace international
   {


      bool UnicodeToMultiByte(UINT uiCodePage, ansichar * pstrMultiByte, strsize nCount, const widechar * pcsz)
      {

         return WideCharToMultiByte2(uiCodePage, 0, pcsz, -1, pstrMultiByte, (i32) nCount, nullptr, nullptr) != FALSE;

      }


      bool UnicodeToMultiByte(UINT uiCodePage, ansichar * pstrMultiByte, strsize iMultiByteCount, const widechar * pcsz, strsize iCount)
      {

         if (CP_UTF8 == uiCodePage)
         {

            unichar_to_utf8(pstrMultiByte, pcsz, iCount);

            return true;

         }

         return WideCharToMultiByte2(uiCodePage, 0, pcsz, (i32) iCount, pstrMultiByte, (i32) iMultiByteCount, nullptr, nullptr) != FALSE;

      }


      bool UnicodeToMultiByte(UINT uiCodePage, string &str, const widechar * pcsz)
      {

         auto srclen = ::str::string_safe_length(pcsz);

         if (srclen <= 0)
         {

            str.Empty();

            return true;

         }

         strsize iCount = UnicodeToMultiByteCount(uiCodePage, pcsz, srclen);

         LPSTR psz = str.get_string_buffer(iCount);

         if(UnicodeToMultiByte(uiCodePage, psz, iCount + 1, pcsz, srclen))
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


      bool UnicodeToMultiByte(UINT uiCodePage, string &str, const widechar * pcsz, strsize iCount)
      {

         if(pcsz == nullptr || *pcsz == '\0' || iCount <= 0)
         {

            str.Empty();

            return true;

         }

         strsize iMultiByteCount = UnicodeToMultiByteCount(uiCodePage, pcsz, iCount);

         LPSTR psz = str.get_string_buffer(iMultiByteCount);

         if(UnicodeToMultiByte(uiCodePage, psz, iMultiByteCount + 1, pcsz, iCount))
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

         LPSTR psz = str.get_string_buffer(iCount * 4); // worst guess?!?

         strsize iLen = unichar_to_utf8(psz, pcsz, iCount);

         str.release_string_buffer(iLen);

         return true;

      }


      strsize UnicodeToMultiByteCount(UINT uiCodePage, const widechar * pcsz)
      {

         return UnicodeToMultiByteCount(uiCodePage, pcsz, ::str::string_safe_length(pcsz));

      }


      strsize UnicodeToMultiByteCount(UINT uiCodePage, const widechar * pcsz, strsize iCount)
      {

         if (CP_UTF8 == uiCodePage)
         {

            return unichar_to_utf8_len(pcsz, iCount);

         }
         else
         {

            if (iCount == -1)
            {

               return WideCharToMultiByte2(uiCodePage, 0, pcsz, (i32)iCount, nullptr, 0, nullptr, nullptr) - 1;

            }
            else
            {

               return WideCharToMultiByte2(uiCodePage, 0, pcsz, (i32)iCount, nullptr, 0, nullptr, nullptr);

            }

         }

      }


      strsize Utf8ToMultiByteCount(UINT uiCodePage, const char * pcsz)
      {

         return WideCharToMultiByte2(uiCodePage, 0, MultiByteToUnicode(uiCodePage, pcsz), -1, nullptr, 0, nullptr, nullptr) - 1;

      }


      bool MultiByteToUnicode(UINT uiCodePage, widechar * pwsz, strsize iBuffer, const char * pcsz, strsize iCount)
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

         return MultiByteToWideChar2(uiCodePage, 0, pcsz, (i32) iCount, pwsz, (i32) iBuffer) != 0;

      }


      bool MultiByteToUnicode(UINT uiCodePage, widechar * pwsz, strsize iBuffer, const char * pcsz)
      {

         return MultiByteToUnicode(uiCodePage, pwsz, iBuffer, pcsz, -1);

      }


      strsize MultiByteToUnicodeCount(UINT uiCodePage, const char * pcsz, strsize iCount)
      {

         return MultiByteToWideChar2(uiCodePage, 0, pcsz, (i32) iCount, nullptr, 0);

      }


      strsize MultiByteToUnicodeCount(UINT uiCodePage, const char * pcsz)
      {

         return MultiByteToUnicodeCount(uiCodePage, pcsz, -1);

      }


      wstring MultiByteToUnicode(UINT uiCodePage, const char * pcsz)
      {

         return MultiByteToUnicode(uiCodePage, pcsz, -1);

      }


      wstring MultiByteToUnicode(UINT uiCodePage, const char * pcsz, strsize nCount)
      {

         strsize iBuffer = MultiByteToUnicodeCount(uiCodePage, pcsz, nCount);

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
         if(MultiByteToUnicode(uiCodePage, pwsz, iBuffer + 1, pcsz, nCount))

         {
            wstr.release_string_buffer(iBuffer);
            return wstr;
         }
         widechar push[]={0};
         return push;
      }

      wstring MultiByteToUnicode(UINT uiCodePage, const string & str)
      {
         //if(uiCodePage == CP_UTF8)
         {
           // return wstring(str);
         }
         if(str.length() <= 0)
         {
            widechar push[]={0};
            return push;
         }
         strsize iBuffer = MultiByteToUnicodeCount(uiCodePage, str, (strsize) str.get_length());
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

         if(MultiByteToUnicode(uiCodePage,pwsz, iBuffer + 1, str, (strsize) str.get_length()))
         {

            wstr.release_string_buffer(iBuffer);

            return wstr;

         }

         widechar push[]={0};

         return push;

      }


      bool MultiByteToMultiByte(UINT uiCodePageDst, string & str, UINT uiCodePageSrc, const char * pcsz)
      {

         if(uiCodePageDst == uiCodePageSrc)
         {
            str = pcsz;

            return true;
         }
         else
            return UnicodeToMultiByte(uiCodePageDst, str, MultiByteToUnicode(uiCodePageSrc, pcsz));

      }

      bool MultiByteToMultiByte(UINT uiCodePageDst, char * psz, strsize nCount, UINT uiCodePageSrc, const char * pcsz)

      {
         return UnicodeToMultiByte(uiCodePageDst, psz, nCount, MultiByteToUnicode(uiCodePageSrc, pcsz));

      }

      bool MultiByteToMultiByte(UINT uiCodePageDst, string & str, UINT uiCodePageSrc, const char * pcsz, strsize nCount)

      {
         return UnicodeToMultiByte(uiCodePageDst, str, MultiByteToUnicode(uiCodePageSrc, pcsz, nCount));

      }

      //bool MultiByteToOEM(UINT uiCodePage, string & str, const char * pcsz)

      //{
      //   return MultiByteToMultiByte(::GetOEMCP(), str, uiCodePage, pcsz);

      //}

      //bool MultiByteToOEM(UINT uiCodePage, string & str, const char * pcsz, strsize nCount)

      //{
      //   return MultiByteToMultiByte(::GetOEMCP(), str, uiCodePage, pcsz, nCount);

      //}

      //bool OEMToMultiByte(UINT uiCodePage, string & str, const char * pcsz)

      //{
      //   return MultiByteToMultiByte(uiCodePage, str, ::GetOEMCP(), pcsz);

      //}

      //bool OEMToMultiByte(UINT uiCodePage, string & str, const char * pcsz, strsize nCount)

      //{
      //   return MultiByteToMultiByte(uiCodePage, str, ::GetOEMCP(), pcsz, nCount);

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

      bool MultiByteToMultiByte(UINT uiCodePageDst, memory & str, UINT uiCodePageSrc, const char * pcsz)

      {
         return UnicodeToMultiByte(uiCodePageDst, str, MultiByteToUnicode(uiCodePageSrc, pcsz));

      }

      bool MultiByteToMultiByte(UINT uiCodePageDst, memory & str, UINT uiCodePageSrc, const char * pcsz, strsize nCount)

      {
         return UnicodeToMultiByte(uiCodePageDst, str, MultiByteToUnicode(uiCodePageSrc, pcsz, nCount));

      }

      bool UnicodeToMultiByte(UINT uiCodePage, memory & memstorage, const widechar * pcsz)

      {
         memstorage.set_size(UnicodeToMultiByteCount(uiCodePage, pcsz));

         return UnicodeToMultiByte(uiCodePage, (char *) memstorage.get_data(), (strsize) memstorage.get_size(), pcsz);

      }

      //bool OEMToMultiByte(UINT uiCodePage, memory & str, const char * pcsz)

      //{
      //   return MultiByteToMultiByte(uiCodePage, str, ::GetOEMCP(), pcsz);

      //}

      //bool OEMToMultiByte(UINT uiCodePage, memory & str, const char * pcsz, strsize nCount)

      //{
      //   return MultiByteToMultiByte(uiCodePage, str, ::GetOEMCP(), pcsz, nCount);

      //}

      ///////////////////////////////////////////////////////////////
      // ACP ( GetACP() function) conversion
      ///////////////////////////////////////////////////////////////

      string UnicodeToMultiByte(UINT uiCodePage, const widechar * pcsz)

      {
         string str;
         UnicodeToMultiByte(uiCodePage, str, pcsz);

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


      wstring utf8_to_unicode(const string & str)
      {

         return MultiByteToUnicode(CodePageUtf8, str);

      }


      wstring utf8_to_unicode(const var & var)
      {

         return MultiByteToUnicode(CodePageUtf8, (const string &) var);

      }


      strsize utf8_to_unicode_count(const char * pcsz, strsize count)
      {

         return MultiByteToUnicodeCount(CodePageUtf8, pcsz, (strsize) count);

      }


      strsize utf8_to_unicode_count(const string & str)
      {

         return MultiByteToUnicodeCount(CodePageUtf8, str, (strsize) str.get_length());

      }


      string multibyte_to_utf8(UINT uiCodePageSrc, const char * pcsz)
      {

         string str;

         if (!MultiByteToMultiByte(CP_UTF8, str, uiCodePageSrc, pcsz))

         {

            return "";

         }

         return str;

      }


      bool multibyte_to_utf8(UINT uiCodePageSrc, string & str, const char * pcsz)

      {
         return MultiByteToMultiByte(CP_UTF8, str, uiCodePageSrc, pcsz);

      }

      bool multibyte_to_utf8(UINT uiCodePageSrc, string & str, const char * pcsz, strsize nCount)

      {
         return MultiByteToMultiByte(CP_UTF8, str, uiCodePageSrc, pcsz, nCount);

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
         return MultiByteToUnicode(CP_UTF8, pcsz, (strsize) iCount);

      }

      bool utf8_to_unicode(widechar * pwsz, strsize iBuffer, const char * pcsz, strsize iCount)

      {
         return MultiByteToUnicode(CP_UTF8, pwsz, (strsize) iBuffer, pcsz, (strsize) iCount);

      }

      bool utf8_to_unicode(widechar * pwsz, strsize iBuffer, const char * pcsz)

      {
         return utf8_to_unicode(pwsz, (strsize) iBuffer, pcsz, -1);

      }

      bool utf8_to_multibyte(UINT uiCodePage, string & str, const char * pcsz)

      {
         return MultiByteToMultiByte(CodePageUtf8, str, uiCodePage, pcsz);

      }

      bool utf8_to_multibyte(UINT uiCodePage, string & str, const char * pcsz, strsize nCount)

      {
         return MultiByteToMultiByte(CodePageUtf8, str, uiCodePage, pcsz, nCount);

      }

      bool utf8_to_multibyte(UINT uiCodePage, char * psz, strsize nCount, const char * pcsz)

      {
         return MultiByteToMultiByte(CodePageUtf8, psz, nCount, uiCodePage, pcsz);

      }


      //bool AcpToUtf8(LPTSTR pstrUnicode, strsize nCount, const char * pcsz)

      //{
      //   return MultiByteToMultiByte(CP_UTF8, pstrUnicode, nCount, g_uiACP, pcsz);

      //}

      //bool AcpToUtf8(string & str, const char * pcsz, strsize iSize)

      //{
      //   return MultiByteToMultiByte(CP_UTF8, str, g_uiACP, pcsz, iSize);

      //}


   } // namespace international


} // namespace str


