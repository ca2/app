//
// Created by camilo on 2022-10-22 22:21 <3ThomasBorregaardSørensen!!
//
#include "framework.h"
#include "international2.h"
////#include "acme/exception/exception.h"
#include "acme/primitive/primitive/memory.h"


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


//bool CLASS_DECL_ACME unicode_to_multibyte(::u32 uCodePage, memory & str, const ::wide_character * scopedstr);
//
//
//bool CLASS_DECL_ACME multibyte_to_multibyte(::u32 uCodePageDest, memory & str, ::u32 uCodePageSrc, const ::scoped_string & scopedstr);
//
//bool CLASS_DECL_ACME multibyte_to_multibyte(::u32 uCodePageDest, memory & str, ::u32 uCodePageSrc, const ::scoped_string & scopedstr, strsize nCount);
//
//
//bool CLASS_DECL_ACME multibyte_to_utf8(::u32 uCodePageSrc, memory & str, const ::scoped_string & scopedstr);
//
//bool CLASS_DECL_ACME multibyte_to_utf8(::u32 uCodePageSrc, memory & str, const ::scoped_string & scopedstr, strsize nCount);
//

//      bool CLASS_DECL_ACME OEMToMultiByte(::u32 uCodePage, memory & str, const ::scoped_string & scopedstr);

//      bool CLASS_DECL_ACME OEMToMultiByte(::u32 uCodePage, memory & str, const ::scoped_string & scopedstr, strsize nCount);


//bool CLASS_DECL_ACME utf8_to_multibyte(::u32 uCodePage, memory & str, const ::scoped_string & scopedstr);
//
//bool CLASS_DECL_ACME utf8_to_multibyte(::u32 uCodePage, memory & str, const ::scoped_string & scopedstr, strsize nCount);
//

//      bool CLASS_DECL_ACME OemToUtf8(memory & str, const ::scoped_string & scopedstr);

//      bool CLASS_DECL_ACME OemToUtf8(memory & str, const ::scoped_string & scopedstr, strsize nCount);


/*      void unicode_to_utf8(string_array & stra, string_array & stra)
      {
         string str;
         for(strsize i = 0; i < stra.get_size(); i++)
         {
            unicode_to_utf8(str, stra[i]);
            stra.add(str);
         }
      }

      void utf8_to_unicode(string_array & stra, string_array & stra)
      {
         string str;
         for(strsize i = 0; i < stra.get_size(); i++)
         {
            utf8_to_unicode(str, stra[i]);
            stra.add(str);
         }
      }*/


bool multibyte_to_utf8(::u32 uCodePageSrc, memory & str, const ::scoped_string & scopedstr)
{

#ifdef WINDOWS

return multibyte_to_multibyte(CP_UTF8, str, uCodePageSrc, scopedstr);

#else

throw ::exception(todo, "multibyte");

#endif

}

//
//bool multibyte_to_utf8(::u32 uCodePageSrc, memory & str, const ::scoped_string & scopedstr)
//{
//
//#ifdef WINDOWS
//
//return multibyte_to_multibyte(CP_UTF8, str, uCodePageSrc, scopedstr);
//
//#else
//
//throw ::exception(todo, "multibyte");
//
//#endif
//
//}


//bool OemToUtf8(memory & str, const ::scoped_string & scopedstr)

//{
//   return multibyte_to_multibyte(CP_UTF8, str, CP_OEMCP, scopedstr);

//}

//bool OemToUtf8(memory & str, const ::scoped_string & scopedstr, strsize nCount)

//{
//   return multibyte_to_multibyte(CP_UTF8, str, CP_OEMCP, scopedstr, nCount);

//}


string CLASS_DECL_ACME utf8_to_multibyte(::u32 uCodePage, const ::scoped_string & scopedstr)
{

   string str;

   if (!utf8_to_multibyte(uCodePage, str, scopedstr))
   {

      throw ::exception(error_encoding);

   }

   return str;

}


bool utf8_to_multibyte(::u32 uCodePage, ::string & str, const ::scoped_string & scopedstr)
{

   return multibyte_to_multibyte(CodePageUtf8, str, uCodePage, scopedstr);

}

//bool utf8_to_multibyte(::u32 uCodePage, memory & str, const ::scoped_string & scopedstr, strsize nCount)
//
//{
//return multibyte_to_multibyte(CodePageUtf8, str, uCodePage, scopedstr, nCount);
//
//}

//
//   } // namespace international
//
//
//} // namespace str
//


