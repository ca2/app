#pragma once





CLASS_DECL_APEX
i32
MultiByteToWideChar2(
UINT     CodePage,
DWORD    dwFlags,
LPCSTR   pMultiByteStr,

i32      cbMultiByte,
widechar *  pWideCharStr,

i32      cchWideChar);

CLASS_DECL_APEX
i32
WideCharToMultiByte2(
UINT     CodePage,
DWORD    dwFlags,
const widechar *  pWideCharStr,

i32      cchWideChar,
LPSTR   pMultiByteStr,

i32      cbMultiByte,
LPCSTR   pDefaultChar,

LPBOOL  pUsedDefaultChar);






