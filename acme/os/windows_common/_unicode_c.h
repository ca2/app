#pragma once





CLASS_DECL_ACME
i32
MultiByteToWideChar2(
::u32     CodePage,
::u32    dwFlags,
const char *   pMultiByteStr,

i32      cbMultiByte,
widechar *  pWideCharStr,

i32      cchWideChar);

CLASS_DECL_ACME
i32
WideCharToMultiByte2(
::u32     CodePage,
::u32    dwFlags,
const widechar *  pWideCharStr,

i32      cchWideChar,
char *   pMultiByteStr,

i32      cbMultiByte,
const char *   pDefaultChar,

int_bool *  pUsedDefaultChar);






