#include "framework.h"
#include "acme/operating_system.h"


namespace str
{




BSTR AllocSysString(const wd32char * pchData, strsize nDataLength) noexcept
{

   BSTR bstr = nullptr;

   strsize nLen = utf_to_utf_length(bstr, pchData, nDataLength);

   bstr = ::SysAllocStringLen(nullptr, (::u32)nLen);

   if (bstr != nullptr)
   {

      utf_to_utf(bstr, pchData, nDataLength);

   }

   return bstr;

}


// pbstr is [in,out] BSTR string
bool ReAllocSysString(BSTR * pbstr, const wd32char * pchData, strsize nDataLength) noexcept
{

   strsize nLen = utf_to_utf_length(pbstr, pchData, nDataLength);

   bool bSuccess = ::SysReAllocStringLen(pbstr, nullptr, (::u32)nLen) != 0;

   if (bSuccess)
   {

      utf_to_utf(*pbstr, pchData, nDataLength);

   }

   return bSuccess;

}



u32 format_message(u32 dwFlags, const void * pSource, u32 dwMessageID, u32 dwLanguageID, wd32char * pszBuffer, u32 nSize, va_list * pArguments) noexcept
{

#ifdef WINDOWS

   throw_todo();

   return 0;

   //return ::FormatMessageW(dwFlags, pSource, dwMessageID, dwLanguageID, pszBuffer, nSize, pArguments);

#else

   return 0;

#endif

}


//strsize  char_traits::SafeStringLen(const wd32char * psz) noexcept
//{
//   // returns length in bytes
//   return (psz != nullptr) ? strsize(strlen(psz)) : 0;
//}
//
//strsize  char_traits::SafeStringLen(const wd32char * psz) noexcept
//{
//   // returns length in wchar_ts
//#ifdef WINDOWS
//   return (psz != nullptr) ? strsize(wd32_len(psz)) : 0;
//#else
//   return (psz != nullptr) ? strsize(wide_length(psz)) : 0;
//#endif
//}
//
//strsize  char_traits::GetCharLen(const wd32char* pch) noexcept
//{
//   (void)pch;
//   // returns wd32char length
//   return 1;
//}
//
//strsize  char_traits::GetCharLen(const wd32char* pch) noexcept
//{
//   // returns wd32char length
//   return  ::str::get_utf8_char(pch).get_length();
//}


u32 get_environment_variable(const wd32char * pszVar, wd32char * pszBuffer, u32 dwSize)
{

#ifdef _UWP

   __throw(todo);

#elif defined(WINDOWS_DESKTOP)

   wstring wstr;

   auto psz = wstr.get_string_buffer(dwSize);

   wstring wstrVar(pszVar);

   auto result = ::GetEnvironmentVariableW(wstrVar, psz, dwSize);

   utf_to_utf(pszBuffer, psz);

   return result;

#else

   string strVar(pszVar);

   auto pszEnv = getenv(strVar);

   wd32string wstrEnv(pszEnv);

   if (pszBuffer == nullptr)
   {

      if (pszEnv == nullptr)
      {

         return 0;

      }
      else
      {

         return (u32)wstrEnv.get_length();

      }

   }

   return (u32)__wd32len(wd32_count_copy(pszBuffer, wstrEnv, dwSize));

#endif

}


} // namespace str





void output_debug_string(const wd32char * psz)
{

   string str(psz);

   output_debug_string(str);

}

