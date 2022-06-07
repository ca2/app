#include "framework.h"

#ifdef WINDOWS

//#include <winnls.h>

#else

//#include "acme/operating_system/cross/windows/e.h"

#endif

//namespace str
//{
//
//
//   namespace international
//   {


      bool unicode_to_multibyte(::u32 uCodePage, ansichar * pstrMultiByte, strsize nCount, const widechar * pcsz)
      {

         return WideCharToMultiByte2(uCodePage, 0, pcsz, -1, pstrMultiByte, (i32) nCount, nullptr, nullptr) != false;

      }


      bool unicode_to_multibyte(::u32 uCodePage, ansichar * pstrMultiByte, strsize iMultiByteCount, const widechar * pcsz, strsize iCount)
      {

         if (65001 == uCodePage)
         {

            unichar_to_utf8(pstrMultiByte, pcsz, iCount);

            return true;

         }

         return WideCharToMultiByte2(uCodePage, 0, pcsz, (i32) iCount, pstrMultiByte, (i32) iMultiByteCount, nullptr, nullptr) != false;

      }


      bool unicode_to_multibyte(::u32 uCodePage, string &str, const widechar * pcsz)
      {

         auto srclen = ::str().string_safe_length(pcsz);

         if (srclen <= 0)
         {

            str.Empty();

            return true;

         }

         strsize iCount = unicode_to_multibyte_count(uCodePage, pcsz, srclen);

         char * psz = str.get_string_buffer(iCount);

         if(unicode_to_multibyte(uCodePage, psz, iCount + 1, pcsz, srclen))
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


      bool unicode_to_multibyte(::u32 uCodePage, string &str, const widechar * pcsz, strsize iCount)
      {

         if(pcsz == nullptr || *pcsz == '\0' || iCount <= 0)
         {

            str.Empty();

            return true;

         }

         strsize iMultiByteCount = unicode_to_multibyte_count(uCodePage, pcsz, iCount);

         char * psz = str.get_string_buffer(iMultiByteCount);

         if(unicode_to_multibyte(uCodePage, psz, iMultiByteCount + 1, pcsz, iCount))
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


      strsize unicode_to_multibyte_count(::u32 uCodePage, const widechar * pcsz)
      {

         return unicode_to_multibyte_count(uCodePage, pcsz, ::str().string_safe_length(pcsz));

      }


      strsize unicode_to_multibyte_count(::u32 uCodePage, const widechar * pcsz, strsize iCount)
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


      strsize utf8_to_multibyte_count(::u32 uCodePage, const char * pcsz)
      {

         return WideCharToMultiByte2(uCodePage, 0, multibyte_to_unicode(uCodePage, pcsz), -1, nullptr, 0, nullptr, nullptr) - 1;

      }


      bool multibyte_to_unicode(::u32 uCodePage, widechar * pwsz, strsize iBuffer, const char * pcsz, strsize iCount)
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


      bool multibyte_to_unicode(::u32 uCodePage, widechar * pwsz, strsize iBuffer, const char * pcsz)
      {

         return multibyte_to_unicode(uCodePage, pwsz, iBuffer, pcsz, -1);

      }


      strsize multibyte_to_unicode_count(::u32 uCodePage, const char * pcsz, strsize iCount)
      {

         return MultiByteToWideChar2(uCodePage, 0, pcsz, (i32) iCount, nullptr, 0);

      }


      strsize multibyte_to_unicode_count(::u32 uCodePage, const char * pcsz)
      {

         return multibyte_to_unicode_count(uCodePage, pcsz, -1);

      }


      wstring multibyte_to_unicode(::u32 uCodePage, const char * pcsz)
      {

         return multibyte_to_unicode(uCodePage, pcsz, -1);

      }

#define ERROR_NO_UNICODE_TRANSLATION     1113L

      wstring multibyte_to_unicode(::u32 uCodePage, const char * pcsz, strsize nCount)
      {

         strsize iBuffer = multibyte_to_unicode_count(uCodePage, pcsz, nCount);

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
         if(multibyte_to_unicode(uCodePage, pwsz, iBuffer + 1, pcsz, nCount))

         {
            wstr.release_string_buffer(iBuffer);
            return wstr;
         }
         widechar push[]={0};
         return push;
      }

      wstring multibyte_to_unicode(::u32 uCodePage, const ::string & str)
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
         strsize iBuffer = multibyte_to_unicode_count(uCodePage, str, (strsize) str.get_length());
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

         if(multibyte_to_unicode(uCodePage,pwsz, iBuffer + 1, str, (strsize) str.get_length()))
         {

            wstr.release_string_buffer(iBuffer);

            return wstr;

         }

         widechar push[]={0};

         return push;

      }


      bool multibyte_to_multibyte(::u32 uCodePageDst, string & str, ::u32 uCodePageSrc, const char * pcsz)
      {

         if(uCodePageDst == uCodePageSrc)
         {
            str = pcsz;

            return true;
         }
         else
            return unicode_to_multibyte(uCodePageDst, str, multibyte_to_unicode(uCodePageSrc, pcsz));

      }

      bool multibyte_to_multibyte(::u32 uCodePageDst, char * psz, strsize nCount, ::u32 uCodePageSrc, const char * pcsz)

      {
         return unicode_to_multibyte(uCodePageDst, psz, nCount, multibyte_to_unicode(uCodePageSrc, pcsz));

      }

      bool multibyte_to_multibyte(::u32 uCodePageDst, string & str, ::u32 uCodePageSrc, const char * pcsz, strsize nCount)

      {
         return unicode_to_multibyte(uCodePageDst, str, multibyte_to_unicode(uCodePageSrc, pcsz, nCount));

      }

      //bool MultiByteToOEM(::u32 uCodePage, string & str, const char * pcsz)

      //{
      //   return multibyte_to_multibyte(::GetOEMCP(), str, uCodePage, pcsz);

      //}

      //bool MultiByteToOEM(::u32 uCodePage, string & str, const char * pcsz, strsize nCount)

      //{
      //   return multibyte_to_multibyte(::GetOEMCP(), str, uCodePage, pcsz, nCount);

      //}

      //bool OEMToMultiByte(::u32 uCodePage, string & str, const char * pcsz)

      //{
      //   return multibyte_to_multibyte(uCodePage, str, ::GetOEMCP(), pcsz);

      //}

      //bool OEMToMultiByte(::u32 uCodePage, string & str, const char * pcsz, strsize nCount)

      //{
      //   return multibyte_to_multibyte(uCodePage, str, ::GetOEMCP(), pcsz, nCount);

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

      bool multibyte_to_multibyte(::u32 uCodePageDst, memory & str, ::u32 uCodePageSrc, const char * pcsz)

      {
         return unicode_to_multibyte(uCodePageDst, str, multibyte_to_unicode(uCodePageSrc, pcsz));

      }

      bool multibyte_to_multibyte(::u32 uCodePageDst, memory & str, ::u32 uCodePageSrc, const char * pcsz, strsize nCount)

      {
         return unicode_to_multibyte(uCodePageDst, str, multibyte_to_unicode(uCodePageSrc, pcsz, nCount));

      }

      bool unicode_to_multibyte(::u32 uCodePage, memory & memstorage, const widechar * pcsz)

      {
         memstorage.set_size(unicode_to_multibyte_count(uCodePage, pcsz));

         return unicode_to_multibyte(uCodePage, (char *) memstorage.get_data(), (strsize) memstorage.get_size(), pcsz);

      }

      //bool OEMToMultiByte(::u32 uCodePage, memory & str, const char * pcsz)

      //{
      //   return multibyte_to_multibyte(uCodePage, str, ::GetOEMCP(), pcsz);

      //}

      //bool OEMToMultiByte(::u32 uCodePage, memory & str, const char * pcsz, strsize nCount)

      //{
      //   return multibyte_to_multibyte(uCodePage, str, ::GetOEMCP(), pcsz, nCount);

      //}

      ///////////////////////////////////////////////////////////////
      // ACP ( GetACP() function) conversion
      ///////////////////////////////////////////////////////////////

      string unicode_to_multibyte(::u32 uCodePage, const widechar * pcsz)

      {
         string str;
         unicode_to_multibyte(uCodePage, str, pcsz);

         return str;
      }

/*      bool UnicodeToACP(string & str, const widechar * pcsz)

      {
         return unicode_to_multibyte(g_uiACP, str, pcsz);

      }

      bool UnicodeToACP(char * pstrUnicode, strsize nCount, const widechar * pcsz)

      {
         return unicode_to_multibyte(g_uiACP, pstrUnicode, nCount, pcsz);

      }


      string UnicodeToACP(const widechar * pcsz)

      {
         return unicode_to_multibyte(CP_ACP, pcsz);

      }


      bool ACPToUnicode(widechar * pstrUnicode, strsize nCount, const char * pcsz)

      {
         return multibyte_to_unicode(g_uiACP, pstrUnicode, nCount, pcsz);

      }

      wstring  ACPToUnicode(const char * pcsz)

      {
         return multibyte_to_unicode(g_uiACP, pcsz).detach();

      }

      wstring  ACPToUnicode(const char * pcsz, strsize iSize)

      {
         return multibyte_to_unicode(g_uiACP, pcsz, iSize).detach();

      }*/

      ///////////////////////////////////////////////////////////////
      // OEM ( GetOEM() function) conversion
      ///////////////////////////////////////////////////////////////

/*      bool UnicodeToOEM(string & str, const widechar * pcsz)

      {
         return unicode_to_multibyte(CodePageOem, str, pcsz);

      }

      bool UnicodeToOEM(char * pstrUnicode, strsize nCount, const widechar * pcsz)

      {
         return unicode_to_multibyte(CodePageOem, pstrUnicode, nCount, pcsz);

      }



      bool OEMToUnicode(widechar * pstrUnicode, strsize nCount, const char * pcsz)

      {
         return multibyte_to_unicode(CodePageOem, pstrUnicode, nCount, pcsz);

      }

      wstring OEMToUnicode(const char * pcsz)

      {
         return multibyte_to_unicode(CodePageOem, pcsz).detach();

      } */

      bool unicode_to_utf8(string & str, const widechar * pcsz)

      {
         return unicode_to_multibyte(CodePageUtf8, str, pcsz);

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
         return multibyte_to_unicode(CodePageUtf8, pcsz);

      }


      wstring utf8_to_unicode(const ::string & str)
      {

         return multibyte_to_unicode(CodePageUtf8, str);

      }


      wstring utf8_to_unicode(const ::payload & payload)
      {

         return multibyte_to_unicode(CodePageUtf8, (const string &) payload);

      }


      strsize utf8_to_unicode_count(const char * pcsz, strsize count)
      {

         return multibyte_to_unicode_count(CodePageUtf8, pcsz, (strsize) count);

      }


      strsize utf8_to_unicode_count(const ::string & str)
      {

         return multibyte_to_unicode_count(CodePageUtf8, str, (strsize) str.get_length());

      }


      string multibyte_to_utf8(::u32 uCodePageSrc, const char * pcsz)
      {

         string str;

         if (!multibyte_to_multibyte(65001, str, uCodePageSrc, pcsz))

         {

            return "";

         }

         return str;

      }


      bool multibyte_to_utf8(::u32 uCodePageSrc, string & str, const char * pcsz)

      {
         return multibyte_to_multibyte(65001, str, uCodePageSrc, pcsz);

      }

      bool multibyte_to_utf8(::u32 uCodePageSrc, string & str, const char * pcsz, strsize nCount)

      {
         return multibyte_to_multibyte(65001, str, uCodePageSrc, pcsz, nCount);

      }

/*
      bool OemToUtf8(string & str, const char * pcsz)

      {
         return multibyte_to_multibyte(CP_UTF8, str, CP_OEMCP, pcsz);

      }

      bool OemToUtf8(string & str, const char * pcsz, strsize nCount)

      {
         return multibyte_to_multibyte(CP_UTF8, str, CP_OEMCP, pcsz, nCount);

      }
*/
      wstring utf8_to_unicode(const char * pcsz, strsize iCount)

      {
         return multibyte_to_unicode(65001, pcsz, (strsize) iCount);

      }

      bool utf8_to_unicode(widechar * pwsz, strsize iBuffer, const char * pcsz, strsize iCount)

      {
         return multibyte_to_unicode(65001, pwsz, (strsize) iBuffer, pcsz, (strsize) iCount);

      }

      bool utf8_to_unicode(widechar * pwsz, strsize iBuffer, const char * pcsz)

      {
         return utf8_to_unicode(pwsz, (strsize) iBuffer, pcsz, -1);

      }

      bool utf8_to_multibyte(::u32 uCodePage, string & str, const char * pcsz)

      {
         return multibyte_to_multibyte(CodePageUtf8, str, uCodePage, pcsz);

      }

      bool utf8_to_multibyte(::u32 uCodePage, string & str, const char * pcsz, strsize nCount)

      {
         return multibyte_to_multibyte(CodePageUtf8, str, uCodePage, pcsz, nCount);

      }

      bool utf8_to_multibyte(::u32 uCodePage, char * psz, strsize nCount, const char * pcsz)

      {
         return multibyte_to_multibyte(CodePageUtf8, psz, nCount, uCodePage, pcsz);

      }


      //bool AcpToUtf8(char * pstrUnicode, strsize nCount, const char * pcsz)

      //{
      //   return multibyte_to_multibyte(CP_UTF8, pstrUnicode, nCount, g_uiACP, pcsz);

      //}

      //bool AcpToUtf8(string & str, const char * pcsz, strsize iSize)

      //{
      //   return multibyte_to_multibyte(CP_UTF8, str, g_uiACP, pcsz, iSize);

      //}

//
//   } // namespace international
//
//
//} // namespace str
//
//
