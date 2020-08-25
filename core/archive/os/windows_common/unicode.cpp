#include "framework.h"





CLASS_DECL_AURA
i32
MultiByteToWideChar2(
UINT     CodePage,
DWORD    dwFlags,
LPCSTR   pMultiByteStr,

i32      cbMultiByte,
LPWSTR  pWideCharStr,

i32      cchWideChar)
{

   return MultiByteToWideChar(CodePage, dwFlags, pMultiByteStr, cbMultiByte, pWideCharStr, cchWideChar);


}

CLASS_DECL_AURA
i32
WideCharToMultiByte2(
UINT     CodePage,
DWORD    dwFlags,
LPCWSTR  pWideCharStr,

i32      cchWideChar,
LPSTR   pMultiByteStr,

i32      cbMultiByte,
LPCSTR   pDefaultChar,

LPBOOL  pUsedDefaultChar)

{


   return WideCharToMultiByte(CodePage, dwFlags, pWideCharStr, cchWideChar, pMultiByteStr, cbMultiByte, pDefaultChar, pUsedDefaultChar);


}



