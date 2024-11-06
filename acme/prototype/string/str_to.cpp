// Created by camilo on 2022-06-07 07:39 <3ThomasBorregaardSorense!! Mummi and bilbo!!
#include "framework.h"
#include "str.h"
#include "string.h"


bool str::to(huge_integer & i, const ::string & str)
{

   const ::ansi_character * pszEnd = nullptr;

   huge_integer iConversion = ::ansi_to_huge_integer(str, &pszEnd);

   if (pszEnd == str.c_str())
   {

      return false;

   }

   i = iConversion;

   return true;

}


bool str::to(int & i, const ::string & str)
{

   const ::ansi_character * pszEnd = nullptr;

   i = ::ansi_to_int(str, &pszEnd, 10);

   if (pszEnd == str.c_str())
   {

      return false;

   }

   return true;

}


bool str::to(huge_integer & i, int iBase, const ::string & str)
{

   if (iBase < 0 || iBase == 1 || iBase > 36)
   {

      return false;

   }

   char * pszEnd;

#ifdef WINDOWS

   huge_integer iConversion = ::_strtoi64(str, &pszEnd, iBase);

#else

   huge_integer iConversion = ::ansi_to_huge_integer(str, (const char **) & pszEnd, iBase);

#endif

   if (pszEnd == str.c_str())
   {

      return false;

   }

   i = iConversion;

   return true;

}

bool str::to(int & i, int iBase, const ::string & str)
{

   if (iBase < 0 || iBase == 1 || iBase > 36)
      return false;

   char * pszEnd;

#ifdef WINDOWS

   huge_integer iConversion = ::_strtoi64(str, &pszEnd, iBase);

#else

   huge_integer iConversion = ::ansi_to_huge_integer(str, (const char **) & pszEnd, iBase);

#endif

   if (pszEnd == str.c_str())
   {

      return false;

   }

   if (iConversion > numeric_info< int >::maximum())
   {

      return false;

   }

   i = (int)iConversion;

   return true;

}

bool str::to(huge_natural & u, const ::string & str)
{

   const ::ansi_character * pszEnd = nullptr;

   huge_natural uiConversion = ::ansi_to_huge_integer(str, &pszEnd);

   if (pszEnd == str.c_str())
   {

      return false;

   }

   u = uiConversion;

   return true;

}

bool str::to(unsigned int & u, const ::string & str)
{

   const ::ansi_character * pszEnd = nullptr;

   huge_integer uiConversion = ::ansi_to_unsigned_int(str, &pszEnd);

   if (pszEnd == str.c_str())
   {

      return false;

   }

   if (uiConversion > numeric_info < unsigned int > ::maximum())
   {

      return false;

   }

   u = (unsigned int)uiConversion;

   return true;

}


bool str::to(huge_natural & u, int iBase, const ::string & str)
{

   if (iBase < 0 || iBase == 1 || iBase > 36)
   {

      return false;

   }

   const ::ansi_character * pszEnd = nullptr;

   huge_natural uiConversion = ::ansi_to_huge_natural(str, &pszEnd, iBase);

   if (pszEnd == str.c_str())
   {

      return false;

   }

   u = uiConversion;

   return true;

}


bool str::to(unsigned int & u, int iBase, const ::string & str)
{

   if (iBase < 0 || iBase == 1 || iBase > 36)
   {

      return false;

   }

   const ::ansi_character * pszEnd = nullptr;

   unsigned int uiConversion = ::ansi_to_unsigned_int(str, &pszEnd, iBase);

   if (pszEnd == str.c_str())
   {

      return false;

   }

   if (uiConversion > numeric_info< unsigned int >::maximum())
   {

      return false;

   }

   u = uiConversion;

   return true;

}

iptr str::to_iptr(const ::string & str)
{

#if defined(_LP64) || defined(_AMD64_)

   return to_huge_integer(str);

#else
   return to_int(str);

#endif

}




