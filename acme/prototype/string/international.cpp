#include "framework.h"
#include "international.h"
//#include "string.h"
//#include "international2.h"
#include "acme/prototype/prototype/memory.h"
//#include "acme/prototype/prototype/payload.h"



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


//      bool unicode_to_multibyte(unsigned int uCodePage, ::ansi_character * pstrMultiByte, character_count nCount, const ::wide_character * pcsz)
//      {
//
//         return WideCharToMultiByte2(uCodePage, 0, pcsz, -1, pstrMultiByte, (int) nCount, nullptr, nullptr) != false;
//
//      }


      bool unicode_to_multibyte(unsigned int uCodePage, ::ansi_character * pstrMultiByte, character_count iMultiByteCount, const ::scoped_wstring & scopedwstr)
      {

         if (65001 == uCodePage)
         {

            unichar_to_utf8(pstrMultiByte, scopedwstr, scopedwstr.size());

            return true;

         }

         return WideCharToMultiByte2(uCodePage, 0, scopedwstr.begin(), (int) scopedwstr.size(), pstrMultiByte, (int) iMultiByteCount, nullptr, nullptr) != false;

      }


      bool unicode_to_multibyte(unsigned int uCodePage, string &str, const ::scoped_wstring & scopedwstr)
      {

         auto srclen = scopedwstr.size();

         if (srclen <= 0)
         {

            str.empty();

            return true;

         }

         character_count iCount = unicode_to_multibyte_count(uCodePage, scopedwstr);

         char * psz = str.get_buffer(iCount);

         if(unicode_to_multibyte(uCodePage, psz, iCount + 1, scopedwstr))
         {

            str.release_buffer(iCount);

            return true;

         }
         else
         {

            str.release_buffer(0);

            str.empty();

            return false;

         }

         return true;

      }


//      bool unicode_to_multibyte(unsigned int uCodePage, string &str, const ::wide_character * pcsz, character_count iCount)
//      {
//
//         if(pcsz == nullptr || *pcsz == '\0' || iCount <= 0)
//         {
//
//            str.empty();
//
//            return true;
//
//         }
//
//         character_count iMultiByteCount = unicode_to_multibyte_count(uCodePage, { pcsz, iCount});
//
//         char * psz = str.get_buffer(iMultiByteCount);
//
//         if(unicode_to_multibyte(uCodePage, psz, iMultiByteCount + 1, { pcsz, iCount}))
//         {
//
//            str.release_buffer(iMultiByteCount);
//
//            return true;
//
//         }
//         else
//         {
//
//            str.release_buffer(0);
//
//            str.empty();
//
//            return false;
//
//         }
//
//      }


      bool unicode_to_utf8(string & str, const ::scoped_wstring & scopedwstr)
      {

         auto lenTarget = unichar_to_utf8_len(scopedwstr, scopedwstr.size());

         char * psz = str.get_buffer(lenTarget); // worst guess?!?

         character_count iLen = unichar_to_utf8(psz, scopedwstr, scopedwstr.size());

         str.release_buffer(iLen);

         return true;

      }


//      character_count unicode_to_multibyte_count(unsigned int uCodePage, const ::wide_character * pcsz)
//      {
//
//         return unicode_to_multibyte_count(uCodePage, {pcsz, string_safe_length(pcsz)});
//
//      }


      character_count unicode_to_multibyte_count(unsigned int uCodePage, const ::scoped_wstring & scopedwstr)
      {

         if (65001 == uCodePage)
         {

            return unichar_to_utf8_len(scopedwstr.begin(), scopedwstr.size());

         }
         else
         {

            return WideCharToMultiByte2(uCodePage, 0, scopedwstr.begin(), (int)scopedwstr.size(), nullptr, 0, nullptr, nullptr);

         }

      }


      character_count utf8_to_multibyte_count(unsigned int uCodePage, const ::scoped_string & scopedstr)
      {

         return WideCharToMultiByte2(uCodePage, 0, multibyte_to_unicode(uCodePage, scopedstr), -1, nullptr, 0, nullptr, nullptr) - 1;

      }


      bool multibyte_to_unicode(unsigned int uCodePage, ::wide_character * pwsz, character_count iBuffer, const_char_pointer pcsz, character_count iCount)
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

         return MultiByteToWideChar2(uCodePage, 0, pcsz, (int) iCount, pwsz, (int) iBuffer) != 0;

      }


      bool multibyte_to_unicode(unsigned int uCodePage, ::wide_character * pwsz, character_count iBuffer, const ::scoped_string & scopedstr)
      {

         return multibyte_to_unicode(uCodePage, pwsz, iBuffer, scopedstr, scopedstr.size());

      }


      character_count multibyte_to_unicode_count(unsigned int uCodePage, const ::scoped_string & scopedstr)
      {

         return MultiByteToWideChar2(uCodePage, 0, scopedstr, (int) scopedstr.size(), nullptr, 0);

      }

