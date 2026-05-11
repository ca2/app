#pragma once


//namespace str
//{
//
//
//   namespace international
//   {
//


      //bool CLASS_DECL_ACME unicode_to_multibyte(::u32 uCodePage, char * psz, character_count nCount, const ::wide_character * pcsz);

      bool CLASS_DECL_ACME unicode_to_multibyte(::u32 uCodePage, char * psz, character_count iBuffer, const ::scoped_wstring & scopedwstr);

      character_count CLASS_DECL_ACME unicode_to_multibyte_count(::u32 uCodePage, const ::scoped_wstring & scopedwstr);

      //character_count   CLASS_DECL_ACME unicode_to_multibyte_count(::u32 uCodePage, const ::wide_character * pcsz, character_count iCount);

      //bool CLASS_DECL_ACME unicode_to_multibyte(::u32 uCodePage, string & str, const ::wide_character * pcsz);

      bool CLASS_DECL_ACME unicode_to_multibyte(::u32 uCodePage, string & str, const ::scoped_wstring & scopedwstr);

      string CLASS_DECL_ACME unicode_to_multibyte(::u32 uCodePage, const ::scoped_wstring & scopedwstr);

      bool CLASS_DECL_ACME multibyte_to_unicode(::u32 uCodePage, ::wide_character * pwsz, character_count iBuffer, const ::scoped_string & scopedstr);

      //bool CLASS_DECL_ACME multibyte_to_unicode(::u32 uCodePage, ::wide_character * pwsz, character_count nCount, const_char_pointer lpcsz);

      CLASS_DECL_ACME wstring multibyte_to_unicode(::u32 uCodePage, const ::scoped_string & scopedstr);

      //CLASS_DECL_ACME wstring multibyte_to_unicode(::u32 uCodePage, const ::scoped_string & scopedstr);

      character_count  CLASS_DECL_ACME multibyte_to_unicode_count(::u32 uCodePage, const ::scoped_string & scopedstr);

      //character_count  CLASS_DECL_ACME multibyte_to_unicode_count(::u32 uCodePage, const ::scoped_string & scopedstr, character_count iCount);

      CLASS_DECL_ACME wstring multibyte_to_unicode(::u32 uCodePage, const ::scoped_string & scopedstr);

      string CLASS_DECL_ACME multibyte_to_multibyte(::u32 uCodePageDest, ::u32 uCodePageSrc, const ::scoped_string & scopedstr);
      bool CLASS_DECL_ACME multibyte_to_multibyte(::u32 uCodePageDest, string & str, ::u32 uCodePageSrc, const ::scoped_string & scopedstr);

      //bool CLASS_DECL_ACME multibyte_to_multibyte(::u32 uCodePageDest, string & str, ::u32 uCodePageSrc, const ::scoped_string & scopedstr, character_count nCount);

      //bool CLASS_DECL_ACME multibyte_to_multibyte(::u32 uCodePageDest, char * psz, character_count nCount, ::u32 uCodePageSrc, const_char_pointer lpcsz);

      string CLASS_DECL_ACME multibyte_to_utf8(::u32 uCodePageSrc, const ::scoped_string & scopedstr);

      bool CLASS_DECL_ACME multibyte_to_utf8(::u32 uCodePageSrc, string & str, const ::scoped_string & scopedstr);

      //bool CLASS_DECL_ACME multibyte_to_utf8(::u32 uCodePageSrc, string & str, const ::scoped_string & scopedstr, character_count nCount);

      character_count   CLASS_DECL_ACME utf8_to_multibyte_count(::u32 uCodePage, const ::scoped_string & scopedstr);

      string CLASS_DECL_ACME utf8_to_multibyte(::u32 uCodePage, const ::scoped_string & scopedstr);

      bool CLASS_DECL_ACME utf8_to_multibyte(::u32 uCodePage, string & str, const ::scoped_string & scopedstr);

      //bool CLASS_DECL_ACME utf8_to_multibyte(::u32 uCodePage, string & str, const ::scoped_string & scopedstr, character_count nCount);

      //bool CLASS_DECL_ACME utf8_to_multibyte(::u32 uCodePageSrc, char * psz, character_count nCount, const_char_pointer lpcsz);

      //bool CLASS_DECL_ACME unicode_to_utf8(string & str, const ::wide_character * pcsz);

      //bool CLASS_DECL_ACME unicode_to_utf8(string & str, const wchar_t * pcsz);

      CLASS_DECL_ACME wstring utf8_to_unicode(const ::scoped_string & scopedstr);

      //CLASS_DECL_ACME wstring utf8_to_unicode(const ::scoped_string & scopedstr, character_count iCount);

      bool CLASS_DECL_ACME unicode_to_utf8(string & str, const ::scoped_wstring & scopedwstr);

      string CLASS_DECL_ACME unicode_to_utf8(const ::scoped_wstring & scopedwstr);

      //string CLASS_DECL_ACME unicode_to_utf8(const wchar_t * pcsz);

      CLASS_DECL_ACME string unicode_to_multibyte(::u32 uCodePage, const ::scoped_wstring & scopedwstr);

      CLASS_DECL_ACME bool unicode_to_utf8(string & str, const ::scoped_wstring & scopedwstr);

      CLASS_DECL_ACME character_count utf8_to_unicode_count(const ::scoped_string & scopedstr);

      //CLASS_DECL_ACME character_count utf8_to_unicode_count(const ::scoped_string & scopedstr);

      CLASS_DECL_ACME bool multibyte_to_utf8(::u32 uCodePageSrc, string & str, const ::scoped_string & scopedstr);

      //CLASS_DECL_ACME bool multibyte_to_utf8(::u32 uCodePageSrc, string & str, const ::scoped_string & scopedstr, character_count nCount);

      CLASS_DECL_ACME wstring utf8_to_unicode(const ::scoped_string & scopedstr);

      //CLASS_DECL_ACME bool utf8_to_unicode(::wide_character * pwsz, character_count iBuffer, const_char_pointer lpcsz, character_count iCount);

      CLASS_DECL_ACME bool utf8_to_unicode(::wide_character * pwsz, character_count iBuffer, const ::scoped_string & scopedstr);

      CLASS_DECL_ACME bool utf8_to_multibyte(::u32 uCodePage, string & str, const ::scoped_string & scopedstr);

      //CLASS_DECL_ACME bool utf8_to_multibyte(::u32 uCodePage, string & str, const ::scoped_string & scopedstr, character_count nCount);

      //CLASS_DECL_ACME bool utf8_to_multibyte(::u32 uCodePage, char * psz, character_count nCount, const_char_pointer lpcsz);


//   } // namespace international
//
//
//} // namespace str


//inline wstring unicode(const ::scoped_string & scopedstr) { return utf8_to_unicode(scopedstr);  }
//inline string utf8(const ::wide_character * pwsz) { return unicode_to_utf8(pwsz); }


#define unitext(text) (unicode_to_utf8(L##text))


