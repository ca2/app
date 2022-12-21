// Created by camilo on 2022-06-07 07:39 <3ThomasBorregaardSorense!! Mummi and bilbo!!
#include "framework.h"
#include "str.h"
#include "string.h"


bool str::to(i64 & i, const ::string & str)
{

   const ::ansi_character * pszEnd = nullptr;

   i64 iConversion = ::ansi_to_i64(str, &pszEnd);

   if (pszEnd == str.c_str())
   {

      return false;

   }

   i = iConversion;

   return true;

}


bool str::to(i32 & i, const ::string & str)
{

   const ::ansi_character * pszEnd = nullptr;

   i = ::ansi_to_i32(str, &pszEnd, 10);

   if (pszEnd == str.c_str())
   {

      return false;

   }

   return true;

}


bool str::to(i64 & i, int iBase, const ::string & str)
{

   if (iBase < 0 || iBase == 1 || iBase > 36)
   {

      return false;

   }

   char * pszEnd;

#ifdef WINDOWS

   i64 iConversion = ::_strtoi64(str, &pszEnd, iBase);

#else

   i64 iConversion = ::ansi_to_i64(str, (const char **) & pszEnd, iBase);

#endif

   if (pszEnd == str.c_str())
   {

      return false;

   }

   i = iConversion;

   return true;

}

bool str::to(i32 & i, i32 iBase, const ::string & str)
{

   if (iBase < 0 || iBase == 1 || iBase > 36)
      return false;

   char * pszEnd;

#ifdef WINDOWS

   i64 iConversion = ::_strtoi64(str, &pszEnd, iBase);

#else

   i64 iConversion = ::ansi_to_i64(str, (const char **) & pszEnd, iBase);

#endif

   if (pszEnd == str.c_str())
   {

      return false;

   }

   if (iConversion > numeric_info< i32 >::maximum())
   {

      return false;

   }

   i = (i32)iConversion;

   return true;

}

bool str::to(u64 & u, const ::string & str)
{

   const ::ansi_character * pszEnd = nullptr;

   u64 uiConversion = ::ansi_to_i64(str, &pszEnd);

   if (pszEnd == str.c_str())
   {

      return false;

   }

   u = uiConversion;

   return true;

}

bool str::to(u32 & u, const ::string & str)
{

   const ::ansi_character * pszEnd = nullptr;

   i64 uiConversion = ::ansi_to_u32(str, &pszEnd);

   if (pszEnd == str.c_str())
   {

      return false;

   }

   if (uiConversion > numeric_info < u32 > ::maximum())
   {

      return false;

   }

   u = (u32)uiConversion;

   return true;

}


bool str::to(u64 & u, i32 iBase, const ::string & str)
{

   if (iBase < 0 || iBase == 1 || iBase > 36)
   {

      return false;

   }

   const ::ansi_character * pszEnd = nullptr;

   u64 uiConversion = ::ansi_to_u64(str, &pszEnd, iBase);

   if (pszEnd == str.c_str())
   {

      return false;

   }

   u = uiConversion;

   return true;

}


bool str::to(u32 & u, i32 iBase, const ::string & str)
{

   if (iBase < 0 || iBase == 1 || iBase > 36)
   {

      return false;

   }

   const ::ansi_character * pszEnd = nullptr;

   u32 uiConversion = ::ansi_to_u32(str, &pszEnd, iBase);

   if (pszEnd == str.c_str())
   {

      return false;

   }

   if (uiConversion > numeric_info< u32 >::maximum())
   {

      return false;

   }

   u = uiConversion;

   return true;

}

iptr str::to_iptr(const ::string & str)
{

#if defined(_LP64) || defined(_AMD64_)

   return to_i64(str);

#else
   return to_i32(str);

#endif

}