//
//      character_count multibyte_to_unicode_count(unsigned int uCodePage, const ::scoped_string & scopedstr)
//      {
//
//         return multibyte_to_unicode_count(uCodePage, pcsz, -1);
//
//      }


//      wstring multibyte_to_unicode(unsigned int uCodePage, const ::scoped_string & scopedstr)
//      {
//
//         return multibyte_to_unicode(uCodePage, scopedstr);
//
//      }

#define ERROR_NO_UNICODE_TRANSLATION     1113L

      wstring multibyte_to_unicode(unsigned int uCodePage, const_char_pointer psz)
      {

         character_count iBuffer = multibyte_to_unicode_count(uCodePage, psz);

         if(iBuffer == ERROR_NO_UNICODE_TRANSLATION)
         {
            ::wide_character push[]={0};
            return push;
         }
         else if(iBuffer == 0)
         {
            ::wide_character push[]={0};
            return push;
         }
         wstring wstr;
         auto pwsz = wstr.get_buffer(iBuffer);
         if(multibyte_to_unicode(uCodePage, pwsz, iBuffer + 1, psz))

         {
            wstr.release_buffer(iBuffer);
            return wstr;
         }
         ::wide_character push[]={0};
         return push;
      }


      wstring multibyte_to_unicode(unsigned int uCodePage, const ::scoped_string & scopedstr)
      {
         //if(uCodePage == CP_UTF8)
         {
           // return wstring(str);
         }
         if(scopedstr.length() <= 0)
         {
            ::wide_character push[]={0};
            return push;
         }
         character_count iBuffer = multibyte_to_unicode_count(uCodePage, scopedstr);
         if(iBuffer == ERROR_NO_UNICODE_TRANSLATION)
         {
            ::wide_character push[]={0};
            return push;
         }
         else if(iBuffer == 0)
         {
            ::wide_character push[]={0};
            return push;
         }

         wstring wstr;

         ::wide_character * pwsz = wstr.get_buffer(iBuffer);

         if(multibyte_to_unicode(uCodePage,pwsz, iBuffer + 1, scopedstr, (character_count) scopedstr.length()))
         {

            wstr.release_buffer(iBuffer);

            return wstr;

         }

         ::wide_character push[]={0};

         return push;

      }


      string CLASS_DECL_ACME multibyte_to_multibyte(unsigned int uCodePageDest, unsigned int uCodePageSrc, const ::scoped_string & scopedstr)
      {

         ::string str;

         if (!multibyte_to_multibyte(uCodePageDest, str, uCodePageSrc, scopedstr))
         {

            throw ::exception(error_encoding);

         }

         return str;

      }


      bool multibyte_to_multibyte(unsigned int uCodePageDst, string & str, unsigned int uCodePageSrc, const ::scoped_string & scopedstr)
      {

         if(uCodePageDst == uCodePageSrc)
         {
            str = scopedstr;

            return true;
         }
         else
            return unicode_to_multibyte(uCodePageDst, str, multibyte_to_unicode(uCodePageSrc, scopedstr));

      }


      bool multibyte_to_multibyte(unsigned int uCodePageDst, char * psz, character_count nCount, unsigned int uCodePageSrc, const ::scoped_string & scopedstr)
      {

         return unicode_to_multibyte(uCodePageDst, psz, nCount, multibyte_to_unicode(uCodePageSrc, scopedstr));

      }


