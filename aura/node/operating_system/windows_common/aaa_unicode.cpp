#include "framework.h"





CLASS_DECL_AURA
i32
MultiByteToWideChar2(
::u32     CodePage,
::u32    dwFlags,
const char *   pMultiByteStr,

i32      cbMultiByte,
LPWSTR  pWideCharStr,

i32      cchWideChar)
{

   return MultiByteToWideChar(CodePage, dwFlags, pMultiByteStr, cbMultiByte, pWideCharStr, cchWideChar);


}

CLASS_DECL_AURA
i32
WideCharToMultiByte2(
::u32     CodePage,
::u32    dwFlags,
const widechar *  pWideCharStr,

i32      cchWideChar,
char *   pMultiByteStr,

i32      cbMultiByte,
const char *   pDefaultChar,

int_bool *  pUsedDefaultChar)

{


   return WideCharToMultiByte(CodePage, dwFlags, pWideCharStr, cchWideChar, pMultiByteStr, cbMultiByte, pDefaultChar, pUsedDefaultChar);


}



