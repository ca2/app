#include "framework.h"
//#include "string.h"


template < typename CHAR_TYPE >
int chars_to_int(const CHAR_TYPE * psz, const CHAR_TYPE ** pszEnd, int iBase)
{

   int iResult = 0;

   int iDigit;

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
unsigned int chars_to_unsigned_int(const CHAR_TYPE *psz, const CHAR_TYPE ** pszEnd, int iBase)
{

   unsigned int iResult = 0;

   int iDigit;

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
long long chars_to_long_long(const CHAR_TYPE *psz, const CHAR_TYPE ** pszEnd, int iBase)
{

   long long iResult = 0;

   int iDigit;

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
unsigned long long chars_to_unsigned_long_long(const CHAR_TYPE *psz, const CHAR_TYPE ** pszEnd, int iBase)
{

   unsigned long long iResult = 0;

   int iDigit;

   if (psz != nullptr)
   {

      if(iBase > 1)
      {

         while (true)
         {

            CHAR_TYPE ch = wd32_char_tolower(*psz);

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



int __ansitoi32(const ::ansi_character *psz, ::ansi_character ** pszEnd, int iBase) { return chars_to_int < ::ansi_character >(psz, (const ::ansi_character **)pszEnd, iBase); }
unsigned int __ansitou32(const ::ansi_character *psz, ::ansi_character ** pszEnd, int iBase) { return chars_to_unsigned_int < ::ansi_character >(psz, (const ::ansi_character **)pszEnd, iBase); }
long long __ansitoi64(const ::ansi_character *psz, ::ansi_character ** pszEnd, int iBase) { return chars_to_long_long < ::ansi_character >(psz, (const ::ansi_character **)pszEnd, iBase); }
unsigned long long __ansitou64(const ::ansi_character *psz, ::ansi_character ** pszEnd, int iBase) { return chars_to_unsigned_long_long < ::ansi_character >(psz, (const ::ansi_character **)pszEnd, iBase); }


int __wd16toi32(const ::wd16_character *psz, ::wd16_character ** pszEnd, int iBase) { return chars_to_int < ::wd16_character >(psz, (const ::wd16_character **)pszEnd, iBase); }
unsigned int __wd16tou32(const ::wd16_character *psz, ::wd16_character ** pszEnd, int iBase) { return chars_to_unsigned_int < ::wd16_character >(psz, (const ::wd16_character **)pszEnd, iBase); }
long long __wd16toi64(const ::wd16_character *psz, ::wd16_character ** pszEnd, int iBase) { return chars_to_long_long < ::wd16_character >(psz, (const ::wd16_character **)pszEnd, iBase); }
unsigned long long __wd16tou64(const ::wd16_character *psz, ::wd16_character ** pszEnd, int iBase) { return chars_to_unsigned_long_long < ::wd16_character >(psz, (const ::wd16_character **)pszEnd, iBase); }


int __wd32toi32(const ::wd32_character *psz, ::wd32_character ** pszEnd, int iBase) { return chars_to_int < ::wd32_character >(psz, (const ::wd32_character **)pszEnd, iBase); }
unsigned int __wd32tou32(const ::wd32_character *psz, ::wd32_character ** pszEnd, int iBase) { return chars_to_unsigned_int < ::wd32_character >(psz, (const ::wd32_character **)pszEnd, iBase); }
long long __wd32toi64(const ::wd32_character *psz, ::wd32_character ** pszEnd, int iBase) { return chars_to_long_long < ::wd32_character >(psz, (const ::wd32_character **)pszEnd, iBase); }
unsigned long long __wd32tou64(const ::wd32_character *psz, ::wd32_character ** pszEnd, int iBase) { return chars_to_unsigned_long_long < ::wd32_character >(psz, (const ::wd32_character **)pszEnd, iBase); }







