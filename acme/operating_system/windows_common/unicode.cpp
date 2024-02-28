#include "framework.h"
#include "acme/_operating_system.h"


CLASS_DECL_ACME i32 MultiByteToWideChar2(
   ::u32 CodePage, ::u32 uFlags, const char * pMultiByteStr,
   i32 cbMultiByte, LPWSTR  pWideCharStr, i32 cchWideChar)
{

   return MultiByteToWideChar(CodePage, uFlags, pMultiByteStr, cbMultiByte, pWideCharStr, cchWideChar);


}


CLASS_DECL_ACME i32 WideCharToMultiByte2(
   ::u32 CodePage, ::u32 uFlags, const ::wide_character *  pWideCharStr,
   i32 cchWideChar, char * pMultiByteStr, i32 cbMultiByte,
   const char * pDefaultChar, int_bool * pUsedDefaultChar)
{

   return WideCharToMultiByte(CodePage, uFlags, pWideCharStr, cchWideChar, pMultiByteStr, cbMultiByte, pDefaultChar, pUsedDefaultChar);

}



