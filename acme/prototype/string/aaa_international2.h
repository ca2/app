#pragma once

//////#include "acme/exception/exception.h"

//
//namespace str
//{
//
//
//   namespace international
//   {
//

//      void CLASS_DECL_ACME unicode_to_utf8(string_array & stra, string_array & stra);
  //    void CLASS_DECL_ACME utf8_to_unicode(string_array & stra, string_array & stra);


      bool CLASS_DECL_ACME unicode_to_multibyte(unsigned int uCodePage, memory & str, const ::scoped_wstring & scopedwstr);


      bool CLASS_DECL_ACME multibyte_to_multibyte(unsigned int uCodePageDest, memory & str, unsigned int uCodePageSrc, const ::scoped_string & scopedstr);

      //bool CLASS_DECL_ACME multibyte_to_multibyte(unsigned int uCodePageDest, memory & str, unsigned int uCodePageSrc, const ::scoped_string & scopedstr, character_count nCount);


      bool CLASS_DECL_ACME multibyte_to_utf8(unsigned int uCodePageSrc, memory & str, const ::scoped_string & scopedstr);

      //bool CLASS_DECL_ACME multibyte_to_utf8(unsigned int uCodePageSrc, memory & str, const ::scoped_string & scopedstr, character_count nCount);


//      bool CLASS_DECL_ACME OEMToMultiByte(unsigned int uCodePage, memory & str, const ::scoped_string & scopedstr);

//      bool CLASS_DECL_ACME OEMToMultiByte(unsigned int uCodePage, memory & str, const ::scoped_string & scopedstr, character_count nCount);

      string CLASS_DECL_ACME utf8_to_multibyte(unsigned int uCodePage,  const ::scoped_string & scopedstr);
      bool CLASS_DECL_ACME utf8_to_multibyte(unsigned int uCodePage, ::string & str, const ::scoped_string & scopedstr);

      //bool CLASS_DECL_ACME utf8_to_multibyte(unsigned int uCodePage, memory & str, const ::scoped_string & scopedstr, character_count nCount);


//      bool CLASS_DECL_ACME OemToUtf8(memory & str, const ::scoped_string & scopedstr);

//      bool CLASS_DECL_ACME OemToUtf8(memory & str, const ::scoped_string & scopedstr, character_count nCount);


/*      inline void unicode_to_utf8(string_array & stra, string_array & stra)
      {
         string str;
         for(character_count i = 0; i < stra.get_size(); i++)
         {
            unicode_to_utf8(str, stra[i]);
            stra.add(str);
         }
      }

      inline void utf8_to_unicode(string_array & stra, string_array & stra)
      {
         string str;
         for(character_count i = 0; i < stra.get_size(); i++)
         {
            utf8_to_unicode(str, stra[i]);
            stra.add(str);
         }
      }*/


CLASS_DECL_ACME bool multibyte_to_utf8(unsigned int uCodePageSrc, memory & str, const ::scoped_string & scopedstr);


//CLASS_DECL_ACME bool multibyte_to_utf8(unsigned int uCodePageSrc, memory & str, const ::scoped_string & scopedstr, character_count nCount);
//      {
//
//#ifdef WINDOWS
//
//         return multibyte_to_multibyte(CP_UTF8, str, uCodePageSrc, pcsz, nCount);
//
//#else
//
//         throw ::exception(todo, "multibyte");
//
//#endif
//
//      }


      //inline bool OemToUtf8(memory & str, const ::scoped_string & scopedstr)

      //{
      //   return multibyte_to_multibyte(CP_UTF8, str, CP_OEMCP, pcsz);

      //}

      //inline bool OemToUtf8(memory & str, const ::scoped_string & scopedstr, character_count nCount)

      //{
      //   return multibyte_to_multibyte(CP_UTF8, str, CP_OEMCP, pcsz, nCount);

      //}

CLASS_DECL_ACME bool utf8_to_multibyte(unsigned int uCodePage, memory & str, const ::scoped_string & scopedstr);
//
//      {
//         return multibyte_to_multibyte(CodePageUtf8, str, uCodePage, pcsz);
//
//      }

      //CLASS_DECL_ACME bool utf8_to_multibyte(unsigned int uCodePage, memory & str, const ::scoped_string & scopedstr, character_count nCount);
//
//      {
//         return multibyte_to_multibyte(CodePageUtf8, str, uCodePage, pcsz, nCount);
//
//      }

//
//   } // namespace international
//
//
//} // namespace str
//


