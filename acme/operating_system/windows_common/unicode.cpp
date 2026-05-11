#include "framework.h"
#include "acme/_operating_system.h"


CLASS_DECL_ACME int MultiByteToWideChar2(
   ::u32 CodePage, ::u32 uFlags, const_char_pointer pMultiByteStr,
   int cbMultiByte, LPWSTR  pWideCharStr, int cchWideChar)
{

   return MultiByteToWideChar(CodePage, uFlags, pMultiByteStr, cbMultiByte, pWideCharStr, cchWideChar);


}


CLASS_DECL_ACME int WideCharToMultiByte2(
   ::u32 CodePage, ::u32 uFlags, const ::wide_character *  pWideCharStr,
   int cchWideChar, char * pMultiByteStr, int cbMultiByte,
   const_char_pointer pDefaultChar, ::i32_bool * pUsedDefaultChar)
{

   return WideCharToMultiByte(CodePage, uFlags, pWideCharStr, cchWideChar, pMultiByteStr, cbMultiByte, pDefaultChar, pUsedDefaultChar);

}



