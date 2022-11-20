//
// Created by camilo on 2022-10-22 22:21 <3ThomasBorregaardSorensen!!
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


//bool CLASS_DECL_ACME unicode_to_multibyte(::u32 uCodePage, memory & str, const widechar * pcsz);
//
//
//bool CLASS_DECL_ACME multibyte_to_multibyte(::u32 uCodePageDest, memory & str, ::u32 uCodePageSrc, const char * pcsz);
//
//bool CLASS_DECL_ACME multibyte_to_multibyte(::u32 uCodePageDest, memory & str, ::u32 uCodePageSrc, const char * pcsz, strsize nCount);
//
//
//bool CLASS_DECL_ACME multibyte_to_utf8(::u32 uCodePageSrc, memory & str, const char * pcsz);
//
//bool CLASS_DECL_ACME multibyte_to_utf8(::u32 uCodePageSrc, memory & str, const char * pcsz, strsize nCount);
//

//      bool CLASS_DECL_ACME OEMToMultiByte(::u32 uCodePage, memory & str, const char * pcsz);

//      bool CLASS_DECL_ACME OEMToMultiByte(::u32 uCodePage, memory & str, const char * pcsz, strsize nCount);


//bool CLASS_DECL_ACME utf8_to_multibyte(::u32 uCodePage, memory & str, const char * pcsz);
//
//bool CLASS_DECL_ACME utf8_to_multibyte(::u32 uCodePage, memory & str, const char * pcsz, strsize nCount);
//

//      bool CLASS_DECL_ACME OemToUtf8(memory & str, const char * pcsz);

//      bool CLASS_DECL_ACME OemToUtf8(memory & str, const char * pcsz, strsize nCount);


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


bool multibyte_to_utf8(::u32 uCodePageSrc, memory & str, const char * pcsz)
{

#ifdef WINDOWS

return multibyte_to_multibyte(CP_UTF8, str, uCodePageSrc, pcsz);

#else

throw ::exception(todo, "multibyte");

#endif

}


bool multibyte_to_utf8(::u32 uCodePageSrc, memory & str, const char * pcsz, strsize nCount)
{

#ifdef WINDOWS

return multibyte_to_multibyte(CP_UTF8, str, uCodePageSrc, pcsz, nCount);

#else

throw ::exception(todo, "multibyte");

#endif

}


//bool OemToUtf8(memory & str, const char * pcsz)

//{
//   return multibyte_to_multibyte(CP_UTF8, str, CP_OEMCP, pcsz);

//}

//bool OemToUtf8(memory & str, const char * pcsz, strsize nCount)

//{
//   return multibyte_to_multibyte(CP_UTF8, str, CP_OEMCP, pcsz, nCount);

//}

bool utf8_to_multibyte(::u32 uCodePage, memory & str, const char * pcsz)
{

   return multibyte_to_multibyte(CodePageUtf8, str, uCodePage, pcsz);

}

bool utf8_to_multibyte(::u32 uCodePage, memory & str, const char * pcsz, strsize nCount)

{
return multibyte_to_multibyte(CodePageUtf8, str, uCodePage, pcsz, nCount);

}

//
//   } // namespace international
//
//
//} // namespace str
//


