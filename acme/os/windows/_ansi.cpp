#include "framework.h"
#include "acme/operating_system.h"


namespace str
{


   BSTR AllocSysString(const ansichar * pchData, strsize nDataLength) noexcept
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
   bool ReAllocSysString(BSTR * pbstr, const ansichar * pchData, strsize nDataLength) noexcept
   {

      strsize nLen = utf_to_utf_length(pbstr, pchData, nDataLength);

      bool bSuccess = ::SysReAllocStringLen(pbstr, nullptr, (::u32)nLen) != 0;

      if (bSuccess)
      {

         utf_to_utf(*pbstr, pchData, nDataLength);

      }

      return bSuccess;

   }


   u32 format_message(u32 dwFlags, const void * pSource, u32 dwMessageID, u32 dwLanguageID, ansichar * pszBuffer, u32 nSize, va_list * pArguments) noexcept
   {

       return ::FormatMessageA(dwFlags, pSource, dwMessageID, dwLanguageID, pszBuffer, nSize, pArguments);

   }

   
   ::u32 get_environment_variable(const ansichar * pszVar, ansichar * pszBuffer, ::u32 dwSize)
   {

#ifdef _UWP

         __throw(todo());

#elif defined(WINDOWS_DESKTOP)

         return ::GetEnvironmentVariableA(pszVar, pszBuffer, dwSize);

#else

         const ansichar * pszEnv = getenv(pszVar);

         if (pszBuffer == nullptr)
         {

            if (pszEnv == nullptr)
            {

               return 0;

            }
            else
            {

               return (u32)strlen(pszEnv);

            }

         }

         return (u32)strlen(ansi_count_copy(pszBuffer, pszEnv, dwSize));

#endif

   }


} // namespace str



