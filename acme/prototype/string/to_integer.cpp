#include "framework.h"
//#include "string.h"


template < typename CHAR_TYPE >
::i32 chars_to_int(const CHAR_TYPE * psz, const CHAR_TYPE ** pszEnd, ::i32 iBase)
{

   ::i32 iResult = 0;

   ::i32 iDigit;

   bool bSign = false;

   if (psz != nullptr)
   {

      if(iBase > 1)
      {

         bSign = *psz == '-';

         if(bSign)
         {

            psz++;

         }

         while (true)
         {

            CHAR_TYPE ch = character_tolower(*psz);

            if (ch == '\0')
            {

               break;

            }
            else if(character_isdigit(ch) && (iDigit = ch - '0') < iBase)
            {

               iResult = iResult * iBase + iDigit;

            }
            else if(character_isalpha(ch) && (iDigit = ch - 'a') < iBase)
            {

               iResult = iResult * iBase + iDigit;

            }
            else
            {

               break;

            }

            psz++;

         }

      }

      if (pszEnd != nullptr)
      {

         *pszEnd = psz;

      }

   }

   return bSign ? -iResult : iResult;

}


template < typename CHAR_TYPE >
::u32 chars_to_u32(const CHAR_TYPE *psz, const CHAR_TYPE ** pszEnd, ::i32 iBase)
{

   ::u32 iResult = 0;

   ::i32 iDigit;

   if (psz != nullptr)
   {

      if(iBase > 1)
      {

         while (true)
         {

            ::wd32_character ch = wd32_char_tolower(*psz);

            if (ch == '\0')
            {

               break;

            }
            else if(wd32_char_isdigit(ch) && (iDigit = ch - '0') < iBase)
            {

               iResult = iResult * iBase + iDigit;

            }
            else if(wd32_char_isalpha(ch) && (iDigit = ch - 'a') < iBase)
            {

               iResult = iResult * iBase + iDigit;

            }
            else
            {

               break;

            }

            psz++;

         }

      }

     if (pszEnd != nullptr)
     {

        *pszEnd = psz;

     }

  }

  return iResult;

}


template < typename CHAR_TYPE >
::i64 chars_to_i64(const CHAR_TYPE *psz, const CHAR_TYPE ** pszEnd, ::i32 iBase)
{

   ::i64 iResult = 0;

   ::i32 iDigit;

   bool bSign = false;

   if (psz != nullptr)
   {

      if(iBase > 1)
      {

         bSign = *psz == '-';

         if(bSign)
         {

            psz++;

         }

         while (true)
         {

            ::wd32_character ch = wd32_char_tolower(*psz);

            if (ch == '\0')
            {

               break;

            }
            else if(wd32_char_isdigit(ch) && (iDigit = ch - '0') < iBase)
            {

               iResult = iResult * iBase + iDigit;

            }
            else if(wd32_char_isalpha(ch) && (iDigit = ch - 'a') < iBase)
            {

               iResult = iResult * iBase + iDigit;

            }
            else
            {

               break;

            }

            psz++;

         }

      }

      if (pszEnd != nullptr)
      {

         *pszEnd = psz;

      }

   }

   return bSign ? -iResult : iResult;

}


template < typename CHAR_TYPE >
::u64 chars_to_u64(const CHAR_TYPE *psz, const CHAR_TYPE ** pszEnd, ::i32 iBase)
{

   ::u64 iResult = 0;

   ::i32 iDigit;

   if (psz != nullptr)
   {

      if(iBase > 1)
      {

         while (true)
         {

            auto ch = wd32_char_tolower(*psz);

            if (ch == '\0')
            {

               break;

            }
            else if(wd32_char_isdigit(ch) && (iDigit = ch - '0') < iBase)
            {

               iResult = iResult * iBase + iDigit;

            }
            else if(wd32_char_isalpha(ch) && (iDigit = ch - 'a') < iBase)
            {

               iResult = iResult * iBase + iDigit;

            }
            else
            {

               break;

            }

            psz++;

         }

      }

     if (pszEnd != nullptr)
     {

        *pszEnd = psz;

     }

  }

  return iResult;

}



::i32 __ansitoi32(const_char_pointer psz, ::ansi_character ** pszEnd, ::i32 iBase) { return chars_to_int < ::ansi_character >(psz, (const_char_pointer *)pszEnd, iBase); }
::u32 __ansitou32(const_char_pointer psz, ::ansi_character ** pszEnd, ::i32 iBase) { return chars_to_u32 < ::ansi_character >(psz, (const_char_pointer *)pszEnd, iBase); }
::i64 __ansitoi64(const_char_pointer psz, ::ansi_character ** pszEnd, ::i32 iBase) { return chars_to_i64 < ::ansi_character >(psz, (const_char_pointer *)pszEnd, iBase); }
::u64 __ansitou64(const_char_pointer psz, ::ansi_character ** pszEnd, ::i32 iBase) { return chars_to_u64 < ::ansi_character >(psz, (const_char_pointer *)pszEnd, iBase); }


::i32 __wd16toi32(const ::wd16_character *psz, ::wd16_character ** pszEnd, ::i32 iBase) { return chars_to_int < ::wd16_character >(psz, (const ::wd16_character **)pszEnd, iBase); }
::u32 __wd16tou32(const ::wd16_character *psz, ::wd16_character ** pszEnd, ::i32 iBase) { return chars_to_u32 < ::wd16_character >(psz, (const ::wd16_character **)pszEnd, iBase); }
::i64 __wd16toi64(const ::wd16_character *psz, ::wd16_character ** pszEnd, ::i32 iBase) { return chars_to_i64 < ::wd16_character >(psz, (const ::wd16_character **)pszEnd, iBase); }
::u64 __wd16tou64(const ::wd16_character *psz, ::wd16_character ** pszEnd, ::i32 iBase) { return chars_to_u64 < ::wd16_character >(psz, (const ::wd16_character **)pszEnd, iBase); }


::i32 __wd32toi32(const ::wd32_character *psz, ::wd32_character ** pszEnd, ::i32 iBase) { return chars_to_int < ::wd32_character >(psz, (const ::wd32_character **)pszEnd, iBase); }
::u32 __wd32tou32(const ::wd32_character *psz, ::wd32_character ** pszEnd, ::i32 iBase) { return chars_to_u32 < ::wd32_character >(psz, (const ::wd32_character **)pszEnd, iBase); }
::i64 __wd32toi64(const ::wd32_character *psz, ::wd32_character ** pszEnd, ::i32 iBase) { return chars_to_i64 < ::wd32_character >(psz, (const ::wd32_character **)pszEnd, iBase); }
::u64 __wd32tou64(const ::wd32_character *psz, ::wd32_character ** pszEnd, ::i32 iBase) { return chars_to_u64 < ::wd32_character >(psz, (const ::wd32_character **)pszEnd, iBase); }







