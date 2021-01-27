#pragma once


class ::payload;


namespace str
{


   namespace international
   {


      enum ECodePage
      {
         CodePageShiftJIS = 932,
         CodePageLatin1 = 1252,
#ifdef WINDOWS
         CodePageUtf8 = CP_UTF8,
         CodePageAnsi = CP_ACP,
         CodePageOem = CP_OEMCP,
#else
         CodePageUtf8 = 65001,
         CodePageAnsi = 10,
         CodePageOem = 11
#endif
      };


      bool CLASS_DECL_ACME UnicodeToMultiByte(::u32 uCodePage, char * psz, strsize nCount, const widechar * pcsz);

      bool CLASS_DECL_ACME UnicodeToMultiByte(::u32 uCodePage, char * psz, strsize iBuffer, const widechar * lpcsz, strsize iCount);

      strsize   CLASS_DECL_ACME UnicodeToMultiByteCount(::u32 uCodePage, const widechar * pcsz);

      strsize   CLASS_DECL_ACME UnicodeToMultiByteCount(::u32 uCodePage, const widechar * pcsz, strsize iCount);

      bool CLASS_DECL_ACME UnicodeToMultiByte(::u32 uCodePage, string & str, const widechar * pcsz);

      bool CLASS_DECL_ACME UnicodeToMultiByte(::u32 uCodePage, string & str, const widechar * pcsz, strsize iCount);

      string CLASS_DECL_ACME UnicodeToMultiByte(::u32 uCodePage, const widechar * pcsz);

      bool CLASS_DECL_ACME MultiByteToUnicode(::u32 uCodePage, widechar * pwsz, strsize iBuffer, const char  * lpcsz, strsize iCount);

      bool CLASS_DECL_ACME MultiByteToUnicode(::u32 uCodePage, widechar * pwsz, strsize nCount, const char * lpcsz);

      CLASS_DECL_ACME wstring MultiByteToUnicode(::u32 uCodePage, const char * pcsz, strsize nCount);

      CLASS_DECL_ACME wstring MultiByteToUnicode(::u32 uCodePage, const string & str);
      strsize  CLASS_DECL_ACME MultiByteToUnicodeCount(::u32 uCodePage, const char * pcsz);

      strsize  CLASS_DECL_ACME MultiByteToUnicodeCount(::u32 uCodePage, const char * pcsz, strsize iCount);

      CLASS_DECL_ACME wstring MultiByteToUnicode(::u32 uCodePage, const char * pcsz);

      bool CLASS_DECL_ACME MultiByteToMultiByte(::u32 uCodePageDest, string & str, ::u32 uCodePageSrc, const char * pcsz);

      bool CLASS_DECL_ACME MultiByteToMultiByte(::u32 uCodePageDest, string & str, ::u32 uCodePageSrc, const char * pcsz, strsize nCount);

      bool CLASS_DECL_ACME MultiByteToMultiByte(::u32 uCodePageDest, char * psz, strsize nCount, ::u32 uCodePageSrc, const char * lpcsz);

      string CLASS_DECL_ACME multibyte_to_utf8(::u32 uCodePageSrc, const char * pcsz);

      bool CLASS_DECL_ACME multibyte_to_utf8(::u32 uCodePageSrc, string & str, const char * pcsz);

      bool CLASS_DECL_ACME multibyte_to_utf8(::u32 uCodePageSrc, string & str, const char * pcsz, strsize nCount);

      strsize   CLASS_DECL_ACME Utf8ToMultiByteCount(::u32 uCodePage, const char * pcsz);

      bool CLASS_DECL_ACME utf8_to_multibyte(::u32 uCodePage, string & str, const char * pcsz);

      bool CLASS_DECL_ACME utf8_to_multibyte(::u32 uCodePage, string & str, const char * pcsz, strsize nCount);

      bool CLASS_DECL_ACME utf8_to_multibyte(::u32 uCodePageSrc, char * psz, strsize nCount, const char * lpcsz);

      bool CLASS_DECL_ACME unicode_to_utf8(string & str, const widechar * pcsz);

      bool CLASS_DECL_ACME unicode_to_utf8(string & str, const wchar_t * pcsz);

      CLASS_DECL_ACME wstring utf8_to_unicode(const string & str);
      CLASS_DECL_ACME wstring utf8_to_unicode(const char * pcsz, strsize iCount);

      bool CLASS_DECL_ACME unicode_to_utf8(string & str, const widechar * pcsz, strsize iCount);

      string CLASS_DECL_ACME unicode_to_utf8(const widechar * pcsz);
      string CLASS_DECL_ACME unicode_to_utf8(const wchar_t * pcsz);

      CLASS_DECL_ACME string UnicodeToMultiByte(::u32 uCodePage, const widechar * pcsz);

      CLASS_DECL_ACME bool unicode_to_utf8(string & str, const widechar * pcsz);

      CLASS_DECL_ACME strsize utf8_to_unicode_count(const char * pcsz, strsize count = -1);

      CLASS_DECL_ACME strsize utf8_to_unicode_count(const string & str);

      CLASS_DECL_ACME bool multibyte_to_utf8(::u32 uCodePageSrc, string & str, const char * pcsz);

      CLASS_DECL_ACME bool multibyte_to_utf8(::u32 uCodePageSrc, string & str, const char * pcsz, strsize nCount);

      CLASS_DECL_ACME wstring utf8_to_unicode(const char * pcsz, strsize iCount);

      CLASS_DECL_ACME bool utf8_to_unicode(widechar * pwsz, strsize iBuffer, const char * lpcsz, strsize iCount);

      CLASS_DECL_ACME bool utf8_to_unicode(widechar * pwsz, strsize iBuffer, const char * lpcsz);

      CLASS_DECL_ACME bool utf8_to_multibyte(::u32 uCodePage, string & str, const char * pcsz);

      CLASS_DECL_ACME bool utf8_to_multibyte(::u32 uCodePage, string & str, const char * pcsz, strsize nCount);

      CLASS_DECL_ACME bool utf8_to_multibyte(::u32 uCodePage, char * psz, strsize nCount, const char * lpcsz);


   } // namespace international


} // namespace str


inline wstring unicode(const char * psz) { return ::str::international::utf8_to_unicode(psz);  }
inline string utf8(const widechar * pwsz) { return ::str::international::unicode_to_utf8(pwsz); }


#define unitext(text) (::str::international::unicode_to_utf8(L##text))


