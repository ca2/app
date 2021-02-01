#include "framework.h"
#include "acme/operating_system.h"


namespace str
{


#ifdef WINDOWS


   BSTR AllocSysString(const wd16char * pchData, strsize nDataLength) noexcept
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
   bool ReAllocSysString(BSTR * pbstr, const wd16char * pchData, strsize nDataLength) noexcept
   {

      strsize nLen = utf_to_utf_length(pbstr, pchData, nDataLength);

      bool bSuccess = ::SysReAllocStringLen(pbstr, nullptr, (::u32)nLen) != 0;

      if (bSuccess)
      {

         utf_to_utf(*pbstr, pchData, nDataLength);

      }

      return bSuccess;

   }


#endif


   u32 format_message(u32 dwFlags, const void * pSource, u32 dwMessageID, u32 dwLanguageID, wd16char * pszBuffer, u32 nSize, va_list * pArguments) noexcept
   {

#ifdef WINDOWS

      return ::FormatMessageW(dwFlags, pSource, dwMessageID, dwLanguageID, pszBuffer, nSize, pArguments);

#else

      return 0;

#endif

   }


   //strsize  char_traits::SafeStringLen(const wd16char * psz) noexcept
   //{
   //   // returns length in bytes
   //   return (psz != nullptr) ? strsize(strlen(psz)) : 0;
   //}
   //
   //strsize  char_traits::SafeStringLen(const wd16char * psz) noexcept
   //{
   //   // returns length in wchar_ts
   //#ifdef WINDOWS
   //   return (psz != nullptr) ? strsize(wd16_len(psz)) : 0;
   //#else
   //   return (psz != nullptr) ? strsize(wd16__length(psz)) : 0;
   //#endif
   //}
   //
   //strsize  char_traits::GetCharLen(const wd16char* pch) noexcept
   //{
   //   (void)pch;
   //   // returns wd16char length
   //   return 1;
   //}
   //
   //strsize  char_traits::GetCharLen(const wd16char* pch) noexcept
   //{
   //   // returns wd16char length
   //   return  ::str::get_utf8_char(pch).get_length();
   //}


   u32 get_environment_variable(const wd16char * pszVar, wd16char * pszBuffer, u32 dwSize)
   {

#ifdef _UWP

      __throw(todo());

#elif defined(WINDOWS_DESKTOP)

      return ::GetEnvironmentVariableW(pszVar, pszBuffer, dwSize);

#else

      string strVar(pszVar);

      auto pszEnv = getenv(strVar);

      wd16string wstrEnv(pszEnv);

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

      return (u32)__wd16len(wd16_count_copy(pszBuffer, wstrEnv, dwSize));

#endif

   }



} // namespace str



