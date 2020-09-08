#pragma once


class var;


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


      bool CLASS_DECL_APEX UnicodeToMultiByte(UINT uiCodePage, char * psz, strsize nCount, const widechar * pcsz);

      bool CLASS_DECL_APEX UnicodeToMultiByte(UINT uiCodePage, char * psz, strsize iBuffer, const widechar * lpcsz, strsize iCount);

      strsize   CLASS_DECL_APEX UnicodeToMultiByteCount(UINT uiCodePage, const widechar * pcsz);

      strsize   CLASS_DECL_APEX UnicodeToMultiByteCount(UINT uiCodePage, const widechar * pcsz, strsize iCount);

      bool CLASS_DECL_APEX UnicodeToMultiByte(UINT uiCodePage, string & str, const widechar * pcsz);

      bool CLASS_DECL_APEX UnicodeToMultiByte(UINT uiCodePage, string & str, const widechar * pcsz, strsize iCount);

      string CLASS_DECL_APEX UnicodeToMultiByte(UINT uiCodePage, const widechar * pcsz);

      bool CLASS_DECL_APEX MultiByteToUnicode(UINT uiCodePage, widechar * pwsz, strsize iBuffer, const char  * lpcsz, strsize iCount);

      bool CLASS_DECL_APEX MultiByteToUnicode(UINT uiCodePage, widechar * pwsz, strsize nCount, const char * lpcsz);

      CLASS_DECL_APEX wstring MultiByteToUnicode(UINT uiCodePage, const char * pcsz, strsize nCount);

      CLASS_DECL_APEX wstring MultiByteToUnicode(UINT uiCodePage, const string & str);
      strsize  CLASS_DECL_APEX MultiByteToUnicodeCount(UINT uiCodePage, const char * pcsz);

      strsize  CLASS_DECL_APEX MultiByteToUnicodeCount(UINT uiCodePage, const char * pcsz, strsize iCount);

      CLASS_DECL_APEX wstring MultiByteToUnicode(UINT uiCodePage, const char * pcsz);

      bool CLASS_DECL_APEX MultiByteToMultiByte(UINT uiCodePageDest, string & str, UINT uiCodePageSrc, const char * pcsz);

      bool CLASS_DECL_APEX MultiByteToMultiByte(UINT uiCodePageDest, string & str, UINT uiCodePageSrc, const char * pcsz, strsize nCount);

      bool CLASS_DECL_APEX MultiByteToMultiByte(UINT uiCodePageDest, char * psz, strsize nCount, UINT uiCodePageSrc, const char * lpcsz);

      string CLASS_DECL_APEX multibyte_to_utf8(UINT uiCodePageSrc, const char * pcsz);

      bool CLASS_DECL_APEX multibyte_to_utf8(UINT uiCodePageSrc, string & str, const char * pcsz);

      bool CLASS_DECL_APEX multibyte_to_utf8(UINT uiCodePageSrc, string & str, const char * pcsz, strsize nCount);

      strsize   CLASS_DECL_APEX Utf8ToMultiByteCount(UINT uiCodePage, const char * pcsz);

      bool CLASS_DECL_APEX utf8_to_multibyte(UINT uiCodePage, string & str, const char * pcsz);

      bool CLASS_DECL_APEX utf8_to_multibyte(UINT uiCodePage, string & str, const char * pcsz, strsize nCount);

      bool CLASS_DECL_APEX utf8_to_multibyte(UINT uiCodePageSrc, char * psz, strsize nCount, const char * lpcsz);

      bool CLASS_DECL_APEX unicode_to_utf8(string & str, const widechar * pcsz);

      bool CLASS_DECL_APEX unicode_to_utf8(string & str, const wchar_t * pcsz);

      CLASS_DECL_APEX wstring utf8_to_unicode(const string & str);
      CLASS_DECL_APEX wstring utf8_to_unicode(const char * pcsz, strsize iCount);

      bool CLASS_DECL_APEX unicode_to_utf8(string & str, const widechar * pcsz, strsize iCount);

      string CLASS_DECL_APEX unicode_to_utf8(const widechar * pcsz);
      string CLASS_DECL_APEX unicode_to_utf8(const wchar_t * pcsz);

      CLASS_DECL_APEX string UnicodeToMultiByte(UINT uiCodePage, const widechar * pcsz);

      CLASS_DECL_APEX bool unicode_to_utf8(string & str, const widechar * pcsz);

      CLASS_DECL_APEX strsize utf8_to_unicode_count(const char * pcsz, strsize count = -1);

      CLASS_DECL_APEX strsize utf8_to_unicode_count(const string & str);

      CLASS_DECL_APEX bool multibyte_to_utf8(UINT uiCodePageSrc, string & str, const char * pcsz);

      CLASS_DECL_APEX bool multibyte_to_utf8(UINT uiCodePageSrc, string & str, const char * pcsz, strsize nCount);

      CLASS_DECL_APEX wstring utf8_to_unicode(const char * pcsz, strsize iCount);

      CLASS_DECL_APEX bool utf8_to_unicode(widechar * pwsz, strsize iBuffer, const char * lpcsz, strsize iCount);

      CLASS_DECL_APEX bool utf8_to_unicode(widechar * pwsz, strsize iBuffer, const char * lpcsz);

      CLASS_DECL_APEX bool utf8_to_multibyte(UINT uiCodePage, string & str, const char * pcsz);

      CLASS_DECL_APEX bool utf8_to_multibyte(UINT uiCodePage, string & str, const char * pcsz, strsize nCount);

      CLASS_DECL_APEX bool utf8_to_multibyte(UINT uiCodePage, char * psz, strsize nCount, const char * lpcsz);


   } // namespace international


} // namespace str


inline wstring unicode(const char * psz) { return ::str::international::utf8_to_unicode(psz);  }
inline string utf8(const widechar * pwsz) { return ::str::international::unicode_to_utf8(pwsz); }


#define unitext(text) (::str::international::unicode_to_utf8(L##text))


