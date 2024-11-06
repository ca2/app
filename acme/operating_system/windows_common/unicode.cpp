#include "framework.h"
#include "acme/_operating_system.h"


CLASS_DECL_ACME int MultiByteToWideChar2(
   unsigned int CodePage, unsigned int uFlags, const char * pMultiByteStr,
   int cbMultiByte, LPWSTR  pWideCharStr, int cchWideChar)
{

   return MultiByteToWideChar(CodePage, uFlags, pMultiByteStr, cbMultiByte, pWideCharStr, cchWideChar);


}


CLASS_DECL_ACME int WideCharToMultiByte2(
   unsigned int CodePage, unsigned int uFlags, const ::wide_character *  pWideCharStr,
   int cchWideChar, char * pMultiByteStr, int cbMultiByte,
   const char * pDefaultChar, int_bool * pUsedDefaultChar)
{

   return WideCharToMultiByte(CodePage, uFlags, pWideCharStr, cchWideChar, pMultiByteStr, cbMultiByte, pDefaultChar, pUsedDefaultChar);

}



