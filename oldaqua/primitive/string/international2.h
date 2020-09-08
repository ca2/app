#pragma once


namespace str
{


   namespace international
   {


//      void CLASS_DECL_AQUA unicode_to_utf8(string_array & stra, string_array & stra);
  //    void CLASS_DECL_AQUA utf8_to_unicode(string_array & stra, string_array & stra);


      bool CLASS_DECL_AQUA UnicodeToMultiByte(UINT uiCodePage, memory & str, const widechar * pcsz);


      bool CLASS_DECL_AQUA MultiByteToMultiByte(UINT uiCodePageDest, memory & str, UINT uiCodePageSrc, const char * pcsz);

      bool CLASS_DECL_AQUA MultiByteToMultiByte(UINT uiCodePageDest, memory & str, UINT uiCodePageSrc, const char * pcsz, strsize nCount);


      bool CLASS_DECL_AQUA multibyte_to_utf8(UINT uiCodePageSrc, memory & str, const char * pcsz);

      bool CLASS_DECL_AQUA multibyte_to_utf8(UINT uiCodePageSrc, memory & str, const char * pcsz, strsize nCount);


//      bool CLASS_DECL_AQUA OEMToMultiByte(UINT uiCodePage, memory & str, const char * pcsz);

//      bool CLASS_DECL_AQUA OEMToMultiByte(UINT uiCodePage, memory & str, const char * pcsz, strsize nCount);


      bool CLASS_DECL_AQUA utf8_to_multibyte(UINT uiCodePage, memory & str, const char * pcsz);

      bool CLASS_DECL_AQUA utf8_to_multibyte(UINT uiCodePage, memory & str, const char * pcsz, strsize nCount);


//      bool CLASS_DECL_AQUA OemToUtf8(memory & str, const char * pcsz);

//      bool CLASS_DECL_AQUA OemToUtf8(memory & str, const char * pcsz, strsize nCount);


/*      inline void unicode_to_utf8(string_array & stra, string_array & stra)
      {
         string str;
         for(strsize i = 0; i < stra.get_size(); i++)
         {
            unicode_to_utf8(str, stra[i]);
            stra.add(str);
         }
      }

      inline void utf8_to_unicode(string_array & stra, string_array & stra)
      {
         string str;
         for(strsize i = 0; i < stra.get_size(); i++)
         {
            utf8_to_unicode(str, stra[i]);
            stra.add(str);
         }
      }*/

      inline bool multibyte_to_utf8(UINT uiCodePageSrc, memory & str, const char * pcsz)

      {
         return MultiByteToMultiByte(CP_UTF8, str, uiCodePageSrc, pcsz);

      }

      inline bool multibyte_to_utf8(UINT uiCodePageSrc, memory & str, const char * pcsz, strsize nCount)

      {
         return MultiByteToMultiByte(CP_UTF8, str, uiCodePageSrc, pcsz, nCount);

      }

      //inline bool OemToUtf8(memory & str, const char * pcsz)

      //{
      //   return MultiByteToMultiByte(CP_UTF8, str, CP_OEMCP, pcsz);

      //}

      //inline bool OemToUtf8(memory & str, const char * pcsz, strsize nCount)

      //{
      //   return MultiByteToMultiByte(CP_UTF8, str, CP_OEMCP, pcsz, nCount);

      //}

      inline bool utf8_to_multibyte(UINT uiCodePage, memory & str, const char * pcsz)

      {
         return MultiByteToMultiByte(CodePageUtf8, str, uiCodePage, pcsz);

      }

      inline bool utf8_to_multibyte(UINT uiCodePage, memory & str, const char * pcsz, strsize nCount)

      {
         return MultiByteToMultiByte(CodePageUtf8, str, uiCodePage, pcsz, nCount);

      }


   } // namespace international


} // namespace str