//      bool multibyte_to_multibyte(unsigned int uCodePageDst, string & str, unsigned int uCodePageSrc, const ::scoped_string & scopedstr)
//      {
//
//         return unicode_to_multibyte(uCodePageDst, str, multibyte_to_unicode(uCodePageSrc, scopedstr));
//
//      }

      //bool MultiByteToOEM(unsigned int uCodePage, string & str, const ::scoped_string & scopedstr)

      //{
      //   return multibyte_to_multibyte(::GetOEMCP(), str, uCodePage, pcsz);

      //}

      //bool MultiByteToOEM(unsigned int uCodePage, string & str, const ::scoped_string & scopedstr, character_count nCount)

      //{
      //   return multibyte_to_multibyte(::GetOEMCP(), str, uCodePage, pcsz, nCount);

      //}

      //bool OEMToMultiByte(unsigned int uCodePage, string & str, const ::scoped_string & scopedstr)

      //{
      //   return multibyte_to_multibyte(uCodePage, str, ::GetOEMCP(), pcsz);

      //}

      //bool OEMToMultiByte(unsigned int uCodePage, string & str, const ::scoped_string & scopedstr, character_count nCount)

      //{
      //   return multibyte_to_multibyte(uCodePage, str, ::GetOEMCP(), pcsz, nCount);

      //}


      string unicode_to_utf8(const ::scoped_wstring & scopedwstr)
      {

         string str;

         unicode_to_utf8(str, scopedwstr);

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


      //bool multibyte_to_multibyte(unsigned int uCodePageDst, ::string & str, unsigned int uCodePageSrc, const ::scoped_string & scopedstr)
      //{

      //   return unicode_to_multibyte(uCodePageDst, str, multibyte_to_unicode(uCodePageSrc, scopedstr));

      //}


//      bool multibyte_to_multibyte(unsigned int uCodePageDst, memory & str, unsigned int uCodePageSrc, const ::scoped_string & scopedstr, character_count nCount)
//
//      {
//         return unicode_to_multibyte(uCodePageDst, str, multibyte_to_unicode(uCodePageSrc, pcsz, nCount));
//
//      }


      bool unicode_to_multibyte(unsigned int uCodePage, memory & memstorage, const ::scoped_wstring & scopedwstr)
      {

         memstorage.set_size(unicode_to_multibyte_count(uCodePage, scopedwstr));

         return unicode_to_multibyte(uCodePage, (char *) memstorage.begin(), (character_count) memstorage.size(), scopedwstr);

      }


      //bool OEMToMultiByte(unsigned int uCodePage, memory & str, const ::scoped_string & scopedstr)

      //{
      //   return multibyte_to_multibyte(uCodePage, str, ::GetOEMCP(), pcsz);

      //}

      //bool OEMToMultiByte(unsigned int uCodePage, memory & str, const ::scoped_string & scopedstr, character_count nCount)

      //{
      //   return multibyte_to_multibyte(uCodePage, str, ::GetOEMCP(), pcsz, nCount);

      //}

      ///////////////////////////////////////////////////////////////
      // ACP ( GetACP() function) conversion
      ///////////////////////////////////////////////////////////////

      string unicode_to_multibyte(unsigned int uCodePage, const ::scoped_wstring & scopedwstr)
      {

         string str;

         unicode_to_multibyte(uCodePage, str, scopedwstr);

         return str;

      }


/*      bool UnicodeToACP(string & str, const ::scoped_wstring & scopedwstr)

      {
         return unicode_to_multibyte(g_uiACP, str, pcsz);

      }

      bool UnicodeToACP(char * pstrUnicode, character_count nCount, const ::scoped_wstring & scopedwstr)

      {
         return unicode_to_multibyte(g_uiACP, pstrUnicode, nCount, pcsz);

      }


      string UnicodeToACP(const ::scoped_wstring & scopedwstr)

      {
         return unicode_to_multibyte(CP_ACP, pcsz);

      }


      bool ACPToUnicode(::wide_character * pstrUnicode, character_count nCount, const ::scoped_string & scopedstr)

      {
         return multibyte_to_unicode(g_uiACP, pstrUnicode, nCount, pcsz);

      }

      wstring  ACPToUnicode(const ::scoped_string & scopedstr)

      {
         return multibyte_to_unicode(g_uiACP, pcsz).detach();

      }

      wstring  ACPToUnicode(const ::scoped_string & scopedstr, character_count iSize)

      {
         return multibyte_to_unicode(g_uiACP, pcsz, iSize).detach();

      }*/

      ///////////////////////////////////////////////////////////////
      // OEM ( GetOEM() function) conversion
      ///////////////////////////////////////////////////////////////

/*      bool UnicodeToOEM(string & str, const ::scoped_wstring & scopedwstr)

      {
         return unicode_to_multibyte(CodePageOem, str, pcsz);

      }

      bool UnicodeToOEM(char * pstrUnicode, character_count nCount, const ::scoped_wstring & scopedwstr)

      {
         return unicode_to_multibyte(CodePageOem, pstrUnicode, nCount, pcsz);

      }



      bool OEMToUnicode(::wide_character * pstrUnicode, character_count nCount, const ::scoped_string & scopedstr)

      {
         return multibyte_to_unicode(CodePageOem, pstrUnicode, nCount, pcsz);

      }

      wstring OEMToUnicode(const ::scoped_string & scopedstr)

      {
         return multibyte_to_unicode(CodePageOem, pcsz).detach();

      } */

//      bool unicode_to_utf8(string & str, const ::scoped_wstring & scopedwstr)
//
//      {
//         return unicode_to_multibyte(CodePageUtf8, str, scopedwstr);
//
//      }
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


      wstring utf8_to_unicode(const ::scoped_string & scopedstr)
      {

         return multibyte_to_unicode(CodePageUtf8, scopedstr);

      }


      wstring utf8_to_unicode(const_char_pointer psz)
      {

         return multibyte_to_unicode(CodePageUtf8, psz);

      }


      wstring utf8_to_unicode(const ::payload & payload)
      {

         return multibyte_to_unicode(CodePageUtf8, (const ::scoped_string &) payload);

      }


      character_count utf8_to_unicode_count(const ::scoped_string & scopedstr)
      {

         return multibyte_to_unicode_count(CodePageUtf8, scopedstr);

      }


      character_count utf8_to_unicode_count(const_char_pointer psz)
      {

         return multibyte_to_unicode_count(CodePageUtf8, psz);

      }


      string multibyte_to_utf8(unsigned int uCodePageSrc, const ::scoped_string & scopedstr)
      {

         string str;

         if (!multibyte_to_multibyte(65001, str, uCodePageSrc, scopedstr))

         {

            return "";

         }

         return str;

      }


      bool multibyte_to_utf8(unsigned int uCodePageSrc, string & str, const ::scoped_string & scopedstr)
      {

         return multibyte_to_multibyte(65001, str, uCodePageSrc, scopedstr);

      }

//      bool multibyte_to_utf8(unsigned int uCodePageSrc, string & str, const ::scoped_string & scopedstr, character_count nCount)
//
//      {
//         return multibyte_to_multibyte(65001, str, uCodePageSrc, pcsz, nCount);
//
//      }

/*
      bool OemToUtf8(string & str, const ::scoped_string & scopedstr)

      {
         return multibyte_to_multibyte(CP_UTF8, str, CP_OEMCP, pcsz);

      }

      bool OemToUtf8(string & str, const ::scoped_string & scopedstr, character_count nCount)

      {
         return multibyte_to_multibyte(CP_UTF8, str, CP_OEMCP, pcsz, nCount);

      }
*/
//      wstring utf8_to_unicode(const ::scoped_string & scopedstr)
//      {
//
//         return multibyte_to_unicode(65001, scopedstr);
//
//      }


      bool utf8_to_unicode(::wide_character * pwsz, character_count iBuffer, const ::scoped_string & scopedstr)
      {

         return multibyte_to_unicode(65001, pwsz, (character_count) iBuffer, scopedstr);

      }


//      bool utf8_to_unicode(::wide_character * pwsz, character_count iBuffer, const ::scoped_string & scopedstr)
//      {
//
//         return utf8_to_unicode(pwsz, (character_count) iBuffer, pcsz, -1);
//
//      }


      string CLASS_DECL_ACME utf8_to_multibyte(unsigned int uCodePage, const ::scoped_string & scopedstr)
      {

         string str;

         if (!utf8_to_multibyte(uCodePage, str, scopedstr))
         {

            throw ::exception(error_encoding);

         }

         return str;

      }


      bool utf8_to_multibyte(unsigned int uCodePage, string & str, const ::scoped_string & scopedstr)
      {

         return multibyte_to_multibyte(CodePageUtf8, str, uCodePage, scopedstr);

      }


//      bool utf8_to_multibyte(unsigned int uCodePage, string & str, const ::scoped_string & scopedstr)
//      {
//
//         return multibyte_to_multibyte(CodePageUtf8, str, uCodePage, scopedstr);
//
//      }


      bool utf8_to_multibyte(unsigned int uCodePage, char * psz, character_count nCount, const ::scoped_string & scopedstr)

      {
         return multibyte_to_multibyte(CodePageUtf8, psz, nCount, uCodePage, scopedstr);

      }


      //bool AcpToUtf8(char * pstrUnicode, character_count nCount, const ::scoped_string & scopedstr)

      //{
      //   return multibyte_to_multibyte(CP_UTF8, pstrUnicode, nCount, g_uiACP, pcsz);

      //}

      //bool AcpToUtf8(string & str, const ::scoped_string & scopedstr, character_count iSize)

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
