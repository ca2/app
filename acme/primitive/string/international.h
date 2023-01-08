#pragma once


//namespace str
//{
//
//
//   namespace international
//   {
//


      //bool CLASS_DECL_ACME unicode_to_multibyte(::u32 uCodePage, char * psz, strsize nCount, const ::wide_character * pcsz);

      bool CLASS_DECL_ACME unicode_to_multibyte(::u32 uCodePage, char * psz, strsize iBuffer, const ::scoped_wstring & scopedwstr);

      strsize CLASS_DECL_ACME unicode_to_multibyte_count(::u32 uCodePage, const ::scoped_wstring & scopedwstr);

      //strsize   CLASS_DECL_ACME unicode_to_multibyte_count(::u32 uCodePage, const ::wide_character * pcsz, strsize iCount);

      //bool CLASS_DECL_ACME unicode_to_multibyte(::u32 uCodePage, string & str, const ::wide_character * pcsz);

      bool CLASS_DECL_ACME unicode_to_multibyte(::u32 uCodePage, string & str, const ::scoped_wstring & scopedwstr);

      string CLASS_DECL_ACME unicode_to_multibyte(::u32 uCodePage, const ::scoped_wstring & scopedwstr);

      bool CLASS_DECL_ACME multibyte_to_unicode(::u32 uCodePage, ::wide_character * pwsz, strsize iBuffer, const ::scoped_string & scopedstr);

      //bool CLASS_DECL_ACME multibyte_to_unicode(::u32 uCodePage, ::wide_character * pwsz, strsize nCount, const char * lpcsz);

      CLASS_DECL_ACME wstring multibyte_to_unicode(::u32 uCodePage, const ::scoped_string & scopedstr);

      //CLASS_DECL_ACME wstring multibyte_to_unicode(::u32 uCodePage, const ::string & str);

      strsize  CLASS_DECL_ACME multibyte_to_unicode_count(::u32 uCodePage, const ::scoped_string & scopedstr);

      //strsize  CLASS_DECL_ACME multibyte_to_unicode_count(::u32 uCodePage, const ::scoped_string & scopedstr, strsize iCount);

      CLASS_DECL_ACME wstring multibyte_to_unicode(::u32 uCodePage, const ::scoped_string & scopedstr);

      bool CLASS_DECL_ACME multibyte_to_multibyte(::u32 uCodePageDest, string & str, ::u32 uCodePageSrc, const ::scoped_string & scopedstr);

      //bool CLASS_DECL_ACME multibyte_to_multibyte(::u32 uCodePageDest, string & str, ::u32 uCodePageSrc, const ::scoped_string & scopedstr, strsize nCount);

      //bool CLASS_DECL_ACME multibyte_to_multibyte(::u32 uCodePageDest, char * psz, strsize nCount, ::u32 uCodePageSrc, const char * lpcsz);

      string CLASS_DECL_ACME multibyte_to_utf8(::u32 uCodePageSrc, const ::scoped_string & scopedstr);

      bool CLASS_DECL_ACME multibyte_to_utf8(::u32 uCodePageSrc, string & str, const ::scoped_string & scopedstr);

      //bool CLASS_DECL_ACME multibyte_to_utf8(::u32 uCodePageSrc, string & str, const ::scoped_string & scopedstr, strsize nCount);

      strsize   CLASS_DECL_ACME utf8_to_multibyte_count(::u32 uCodePage, const ::scoped_string & scopedstr);

      bool CLASS_DECL_ACME utf8_to_multibyte(::u32 uCodePage, string & str, const ::scoped_string & scopedstr);

      //bool CLASS_DECL_ACME utf8_to_multibyte(::u32 uCodePage, string & str, const ::scoped_string & scopedstr, strsize nCount);

      //bool CLASS_DECL_ACME utf8_to_multibyte(::u32 uCodePageSrc, char * psz, strsize nCount, const char * lpcsz);

      //bool CLASS_DECL_ACME unicode_to_utf8(string & str, const ::wide_character * pcsz);

      //bool CLASS_DECL_ACME unicode_to_utf8(string & str, const wchar_t * pcsz);

      CLASS_DECL_ACME wstring utf8_to_unicode(const ::scoped_string & scopedstr);

      //CLASS_DECL_ACME wstring utf8_to_unicode(const ::scoped_string & scopedstr, strsize iCount);

      bool CLASS_DECL_ACME unicode_to_utf8(string & str, const ::scoped_wstring & scopedwstr);

      string CLASS_DECL_ACME unicode_to_utf8(const ::scoped_wstring & scopedwstr);

      //string CLASS_DECL_ACME unicode_to_utf8(const wchar_t * pcsz);

      CLASS_DECL_ACME string unicode_to_multibyte(::u32 uCodePage, const ::scoped_wstring & scopedwstr);

      CLASS_DECL_ACME bool unicode_to_utf8(string & str, const ::scoped_wstring & scopedwstr);

      CLASS_DECL_ACME strsize utf8_to_unicode_count(const ::scoped_string & scopedstr);

      //CLASS_DECL_ACME strsize utf8_to_unicode_count(const ::string & str);

      CLASS_DECL_ACME bool multibyte_to_utf8(::u32 uCodePageSrc, string & str, const ::scoped_string & scopedstr);

      //CLASS_DECL_ACME bool multibyte_to_utf8(::u32 uCodePageSrc, string & str, const ::scoped_string & scopedstr, strsize nCount);

      CLASS_DECL_ACME wstring utf8_to_unicode(const ::scoped_string & scopedstr);

      //CLASS_DECL_ACME bool utf8_to_unicode(::wide_character * pwsz, strsize iBuffer, const char * lpcsz, strsize iCount);

      CLASS_DECL_ACME bool utf8_to_unicode(::wide_character * pwsz, strsize iBuffer, const ::scoped_string & scopedstr);

      CLASS_DECL_ACME bool utf8_to_multibyte(::u32 uCodePage, string & str, const ::scoped_string & scopedstr);

      //CLASS_DECL_ACME bool utf8_to_multibyte(::u32 uCodePage, string & str, const ::scoped_string & scopedstr, strsize nCount);

      //CLASS_DECL_ACME bool utf8_to_multibyte(::u32 uCodePage, char * psz, strsize nCount, const char * lpcsz);


//   } // namespace international
//
//
//} // namespace str


//inline wstring unicode(const ::scoped_string & scopedstr) { return utf8_to_unicode(psz);  }
//inline string utf8(const ::wide_character * pwsz) { return unicode_to_utf8(pwsz); }


#define unitext(text) (unicode_to_utf8(L##text))


